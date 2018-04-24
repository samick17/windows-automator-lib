(function() {
	const Lib = require('windows-automator-lib');
	const Core = Lib.Core;
	const VK = Lib.VK;
	var isStart = false;
	function rightClick(callback) {
		Core.mouseLeftDown();
		setTimeout(function() {
			Core.mouseLeftUp();
			setTimeout(function() {
				callback();
			}, 30);
		}, 30);
	}
	function pauseMagicSpell(callback) {
		console.log('pause magic spell');
		Core.keyDown('OEM_3');//the '~' key
		setTimeout(function() {
			Core.keyUp('OEM_3');
			setTimeout(function() {
				callback();
			}, 100);
		}, 100);
	}
	function loopAsync(index, count, time, workCallback, callback) {
		if(index < count) {
			setTimeout(function() {
				workCallback(function() {
					loopAsync(index+1, count, time, workCallback, callback);
				});
			}, time);
		} else {
			callback();
		}
	}
	function bot(callback) {
		setTimeout(function() {
			console.log('[bot] newloop');
			pauseMagicSpell(function() {
				pauseMagicSpell(function() {
					console.log('f1');
					Core.combinationKeyByVKValue([VK.F1]);
					setTimeout(function() {
						loopAsync(0, 60, 50, function(callback) {
							console.log('rightclick');
							rightClick(function() {
								callback();
							});
						}, function() {
							setTimeout(function() {
								bot(callback);
							}, 3000);
						});
					}, 1500);
				});
			});
		}, 500);
	}

	process.on('exit', function() {
		console.log('script terminated!');
	});

	function main() {
		bot(function() {
			console.log();
		});
	}
	main();
})();