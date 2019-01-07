// ------------------------------------------------------------------
// 
// This is the game object.  Everything about the game is located in 
// this object.
//
// ------------------------------------------------------------------
let MyGame = {};

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
		context: context
	};
}());

//------------------------------------------------------------------
//
// This function provides the "game" code.
//
//------------------------------------------------------------------
MyGame.main = (function (graphics) {
	'use strict';

	console.log('game initializing...');
	let lastTimeStamp = performance.now();
	let particles = [];

	//------------------------------------------------------------------
	//
	// Update the particles
	//
	//------------------------------------------------------------------
	function update(elapsedTime) {
		let keepMe = [];

		for (let particle = 0; particle < particles.length; particle++) {
			particles[particle].alive += elapsedTime;
			particles[particle].position.x += (elapsedTime * particles[particle].speed * particles[particle].direction.x);
			particles[particle].position.y += (elapsedTime * particles[particle].speed * particles[particle].direction.y);
			particles[particle].rotation += particles[particle].speed / .5;

			if (particles[particle].alive <= particles[particle].lifetime) {
				keepMe.push(particles[particle]);
			}
		}

		for (let particle = 0; particle < 25; particle++) {
			let p = {
				position: { x: 300, y: 300 },
				direction: Random.nextCircleVector(),
				speed: Random.nextGaussian( 0.05, .025 ),	// pixels per millisecond
				rotation: 0,
				lifetime: Random.nextGaussian(2000, 1000),	// milliseconds
				alive: 0,
				size: Random.nextGaussian(5, 2),
				fill: 'rgb(255, 255, 255)',
				stroke: 'rgb(0, 0, 0)'
			};
			keepMe.push(p);
		}
		particles = keepMe;
	}

	function drawParticle(p) {
		if (p.alive > 100) {
		graphics.context.save();
		graphics.context.translate(p.position.x + p.size / 2, p.position.y + p.size / 2);
		graphics.context.rotate(p.rotation);
		graphics.context.translate(-(p.position.x + p.size / 2), -(p.position.y + p.size / 2));

		graphics.context.fillStyle = p.fill;
		graphics.context.strokeStyle = p.stroke;
		graphics.context.fillRect(p.position.x, p.position.y, p.size, p.size);
		graphics.context.strokeRect(p.position.x, p.position.y, p.size, p.size);

		graphics.context.restore();
		}
	}

	//------------------------------------------------------------------
	//
	// Render the particles
	//
	//------------------------------------------------------------------
	function render() {
		graphics.clear();

		for (let particle = 0; particle < particles.length; particle++) {
			drawParticle(particles[particle]);
		}
	}

	//------------------------------------------------------------------
	//
	// This is the Game Loop function!
	//
	//------------------------------------------------------------------
	function gameLoop(time) {
		let elapsedTime = (time - lastTimeStamp);

		update(elapsedTime);
		lastTimeStamp = time;
		
		render();
		
		requestAnimationFrame(gameLoop);
	};

	requestAnimationFrame(gameLoop);
}(MyGame.graphics));
