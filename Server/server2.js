var express = require('express');
var app = express();
app.set('view engine', 'ejs');
app.get('/', function(request, response) {
response.render('index', {
title: 'Home',
message: 'this is an app'
});
});
app.listen(80);
console.log("Server listening");