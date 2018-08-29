const Core = require('../core');

let wins = Core.getAllWindows().filter((win) => {
	return win.name.indexOf('Flappy Bird') >= 0;
});

if(wins.length) {
	let hwnd = wins[0].hwnd;
	//let imgData = Core.getScreenShotData(hwnd);
	let imgData = Core.getScreenShotData(hwnd, 20, 100, 50, 50);

	console.log(imgData.data.length);

}
