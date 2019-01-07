MyGame.graphics = (function(components) {
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
	};



	let order_counter = 1;



	let block_cell = {
		is_snake : false,
		is_obstacle : false,
		is_arena : false,
		is_borderwall : false,
		is_food : false,
		body_order : 0,
		width : 0,
		height : 0,
		start_x : 0,
		start_y : 0,
		index_i : 0,
		index_j : 0,
		drawMe : function(){
			if(this.is_snake){
				//console.log('are we in here?');
				let fraction = .1;
				context.fillStyle = 'black';
				context.fillRect(this.start_x, this.start_y, this.width, this.height);
				context.fillStyle = 'white';
				context.fillRect(this.start_x + (fraction*this.width), this.start_y + (fraction*this.height), 
				this.width - (fraction*this.width), this.height - (fraction*this.height));
				//context.strokeStyle = 'red';
				//context.strokeRect(this.start_x, this.start_y, this.width, this.height);
			}
			if(this.is_borderwall){
				let fraction = .1;
				context.fillStyle = 'black';
				context.fillRect(this.start_x, this.start_y, this.width, this.height);
				context.fillStyle = 'red';
				context.fillRect(this.start_x + (fraction*this.width), this.start_y + (fraction*this.height), 
				this.width - (fraction*this.width), this.height - (fraction*this.height));
			}
			if(this.is_arena){
				let fraction = .1;
				context.fillStyle = 'blue';
				context.fillRect(this.start_x, this.start_y, this.width, this.height);
			}
			if(this.is_obstacle){
				let fraction = .1;
				context.fillStyle = 'black';
				context.fillRect(this.start_x, this.start_y, this.width, this.height);
				context.fillStyle = 'green';
				context.fillRect(this.start_x + (fraction*this.width), this.start_y + (fraction*this.height), 
				this.width - (fraction*this.width), this.height - (fraction*this.height));
			}
			if(this.is_food){
				let fraction = .1;
				context.fillStyle = 'black';
				context.fillRect(this.start_x, this.start_y, this.width, this.height);
				context.fillStyle = 'orange';
				context.fillRect(this.start_x + (fraction*this.width), this.start_y + (fraction*this.height), 
				this.width - (fraction*this.width), this.height - (fraction*this.height));
			}

		},
		updateMe : function(){

		}

	};

	let block_cell_array = [];
	

	let snake = {
		direction : '',
		previous_direction : '',
		delay_master : 0,
		delay : 0,
		head_i : 0,
		head_j : 0,
		tail_i : 0,
		tail_j : 0,
		validmove : function(){
			if(this.direction == 'up'){
				let tempblock = block_cell_array[this.head_i-1][this.head_j];
				if(tempblock.is_borderwall || tempblock.is_obstacle || tempblock.is_snake){
					return false;
				}

				

				if(tempblock.is_food){
					tempblock.is_food = false;
					tempblock.is_snake = true;
					currentScore++;
					this.delay_master = this.delay_master + 3;
					is_food_eaten = true;
				}

				snake.head_i = this.head_i-1;
				snake.head_j = this.head_j;
				tempblock.body_order = order_counter;
				order_counter++;
				this.consumeTail();


				tempblock.is_snake = true;
				tempblock.is_arena = false;
				tempblock.is_borderwall = false;
				tempblock.is_food = false;
				tempblock.is_obstacle = false;

				return true;
				


			}
			if(this.direction == 'right'){
				let tempblock = block_cell_array[this.head_i][this.head_j+1];
				if(tempblock.is_borderwall || tempblock.is_obstacle || tempblock.is_snake){
					return false;
				}

				if(tempblock.is_food){
					tempblock.is_food = false;
					tempblock.is_snake = true;
					currentScore++;
					this.delay_master = this.delay_master + 3;
					is_food_eaten = true;
				}

				snake.head_i = this.head_i;
				snake.head_j = this.head_j+1;
				tempblock.body_order = order_counter;
				order_counter++;
				this.consumeTail();

				tempblock.is_snake = true;
				tempblock.is_arena = false;
				tempblock.is_borderwall = false;
				tempblock.is_food = false;
				tempblock.is_obstacle = false;

				return true;

			}
			if(this.direction == 'left'){
				let tempblock = block_cell_array[this.head_i][this.head_j-1];
				if(tempblock.is_borderwall || tempblock.is_obstacle || tempblock.is_snake){
					return false;
				}
				

				if(tempblock.is_food){
					tempblock.is_food = false;
					tempblock.is_snake = true;
					currentScore++;
					this.delay_master = this.delay_master + 3;
					is_food_eaten = true;
				}

				snake.head_i = this.head_i;
				snake.head_j = this.head_j-1;
				tempblock.body_order = order_counter;
				order_counter++;
				this.consumeTail();

				tempblock.is_snake = true;
				tempblock.is_arena = false;
				tempblock.is_borderwall = false;
				tempblock.is_food = false;
				tempblock.is_obstacle = false;

				return true;

			}
			if(this.direction == 'down'){
				let tempblock = block_cell_array[this.head_i+1][this.head_j];
				if(tempblock.is_borderwall || tempblock.is_obstacle || tempblock.is_snake){
					return false;
				}

				if(tempblock.is_food){
					tempblock.is_food = false;
					tempblock.is_snake = true;
					currentScore++;
					this.delay_master = this.delay_master + 3;
					is_food_eaten = true;
				}

				snake.head_i = this.head_i+1;
				snake.head_j = this.head_j;
				tempblock.body_order = order_counter;
				order_counter++;
				this.consumeTail();
				tempblock.is_snake = true;
				tempblock.is_arena = false;
				tempblock.is_borderwall = false;
				tempblock.is_food = false;
				tempblock.is_obstacle = false;

				return true;
			}


		},
		consumeTail : function(){
			// move the tail in the direction of the body based on delays
			if(this.delay_master <= 0){
				// Consume the tail  with the smallest body order counter out right

				// set the top
				let minBlock = block_cell_array[this.tail_i - 1][this.tail_j];

				// check bottom 
				if(block_cell_array[this.tail_i + 1][this.tail_j].body_order < minBlock.body_order){
					minBlock = block_cell_array[this.tail_i + 1][this.tail_j];
				}

				// check left
				if(block_cell_array[this.tail_i][this.tail_j - 1].body_order < minBlock.body_order){
					minBlock = block_cell_array[this.tail_i][this.tail_j - 1];
				}

				// check right
				if(block_cell_array[this.tail_i][this.tail_j + 1].body_order < minBlock.body_order){
					minBlock = block_cell_array[this.tail_i][this.tail_j + 1];
				}

				// Now we have min block.

				// delete the tail, 
				let deleteBlock = block_cell_array[this.tail_i][this.tail_j]

				deleteBlock.is_snake = false;
				deleteBlock.is_arena = true;
				deleteBlock.body_order = 999999999;

				this.tail_i = minBlock.index_i;
				this.tail_j = minBlock.index_j;
				

				return;
			}
			this.delay_master = this.delay_master -1;

		}
	};

	let should_update = false;
	let move_timer = 0;


	let gameEnd = false;
	let currentScore = 0;
	let showCountScreen = true;
	let countTimer = 3;
	let is_food_eaten = false;










	function GameBoard(spec) {
		let that = {};

		let block_width = canvas.width/spec.size;
		let block_height = canvas.height/spec.size;

		// set up the arena!

		function SetUpTheArena(){
			for(var i = 0; i < spec.size; i++){
				let temparr = [];
				block_cell_array.push(temparr);
				for(var j = 0; j < spec.size; j++){
					let newBlock = Object.create(block_cell);
					newBlock.is_snake = false;
					newBlock.is_obstacle = false;
					newBlock.is_arena = true;
					newBlock.is_borderwall = false;
					newBlock.is_food = false;
					newBlock.body_order = 999999999;
					if(i == 0 || j == 0){
						newBlock.is_borderwall = true;
						newBlock.is_snake = false;
						newBlock.is_obstacle = false;
						newBlock.is_arena = false;
						newBlock.is_food = false;
					}
					if(i == (spec.size - 1) || j == (spec.size - 1)){
						newBlock.is_borderwall = true;
						newBlock.is_snake = false;
						newBlock.is_obstacle = false;
						newBlock.is_arena = false;
						newBlock.is_food = false;
					}
					newBlock.width = block_width;
					newBlock.height = block_height;
					newBlock.start_x = j*block_width;
					newBlock.start_y = i*block_height;
					newBlock.index_i = i;
					newBlock.index_j = j;
					block_cell_array[i][j] = newBlock;
				}
			
				// block_cell_array.push(temparr);
				// temparr.length = 0;
			}
			//console.log(block_cell_array[5][5]);

			// Randomly place 15 obstacles.
			let obstacle_count = 0;
			while(obstacle_count < 15){
				let random_numberi = Math.floor(Math.random() * (spec.size));
				let random_numberj = Math.floor(Math.random() * (spec.size));
				if(block_cell_array[random_numberi][random_numberj].is_arena){
					block_cell_array[random_numberi][random_numberj].is_arena = false;	
					block_cell_array[random_numberi][random_numberj].is_obstacle = true;
					obstacle_count++;
				}
			}

		}
		SetUpTheArena();

		// pick a starting location for the snake head.
		function SetUpTheSnake(){
			let head_found = false;
			while(!head_found){
				let random_numberi = Math.floor(Math.random() * (spec.size));
				let random_numberj = Math.floor(Math.random() * (spec.size));
				if(block_cell_array[random_numberi][random_numberj].is_arena){
					block_cell_array[random_numberi][random_numberj].is_arena = false;	
					block_cell_array[random_numberi][random_numberj].is_snake = true;
					block_cell_array[random_numberi][random_numberj].body_order = order_counter;
					order_counter++;
					snake.direction = '';
					snake.delay_master = 0;
					snake.delay = 1;
					snake.head_i = random_numberi;
					snake.head_j = random_numberj;
					snake.tail_i = snake.head_i;
					snake.tail_j = snake.head_j;
					head_found = true;
				}
			}
		}
		SetUpTheSnake();

		function SetUpTheFood(){
			let food_found = false;
			while(!food_found){
				let random_numberi = Math.floor(Math.random() * (spec.size));
				let random_numberj = Math.floor(Math.random() * (spec.size));
				if(block_cell_array[random_numberi][random_numberj].is_arena){
					block_cell_array[random_numberi][random_numberj].is_arena = false;	
					block_cell_array[random_numberi][random_numberj].is_food = true;
					food_found = true;
				}
			}
		}
		SetUpTheFood();






		function gameOver(){
			console.log('gameOver!')

			//localStorage.setItem('currentHighScore',currentHighScore);

			let hs1 = localStorage.getItem('currentHighScoreSnake1');
			let hs2 = localStorage.getItem('currentHighScoreSnake2');
			let hs3 = localStorage.getItem('currentHighScoreSnake3');
			let hs4 = localStorage.getItem('currentHighScoreSnake4');
			let hs5 = localStorage.getItem('currentHighScoreSnake5');

			let cur = currentScore;
			console.log('score', cur, hs1);

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
			localStorage.setItem('currentHighScoreSnake1',hs1);
			localStorage.setItem('currentHighScoreSnake2',hs2);
			localStorage.setItem('currentHighScoreSnake3',hs3);
			localStorage.setItem('currentHighScoreSnake4',hs4);
			localStorage.setItem('currentHighScoreSnake5',hs5);
			gameEnd = true;
            //location.reload();
		}


		//*************************MEMBER FUNCTIONS


		that.update = function(elapsedTime) {
			if(!showCountScreen && !gameEnd){
				move_timer = move_timer + (elapsedTime);
				//console.log('are we in here');
				if(should_update){
					//console.log('are we in here', move_timer);
					// We should move the snake head in the snake.direction
					if(move_timer > 150){
						
						//snake.validmove();
						if(!snake.validmove()){
							gameOver();
						}
						if(is_food_eaten){
							SetUpTheFood();
							is_food_eaten = false;
						}
						move_timer = 0;
					}
					
				}

			}


		}
		that.moveLeft = function(){
			//console.log('left');
		
			should_update = true;
			if(snake.direction != 'right'){
				snake.direction = 'left';
			}
			


		}
		that.moveRight = function(){
			//console.log('right');
			should_update = true;
			if(snake.direction != 'left'){
				snake.direction = 'right';
			}



		}
		that.moveUp = function(){
			//console.log('up');
			should_update = true;
			if(snake.direction != 'down'){
				snake.direction = 'up';
			}
			


		}
		that.moveDown = function(){
			//console.log('down');
			should_update = true;
			if(snake.direction != 'up'){
				snake.direction = 'down'
			}
			


		}

		that.draw = function(elapsedTime){

			if(!gameEnd){
	
				if(showCountScreen){
					if(countTimer < 1){
						showCountScreen = false;
						return;
					}
					context.font = "120px Arial";
					context.fillStyle = 'red';
					context.fillText(((countTimer).toFixed(0)),canvas.width/2,canvas.height/2);
					countTimer = countTimer - (elapsedTime/1000);
				}
				else{
					for(var i = 0; i < spec.size; i++){
						for(var j = 0; j < spec.size; j++){
							block_cell_array[i][j].drawMe();
						}
					}
				}


			}
			else{
				context.font = "20px Arial";
				context.fillStyle = 'red';
				var stringout = 'GAME OVER! YOUR SCORE WAS:';
				stringout = stringout + currentScore;
				stringout += ' PRESS esc TO RETURN.'
				context.fillText(stringout,0,canvas.height/2);				
			}












		}
		
		return that;
	}

	function ScoreBoard(spec) {
		let that = {};
		let startx = canvas.width - ((1/7)*canvas.width);
		let starty = (1/7)*canvas.height;
		let startTime = 0;
		let score = 0

		that.draw = function(elapsedTime){
			startTime += elapsedTime/1000.;
			context.font = "50px Arial";
			context.fillStyle = 'red';
			context.fillText(((startTime).toFixed(2)),startx,starty);
			//context.stroke();
			//console.log(startTime);
			//countTimer = countTimer - (eltime/1000);
		}
		return that;
	}


	return {
		clear : clear,
		GameBoard : GameBoard
	};
}(MyGame.components));
