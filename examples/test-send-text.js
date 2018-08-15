const Core = require('../core');
//if installed by package, using:
//const Core = require('windows-automator-lib').Core;

let wait = (time) => {
	return new Promise((resolve) => {
		setTimeout(() => {
			resolve()
		}, time);
	});
}

(async () => {
	let text = '@axp2';
	Core.mouseMove(250, 72)
	Core.mouseLeftClick()
	
	for(let i = 0; i < 10; i++) {
		await wait(500);
		Core.sendText(text);
	}
})();
