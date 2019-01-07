MyGame.screens['high-scores'] = (function(game) {
	'use strict';
	
	function initialize() {
		console.log("initializing high scores");
		document.getElementById('id-high-scores-back').addEventListener(
			'click',
			function() { game.showScreen('main-menu'); });
		document.getElementById('id-high-scores-clear').addEventListener(
			'click',
			function() {
				console.log('Setting Scores to zero.');
				localStorage.setItem('currentHighScoreSnake1',0);
				localStorage.setItem('currentHighScoreSnake2',0);
				localStorage.setItem('currentHighScoreSnake3',0);
				localStorage.setItem('currentHighScoreSnake4',0);
				localStorage.setItem('currentHighScoreSnake5',0);
				MyGame.screens['high-scores'].run();
			});
	}
	
	function run() {
		console.log('running and getting the scores');
		let hs1 = localStorage.getItem('currentHighScoreSnake1');
		let hs2 = localStorage.getItem('currentHighScoreSnake2');
		let hs3 = localStorage.getItem('currentHighScoreSnake3');
		let hs4 = localStorage.getItem('currentHighScoreSnake4');
		let hs5 = localStorage.getItem('currentHighScoreSnake5');
		if(hs1 == null){	
			localStorage.setItem('currentHighScoreSnake1',0);
			hs1 = localStorage.getItem('currentHighScoreSnake1');
		}
		if(hs2 == null){	
			localStorage.setItem('currentHighScoreSnake2',0);
			hs2 = localStorage.getItem('currentHighScoreSnake2');
		}
		if(hs3 == null){	
			localStorage.setItem('currentHighScoreSnake3',0);
			hs3 = localStorage.getItem('currentHighScoreSnake3');
		}
		if(hs4 == null){	
			localStorage.setItem('currentHighScoreSnake4',0);
			hs4 = localStorage.getItem('currentHighScoreSnake4');
		}
		if(hs5 == null){	
			localStorage.setItem('currentHighScoreSnake5',0);
			hs5 = localStorage.getItem('currentHighScoreSnake5');
		}
		//let outputString = '';
		//outputString += hs1.toString();
		document.getElementById('hslist').innerText = hs1 + ',\n';
		document.getElementById('hslist').innerText += hs2 + ',\n';
		document.getElementById('hslist').innerText += hs3 + ',\n';
		document.getElementById('hslist').innerText += hs4 + ',\n';
		document.getElementById('hslist').innerText += hs5 + '\n';
	}
	
	return {
		initialize : initialize,
		run : run
	};
}(MyGame.game));
