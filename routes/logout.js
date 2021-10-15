var express = require('express');
var router = express.Router();
var mymongo = require('mongodb').MongoClient;

// mongo ipaddress
var mongoUrl = "mongodb://127.0.0.1:27017/";



// logout code
router.get('/', function (request, response) {
    request.session.destroy(function (err) { // distroy session
        if (err) 
            throw err;
        
        console.log("deleting session");
        return response.redirect('/login'); // send them to home page
    });
});

module.exports = router

