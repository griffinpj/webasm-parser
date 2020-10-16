const express = require('express');
const app = express();
const port = 3000;
const path = require('path');
const fs = require('fs');


app.use(express.static('webasm'));

//app.get('/:a+:b', (req, res) => {
//   var a = req.params.a;
//   var b = req.params.b;
//
//  var result = addTwo(a, b) 


//   res.send(`Eureka! The answer is ${result})`);
//});

app.listen(port, () => {
   console.log(`Listening on port http://localhost:${port}`);
});
