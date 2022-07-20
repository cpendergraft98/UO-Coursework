/*
If run locally on localhost, it is necessary that Node.js is installed
and that node package manager(npm) is operational.
Locally server can be initiated by running npm install followed by npm start.
*/

// node requirements
const body_parser = require('body-parser');
// Requies http node library.
const http = require('http');
// Express library runs our server.
const express = require('express');
// multer library handles file upload.
const multer = require('multer');
// path library handles path concatenation and manipulation for server.
const path = require('path');
// Import TPSAlgorithm and db files from Server folder.
const algo = require('./Server/TSPAlgorithm');
const dbjs = require('./Server/db');
// Install priority-heap-queue library from npm.
const PriorityQueue = require('priority-heap-queue');


// limit the filesize to 10 MB, anything higher than that and an error will be throw
// also limit to only 1 file uploaded
const multerproto = multer({
    // Define limits in bytes for server upload.
    limits: {
        fileSize: 10000000,
        files: 1
    },
    fileFilter:(req,file,cb) => {
        // verify that uploaded file is of mimetype text/plain
        if (file.mimetype !== 'text/plain') {
            return cb(null, false);
        }
        cb(null, true);
    }
});


// this makes calling multer so it's not one massive line
const upload = multerproto.single('file');

// creating server instance using expressjs and port
const port = process.env.PORT || 5000;
// Create new express.js object, for server functionality.
const app = new express();

// Tell express to use parsing tools.
// app will use the dependancies natively
app.use(body_parser.text());
app.use(body_parser.json());
app.use(body_parser.urlencoded({ extended: true }));

// a script for running multer to prioritize large file size over invalid file type 
const multerErrorHandler = function(err, req, res, next) {
    // If file upload error, return error status to calling function.
    if (err) {
        res.status(403).json(err);
    } else {
        next();
    }
}

// Create paths to the WebStart folder and Server folder, containing project code.
const script_path = path.join(__dirname, 'WebStart');
const backend_path = path.join(__dirname, 'Server');

// Load all resources from the given directories.
// static resources  (i.e. js files)
app.use(express.static(script_path));
app.use(express.static(backend_path));

// Called when main web page is requested on server.
// index webpage
app.get('/', function(req, res) {
    // since db is loaded before the index page (line 13), just check to see if its size is 0 (as it should be)
    if (dbjs.db.size !== 0) {
        dbjs.db.clear();
    }
    // Indicate that server is delivering request and send main html file to client.
    console.log("Delivering front page");
    res.sendFile(path.join(script_path, 'testmap.html'));
});

// Server function for uploading file. Used multer library.
// post function for file upload, multerErrorHandler checks for excessive size after
app.post('/send_file', upload, multerErrorHandler, function(req, res) {
    // if req.file is undefined then upload failed
    if (req.file === undefined) {
        message = "Invalid input type.";
        return res.status(415).json(message);
    }
    console.log("Sending file");
    // get the file text
    var file_text = req.file.buffer.toString();
    // remove whitespaces
    file_text = file_text.trim()
    // wacky regex to cover both \r\n and \n ends for Windows/Unix
    var input_array = file_text.split(/\r?\n/);
    // Send status and array of addresses back to calling function.
    res.status(200).send(input_array);
});

// Server function returns list of addresses from the database.
// Calls database function getAddressList and getAllLatLng getting both address and coordinate lists.
app.get('/get_list', function(req, res) {
    console.log("getting list of addresses from server");
    // get all of the latitude longitude
    // Also get all adresses associated with coordinates.
    var address_list = dbjs.getAddressList();
    var location_list = dbjs.getAllLatLng();
    // if there are more than 1 locations
    if (location_list.length > 1) {
        res.status(200).send({addresses: address_list, coords: location_list});
    // Send message to client indicating more addresses must be input.
    } else if (location_list.length < 2 && location_list.length >= 0) {
        res.status(400).send("Please enter 2 or more addresses.");
    // Send error message to client indicating address retreval has failed.
    } else {
        res.status(406).send("Error getting address information.");
    }
});

// gets the size of the db
app.get('/db_size', function(req, res) {
    var db_size = dbjs.dbSize();
    console.log(db_size);
    res.status(200).send(db_size.toString());
})

// Check if the database is empty. Calls db function dbSize().
app.get('/db_empty', function(req, res) {
    res.status(200).send(dbjs.dbSize() == 0);
});

// Check if the database has a specific key contained in it. Calls db function dbHas().
app.post('/db_has', function(req,res) {
    res.status(200).send(dbjs.dbHas(req.body));
});

// Server function handles adding key and object pairs to the db.
app.post('/add_to_db', function(req, res) {
    // Call db function dbSet() returning a boolean value.
    var inserted = true;
    if (dbjs.dbSize() >= 10) {
        inserted = false;
    } else {
        inserted = dbjs.dbSet(req.body.address, req.body);
    }
    res.status(200).send(inserted);
});

// Server function specifically for adding adresses from a file to the database.
// Requires special handling.
app.post('/add_to_db_file', function(req,res) {
    // Call dbSetFile function.
    var inserted;
    if (dbjs.dbSize() >= 10) {
        inserted = false;
    } else {
        inserted = dbjs.dbSetFile(req.body.address, req.body);
    }
    res.status(200).send(inserted);
});

// Function for removing key object pairs from the database.
app.post('/remove_from_db', function(req, res) {
    // Get data from the POST request body.
    var body = req.body;
    // Get address string.
    var addJson = Object.keys(body);
    // Call dbDelete returning succes boolean.
    var was_removed = dbjs.dbDelete(addJson[0]);
    res.status(200).send(was_removed);
});

// Server function for calling TSP Algorithm function.
// TSP algorithm is run on server for speed and for use of npm libraries which do not run in default javascript.
app.post('/optimize', function(req, res) {
    // Time out the distance matrix calculation so that google api does not throttle our api key.
    setTimeout(() => {
    // req.body contains the distance matrix
    var d_matrix = req.body;
    // Get optimised list of indices by calling algorithm function prim. See reference in TSPAlgorithm.js file.
    var opti_list = algo.prim(d_matrix);

    // send optimization back to client for handling
    res.status(200).send(opti_list);
    }, 500);
});

// Server function for resetting the the google map object, removing all markers and paths.
app.post('/reset', function(req,res) {
    // Wait to reset the server until db has cleared.
    setTimeout(()=>{
    // Log to console that reset operation is being performed.
    console.log("Resetting db and map");
    // Call db clear() function.
    dbjs.db.clear();
    // Send success code back to caller.
    res.status(200).send("Success");
    }, 100)
});

// Initiates server to listen on the specified port of the server.
// Waits for requests from client applications such as web browsers.
// opens the server for listening on whatever port is
app.listen(port, () => {
    console.log(`Listening for connections at localhost:${port}`);
});
