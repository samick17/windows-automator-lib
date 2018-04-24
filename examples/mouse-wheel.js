const Core = require('../core');
//if installed by package, using:
//const Core = require('windows-automator-lib').Core;

var wheelValue = -20;
Core.mouseLeftClick();
setTimeout(function() {
	Core.mouseMoveOffset(5,15);
	Core.mouseWheel(wheelValue);
}, 2000);

