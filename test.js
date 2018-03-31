var addon = require('bindings')('addon.node');
var path = require("path");

var obj1 = {a:1,b:2,c:()=>{return a+b;}};
var path = path.join(__dirname,"/data/shareMem");
console.log(path);
addon.typeFlush(path,1024);
var offset = addon.typeWrite(path,1024,0,obj1);
console.log(offset);
addon.typeClose(path,1024);
var obj2 = addon.typeRead(path,1024,0);
setInterval(()=>{
    console.log(obj2);
    // addon.typeReset(path,1024,0);
},1000)

