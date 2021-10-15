var express = require('express');
var router = express.Router();
var bodyParser = require('body-parser');
var mymongo = require('mongodb').MongoClient;

// mongo ipaddress
var mongoUrl = "mongodb://127.0.0.1:27017/";

// express garbage
express().use(bodyParser.urlencoded({extended: true}));
express().use(bodyParser.json());

// code that runs when user tries to open 'register' page
router.get('/', function (req, res, next) {
    if (req.session.loggedin) 
        return res.redirect('/dashboard');
    
    res.render('register', {
        errors: req.flash('error')[0]
    });
});

// code that runs when user submits register details
router.post('/', function (req, res) {
    if (req.session.loggedin) 
        res.redirect('/dashboard');
    
    // get input from user
    var username = req.body.username;
    var email = req.body.email;
    var password = req.body.password;
    var age = req.body.age;
    var weight = req.body.weight;
    var height = req.body.height;
    var address = req.body.address;
    var gender = req.body.gender;

    // check if form is completed. if not, send user back to complete form
    if (!username || !password || !email || !age || !weight || !height || !address|| !gender) {
        req.flash('error', 'incompleteForm');
        return res.redirect('/register');
    }
    // check if email is valid. If not, then send user back to register
    /*if (!/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(email)) {
        req.flash('error', 'invalidEmail');
        return res.redirect('/register');
    }*/
    // now check if email is already being used
    mymongo.connect(mongoUrl, function (err, server) {
        if (err) 
            throw err;
        
        var localDrive = server.db("VASP-DB");
        localDrive.collection("users").find({email: email}).toArray(function (err, result) {
            if (err) 
                throw err;
            
            // if email is used, tell the user to login with that email
            if (result != 0) {
                req.flash('error', 'emailInUse');
                return res.redirect('/register');
            }
            /*now, since everything is checked, 
      add the user into the database and log them in*/
            var new_user = {
                username: username,
                password: password,
                email: email,
                age: age,
                height: height,
                weight: weight,
                address: address,
                gender: gender
            }; // creates object of new user
            localDrive.collection("users").insertOne(new_user, function (err, result) {
                if (err) 
                    throw err;
                
                req.session.loggedin = true;
                req.session.username = username;
                req.session.email = email;
                return res.redirect('/dashboard');
            });
        });
    });
});

module.exports = router;

