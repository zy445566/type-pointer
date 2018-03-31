var addon = require('bindings')('addon.node');
var path = require("path");

var path = path.join(__dirname,"/data/shareMem");
var obj2 = addon.typeRead(path,1024,0);
console.log(obj2);