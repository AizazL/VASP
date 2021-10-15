var express = require('express');
var router = express.Router();
var mymongo = require('mongodb').MongoClient;

// mongo ipaddress
var mongoUrl = "mongodb://127.0.0.1:27017/";


router.get('/', function (req, res, next) {
    return res.render("coldFlu")
});

module.exports = router

