MyGame.screens['about'] = (function(game) {
	'use strict';
	
	function initialize() {
		console.log("initializing about");
		document.getElementById('id-about-back').addEventListener(
			'click',
			function() { game.showScreen('main-menu'); });
	}
	
	function run() {
		console.log("running about");

		//
		// I know this is empty, there isn't anything to do.
	}
	
	return {
		initialize : initialize,
		run : run
	};
}(MyGame.game));
