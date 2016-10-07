var Core = require('../core');

var wheelValue = -20;
Core.mouseLeftClick();
setTimeout(function() {
	Core.mouseMoveOffset(5,15);
	Core.mouseWheel(wheelValue);
}, 2000);

