(function() {
	const Lib = require('windows-automator-lib');
	const Core = Lib.Core;
	const VK = Lib.VK;
	const HotkeyModifier = Lib.HotkeyModifiers;
	const Utils = require('util');
	const GlobalHotKeys = require('./global-hot-keys');
	const fork = require('child_process').fork;
	/*
	example of register hotkey
	*/

	function registerHotkey(id, keyEventConfig) {
		var keyId = parseInt(id);
		var success = Core.regHotKey(keyId, keyEventConfig.modKey, keyEventConfig.key);
		if(!success) {
			throw Utils.format('register key :%s failed', keyId);
		}
	}
	var botProc;

	var keyEventMap = {
		1: {
			modKey: HotkeyModifier.CONTROL,
			key: VK.H,
			handler: function() {
				return new Promise((resolve, reject) => {
					console.log('start');
					if(!botProc) {
						botProc = fork('./script.js');
						botProc.stdout.on('data', function(data) {
							console.log(data.toString());
						});
						botProc.stderr.on('data', function(data) {
							console.log(data.toString());
						});
						console.log('[bot]start');
					} else {
						botProc.kill();
						botProc = undefined;
						console.log('[bot]pause');
					}
					resolve();
				});
			}
		},
		2: {
			modKey: HotkeyModifier.CONTROL,
			key: VK.G,
			handler: function() {
				console.log('handle event 2');
				process.exit();
			}
		}
	};

	function onKey() {
		GlobalHotKeys.getHotKey()
		.then(function(keyId) {
			if(keyId in keyEventMap) {
				var promise = keyEventMap[keyId].handler();
				if(promise instanceof Promise) {
					promise.then(function() {
						onKey();
					}, function() {
						onKey();
					});
				} else {
					onKey();
				}
			} else {
				onKey();
			}
		}, function(err) {
			console.log(err);
			onKey();
		});
	}

	function main() {
		try {
			for(var key in keyEventMap) {
				registerHotkey(key, keyEventMap[key]);
			}
			onKey();
		}
		catch(e) {
			console.log(e);
		}
	}
	main();
})();