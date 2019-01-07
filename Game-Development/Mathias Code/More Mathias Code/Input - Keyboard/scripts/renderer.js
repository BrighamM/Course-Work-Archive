// ------------------------------------------------------------------
// 
// This is the game object.  Everything about the game is located in 
// this object.
//
// ------------------------------------------------------------------


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
	function Model(spec) {
		let that = {};
		let ready = false;
		let image = new Image();
		
		//
		// Load the image, set the ready flag once it is loaded so that
		// rendering can begin.
		image.onload = function() { 
			ready = true;
		};
		image.src = spec.image;

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

		that.moveUp = function(elapsedTime) {
			spec.center.y -= (spec.moveRate / 1000) * elapsedTime;
		};

		that.moveDown = function(elapsedTime) {
			spec.center.y += (spec.moveRate / 1000) * elapsedTime;
		};

		that.moveLeft = function(elapsedTime) {
			spec.center.x -= (spec.moveRate / 1000) * elapsedTime;
		};

		that.moveRight = function(elapsedTime) {
			spec.center.x += (spec.moveRate / 1000) * elapsedTime;
		};

		that.rotateRight = function(elapsedTime) {
			spec.rotation += (spec.rotateRate / 1000) * elapsedTime;
		};

		that.rotateLeft = function(elapsedTime) {
			spec.rotation -= (spec.rotateRate / 1000) * elapsedTime;
		};
		
		return that;
	}
	
	return {
		clear : clear,
		Model : Model,
	};
}());

//------------------------------------------------------------------
//
// This is where the core game code is located.
//
//------------------------------------------------------------------
MyGame.main = (function(graphics, input) {

	let myTexture = graphics.Model({
			image : 'images/USU-Logo.png',
			center : { x : 100, y : 100 },
			width : 100, height : 100,
			rotation : 0,
			moveRate: 200, // pixels per second
			rotateRate: 3.14159 // radians per second
		});
	let lastTimeStamp = performance.now();
	let myKeyboard = input.Keyboard();

	function processInput(elapsedTime) {
		myKeyboard.processInput(elapsedTime);
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
	function gameLoop(currentTime) {

		let elapsedTime = currentTime - lastTimeStamp;
		lastTimeStamp = currentTime;
		processInput(elapsedTime);
		update();
		render();

		requestAnimationFrame(gameLoop);
	};

	//
	// Get the gameloop started here
	console.log('game initializing...');
	myKeyboard.registerCommand(KeyEvent.DOM_VK_W, myTexture.moveUp);
	myKeyboard.registerCommand(KeyEvent.DOM_VK_S, myTexture.moveDown);
	myKeyboard.registerCommand(KeyEvent.DOM_VK_A, myTexture.moveLeft);
	myKeyboard.registerCommand(KeyEvent.DOM_VK_D, myTexture.moveRight);
	myKeyboard.registerCommand(KeyEvent.DOM_VK_Q, myTexture.rotateLeft);
	myKeyboard.registerCommand(KeyEvent.DOM_VK_E, myTexture.rotateRight);

	// if (myKeyboard.keys[KeyEvent.DOM_VK_W]) {
	// 	myTexture.moveUp(elapsedTime);
	// }
	// if (myKeyboard.keys[KeyEvent.DOM_VK_S]) {
	// 	myTexture.moveDown(elapsedTime);
	// } 
	// if (myKeyboard.keys[KeyEvent.DOM_VK_A]) {
	// 	myTexture.moveLeft(elapsedTime);
	// } 
	// if (myKeyboard.keys[KeyEvent.DOM_VK_D]) {
	// 	myTexture.moveRight(elapsedTime);
	// } 
	// if (myKeyboard.keys[KeyEvent.DOM_VK_Q]) {
	// 	myTexture.rotateLeft(elapsedTime);
	// } 
	// if (myKeyboard.keys[KeyEvent.DOM_VK_E]) {
	// 	myTexture.rotateRight(elapsedTime);
	// }

	requestAnimationFrame(gameLoop);

}(MyGame.graphics, MyGame.input));
