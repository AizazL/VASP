var express = require('express');
var router = express.Router();
var mymongo = require('mongodb').MongoClient;

// mongo ipaddress
var mongoUrl = "mongodb://127.0.0.1:27017/";



router.get('/', function (request, response) {
    if (!request.session.loggedin) 
        return response.redirect("/login");
    return response.render('healthReport')
});

router.get('/')

module.exports = router