MyGame.screens['help'] = (function(game) {
	'use strict';
	
	function initialize() {
		console.log("initializing help");
		document.getElementById('id-help-back').addEventListener(
			'click',
			function() { game.showScreen('main-menu'); });
	}
	
	function run() {
		console.log('running help');
		//
		// I know this is empty, there isn't anything to do.
	}
	
	return {
		initialize : initialize,
		run : run
	};
}(MyGame.game));
