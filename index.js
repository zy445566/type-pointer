var addon = require('bindings')('addon.node');
class TypePointer{
    mallocValueAddr(value)
    {
        return addon.mallocValueAddr(value);
    }

    readValueByAddr(addr)
    {
        return addon.readValueByAddr(parseInt(addr,16));
    }

    writeValueByAddr(addr,value)
    {
        return addon.writeValueByAddr(parseInt(addr,16),value);
    }

    freeValueByAddr(addr)
    {
        return addon.freeValueByAddr(parseInt(addr,16));
    }
}

module.exports = TypePointer;
