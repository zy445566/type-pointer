var addon = require('bindings')('addon.node')

var obj1 = {a:1,b:2,c:3};
var objaddr = addon.getObjectAddr(obj1);
console.log('objaddr:',objaddr);
var obj2 = addon.getObjectByAddr(parseInt(objaddr,16));
console.log('obj2:',obj2);
console.log('obj1:',obj1);
var objaddr2 = addon.getObjectAddr(obj1);
console.log('objaddr2:',objaddr2);
var obj2addr1 = addon.getObjectAddr(obj2);
console.log('obj2addr1:',obj2addr1);