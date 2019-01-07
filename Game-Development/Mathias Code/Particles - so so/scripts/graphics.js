// ------------------------------------------------------------------
//
// This is the graphics rendering code for the game.
//
// ------------------------------------------------------------------
MyGame.graphics = (function() {
	'use strict';
	
	let canvas = document.getElementById('canvas-main');
	let context = canvas.getContext('2d');

	//------------------------------------------------------------------
	//
	// Place a 'clear' function on the Canvas prototype, this makes it a part
	// of the canvas, rather than making a function that calls and does it.
	//
	//------------------------------------------------------------------
	CanvasRenderingContext2D.prototype.clear = function() {
		this.save();
		this.setTransform(1, 0, 0, 1, 0, 0);
		this.clearRect(0, 0, canvas.width, canvas.height);
		this.restore();
	};

	function drawRectangle(position, size, rotation, fill, stroke) {
		context.save();
		context.translate(position.x + size / 2, position.y + size / 2);
		context.rotate(rotation);
		context.translate(-(position.x + size / 2), -(position.y + size / 2));

		context.fillStyle = fill;
		context.strokeStyle = stroke;
		context.fillRect(position.x, position.y, size, size);
		context.strokeRect(position.x, position.y, size, size);

		context.restore();
	}

	function drawImage(center, size, rotation, image) {
		context.save();
		context.translate(center.x, center.y);
		context.rotate(rotation);
		context.translate(-center.x, -center.y);

		context.drawImage(
			image,
			center.x - size / 2,
			center.y - size / 2,
			size, size);

		context.restore();
	}

	//------------------------------------------------------------------
	//
	// Public function that allows the client code to clear the canvas.
	//
	//------------------------------------------------------------------
	function clear() {
		context.clear();
	}
	
	return {
		clear : clear,
		drawRectangle: drawRectangle,
		drawImage: drawImage
	};
}());
