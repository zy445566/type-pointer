var addon = require('bindings')('addon.node')

var obj = {a:1,b:2,c:3};
console.log('This should be eight:', addon.add(obj))