const spawn = require('child_process').spawn;
const nodeAbi = require('node-abi-version');

function getVersionData() {
	var verAbiMap = {};
	var abiVerMap = {};
	var abiVersionMap = nodeAbi.abiVersionMap;
	for(var ver in abiVersionMap) {
		var abi = abiVersionMap[ver];
		if(!(abi in abiVerMap)) {
			abiVerMap[abi] = ver;
			verAbiMap[ver] = abi;
		}
	}
	return verAbiMap;
}

function execCmd(cmd, args, callback) {
	var p = spawn(cmd, args, {
	  encoding: 'utf8',
	  timeout: 0,
	  maxBuffer: 200*1024,
	  killSignal: 'SIGTERM',
	  cwd: null,
	  env: null
	});
	p.stdout.on('data', (data) => {
		console.log(data.toString());
	});
	p.stderr.on('data', function (data) {
		console.log(data.toString());
	});
	p.on('exit', () => {
		console.log('done');
		callback();
	})
}
function buildTarget(verAbi, callback) {
	var ver = Object.keys(verAbi)[0];
	var abi = verAbi[ver];
	console.log('---- build target ----');
	console.log(`Version: ${ver}`);
	console.log(`ABI: ${abi}`);
	execCmd('cmd', ['/c', 'build-target.bat', ver, abi], callback);
}
const Utils = {
	each: function(items, callback) {
		function doEach(idx, items) {
			function createNextCallback(nextIdx) {
				return function() {
					doEach(nextIdx, items);
				}
			};
			if(idx in items) {
				callback(items[idx], createNextCallback(idx+1));
			}
		}
		function doEachKeys(idx, items, keys) {
			function createNextCallback(nextIdx) {
				return function() {
					doEachKeys(nextIdx, items, keys);
				}
			};
			var key = keys[idx];
			if(key in items) {
				var entry = {};
				entry[key] = items[key];
				callback(entry, createNextCallback(idx+1));
			}
		}
		if(typeof items === 'object') {
			var keys = Object.keys(items);
			doEachKeys(0, items, keys);
		}
		else {
			doEach(0, items);
		}
	}
};
const verAbiMap = getVersionData();
Utils.each(verAbiMap, function(item, callback) {
	buildTarget(item, callback);
});