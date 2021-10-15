var createError = require('http-errors');
var express = require('express');
var path = require('path');
var session = require('express-session');
var cookieParser = require('cookie-parser');
var flash = require('connect-flash');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');
var loginRouter = require("./routes/login");
var registerRouter = require('./routes/register');
var dashboardRouter = require('./routes/dashboard');
var inventoryRouter = require("./routes/inventory");
var logoutRouter = require('./routes/logout');
var healthRouter = require('./routes/healthReport');
var coldFluRouter = require('./routes/coldFlu');
var purchaseRouter = require('./routes/purchase');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'jade');

app.use(session({secret: 'secretcookiespassword', resave: false, name: 'main', saveUninitialized: false}));

// setups flash. used as temperory storage.
app.use(flash());


app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/login', loginRouter)
app.use('/register', registerRouter)
app.use('/dashboard', dashboardRouter)
app.use('/inventory', inventoryRouter)
app.use('/logout', logoutRouter)
app.use('/healthReport', healthRouter)
app.use('/coldFlu', coldFluRouter)
app.use('/purchase', purchaseRouter)

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
