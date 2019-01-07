MyGame.screens['game-play'] = (function(game, graphics, input) {
	'use strict';
	
	let mouseCapture = false;
	let	myMouse = input.Mouse();
	let	myKeyboard = input.Keyboard();
	//let myTexture = null;
	let myGameBoard = null;
	//let myScoreBoard = null;
	let	cancelNextRequest = false;
	let	lastTimeStamp;
	
	function initialize() {
		console.log('game initializing...');

		//  In here we will start by specifying a paddle and giving it some basic movement.

		// myGameBoard = graphics.GameBoard({
		// 	image: './images/background.png'
		// });

		// myTexture = graphics.Texture( {
		// 	image : './images/online-art/C10.png',
		// 	center : { x : 100, y : 100 },
		// 	width : 100, height : 100,
		// 	rotation : 0,
		// 	moveRate : 200,			// pixels per second
		// 	rotateRate : 3.14159	// Radians per second
		// });

		myGameBoard = graphics.GameBoard({
			size : 50,
			//backGroundImage : './images/background.png'
		});

		// myScoreBoard = graphics.ScoreBoard({

		// });

		myKeyboard.registerCommand(KeyEvent.DOM_VK_A, myGameBoard.moveLeft);
		myKeyboard.registerCommand(KeyEvent.DOM_VK_D, myGameBoard.moveRight);
		myKeyboard.registerCommand(KeyEvent.DOM_VK_W, myGameBoard.moveUp);
		myKeyboard.registerCommand(KeyEvent.DOM_VK_S, myGameBoard.moveDown);
		myKeyboard.registerCommand(KeyEvent.DOM_VK_LEFT, myGameBoard.moveLeft);
		myKeyboard.registerCommand(KeyEvent.DOM_VK_RIGHT, myGameBoard.moveRight);
		myKeyboard.registerCommand(KeyEvent.DOM_VK_UP, myGameBoard.moveUp);
		myKeyboard.registerCommand(KeyEvent.DOM_VK_DOWN, myGameBoard.moveDown);
		//myKeyboard.registerCommand(KeyEvent.DOM_VK_Q, myTexture.rotateLeft);
		//myKeyboard.registerCommand(KeyEvent.DOM_VK_E, myTexture.rotateRight);
		myKeyboard.registerCommand(KeyEvent.DOM_VK_ESCAPE, function() {
			// HERE IS WHERE WE SHOULD CALL A RESET FUNCTION, Like texture.reset();
			//
			// Stop the game loop by canceling the request for the next animation frame
			cancelNextRequest = true;
			//
			// Then, return to the main menu
			game.showScreen('main-menu');
			location.reload();
		});
		
		// For the breakout project we only require the arrow buttons
		//
		// Create an ability to move the logo using the mouse
		myMouse = input.Mouse();
		myMouse.registerCommand('mousedown', function(e) {
			// let xPos = e.clientX;
			// let yPos = e.clientY;
			mouseCapture = true;
			// myTexture.moveTo({x : e.clientX, y : e.clientY});
			// myGameBoard.makeExplosion(xPos,yPos);
		});

		myMouse.registerCommand('mouseup', function() {
			mouseCapture = false;
		});

		myMouse.registerCommand('mousemove', function(e) {
			//console.log('cool');
			// if (mouseCapture) {
			// 	myTexture.moveTo({x : e.clientX, y : e.clientY});
			// }
		});
	}



	function processInput(elapsedTime){

	}

	function update(elapsedTime) {
		myKeyboard.update(elapsedTime);
		myMouse.update(elapsedTime);
		myGameBoard.update(elapsedTime);
		//myScoreBoard.update(elapsedTime);
	}
	
	function render(elapsedTime) {
		graphics.clear();
		myGameBoard.draw(elapsedTime);
		//myTexture.draw();
		//myScoreBoard.draw(elapsedTime);
	}

	function gameLoop(time) {
		processInput(time - lastTimeStamp);
		update(time - lastTimeStamp);
		render(time - lastTimeStamp);

		lastTimeStamp = time;

		if (!cancelNextRequest) {
			// The call back method (gameloop) is passed a domhighrestimesstamp
			requestAnimationFrame(gameLoop);
		}
	}





	
	function run() {
		
		lastTimeStamp = performance.now();

		// Start the animation loop
		cancelNextRequest = false;
		requestAnimationFrame(gameLoop);
	}
	
	return {
		initialize : initialize,
		run : run
	};
}(MyGame.game, MyGame.graphics, MyGame.input));
