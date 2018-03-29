var addon = require('bindings')('addon.node')

var obj1 = {a:1,b:2,c:()=>{return a+b;},d:777};
addon.typeFlush("/Users/noder/Documents/GitHub/type-pointer/data/shareMem",1024);
var offset = addon.typeWrite("/Users/noder/Documents/GitHub/type-pointer/data/shareMem",1024,0,obj1);
console.log(offset);
// addon.typeClose("/Users/noder/Documents/GitHub/type-pointer/data/shareMem",1024);
var obj2 = addon.typeRead("/Users/noder/Documents/GitHub/type-pointer/data/shareMem",1024,0);
console.log(obj2);
