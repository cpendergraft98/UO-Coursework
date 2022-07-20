// Several global variables used in scope throughout our project.
// The map variable holds reference to the google map. Allows drawing of paths and markers.
var map;
// The marker array holds all current markers displayed on the map. 
// This stays in scope as long as the map exists.
var markers = [];


// initMap function called by google maps api.
// Initializes the google map services, calls getLocation, and serves to initialize a number of other
function initMap() {
    // Google api directions services and renderer objects.
    // These handle drawing of directions on the map.
    // Renderer has suppressMarkers set to true so that default marker do not show of route render. We have custom markers.
    // These objects stay in scope as long as the map is active.
    directionsService = new google.maps.DirectionsService();
    directionsRenderer = new google.maps.DirectionsRenderer({suppressMarkers:true});
    // Google geocoder object handles translation of address strings into map data (coordinates, place ids, etc.).
    geocoder = new google.maps.Geocoder();

    // Create map at default location: Eugene.
    map = new google.maps.Map(document.getElementById('map'), {
      // Center map at 
      center: {
        lat: 44.0521,
        lng: -123.0868
      },
      zoom: 10,
    });

    // Clear markers array, (useful when reset has been caller)
    clearMarkers();

    // Set the map object value of the google directions
    directionsRenderer.setMap(map);
    // Asychronously call getLocation. This checks for location permission while the map is created with center Eugene
    getLocation();
    // Initialize the google maps autocomplete functionality. This searches and provides auto generated selections when seaching in the input bar.
    // Also stays in scope as long as the map is generated.
    autocomplete = new google.maps.places.Autocomplete(document.getElementById("autocomplete"), {types: ["geocode"]});
}

// Function requsts access from user location, then moves map to location.
// Currently no error handling function.
function getLocation() {
    // Check if location services are active. 
    // Navigator is a build in component of google map services which moves the map to specified lat/lng cordinates.
    if(navigator.geolocation) {
        // Set the navigators current position to the user location retreived above.
        navigator.geolocation.getCurrentPosition(
        (position) => {
          const pos = {
            lat: position.coords.latitude,
            lng: position.coords.longitude,
          };
          // Set map center to position.
          map.setCenter(pos);
        },
        () => {
          // Print error message if location retreival has failed. Webapp continues without failure if this occurs.
          console.log("Error with user location!");
        }
      );
    }
}

// Geocoding function for translating address string into google address data.
// Geocode an address then send a post request to the server to add to (address - lat/lng) pair to db. 
// If succsefful then calls addItem, adding address to the display list.
// Input parameters include address to look up, and boolean value empty, indicating if the list is empty or not.
function geocodeAddress(add, empty) {
    // Use javascript timeout functionality to wait for asyncronous call to finish before moving on.
    setTimeout(() => {
    // Use google gocoding to look up given address, handling the response from google servers.
    geocoder.geocode({address:add}, function(res, status) {
        // Handle function checks if GET request status is acceptable.
        if(status == google.maps.GeocoderStatus.OK) {
            // Retreive lat/lng coordinate data from the JSON object containing address information from the google server.
            var coord = res[0].geometry.location.toJSON();
            // Server post request, calling server function add_to_db_file, which adds the specified object and key to the server database.
            $.post('add_to_db_file', {address:add, location: res[0].geometry.location.toJSON(), start: empty}).done(function(data, status) {
                if (data === false) {
                    alert("ERROR: The maximum amount of addresses is 10.");
                    return;
                } else {
                    // Draw marker to the map. drawMarker function located in gapi.js.
                    drawMarker(coord,add, add);
                }
            });

        } else {
            // Send error message if google geocode request failed.
            console.log("Geocode failed: " + status);
        }
    });
    // Timout waits for 500 ms so that above server request finishes.
    }, 500);
}

// doOptimize initiates optimization of the address list, and displaying of the optimized path.
// Called on click of Optimize button
function doOptimize() {
    // Get request to server, returns list of coordinates and addresses stored in db.
    // Server calls get_list server function, returning the result.
    $.get('get_list').done(function(data, status) {
        // Check that server result is an array, sending server alert if get request failed.
        if (!Array.isArray(data.coords)) {
            alert(data)
        } else {
            // Initialize empty distance matrix to be filled by the google api distance matrix functionality.
            var mat = [];
            // Call distance matrix function found in gapi.js.
            // This function implementes google api distance matrix funtionality.
            getDistanceMatrix(data.coords, data.coords, 'DRIVING', mat, data.addresses);
        }
    // If Server GET request failed, alert server.
    }).fail(function(xhr, status, error) {
        alert(xhr.responseText);
    });
}

// Use itemCounter to give list items unique IDs.
// A global variable used to keep track of the number of items in the address display list.
var itemCounter = 0;

// showInput function initiates series of function calls that occur when address is searched and submitted.
function showInput(){
  // Get the submitted address from the google search input bar.
  var text_to_insert = document.getElementById("autocomplete").value;
  // Get google address data from the google autocomplete services object.
  var obj = autocomplete.getPlace();
  // Get coodinate value for current address from the google api JSON address object.
  var coord = obj.geometry.location.toJSON();
  // Call server POST request add_to_db which adds the provided data object and key to the database.
  $.post('add_to_db', {address: text_to_insert, location: coord, start: 0}).done(function(inserted) {
        // Request handling function checks if item was correctly inserted, adding it to the display list if so.
        if (inserted) {
            // Calls addItem and drawMerker functions seen below. Adds addres to list and places a marker.
            addItem(document.getElementById("the_list"), text_to_insert);
            drawMarker(coord,text_to_insert, text_to_insert);
        } else {
            alert("ERROR: The maximum amount of addresses is 10.");
        }
  });
  // Reset the search bar value to empty after current address has been added to the list.
  document.getElementById("autocomplete").value = "";
}

// Function for removing all addresses from the display list.
// Loops through list of addresses, calling server requests to remove addresses from the database.
function removeAll(list){
  // Temporary listItem and address variables for handling html objects and address text from UI.
  var listItem;
  var address;
  // Temporary store for total address count.
  var itemCount = itemCounter;
  // Loop through addresses in the database and list.
  while(list.firstChild) {
    // Get last item in the address list.
    var listitem = list.lastChild;
    // Get address string associated with item.
    address = listitem.innerText;
    // Remove the address value from its inner text.
    address = address.substring(0, address.length - 6);
    // Call javascript remove function, removing the element from the html page.
    listitem.remove();
    // Send server post request, calling remove_from_db server function.
    $.post('remove_from_db', address);
    // Decrement adrress counter.
    itemCounter--;
  }
}

// removeItem function is called when the Remove button is clicked on an address item in the list.
// Removes address item from the list in the html page and calls server functionality.
function removeItem(){
  // Get the inner text of the parent node of the remove button(the address item).
  var address = this.parentNode.innerText;
  // Retrieve address string from the html element text.
  address = address.substring(0, address.length - 6);
  // Remove parent node(the address html element in the list).
  this.parentNode.remove();
  // SEnd server post request, calling remove_from_db with address string as parameter.
  $.post('remove_from_db', address);
  // Decrement item counter.
  itemCounter--;
  // Remove marker from map.
  removeMarker(address);
}

// addItem add an address item to the address list with the given text as contents.
function addItem(list, text_to_insert) {
  // Increment itemCounter.
  itemCounter ++;
  // Temporary variables store new list and text html elements.
  var listItem = document.createElement('li');
  var span = document.createElement('span');
  // Set ids for both new elements.
  listItem.id = "item_" + itemCounter;
  span.id = "span_" + itemCounter;
  // Set value of display text for inner span object.
  span.innerHTML = text_to_insert;
  // Set the Bootstrap class name for stryling and add text span to list item.
  listItem.className = "list-group-item";
  listItem.appendChild(span);
  // Create html button element for remove button located on address list item.
  var removeButton = document.createElement("button");
  removeButton.contentEditable = false;
  removeButton.innerHTML = "remove";
  // Set click listener, calling above removeItem function.
  removeButton.addEventListener('click', removeItem, false);
  // Add removeButton as child of new list item.
  listItem.appendChild(removeButton);
  // Add list item to provided address list.
  list.appendChild(listItem);
}


