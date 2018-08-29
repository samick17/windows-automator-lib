const binding = require('./dist/Automator');

function zfill(t, len) {
	var r = t;
	for(var i = t.length; i < len; i++) {
		r = '0' + r;
	}
	return r;
}

module.exports = binding;
module.exports.sendText = function(text) {
	for(var i in text) {
		var ch = text[i];
		binding.sendCharByScanCode(ch.charCodeAt());
	}
};
module.exports.pressLeftArrow = function() {
	binding.combinationKey(['shift', 'left']);
};
module.exports.pressRightArrow = function() {
	binding.combinationKey(['shift', 'right']);
};
module.exports.pressUpArrow = function() {
	binding.combinationKey(['shift', 'up']);
};
module.exports.pressDownArrow = function() {
	binding.combinationKey(['shift', 'down']);
};
function getScreenShotData(hwnd, handler, left, top, width, height) {
	var imgData = binding.captureScreen(hwnd, left, top, width, height);
	var dots = [];
	var w = imgData.w, h = imgData.h;
	var data = imgData.data;
	var index = 0;
	handler = handler || {};
	var handleValue = handler.preValue || function(v) {return v};
	var handlePostValue = handler.postValue || function() {};
	var handleColorR = handler.r || function() {};
	var handleColorG = handler.g || function() {};
	var handleColorB = handler.b || function() {};
	for(var i = 0 ; i < data.length; i++) {
		var value = handleValue(data[i]);
		switch(i % 3) {
			case 0:
			dots.push({});
			handleColorB(dots, index, value);
			break;
			case 1:
			handleColorG(dots, index, value);
			break;
			case 2:
			handleColorR(dots, index, value);
			handlePostValue(dots, index);
			index++;
			break;
		}
	}
	return {
		w: w,
		h: h,
		data: dots
	};
};
module.exports.getScreenShotData = function(hwnd, left, top, width, height) {
	return getScreenShotData(hwnd, {
		preValue: function(value) {
			return zfill(value.toString(16), 2);
		},
		r: function(dataArray, index, value) {
			dataArray[index].r = value;
		},
		g: function(dataArray, index, value) {
			dataArray[index].g = value;
		},
		b: function(dataArray, index, value) {
			dataArray[index].b = value;
		},
		postValue: function(dataArray, index) {
			var color = dataArray[index];
			dataArray[index] = '#'+color.r+color.g+color.b;
		}
	}, left, top, width, height);
};
module.exports.getScreenShotDataGrayScale = function(hwnd, left, top, width, height) {
	return getScreenShotData(hwnd, {
		r: function(dataArray, index, value) {
			dataArray[index].r = value;
		},
		g: function(dataArray, index, value) {
			dataArray[index].g = value;
		},
		b: function(dataArray, index, value) {
			dataArray[index].b = value;
		},
		postValue: function(dataArray, index) {
			var color = dataArray[index];
			var v = parseInt((color.r + color.g + color.b) / 765 * 255).toString(16);
			dataArray[index] = '#'+v+v+v;
		}
	}, left, top, width, height);
};
module.exports.getScreenShotDataBlackWhite = function(hwnd, left, top, width, height) {
	return getScreenShotData(hwnd, {
		r: function(dataArray, index, value) {
			dataArray[index].r = value;
		},
		g: function(dataArray, index, value) {
			dataArray[index].g = value;
		},
		b: function(dataArray, index, value) {
			dataArray[index].b = value;
			
		},
		postValue: function(dataArray, index) {
			var color = dataArray[index];
			var sum = (color.r + color.g + color.b);
			var v;
			if(sum < 383) {
				v = '00';
			} else {
				v = 'ff';
			}
			dataArray[index] = '#'+v+v+v;
		}
	}, left, top, width, height);
};
