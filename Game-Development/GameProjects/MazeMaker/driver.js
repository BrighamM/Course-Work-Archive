let previousTime = 0;


LabyrinthGame.main = (function(graph_log){



  // Grab the button and form.
  var mazeButton = document.getElementById('maze_button');
  var mazeForm = document.getElementById('maze_form');
  var button_clicked = false;
  //var main_name = '';
  var main_input_grid_size = -1;
  var main_input_mga = -1;
  var myLabyrinthSet = {};
  var myPawn = {};
  var key_events = [];
  var keyDown_Events = {
      '87': function(){
        myLabyrinthSet.movePlayer(0);
      },
      '83': function(){
        myLabyrinthSet.movePlayer(1);
      },
      '65': function(){
        myLabyrinthSet.movePlayer(2);
      },
      '68': function(){
        myLabyrinthSet.movePlayer(3);
      },
      '38': function(){
        myLabyrinthSet.movePlayer(0);
      },
      '40': function(){
        myLabyrinthSet.movePlayer(1);
      },
      '37': function(){
        myLabyrinthSet.movePlayer(2);
      },
      '39': function(){
        myLabyrinthSet.movePlayer(3);
      },
      '73': function(){
        myLabyrinthSet.movePlayer(0);
      },
      '75': function(){
        myLabyrinthSet.movePlayer(1);
      },
      '74': function(){
        myLabyrinthSet.movePlayer(2);
      },
      '76': function(){
        myLabyrinthSet.movePlayer(3);
      },
      '72': function(){
        console.log('enable hint');
        myLabyrinthSet.toggleHint();
      },
      '66': function(){
        console.log('enable breadCrumbs');
        myLabyrinthSet.toggleBreadCrumbs();
      },
      '80': function(){
        console.log('Path to finish');
        myLabyrinthSet.toggleFinishPath();
      },
      '89': function(){
        console.log('score toggle!');
        myLabyrinthSet.toggleShowScore();
      },
      '78': function(){
        console.log('new game!');
        myLabyrinthSet.startNewGame();
      }
  };
  // Make sure that the onsubmit for the form returns false.
  mazeForm.onsubmit = function() {
    return false;
  };

  mazeButton.onclick = function runthis22(){
    if(!button_clicked){
        //main_name = document.getElementById('user_name').value;
        main_input_grid_size = document.querySelector('input[name="grid-size"]:checked').value;
        main_input_mga = document.querySelector('input[name="mga"]:checked').value;
        button_clicked = true;
        mazeForm.parentNode.removeChild(mazeForm);

        myLabyrinthSet = graph_log.LabyrinthSet({
            background_image: './images/background.png',
            end_image: './images/endRing.png',
            player_image: './images/player.png',
            path_finder: './images/path1.png',
            bread_crumb: './images/breadcrumb.png',
            grid_size: main_input_grid_size,
            MazeGenAlg: main_input_mga
        });
        //myLabyrinthSet.draw();
        previousTime = performance.now();
        requestAnimationFrame(gameLoop);
    }
};





    function processInput(elapsedTime) {
      for(var icount = 0; icount < key_events.length; icount++){
        keyDown_Events[key_events[icount]]();
      }
      key_events.length = 0;
    }
      
    function update(elapsedTime) {
    }
      
    function render(elapsedTime) {
        graph_log.clear();
        if(!myLabyrinthSet.isGameOver()){
          myLabyrinthSet.drawLabyrinth();
          myLabyrinthSet.drawBreadCrumbs();
          myLabyrinthSet.drawFinishPath();
          myLabyrinthSet.drawSingleHint();
          myLabyrinthSet.drawTime(elapsedTime);
          myLabyrinthSet.drawPawns();
        }
        else{
          myLabyrinthSet.drawCreditsAndUIBoard();
        }
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

    console.log('game initializing...');
    //requestAnimationFrame(gameLoop); 

    document.onkeydown = function checkey(e){
        e = e || window.event;
        if([37,38,39,40].indexOf(e.keyCode) > -1){
            e.preventDefault();
        }
        if(keyDown_Events.hasOwnProperty(e.keyCode)){
            key_events.push(e.keyCode);
        }
    }
   

}(LabyrinthGame.graph_log));