
	var ctx = $('canvas')[0].getContext('2d');

	var width = 444, height = 302;
	var x = 0, y = 0;
	dataArray.forEach(function(value, i) {
		ctx.fillStyle = value;
		ctx.fillRect(x, y, 1, 10);
		x++;
		if(i !== 0 && i % width === 0) {
			x = 0;
			y++;
		}
	});