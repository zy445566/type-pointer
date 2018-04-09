# type-pointer
nodejs pointer

# install
-------------------
```sh
npm install type-pointer
```

# prepare
-------------------
```
npm install node-gyp -g
```
You can see:https://github.com/nodejs/node-gyp#installation

# example
-------------------
```node
const TypePointer = require('type-pointer');
const assert = require('assert');

let typePointer = new TypePointer();
var obj1 = {a:1,b:2,c:()=>{return a+b;}};
//----------------mallocValueAddr-----------------
var addr = typePointer.mallocValueAddr(obj1);
//console.log(addr);//0x102709430
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
```