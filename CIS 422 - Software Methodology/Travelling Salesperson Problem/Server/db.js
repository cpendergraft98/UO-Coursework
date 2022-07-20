// Initialize db variable.
// Uses javascript Map() functionality which is essentially a Hash table with a lot of variability.
var db = new Map();

// Put key item pair into the Map.
// Item has form {address: address, location: {lat:lat, lng:lng}, start:true/false}
function dbSet(key, item) {
    // Check that given key does not already exist in the database.
    if (db.has(key)) {
        console.log("key is already inserted!");
        return false;
    }
    // Check if this is the first item being added to the database.
    // Item value is set to indicate this so that starting item is always recognizable.
    if(db.size == 0) {
        item.start = true;
    }
    // Set key object pair in the Map.
    console.log(key + " is being added");
    db.set(key, item);
    return true;
}

// Simpler function for adding key item pairs when adding from a file.
// Handling of start value is done outside of db.
function dbSetFile(key, item) {
    db.set(key, item);
}

// Remove key item pair from db.
function dbDelete(key) { 
    console.log("Deleting key: "+key)
    return db.delete(key);
}

// Retrieve item associated with given key.
function dbGet(key, item) {
    return db.get(key);
}

// Get size of Map.
function dbSize() {
    return db.size;
}

// Check if db contains a key.
function dbHas(key) {
    return db.has(key);
}

// Get lat lng pairs from data objects stored through address keys.
function getAllLatLng() {
    // Initialize array for storing lat/lng values retrieved from the db.
    var locations = [];
    // Loop through database elements.
    for (const [key, value] of db) {
        // First retrieve the starting element(the one that was added first).
        if (value.start == 1) {
            console.log(value.address, value.start);
            locations.push(String(value.location.lat+","+value.location.lng));
        }
    }
    // Now loop through the rest addding remaingng coordinated to the list.
    for (const [key, value] of db) {
        if (value.start == 0) {
            console.log(value.address);
            locations.push(String(value.location.lat+","+value.location.lng));
        }
    }
    return locations;
}

// Get all keys (addresses) from db. Retrieves list addresse strings from the database.
function getAddressList() {
    // Initialize addresses array.
    var addresses = [];
    // Loop through database elemeents, adding each key to the array.
    for (const [key, value] of db) {
        addresses.push(key);
    }
    return addresses;
}

// Export each function used. This allow Express to recognize them ass function of the db object.
// db.js is turned treated like and object from which its functions can be called.
module.exports = { db, dbDelete, dbSet, getAllLatLng, getAddressList, dbHas, dbSize, dbSetFile };



