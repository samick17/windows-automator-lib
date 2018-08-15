const Core = require('../core');
//if installed by package, using:
//const Core = require('windows-automator-lib').Core;

function getExcelHWND() {
	let wins = Core.getAllWindows();
	for(let i in wins) {
		let win = wins[i];
		if(win.name.indexOf('Microsoft Excel') >= 0) {
			return win.hwnd;
		}	
	}
	throw new Error('not found!')
}
let hwnd = getExcelHWND();
console.log(hwnd);
console.log('---------------properties---------------');
console.log(Core.getWindowProperties(hwnd))
console.log('---------------properties---------------');
Core.getChildWindowsById(hwnd)
.forEach((win) => {
	let size = Core.getWindowSize(win.hwnd);
	console.log(win, size);
	console.log(Core.getWindowProperties(win.hwnd));
	console.log('---------------------------------------------');
});
