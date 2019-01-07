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
				console.log('doing work!');
				localStorage.setItem('currentHighScoreBreakout1',0);
				localStorage.setItem('currentHighScoreBreakout2',0);
				localStorage.setItem('currentHighScoreBreakout3',0);
				localStorage.setItem('currentHighScoreBreakout4',0);
				localStorage.setItem('currentHighScoreBreakout5',0);
				MyGame.screens['high-scores'].run();
			});
	}
	
	function run() {
		let hs1 = localStorage.getItem('currentHighScoreBreakout1');
		let hs2 = localStorage.getItem('currentHighScoreBreakout2');
		let hs3 = localStorage.getItem('currentHighScoreBreakout3');
		let hs4 = localStorage.getItem('currentHighScoreBreakout4');
		let hs5 = localStorage.getItem('currentHighScoreBreakout5');
		if(hs1 == null){	
			localStorage.setItem('currentHighScoreBreakout1',0);
			hs1 = localStorage.getItem('currentHighScoreBreakout1');
		}
		if(hs2 == null){	
			localStorage.setItem('currentHighScoreBreakout2',0);
			hs2 = localStorage.getItem('currentHighScoreBreakout2');
		}
		if(hs3 == null){	
			localStorage.setItem('currentHighScoreBreakout3',0);
			hs3 = localStorage.getItem('currentHighScoreBreakout3');
		}
		if(hs4 == null){	
			localStorage.setItem('currentHighScoreBreakout4',0);
			hs4 = localStorage.getItem('currentHighScoreBreakout4');
		}
		if(hs5 == null){	
			localStorage.setItem('currentHighScoreBreakout5',0);
			hs5 = localStorage.getItem('currentHighScoreBreakout5');
		}
		document.getElementById('hslist').innerText = hs1 + ',<br />';
		document.getElementById('hslist').innerHTML += '<br />';
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
