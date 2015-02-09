var rc522 = require('./build/Release/rc522');

rc522(function(rfidTagSerialNumber) {
	console.log(rfidTagSerialNumber);
});