// ------------------------------------------------------------------
// 
// This is the game object.  Everything about the game is located in 
// this object.
//
// ------------------------------------------------------------------
var MyGame = {};

// ------------------------------------------------------------------
// 
// This is the graphics rendering code for the game.
//
// ------------------------------------------------------------------
MyGame.graphics = (function() {
	'use strict';
	
	var canvas = document.getElementById('canvas-main'),
		context = canvas.getContext('2d');
	
	//------------------------------------------------------------------
	//
	// Public method that allows the client code to clear the canvas.
	//
	//------------------------------------------------------------------
	function clear() {
		context.save();
		context.setTransform(1, 0, 0, 1, 0, 0);
		context.clearRect(0, 0, canvas.width, canvas.height);
		context.restore();
	}
	
	//------------------------------------------------------------------
	//
	// This is used to create a texture object that can be used by client
	// code for rendering.
	//
	//------------------------------------------------------------------
	function Texture(spec) {
		var that = {},
			ready = false,
			image = new Image();
		
		//
		// Load the image, set the ready flag once it is loaded so that
		// rendering can begin.
		image.onload = function() { 
			ready = true;
		};
		image.src = spec.image;
		
		that.rotate = function(angle) {
			spec.rotation += angle;
		};
		
		that.moveLeft = function(distance) {
			spec.center.x -= distance;
		};
		
		that.moveRight = function(distance) {
			spec.center.x += distance;
		};
		
		that.moveUp = function(distance) {
			spec.center.y -= distance;
		};
		
		that.moveDown = function(distance) {
			spec.center.y += distance;
		};
		
		that.draw = function() {
			if (ready) {
				context.save();
				
				context.translate(spec.center.x, spec.center.y);
				context.rotate(spec.rotation);
				context.translate(-spec.center.x, -spec.center.y);
				
				context.drawImage(
					image, 
					spec.center.x - spec.width/2, 
					spec.center.y - spec.height/2,
					spec.width, spec.height);
				
				context.restore();
			}
		};
		
		return that;
	}
	
	return {
		clear : clear,
		Texture : Texture,
	};
}());

//------------------------------------------------------------------
//
// This is where the core game code is located.
//
//------------------------------------------------------------------
MyGame.main = (function(graphics) {

	var myTexture = graphics.Texture( {
			image : 'images/USU-Logo.png',
			center : { x : 100, y : 100 },
			width : 100, height : 100,
			rotation : 0
		});

	function onKeyDown(e) {
		//var keyPressed = String.fromCharCode(e.keyCode);
		//console.log(keyPressed + ' : ' + e.keyCode);
		if (e.keyCode === KeyEvent.DOM_VK_A) {
			myTexture.moveLeft(2);
		}
		else if (e.keyCode === KeyEvent.DOM_VK_D) {
			myTexture.moveRight(2);
		}
		else if (e.keyCode === KeyEvent.DOM_VK_W) {
			myTexture.moveUp(2);
		}
		else if (e.keyCode === KeyEvent.DOM_VK_S) {
			myTexture.moveDown(2);
		}
		else if (e.keyCode === KeyEvent.DOM_VK_E) {
			myTexture.rotate(0.02);
		}
		else if (e.keyCode === KeyEvent.DOM_VK_Q) {
			myTexture.rotate(-0.02);
		}
	}

	function update() {
		//
		// Nothing to do here, so sorry...
	}
	
	function render() {
		graphics.clear();
		myTexture.draw();
	}

	//------------------------------------------------------------------
	//
	// This is the Game Loop function!
	//
	//------------------------------------------------------------------
	function gameLoop(/* Not using time, therefore not defining an arg for it */) {

		update();
		render();

		requestAnimationFrame(gameLoop);
	};

	//
	// Get the gameloop started here
	console.log('game initializing...');
	//
	// Register the 'keydown' event with our code
	document.addEventListener('keydown', onKeyDown);
	requestAnimationFrame(gameLoop);
 
}(MyGame.graphics));
