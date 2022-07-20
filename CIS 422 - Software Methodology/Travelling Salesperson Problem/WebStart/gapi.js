// Calls google api and retreives distance matrix for the specified src and dest lists.
// Google istance matrix function are asynchronous so when google api returns, handles result, 
//     calling below getDirections() function. 
// Async function require this type of call response handling and functino nesting.
// d_matrix as parameter represents empty distance matrix to fill.
// addList holds address coordinate values in string form.
function getDistanceMatrix(src, dest, mode, d_matrix, addList) {
    // Create a new google distance matrix function.
    const dm = new google.maps.DistanceMatrixService();
    // Src list, and dest list are in string format. Mode refers to "DRIVING", "TRANSIT", etc.
    const matOptions = {
        origins: src,
        destinations: dest,
        travelMode: mode,
        unitSystem: google.maps.UnitSystem.IMPERIAL
    };
    // Tell google distance matrix services to calculate distance matrix for given paremeters.
    dm.getDistanceMatrix(matOptions, handle);

    // Handler for the api call. Asychronous.
    function handle(response, status) {
        // Check that google response is OK, sending error message if not.
        if(status !== "OK") {
            console.log("Error with distance matrix calculation", response);
            return;
        }
        // Now retrieve the distance matrix data from the returned JSON object from the google api call.
        // Set json rows object returned by google api to data variable. Temporary variable leaves scope at end of function.
        var data = response.rows;
        // For each row in distance matrix JSON data, create new row array.
        for(var i=0 ; i<data.length ; ++i) {
            // Initialize new array for storing the distance matrix.
            var matrix_row = new Array();
            // Add each element distance value to the row array, and row array to distance matrix. See javascript console for format of data.
            for(var j=0 ; j<data[i].elements.length ; ++j) {
                // Check that the status for the distance matrix is OK, indicating distance calculation was successful.
                var matrix_status = data[i].elements[j].status;
                // Handle error message if distance matrix calculation was not successful.
                if (matrix_status !== "OK") {
                    // Complete google distance matrix failure.
                    if (matrix_status === "NOT_FOUND") {
                        alert("ERROR: Geocoding failed.");
                        return;
                    // No results from distance matrix calculation.
                    } else if (matrix_status === "ZERO_RESULTS") {
                        alert("ERROR: Route could not be completed.");
                        return;
                    // Error indicating that too many addresses were provided.
                    } else {
                        alert("ERROR: Max route length exceeded.");
                        return;
                    }
                }
                // Add distance calculation to the distance matrix row.
                matrix_row.push(data[i].elements[j].distance.value);
            }
            // Add row of distance values to the distance matrix.
            d_matrix.push(matrix_row); 
        }

        // Indicate that distance matrix calculation has ended and results are temporarily stored in d_matrix.
        console.log("Done with distance matrix calc"); 

        // Make ajax POST request to the server. Calls the optimize server function which in turn calls the TSP Algorithm functions.
        $.ajax({
           url: 'optimize',
           type: 'POST',
           dataType: 'json',
           contentType: 'application/json',
           data: JSON.stringify(d_matrix),
           success: function(data, status) {
               // On success request handler.
               // Indicate to console that request was a success.
               console.log('post succeeded');
               // Reorder src address list using ordered indices returned by TSP alg.
               // reorderList function can be seen below.
               var ord = reorderList(src, data);

               // Check that list of addresses is atleast 2 addresses.
               // Ord containes the starting address at the start and end so we check that ord has length atleast 3.
               if(ord.length > 2) {
                   // Directions renderer expects src, dest, and waypoints address variables as input.
                   // Split ordered list into three segments.
                   var sub_list = ord.slice(1,ord.length-1);
                   // Waypoints list holds intermediate adresses on path.
                   var waypoints = [];
                   // Fill waypoints list with each non starting address.
                   for(var i=0 ; i<sub_list.length ; ++i) {
                       waypoints.push({location: sub_list[i]});
                   }
                   // Call getDirections() function whcih draws paths and markers to the map.
                   getDirections(ord[0], ord[ord.length-1], waypoints);
               }
           }
       });
    }
}


// Function clears markers array.
// Used to clear temporary markers before drawing path to map.
function clearMarkers() {
    // Loop through markers array, found in index.js, setting each marker to null.
    for(var i=0 ; i<markers.length ; ++i) {
        markers[i].setMap(null);
    }
    markers = [];
}



// Return reordered list given list of indices.
// Order containes indices of address list in optimized order.
function reorderList(list, order) {
    // Initialize new Array fro storing ordered list.
    var ordered = new Array()
    // Loop through addresses, adding them to ordered in correct order.
    for (var i of order) {
        ordered.push(list[i]);
    }
    return ordered;
}

// Calls the directions services and directions renderer functions.
// start and end are addresses and stops is a list of addresses.
// start and end are string of form "lat,lng" while stops is a list of objects of form {location: "lat,lng"}
function getDirections(start, end, stops) {
    // Options for the directions services function.
    var options = {
        origin: start,
        destination: end,
        travelMode: "DRIVING",
        waypoints: stops
    };

    // Route the current addresses, handling rendering and marking drawing.
    // directionService is a object of the google api map intialized in initMap wihtin index.js.
    directionsService.route(options, function(result, status) {
        // Checl that api request has return successfully.
        if(status == "OK") {
            // From the route data stored in result, get the addresses and coordinates of each step.
            // addList and coordList are temporary variables used for storing api result data.
            var addList = [];
            var coordList = [];
            // result contains JSON object with each route, and each leg of each route.
            // Each leg represents directions between two addresses on the path.
            // Loop through each address to address directions values.
            for(var leg of result.routes[0].legs) {
                // Add coordinates and addresses to their respective lists.
                // Used for placing custom markers on the path rather than google maps default markers.
                addList.push(leg.start_address);
                coordList.push(leg.start_location.toJSON());
            }
            // Clear markers (function above operates on global marker array defined in index.js). And draws the route markers.
            clearMarkers();
            drawMarkers(coordList, addList);
            // Draw directions on map.
            directionsRenderer.setDirections(result);
        } else {
            // If directionService failed to route, indicate this to the console.
            console.log("Directions route failed!");
            console.log(route);
        }
    });
}

// Draw markers given a list of coordinates associated with a list of addresses.
function drawMarkers(coord_list, add_list) {
    //var labels = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (var i=0 ; i<coord_list.length ; ++i) {
        // Creates letter code needed to send to google icon url.  See drawMarker function below.
        var letter = String.fromCharCode("A".charCodeAt(0)+i);
        drawMarker(coord_list[i], add_list[i], add_list[i], letter);
    }
}

// drawMarker function creates google maps marker at specified location, with address, and optional icon.
// If default icon is required, leave icon parameter ass null.
function drawMarker(latLng, hover, contentstr, icon) {
    // Google InfoWindow object shows popup when activated.
    var infowindow = new google.maps.InfoWindow();
    // Set content of info window to address string.
    infowindow.setContent(contentstr);

    // If icon is provided, draw custom icon.
    if(icon) {
        // Scale size of the icon to better match default icons.
        icon_scaled = {url: "https://maps.google.com/mapfiles/marker"+icon+".png", scaledSize: new google.maps.Size(26,36)};
        // Create new map marker object with specified settings.
        var marker = new google.maps.Marker({
          position: latLng,
          map: map,
          title: hover,
          icon:icon_scaled,
        });
    // If no icon specified, make marker with default icon.
    } else {
        var marker = new google.maps.Marker({
          position: latLng,
          map: map,
          title: hover,
        });
    }
    // Add on click listener to marker, displaying info window with address inside.
    marker.addListener("click", function () {
      infowindow.open({
        anchor: marker,
        map: map,
        shouldFocus: false,
      });
    });
    // Add address string as variable to marker object. Used when removing a specific marker.
    marker.content = contentstr;
    // Add marker to the global marker array.
    markers.push(marker);
}

// Remove temporary marker from the map. When a address is added to the list but not yet included in the optimized path, this function will remove the
//    marker if it is removed from the list.
// Does not function for removing markers from the optimized path by design choice. The optimized path stays cisible until optimize is pressed again.
function removeMarker(add) {
    console.log("Trying to remove address: ", add);
    // Loop through markers of the marker array.
    console.log(markers.length);
    for(var i=0 ; i<markers.length ; ++i) {
        console.log("encountered: ", markers[i].content);
        // If the content string of the marker matches the marker we want to remove.
        if(markers[i].content == add) {
            // Set the markers map reference to null, removing it and signlaing it for garbage collection.
            markers[i].setMap(null);
            // Splice marker out of markers array and return from loop and function.
            markers.splice(i,1);
            return;
        }
    }
}