const TypePointer = require('./index');
const assert = require('assert');

let typePointer = new TypePointer();
var obj1 = {a:1,b:2,c:()=>{return a+b;}};
//----------------mallocValueAddr-----------------
var addr = typePointer.mallocValueAddr(obj1);
assert(parseInt(addr,16)>0,"mallocValueAddr failed");
//----------------readValueByAddr-----------------
var obj2 = typePointer.readValueByAddr(addr);
assert.deepEqual(obj2, obj1, "readValueByAddr failed");
var obj3 = {d:4};
//----------------writeValueByAddr-----------------
typePointer.writeValueByAddr(addr,obj3);
var obj4 = typePointer.readValueByAddr(addr);
assert.deepEqual(obj4, obj3, "writeValueByAddr failed");
//----------------freeValueByAddr-----------------
typePointer.freeValueByAddr(addr);
var obj5 = typePointer.readValueByAddr(addr);
assert.deepEqual(obj5, undefined, "freeValueByAddr failed");




