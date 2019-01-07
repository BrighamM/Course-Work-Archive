
let previousTime = performance.now();

function processInput(elapsedTime) {

}

function update(elapsedTime) {
	console.log('elapsedTime: ', elapsedTime);
}

function render(elapsedTime) {

}

function gameLoop() {
	let currentTime = performance.now();
	let elapsedTime = currentTime - previousTime;
	previousTime = currentTime;

	processInput(elapsedTime);
	update(elapsedTime);
	render(elapsedTime);

	requestAnimationFrame(gameLoop);
}

gameLoop();
