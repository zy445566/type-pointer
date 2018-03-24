var addon = require('bindings')('addon.node')

var obj1 = {a:1,b:2,c:()=>{return a+b;}};
var objaddr1 = addon.getObjectAddr(obj1);
var obj2 = addon.getObjectByAddr(parseInt(objaddr1,16));
var objaddr2 = addon.getObjectAddr(obj2);
console.log(obj1,objaddr1)
console.log(obj2,objaddr2)
