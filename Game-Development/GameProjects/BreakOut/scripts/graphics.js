MyGame.graphics = (function() {
	'use strict';
	
	let canvas = document.getElementById('canvas-main');
	let	context = canvas.getContext('2d');
	document.body.style.backgroundColor = "black";
	canvas.width = document.body.clientWidth; //document.width is obsolete
	canvas.height = document.body.clientHeight; //document.height is obsolete
	
	//
	// Place a 'clear' function on the Canvas prototype, this makes it a part
	// of the canvas, rather than making a function that calls and does it.
	CanvasRenderingContext2D.prototype.clear = function() {
		this.save();
		this.setTransform(1, 0, 0, 1, 0, 0);
		this.clearRect(0, 0, canvas.width, canvas.height);
		this.restore();
	};
	
	//------------------------------------------------------------------
	//
	// Public method that allows the client code to clear the canvas.
	//
	//------------------------------------------------------------------
	function clear() {
		context.clear();
	}

	let showCountScreen = true;
	let gameEnd = false;
	let countTimer = 3;
	let remainingPaddles = 2;
	let isTopRowHit = false;
	let ballSpeedMultiplier = .003;
	let isSpeedOne = true;
	let isSpeedTwo = false;
	let isSpeedThree = false;
	let isSpeedFour = false;
	let isSpeedFive = false;

	let blocksDestroyed = 1;
	let ball_Array = [];
	let ball = {
		radius: 8,
		x_position: 0,
		y_position: 0,
		speed_x: 0,
		speed_y: 0,
		north_wall: 0,
		south_wall: 0,
		west_wall: 0,
		east_wall: 0,
		getScore: function(input_i){
			if(bBlocksArr[input_i].color == 'yellow'){
				currentScore.score += 1;
				ballScore += 1;
				if(bBlocksArr[input_i].isBottomRow){
					yellowBottomROwSize -= 1;
					if(yellowBottomROwSize == 0){
						currentScore.score += 25;
						ballScore += 25;
						// console.log('yellowbottom');
					}
				}
				else{
					yellowUpperRowSize -= 1;
					if(yellowUpperRowSize == 0){
						currentScore.score += 25;
						ballScore += 25
						// console.log('yellowtop');
					}
				}

			}
			if(bBlocksArr[input_i].color == 'orange'){
				currentScore.score += 2;
				ballScore += 2;
				if(bBlocksArr[input_i].isBottomRow){
					orangeBottomRowSize -= 1;
					if(orangeBottomRowSize == 0){
						currentScore.score += 25;
						ballScore += 25
						// console.log('orangebottom');
					}
				}
				else{
					orangeUpperRowSize -= 1;
					if(orangeUpperRowSize == 0){
						currentScore.score += 25;
						ballScore += 25
						// console.log('orangetop');
					}
				}
			}
			if(bBlocksArr[input_i].color == 'blue'){
				currentScore.score += 3;
				ballScore += 3;
				if(bBlocksArr[input_i].isBottomRow){
					blueBottomRowSize -= 1;
					if(blueBottomRowSize == 0){
						currentScore.score += 25;
						ballScore += 25
						// console.log('bluebottom');
					}
				}
				else{
					blueUpperRowSize -= 1;
					if(blueUpperRowSize == 0){
						currentScore.score += 25;
						ballScore += 25
						// console.log('bluetop');
					}
				}
			}
			if(bBlocksArr[input_i].color == 'green'){
				currentScore.score += 5;
				ballScore += 5;
				if(bBlocksArr[input_i].isBottomRow){
					greenBottomRowSize -= 1;
					if(greenBottomRowSize == 0){
						currentScore.score += 25;
						ballScore += 25
						// console.log('greenbottom');
					}
				}
				else{
					paddle.width = temp_width*2*(5)*(.5);
					greenUpperRowSize -= 1;
					if(greenUpperRowSize == 0){
						currentScore.score += 25;
						ballScore += 25
						// console.log('greentop');
					}
				}
			}

		},
		updateMe: function(){
			// if(this.speed_x < 0){
			// 	this.speed_x = -ballSpeedMultiplier*canvas.width;
			// }
			// else{
			// 	this.speed_x = ballSpeedMultiplier*canvas.width;
			// }
			if(this.speed_y < 0){
				this.speed_y = -ballSpeedMultiplier*canvas.height;
			}
			else{
				this.speed_y = ballSpeedMultiplier*canvas.height;
			}
			let l1x = this.x_position - this.radius;
			let l1y = this.y_position - this.radius;
			let r1x = this.x_position + this.radius;
			let r1y = this.y_position + this.radius;


			if((this.x_position + this.radius + this.speed_x) >= this.east_wall) {
				this.speed_x = -this.speed_x;
			}
			if((this.x_position - this.radius + this.speed_x) <= this.west_wall){
				this.speed_x = -this.speed_x;
			}
			// if((this.y_position + this.speed_y) >= this.south_wall){
			// 	this.speed_y = -this.speed_y;
			// }
			if((this.y_position - this.radius + this.speed_y) <= this.north_wall) {
				this.speed_y = -this.speed_y;
			}
			for(var i = 0; i < bBlocksArr.length; i++){
				if(bBlocksArr[i].exists){


					if(bBlocksArr[i].didHit(l1x,l1y,r1x,r1y)){
						//console.log(blocksDestroyed);
						if(blocksDestroyed == 4){
							if(isSpeedOne){
								ballSpeedMultiplier = ballSpeedMultiplier*1.5;

								isSpeedOne = false;
								isSpeedTwo = true;
							}
						}
						if(blocksDestroyed == 12){
							if(isSpeedTwo){
								ballSpeedMultiplier = ballSpeedMultiplier*1.5;
	
								isSpeedTwo = false;
								isSpeedThree = true;
							}
						}
						if(blocksDestroyed == 36){
							if(isSpeedThree){
								ballSpeedMultiplier = ballSpeedMultiplier*1.5;
		
								isSpeedThree = false;
								isSpeedFour = true;
							}
						}
						if(blocksDestroyed == 62){
							if(isSpeedFour){
								ballSpeedMultiplier = ballSpeedMultiplier*1.5;
	
								isSpeedFour = false;
								isSpeedFive = true;
							}
						}
						
						

						let l2x = bBlocksArr[i].x_start;
						let l2y = bBlocksArr[i].y_start;
						let r2x = bBlocksArr[i].x_start + bBlocksArr[i].width;
						let r2y = bBlocksArr[i].y_start + bBlocksArr[i].height;
						if(this.y_position < l2y && this.x_position > l2x && this.x_position < r2x){
							bBlocksArr[i].exists = false;
							blocksDestroyed += 1;
							this.speed_y = -this.speed_y;
							this.getScore(i);
							break;
						}

						if(this.y_position > r2y && this.x_position > l2x && this.x_position < r2x){
							bBlocksArr[i].exists = false;
							blocksDestroyed += 1;
							this.speed_y = -this.speed_y;
							this.getScore(i);
							break;
						}

						if(this.x_position < l2x && this.y_position > l2y && this.y_position < r2y){
							bBlocksArr[i].exists = false;
							blocksDestroyed += 1;
							this.speed_x = -this.speed_x;
							this.getScore(i);
							break;
						}

						if(this.x_position > r2x && this.y_position > l2y && this.y_position < r2y){
							bBlocksArr[i].exists = false;
							blocksDestroyed += 1;
							this.speed_x = -this.speed_x;
							this.getScore(i);
							break;
						}

						if(this.x_position < r2x && this.x_position > l2x && this.y_position < r2y && this.y_position > l2y){
							bBlocksArr[i].exists = false;
							blocksDestroyed += 1;
							this.speed_x = -this.speed_x;
							this.speed_y = -this.speed_y;
							this.getScore(i);
							break;
						}
						//bBlocksArr[i].exists = false;
						
					};

					
				}
			}
			if(paddle.didHit(l1x,l1y,r1x,r1y)){
				let l2x = paddle.x_position;
				let l2y = paddle.y_position;
				let r2x = l2x + paddle.width;
				let r2y = l2y + paddle.height;
				// top
				if(this.y_position < l2y && this.x_position > l2x && this.x_position < r2x){
					// check and x

					var paddle_center_x = (r2x - (paddle.width/2));
					var vx_v = this.x_position - paddle_center_x;
					vx_v = vx_v/(paddle.width/2)
					// console.log('ball x', this.x_position);
					// console.log('paddle start x',l2x);
					// console.log('paddle end x',r2x);
					// console.log('paddle center x', paddle_center_x);
					// console.log('paddle width',paddle.width);
					// console.log('xv thing',vx_v);
					this.speed_x = vx_v*ballSpeedMultiplier*canvas.width;
					this.speed_y = -this.speed_y;
				}
				// bottom
				if(this.y_position > r2y && this.x_position > l2x && this.x_position < r2x){
					this.speed_y = -this.speed_y;
				}
				// left
				if(this.x_position < l2x && this.y_position > l2y && this.y_position < r2y){
					this.speed_x = -this.speed_x;
				}
				// right
				if(this.x_position > r2x && this.y_position > l2y && this.y_position < r2y){
					this.speed_x = -this.speed_x;
				}
				// inside
				if(this.x_position < r2x && this.x_position > l2x && this.y_position < r2y && this.y_position > l2y){
					this.speed_x = -this.speed_x;
					this.speed_y = -this.speed_y;
				}
			}
			this.x_position = this.x_position + this.speed_x;
			this.y_position = this.y_position + this.speed_y;

		},
		drawMe: function(){
			//var random_boolean = Math.random() >= 0.5;

			context.beginPath();
			context.arc(this.x_position,this.y_position,this.radius,0,2*Math.PI);
			context.fillStyle = 'green';
			context.fill();
			context.strokeStyle = 'purple';
		},
	}

	let nwe_Walls = [];
	let blockWalls = {
		// 21 blockWallss
		x_start: 0,
		y_start: 0,
		width: 0,
		height: 0,
		color: 'grey',
		isNorthWall: false,
		isWestWall: false,
		isEastWall: false,
		drawMe: function(){

			context.fillStyle = 'grey';
			context.fillRect(this.x_start, this.y_start, this.width, this.height);
			context.strokeStyle = 'red';
			context.strokeRect(this.x_start, this.y_start, this.width, this.height);

		},
	}


	let paddle = {
		x_minimum: 0,
		x_maximum: 0,
		width: 0,
		height: 0,
		y_position: 0,
		x_position: 0,
		speed: .01*(canvas.width),
		drawMe: function(){
			context.fillStyle = 'orange';
			context.fillRect(this.x_position, this.y_position, this.width, this.height);
			context.strokeStyle = 'green';
			context.strokeRect(this.x_position, this.y_position, this.width, this.height);
		},
		try_move_left: function(){

			if(this.x_position <= this.x_minimum){
				return;
			}
			this.x_position = this.x_position - this.speed;

		},
		try_move_right: function(){

			if((this.x_position + this.width) >= this.x_maximum ){
				return;
			}
			this.x_position = this.x_position + this.speed;

		},
		didHit: function(tlx,tly,brx,bry){
			// If one rectangle is on left side of other
			if (tlx > (this.x_position + this.width) || (this.x_position) > brx){
				return false;
			}
			// If one rectangle is above other
			if (tly > (this.y_position + this.height) || (this.y_position) > bry){
				return false;
			}
			return true;
		}
		

	}

	let greenUpperRowSize = 19;
	let blueUpperRowSize = 19;
	let orangeUpperRowSize = 19;
	let yellowUpperRowSize = 19;
	let greenBottomRowSize = 19;
	let blueBottomRowSize = 19;
	let orangeBottomRowSize = 19;
	let yellowBottomROwSize = 19;

	let pixel = {
		px_pos: 0,
		py_pos: 0,
		pwidth: 0,
		pheight: 0,
		pcolor: '',
		pvx: 0,
		pvy: 0,
	}
	
	let topIsBroken = false;
	let bBlocksArr = [];
	let breakBlocks = {
		x_start: 0,
		y_start: 0,
		width: 0,
		height: 0,
		exists: true,
		complete: false,
		pixel_count: 500,
		pixelAr: [],
		time_alive: 0,
		death_time: 1,
		isBottomRow: true,
		color: 'black',
		drawMe: function(){
			if(this.exists){
				context.fillStyle = this.color;
				context.fillRect(this.x_start, this.y_start, this.width, this.height);
				context.strokeStyle = 'red';
				context.strokeRect(this.x_start, this.y_start, this.width, this.height);
			}
		},
		didHit: function(tlx,tly,brx,bry){
			// If one rectangle is on left side of other
			if (tlx > (this.x_start+this.width) || (this.x_start) > brx){
				return false;
			}
			// If one rectangle is above other
			if (tly > (this.y_start + this.height) || (this.y_start) > bry){
				return false;
			}
			return true;
		},
		blowUp: function(eltime){
			//console.log('i am here too')
			if(!this.complete){
				//console.log(eltime);
				for(var k = 0; k<this.pixel_count; k++){
					this.pixelAr[k].px_pos += this.pixelAr[k].pvx*canvas.width;
					this.pixelAr[k].py_pos += this.pixelAr[k].pvy*canvas.height;
				}
				this.time_alive += (eltime/1000);
				if(this.time_alive < this.death_time){
					//console.log(this.time_alive);
					for(var k = 0; k<this.pixel_count; k++){
						context.fillStyle = 'white';
						context.fillRect(this.pixelAr[k].px_pos,this.pixelAr[k].py_pos,this.width/20,this.height/20);
						context.strokeStyle = 'red';
						context.strokeRect(this.pixelAr[k].px_pos,this.pixelAr[k].py_pos,this.width/20,this.height/20);
					}
				}
				else{
					this.complete = true;
					this.pixelAr.length = 0;
				}
			}			
		}
	}

	let ready = false;
	let image = new Image();
	image.onload = function() { 
		ready = true;
	};

	let ballScore = 0;
	let currentScore = {
		score: 0,
		x_position: 0,
		y_position: 0,
		drawMe: function(){
			context.font = "40px Arial";
			context.fillStyle = 'white';
			context.fillText('Score: ' + this.score,this.x_position,this.y_position);
		}
	};

	let temp_margin = canvas.width/420;
	let temp_width = canvas.width/21;
	let temp_height = (((temp_width - temp_margin)/4));
	let n_h_bricks = Math.floor(canvas.height/temp_width) - 2;
	let s_temp_width = temp_height*2;
	let s_temp_height = temp_width;
	let breakblockxstart = (temp_margin*3/2) + s_temp_width;
	let breakblockystart = (temp_margin*(3/2)) + 2*(s_temp_height + (temp_margin/2));
	
// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	function GameBoard(input){
		let that = {};
		//currentScore.score = localStorage.getItem('currentHighScoreBreakout');

		function configureBackgroundImage(){
			image.src = input.image;
		}
		configureBackgroundImage();		

		function buildBorderWalls(){
			for(var i = 0; i < 20; i++){
				let newWall = Object.create(blockWalls);
				newWall.x_start = (temp_margin/2) + (i*(temp_width+temp_margin));
				newWall.y_start = (temp_margin/2);
				newWall.width = temp_width;
				newWall.height = temp_height*2;
				newWall.isNorthWall = true;
				nwe_Walls.push(newWall);
			}
	
			// Build west Walls
			for(var i = 0; i < n_h_bricks; i++){
				let newWall = Object.create(blockWalls);
				newWall.x_start = (temp_margin/2);
				newWall.y_start = ((temp_margin*(3/2)) + (s_temp_width) + (i*(s_temp_height+temp_margin)));
				newWall.width = s_temp_width;
				newWall.height = s_temp_height;
				newWall.isWestWall = true;
				nwe_Walls.push(newWall);
			}
	
			// Build East walls
			for(var i = 0; i < n_h_bricks; i++){
				let newWall = Object.create(blockWalls);
				newWall.x_start = canvas.width - (temp_margin/2) - s_temp_width;
				newWall.y_start = ((temp_margin*(3/2)) + (s_temp_width) + (i*(s_temp_height+temp_margin)));
				newWall.width = s_temp_width;
				newWall.height = s_temp_height;
				newWall.isEastWall = true;
				nwe_Walls.push(newWall);
			}
		}
		buildBorderWalls();

		function configurePaddle(){
			paddle.width = temp_width*2*(5);
			paddle.height = temp_height;
			paddle.x_minimum = temp_margin/2;
			paddle.x_maximum = canvas.width - (temp_margin/2);
			paddle.y_position = (temp_margin*(3/2)) + (temp_height*2) + (n_h_bricks)*(s_temp_height + temp_margin);
			paddle.x_position = temp_margin/2;
		}
		configurePaddle();

		function configureBall(){
			let newBall = Object.create(ball);
			newBall.x_position = paddle.x_position + (paddle.width/2);
			newBall.y_position = paddle.y_position - newBall.radius*3;
			newBall.north_wall = (temp_margin*(3/2)) + temp_height*2;
			newBall.south_wall = (canvas.height)
			newBall.west_wall = (temp_margin*(3/2)) + s_temp_width;
			newBall.east_wall = canvas.width - newBall.west_wall;
			ball_Array.push(newBall);
		}
		configureBall();

		function buildBreakingWalls(){
			// build the breaking walls
			for(var i = 0; i < 8; i++){
				for(var j = 0; j < 19; j++){
					let newBWall = Object.create(breakBlocks);
					newBWall.x_start = breakblockxstart + (j*(temp_width + temp_margin));
					newBWall.y_start = breakblockystart + (i*((2*temp_height)+(temp_margin)));
					newBWall.width = temp_width;
					newBWall.height = temp_height*2;
					newBWall.exists = true;
					newBWall.pixelAr = [];

					for(var k = 0; k<newBWall.pixel_count; k++){
						//console.log(newBWall.x_start,newBWall.y_start);
						let newPixel = Object.create(pixel);
						newPixel.px_pos = (newBWall.x_start + (newBWall.width/2));
						newPixel.py_pos = (newBWall.y_start + (newBWall.height/2));
						newPixel.pwidth = newBWall.width/20;
						newPixel.pheight = newBWall.height/20;
						newPixel.pvx = (Math.random()*(2) - 1)/1000;
						newPixel.pvy = (Math.random()*(2) - 1)/1000;
						newBWall.pixelAr.push(newPixel);
					}

					if(i % 2 == 0){
						newBWall.isBottomRow = false;
					}
					if(i < 8){
						newBWall.color = 'yellow';
					}
					if(i < 6){
						newBWall.color = 'orange';
					}
					if(i < 4){
						newBWall.color = 'blue';
					}
					if(i < 2){
						newBWall.color = 'green';
					}
					bBlocksArr.push(newBWall);
				}
			}
		}
		buildBreakingWalls();

		function buildScoreBoard(){
			currentScore.score = 0;
			currentScore.x_position = (canvas.width*.005)
			currentScore.y_position = canvas.height - s_temp_height;
		}
		buildScoreBoard();

		function gameOver(){
			console.log('gameOver!')

			//localStorage.setItem('currentHighScore',currentHighScore);

			let hs1 = localStorage.getItem('currentHighScoreBreakout1');
			let hs2 = localStorage.getItem('currentHighScoreBreakout2');
			let hs3 = localStorage.getItem('currentHighScoreBreakout3');
			let hs4 = localStorage.getItem('currentHighScoreBreakout4');
			let hs5 = localStorage.getItem('currentHighScoreBreakout5');

			let cur = currentScore.score;
			console.log('score', cur,hs1);

			for(var i = 0; i<1; i++){
				if(cur > hs1){
					hs5 = hs4;
					hs4 = hs3;
					hs3 = hs2;
					hs2 = hs1;
					hs1 = cur;
					break;
				}
				if(cur > hs2){
					hs5 = hs4;
					hs4 = hs3;
					hs3 = hs2;
					hs2 = cur;
					break;
				}
				if(cur > hs3){
					hs5 = hs4;
					hs4 = hs3;
					hs3 = cur;
					break;
				}
				if(cur > hs4){
					hs5 = hs4;
					hs4 = cur;
					break;
				}
				if(cur > hs5){
					hs5 = cur;
					break;
				}
			}
			localStorage.setItem('currentHighScoreBreakout1',hs1);
			localStorage.setItem('currentHighScoreBreakout2',hs2);
			localStorage.setItem('currentHighScoreBreakout3',hs3);
			localStorage.setItem('currentHighScoreBreakout4',hs4);
			localStorage.setItem('currentHighScoreBreakout5',hs5);
			gameEnd = true;
            //location.reload();
		}

		function newPaddle(){
			remainingPaddles -= 1;
			if(remainingPaddles <= -1){
				gameOver();
			}
			if(blocksDestroyed >= 151){
				gameOver();
			}
			// let newBall = Object.create(ball);
			// newBall.x_position = paddle.x_position + (paddle.width/2);
			// newBall.y_position = paddle.y_position - newBall.radius;
			// newBall.north_wall = (temp_margin*(3/2)) + temp_height*2;
			// newBall.south_wall = (canvas.height)
			// newBall.west_wall = (temp_margin*(3/2)) + s_temp_width;
			// newBall.east_wall = canvas.width - newBall.west_wall;
			// newBall.speed_x = 0*canvas.width;
			// newBall.speed_y = 0*canvas.height;
			// ball_Array.push(newBall);
			configurePaddle();
			configureBall();
			countTimer = 3;
			showCountScreen = true;

			isTopRowHit = false;

		}

// ************************************************ MEMBER FUNCTIONS ******************************************

		that.moveLeft = function() {
			if(!showCountScreen){
				paddle.try_move_left();
			}
		}

		that.moveRight = function() {
			if(!showCountScreen){
				paddle.try_move_right();
			}
		}

		that.reset = function(){
			location.reload();
		}

		that.update = function(eltime){
			// if(!topIsBroken){
			// 	for(var i = 0;i<19;i++){
			// 		if(!bBlocksArr[i].exists){
			// 			topIsBroken = true;
			// 			paddle.width = paddle.width/2;
			// 			break;
			// 		}
			// 	}
			// }
			if(!showCountScreen && !gameEnd){
				if(blocksDestroyed >= 153){
					gameOver();
				}

				for(var i = 0; i < ball_Array.length; i++){
					ball_Array[i].updateMe();
				}
				//ball.updateMe();
				if(ballScore >= 100){
					ballScore = ballScore - 100;
					configureBall();
					// let newBall = Object.create(ball);
					// newBall.x_position = paddle.x_position + (paddle.width/2);
					// newBall.y_position = paddle.y_position - newBall.radius;
					// newBall.north_wall = (temp_margin*(3/2)) + temp_height*2;
					// newBall.south_wall = (canvas.height)
					// newBall.west_wall = (temp_margin*(3/2)) + s_temp_width;
					// newBall.east_wall = canvas.width - newBall.west_wall;
					// newBall.speed_x = ballSpeedMultiplier*canvas.width;
					// newBall.speed_y = ballSpeedMultiplier*canvas.height;
					// ball_Array.push(newBall);
				}
				for(var iball = ball_Array.length - 1; iball >= 0; iball-- ){
					if(ball_Array[iball].y_position > canvas.height){
						ball_Array.splice(iball,1);
					}
				}
				if(ball_Array.length == 0){
					newPaddle();
					//console.log('You have reached the zero!');
				}
			}


		}

		that.addBall = function(){
			let newBall = Object.create(ball);
			newBall.x_position = paddle.x_position + (paddle.width/2);
			newBall.y_position = paddle.y_position - newBall.radius;
			newBall.north_wall = (temp_margin*(3/2)) + temp_height*2;
			newBall.south_wall = (canvas.height)
			newBall.west_wall = (temp_margin*(3/2)) + s_temp_width;
			newBall.east_wall = canvas.width - newBall.west_wall;
			newBall.speed_x = ballSpeedMultiplier*canvas.width;
			newBall.speed_y = ballSpeedMultiplier*canvas.height;
			ball_Array.push(newBall);
		}


		that.draw = function(eltime) {
			if(!gameEnd){
				if (ready) {
					context.save();
					context.globalAlpha = 1.0;
					context.drawImage(image,0,0,canvas.width,canvas.height);
					context.restore();
				}
	
				for(var i = 0; i < nwe_Walls.length; i++){
					nwe_Walls[i].drawMe();
				}
				for(var i = 0; i < bBlocksArr.length; i++){
					bBlocksArr[i].drawMe();
					if(!bBlocksArr[i].exists && !bBlocksArr[i].complete){
						//console.log('inside here');
						bBlocksArr[i].blowUp(eltime);
					}
				}
				paddle.drawMe();
				for(var i = 0; i < ball_Array.length; i++){
					ball_Array[i].drawMe();
				}
				//ball.drawMe();
				context.stroke();
				currentScore.drawMe();
	
				for(var ipaddle = 0; ipaddle < remainingPaddles+1; ipaddle++){
					context.fillStyle = 'orange';
					context.fillRect( .8*canvas.width, canvas.height - (ipaddle*temp_height*2), temp_width*3, temp_height);
					context.strokeStyle = 'green';
					context.strokeRect( .8*canvas.width, canvas.height - (ipaddle*temp_height*2), temp_width*3, temp_height);
				}
				
				if(showCountScreen){
					if(countTimer < 1){
						showCountScreen = false;
						ball_Array[0].speed_x = ballSpeedMultiplier*canvas.width;
						ball_Array[0].speed_y = -ballSpeedMultiplier*canvas.height;
						return;
					}
					context.font = "120px Arial";
					context.fillStyle = 'red';
					context.fillText(((countTimer).toFixed(0)),canvas.width/2,canvas.height/2);
					countTimer = countTimer - (eltime/1000);
				}


			}
			else{
				context.font = "20px Arial";
				context.fillStyle = 'red';
				var stringout = 'GAME OVER! YOUR SCORE WAS:';
				stringout = stringout + currentScore.score;
				stringout += ' PRESS n OR esc TO RETURN.'
				context.fillText(stringout,0,canvas.height/2);				
			}
			
			
		}








		return that;
	}
	


	
				

	return {
		clear : clear,
		GameBoard : GameBoard
	};
}());
