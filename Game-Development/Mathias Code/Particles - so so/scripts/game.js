//------------------------------------------------------------------
//
// This function provides the "game" code.
//
//------------------------------------------------------------------
MyGame.main = (function (graphics) {
	'use strict';

	console.log('game initializing...');
	let lastTimeStamp = performance.now();
	let ps1 = ParticleSystem({
		position: { x: 300, y: 300},
		speed: { mean: 0.07, stdev: 0.025},
		lifetime: { mean: 2000, stdev: 1000 },
		size: { mean: 5, stdev: 2 },
		fill: 'rgba(0, 0, 255, 0.5)',
		image: 'textures/fire.png'
	}, MyGame.graphics);

	// let ps2 = ParticleSystem({
	// 	position: { x: 300, y: 300},
	// 	speed: { mean: 0.02, stdev: 0.0125},
	// 	lifetime: { mean: 3000, stdev: 1000 },
	// 	size: { mean: 7, stdev: 3 },
	// 	fill: 'rgba(255, 0, 0, 0.5)',
	// 	image: 'textures/smoke.png'
	// }, MyGame.graphics);

	//------------------------------------------------------------------
	//
	// Update the particles
	//
	//------------------------------------------------------------------
	function update(elapsedTime) {
		ps1.update(elapsedTime);
		//ps2.update(elapsedTime);
	}

	//------------------------------------------------------------------
	//
	// Render the particles
	//
	//------------------------------------------------------------------
	function render() {
		console.log('render 1');
		graphics.clear();

		//ps2.render();
		ps1.render();
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
