var express = require('express');
var router = express.Router();
var mymongo = require('mongodb').MongoClient;

// mongo ipaddress
var mongoUrl = "mongodb://127.0.0.1:27017/";


/* Sends the Login Page, and show error 
    if user attemted to login before */
router.get('/', function (req, res, next) { // checks if user is already logged in. if they are, then send them home!
    if (req.session.loggedin) 
        return res.redirect("/dashboard");
    
    return res.render('login', {
        loginFailed: req.flash('error')[0]
    }); // if user entered wrong user/pass then show error msg.
});



// Checks username and password with database
router.post('/', function (req, res) {
    var username = req.body.username; // get username and password from the request
    var password = req.body.password;
    mymongo.connect(mongoUrl, function (err, server) { // connects to main server
        if (err) 
            throw err;
        
        var localDrive = server.db("VASP-DB"); // connects to localDrive database
        queryCommand = {
            username: username,
            password: password
        } // prepares the search statement
        localDrive.collection("users").find(queryCommand).toArray(function (err, result) {
            if (err) 
                throw err;
            
            if (result.length > 0) { /*set session details, close any database 
          conection and send user to home page*/
                req.session.loggedin = true;
                req.session.username = username;
                req.session.email = result[0].email;
                console.log(req.session.username);
                server.close();
                return res.redirect('/dashboard');
            } else { /*if username or password is incorrect,
        send user back to the login page with a error message*/
                req.flash('error', true)
                server.close();
                return res.redirect('./login')
            }
        })
    })
});

module.exports = router
