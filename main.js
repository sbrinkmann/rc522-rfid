var logger = require('dachshund-logger').getLogger(__filename);
var spawn = require('child_process').spawn;
var readline = require('readline');
var registeredCallback = null;

logger.info("RFID accessor initialization");

module.exports = exports = function(givenCallback){
	registeredCallback = givenCallback;
};

var initChildProcess = function()
{
	var child = spawn("node", [__dirname + "/" + "rc522_output.js"]);
	var linereader = readline.createInterface(child.stdout, child.stdin);

	linereader.on('line', function (rfidTagSerialNumber) {
		if(registeredCallback instanceof Function)
		{
			registeredCallback(rfidTagSerialNumber);
		}
	});

	child.on('close', function(code) {
		initChildProcess();
	});
};

initChildProcess();
