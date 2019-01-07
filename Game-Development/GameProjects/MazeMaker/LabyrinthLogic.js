LabyrinthGame.graph_log = (function(){
    'use strict';

    
    let canvas = document.getElementById('canvas-main');
    let context = canvas.getContext('2d');
    document.body.style.backgroundColor = "grey";

    canvas.width = document.body.clientWidth; //document.width is obsolete
    canvas.height = document.body.clientHeight; //document.height is obsolete

    let maze_Canvas_Dimensions = {
        start_offsetX: .02*canvas.width,
        start_offsetY: .02*canvas.height,
        width: canvas.width*.6,
        height: canvas.height*.70,
    };

    let maxNumber = Math.pow(10, 1000);

    let score_And_Time = {
        time: 0,
        score: 0,
    };




    // ****************************************LABYRINTH VARIABLES**************************************
    let maze_Cell_Dimensions = {
        xWidth: 0,
        yHeight: 0,
    };

    let maze_Wall = {
        rowStart: -1,
        colStart: -1,
        rowEnd: -1,
        colEnd: -1,
        wall_id: -1,
        is_intact: true
    };
    let wall_Array = [];

    let maze_Cell = {
        row: -1,
        col: -1,
        is_SP_Cell: false,
        is_BreadCrumb: false,
        is_Hint: false,
        id: -1,
        hasNorthWall: true,
        hasSouthWall: true,
        hasWestWall: true,
        hasEastWall: true,
        shortest_distance_from_player: maxNumber,
        is_Current: false,
        has_been_visited: false,
        has_been_scored: false,

        drawMe: function(){
            let xstart = maze_Canvas_Dimensions.start_offsetX + (this.col)*maze_Cell_Dimensions.xWidth;
            let ystart = maze_Canvas_Dimensions.start_offsetY + (this.row)*maze_Cell_Dimensions.yHeight;
            context.beginPath();
            context.moveTo(xstart,ystart);
            if(this.hasNorthWall){
                context.lineTo(xstart + maze_Cell_Dimensions.xWidth,ystart);
            }
            context.moveTo(xstart + maze_Cell_Dimensions.xWidth,ystart);
            if(this.hasEastWall){
                context.lineTo(xstart + maze_Cell_Dimensions.xWidth,ystart + maze_Cell_Dimensions.yHeight);               
            }
            context.moveTo(xstart + maze_Cell_Dimensions.xWidth,ystart + maze_Cell_Dimensions.yHeight);
            if(this.hasSouthWall){
                context.lineTo(xstart,ystart + maze_Cell_Dimensions.yHeight);
            }
            context.moveTo(xstart,ystart + maze_Cell_Dimensions.yHeight);
            if(this.hasWestWall){
                context.lineTo(xstart,ystart);
            }
            context.moveTo(xstart,ystart);
            context.stroke();
        },

        showCrumb: function(){
            if(this.is_BreadCrumb){
                let xstart = maze_Canvas_Dimensions.start_offsetX + (this.col)*maze_Cell_Dimensions.xWidth;
                let ystart = maze_Canvas_Dimensions.start_offsetY + (this.row)*maze_Cell_Dimensions.yHeight;
                if (bread_Crumb_Image_Flag) {
                    context.save();
                    context.translate(xstart, ystart);
                    context.translate(-xstart, -ystart);
                    context.drawImage(bread_Crumb_Image,xstart, ystart,marker_Width,marker_Height);
                    context.restore();
                }

            }

        },

        showPath: function(){
            if(this.is_SP_Cell){
                let xstart = maze_Canvas_Dimensions.start_offsetX + (this.col)*maze_Cell_Dimensions.xWidth;
                let ystart = maze_Canvas_Dimensions.start_offsetY + (this.row)*maze_Cell_Dimensions.yHeight;
                if (path_Image_Flag) {
                    context.save();
                    context.translate(xstart, ystart);
                    context.translate(-xstart, -ystart);
                    context.drawImage(path_Image,xstart + (maze_Cell_Dimensions.xWidth/2)
                    ,ystart + (maze_Cell_Dimensions.yHeight/2),marker_Width*(.75),marker_Height*(.75));
                    context.restore();
                }
            }
        },

        showHint: function(){
            if(this.is_SP_Cell){
                let xstart = maze_Canvas_Dimensions.start_offsetX + (this.col)*maze_Cell_Dimensions.xWidth;
                let ystart = maze_Canvas_Dimensions.start_offsetY + (this.row)*maze_Cell_Dimensions.yHeight;
                if (path_Image_Flag) {
                    context.save();
                    context.translate(xstart, ystart);
                    context.translate(-xstart, -ystart);
                    context.drawImage(path_Image,xstart ,ystart ,marker_Width,marker_Height);
                    context.restore();
                }
            }

        },


    };
    let maze_Cell_Matrix = [];

    // Global toggling bools for varied functionality
    let showMazeCrumbs = false;
    let showMazePath = false;
    let showSingleHint = false;
    let showScore = true;
    let master_Game_Over = false;
    let master_Game_Won = false;
    let currentHighScore = maxNumber*(-1);

    // Marker variables
    let marker_Width = 0;
    let marker_Height = 0;
    let player_marker_startx = 0;
    let player_marker_starty = 0;
    let finish_Marker_x_pos = 0;
    let finish_Marker_y_pos = 0;
    let current_Player_x_pos = 0;
    let current_Player_y_pos = 0;
    let current_Player_Cell_Row = 0;
    let current_Player_Cell_Col = 0;
    let current_Finish_Cell_Row = 0;
    let current_Finish_Cell_Col = 0;

    // Variables for finding the shortest path
    let shortest_Path_Queue = [];
    let temp_shortest_path_cell = {};
    let cur_Row_for_short_path = -1;
    let cur_Col_for_short_path = -1;
    let shortest_path_value_incr = maxNumber;
    let rev_Cur_Fin_Row = -1;
    let rev_Cur_Fin_Col = -1;
    let rev_Min_Path_Val = maxNumber;



    //  Variables for the images
    let goal_Image_Flag = false;
    let goal_Image = new Image();
    goal_Image.onload = function() { 
        goal_Image_Flag = true;
    };

    let player_Image_Flag = false;
    let player_Image = new Image();
    player_Image.onload = function() { 
        player_Image_Flag = true;
    };

    let path_Image_Flag = false;
    let path_Image = new Image();
    path_Image.onload = function() { 
        path_Image_Flag = true;
    };
    
    let bread_Crumb_Image_Flag = false;
    let bread_Crumb_Image = new Image();
    bread_Crumb_Image.onload = function() { 
        bread_Crumb_Image_Flag = true;
    };

    let background_Image_Flag = false;
    let background_Image = new Image();
    background_Image.onload = function(){
        background_Image_Flag = true;
    }


    // Clear function for the main canvas
    function clear() {
        context.save();
        context.setTransform(1, 0, 0, 1, 0, 0);
        context.clearRect(0, 0, canvas.width, canvas.height);
        context.restore();
    }

    function LabyrinthSet(datum) {
        let that = {};
        //currentHighScore = sessionStorage.getItem('currentHighScore');
        currentHighScore = localStorage.getItem('currentHighScore');

        // With the input size we can set the dimensions of the maze cells.
        maze_Cell_Dimensions.xWidth = maze_Canvas_Dimensions.width/datum.grid_size;
        maze_Cell_Dimensions.yHeight = maze_Canvas_Dimensions.height/datum.grid_size;

        marker_Width = maze_Cell_Dimensions.xWidth*.75;
        marker_Height = maze_Cell_Dimensions.yHeight*.75;

        player_marker_startx = maze_Canvas_Dimensions.start_offsetX + (.125*maze_Cell_Dimensions.xWidth);
        player_marker_starty = maze_Canvas_Dimensions.start_offsetY + (.125*maze_Cell_Dimensions.yHeight);

        finish_Marker_x_pos = player_marker_startx + (maze_Canvas_Dimensions.width - maze_Cell_Dimensions.xWidth);
        finish_Marker_y_pos = player_marker_starty + (maze_Canvas_Dimensions.height - maze_Cell_Dimensions.yHeight);

        current_Player_x_pos = player_marker_startx;
        current_Player_y_pos = player_marker_starty;
        
        current_Player_Cell_Row = 0;
        current_Player_Cell_Col = 0;

        current_Finish_Cell_Row = datum.grid_size - 1;
        current_Finish_Cell_Col = datum.grid_size - 1;

        
        goal_Image.src = datum.end_image;
        player_Image.src = datum.player_image;
        path_Image.src = datum.path_finder;
        bread_Crumb_Image.src = datum.bread_crumb;
        background_Image.src = datum.background_image;

        
        function build_Walls_and_Make_Order_Random(){
            for (var irow = 0;irow<datum.grid_size;irow++){
                for (var jcol = 0;jcol<datum.grid_size - 1;jcol++){
                    let new_Maze_Wall = Object.create(maze_Wall);
                    new_Maze_Wall.rowStart = irow;
                    new_Maze_Wall.colStart = jcol;
                    new_Maze_Wall.rowEnd = irow;
                    new_Maze_Wall.colEnd = jcol + 1;
                    new_Maze_Wall.wall_id = wall_Array.length;
                    new_Maze_Wall.is_intact = true;
                    wall_Array.push(new_Maze_Wall);
                }
            }
            for (var irow = 0;irow<datum.grid_size - 1;irow++){
                for (var jcol = 0;jcol<datum.grid_size;jcol++){
                    let new_Maze_Wall = Object.create(maze_Wall);
                    new_Maze_Wall.rowStart = irow;
                    new_Maze_Wall.colStart = jcol;
                    new_Maze_Wall.rowEnd = irow + 1;
                    new_Maze_Wall.colEnd = jcol;
                    new_Maze_Wall.wall_id = wall_Array.length;
                    new_Maze_Wall.is_intact = true;
                    wall_Array.push(new_Maze_Wall);
                }
            }
            function shuffle(array) {
                var currentIndex = array.length, temporaryValue, randomIndex;
                while (0 !== currentIndex) {
                  randomIndex = Math.floor(Math.random() * currentIndex);
                  currentIndex -= 1;
                  temporaryValue = array[currentIndex];
                  array[currentIndex] = array[randomIndex];
                  array[randomIndex] = temporaryValue;
                }
                return array;
            }
            wall_Array = shuffle(wall_Array);
            wall_Array = shuffle(wall_Array);
            wall_Array = shuffle(wall_Array);
            wall_Array = shuffle(wall_Array);
            wall_Array = shuffle(wall_Array);
        }
        build_Walls_and_Make_Order_Random();

        function build_Master_Maze_Matrix_with_Logic(){
            let intCount = 0;
            for (var irow = 0; irow<datum.grid_size; irow++){
                //maze_grid.push([]);
                maze_Cell_Matrix.push([]);
                for(var jcol = 0; jcol<datum.grid_size; jcol++){
                    let new_Maze_Cell = Object.create(maze_Cell);
                    new_Maze_Cell.row = irow;
                    new_Maze_Cell.col = jcol;
                    new_Maze_Cell.is_SP_Cell = false;
                    new_Maze_Cell.is_BreadCrumb = false;
                    new_Maze_Cell.is_Hint = false;
                    new_Maze_Cell.id = intCount;
                    new_Maze_Cell.hasNorthWall = true;
                    new_Maze_Cell.hasSouthWall = true;
                    new_Maze_Cell.hasWestWall = true;
                    new_Maze_Cell.hasEastWall = true;
                    new_Maze_Cell.shortest_distance_from_player = maxNumber;
                    new_Maze_Cell.is_Current = false;
                    new_Maze_Cell.has_been_visited = false;
                    new_Maze_Cell.has_been_scored = false;
                    maze_Cell_Matrix[irow].push(new_Maze_Cell);
                    //maze_grid[irow].push(intCount);
                    intCount++;
                }
            }
            // In this loop we are going to draw walls out of the bag in a random order and if 
            // the matrix cells are different on both sides we then dissolve the wall and set
            // the left side equal to the right side.
            // PROCESSING
            for (var e = 0; e<wall_Array.length; e++){
                let master = maze_Cell_Matrix[wall_Array[e].rowStart][wall_Array[e].colStart].id;
                let slave = maze_Cell_Matrix[wall_Array[e].rowEnd][wall_Array[e].colEnd].id;
                if(master != slave) {
                    wall_Array[e].is_intact = false;
                    if(wall_Array[e].rowEnd > wall_Array[e].rowStart){
                        // I am looking at a horizontal wall!
                        maze_Cell_Matrix[wall_Array[e].rowStart][wall_Array[e].colStart].hasSouthWall = false;
                        maze_Cell_Matrix[wall_Array[e].rowEnd][wall_Array[e].colEnd].hasNorthWall = false;
                    }
                    if(wall_Array[e].colEnd > wall_Array[e].colStart){
                        // I am looking at a vertical wall!
                        maze_Cell_Matrix[wall_Array[e].rowStart][wall_Array[e].colStart].hasEastWall = false;
                        maze_Cell_Matrix[wall_Array[e].rowEnd][wall_Array[e].colEnd].hasWestWall = false;                    
                    }
                    // Loop through the original and set the vals.
                    for (var irow = 0;irow<datum.grid_size;irow++){
                        for(var jcol = 0;jcol<datum.grid_size;jcol++){
                           
                            if(maze_Cell_Matrix[irow][jcol].id == slave) {
                                maze_Cell_Matrix[irow][jcol].id = master;
                            }
                            else{
                                continue;
                            }
                        }
                    }
                }
                else{
                    continue;
                }
            }
        }
        build_Master_Maze_Matrix_with_Logic();

        function compute_Shortest_Path_and_Logic(){
            maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].is_Current = true;
            maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].shortest_distance_from_player = 0;
            maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].has_been_visited = true;
    
            shortest_Path_Queue.push(maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col]);
    
            while(shortest_Path_Queue.length > 0){
                temp_shortest_path_cell = shortest_Path_Queue.shift();
                cur_Row_for_short_path = temp_shortest_path_cell.row;
                cur_Col_for_short_path = temp_shortest_path_cell.col;
                shortest_path_value_incr = temp_shortest_path_cell.shortest_distance_from_player + 1;
                if(!maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path].hasSouthWall){
                    if(!maze_Cell_Matrix[cur_Row_for_short_path + 1][cur_Col_for_short_path].has_been_visited){
                        maze_Cell_Matrix[cur_Row_for_short_path + 1][cur_Col_for_short_path].has_been_visited = true;
                        maze_Cell_Matrix[cur_Row_for_short_path + 1][cur_Col_for_short_path].shortest_distance_from_player = shortest_path_value_incr;
                        shortest_Path_Queue.push(maze_Cell_Matrix[cur_Row_for_short_path + 1][cur_Col_for_short_path]);
                    }
                }
                if(!maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path].hasNorthWall){
                    if(!maze_Cell_Matrix[cur_Row_for_short_path - 1][cur_Col_for_short_path].has_been_visited){
                        maze_Cell_Matrix[cur_Row_for_short_path - 1][cur_Col_for_short_path].has_been_visited = true;
                        maze_Cell_Matrix[cur_Row_for_short_path - 1][cur_Col_for_short_path].shortest_distance_from_player = shortest_path_value_incr;
                        shortest_Path_Queue.push(maze_Cell_Matrix[cur_Row_for_short_path - 1][cur_Col_for_short_path]);
                    }
                }
                if(!maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path].hasEastWall){
                    if(!maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path + 1].has_been_visited){
                        maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path + 1].has_been_visited = true;
                        maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path + 1].shortest_distance_from_player = shortest_path_value_incr;
                        shortest_Path_Queue.push(maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path + 1]);
                    }
                }
                if(!maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path].hasWestWall){
                    if(!maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path - 1].has_been_visited){
                        maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path - 1].has_been_visited = true;
                        maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path - 1].shortest_distance_from_player = shortest_path_value_incr;
                        shortest_Path_Queue.push(maze_Cell_Matrix[cur_Row_for_short_path][cur_Col_for_short_path - 1]);
                    }
                }      
            }
    
            rev_Cur_Fin_Row = current_Finish_Cell_Row;
            rev_Cur_Fin_Col = current_Finish_Cell_Col;
            rev_Min_Path_Val = maze_Cell_Matrix[current_Finish_Cell_Row][current_Finish_Cell_Col].shortest_distance_from_player;
            maze_Cell_Matrix[current_Finish_Cell_Row][current_Finish_Cell_Col].is_SP_Cell = true;
    
            while(rev_Min_Path_Val > 0){
                if(!maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col].hasSouthWall){
                    if(maze_Cell_Matrix[rev_Cur_Fin_Row + 1][rev_Cur_Fin_Col].shortest_distance_from_player < rev_Min_Path_Val){
                        maze_Cell_Matrix[rev_Cur_Fin_Row + 1][rev_Cur_Fin_Col].is_SP_Cell = true;
                        rev_Min_Path_Val = maze_Cell_Matrix[rev_Cur_Fin_Row + 1][rev_Cur_Fin_Col].shortest_distance_from_player;
                        rev_Cur_Fin_Row = rev_Cur_Fin_Row + 1;
                        continue;
                    }
                }
                if(!maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col].hasNorthWall){
                    if(maze_Cell_Matrix[rev_Cur_Fin_Row - 1][rev_Cur_Fin_Col].shortest_distance_from_player < rev_Min_Path_Val){
                        maze_Cell_Matrix[rev_Cur_Fin_Row - 1][rev_Cur_Fin_Col].is_SP_Cell = true;
                        rev_Min_Path_Val = maze_Cell_Matrix[rev_Cur_Fin_Row - 1][rev_Cur_Fin_Col].shortest_distance_from_player;
                        rev_Cur_Fin_Row = rev_Cur_Fin_Row - 1;
                        continue;
                    }
                }
                if(!maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col].hasEastWall){
                    if(maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col + 1].shortest_distance_from_player < rev_Min_Path_Val){
                        maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col + 1].is_SP_Cell = true;
                        rev_Min_Path_Val = maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col + 1].shortest_distance_from_player;
                        rev_Cur_Fin_Col = rev_Cur_Fin_Col + 1;
                        continue;
                    }
                }
                if(!maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col].hasWestWall){
                    if(maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col - 1].shortest_distance_from_player < rev_Min_Path_Val){
                        maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col - 1].is_SP_Cell = true;
                        rev_Min_Path_Val = maze_Cell_Matrix[rev_Cur_Fin_Row][rev_Cur_Fin_Col - 1].shortest_distance_from_player;
                        rev_Cur_Fin_Col = rev_Cur_Fin_Col - 1;
                        continue;
                    }
                }
            }

        }
        compute_Shortest_Path_and_Logic();




//**************************************** CLASS FUNCTIONS **********************************************************

        that.drawLabyrinth = function(){
            context.lineWidth="3";
            context.strokeStyle="black";
            if (background_Image_Flag) {
                let xbitemp = maze_Canvas_Dimensions.start_offsetX;
                let ybitemp = maze_Canvas_Dimensions.start_offsetY
                context.save();
                context.translate(xbitemp, ybitemp);
                context.translate(-xbitemp, -ybitemp);
                context.globalAlpha = .5;
                context.drawImage(background_Image,xbitemp,ybitemp,maze_Canvas_Dimensions.width,maze_Canvas_Dimensions.height);
                context.restore();
            }

            for (var irow = 0; irow<datum.grid_size; irow++){
                for(var jcol = 0; jcol<datum.grid_size; jcol++){
                    maze_Cell_Matrix[irow][jcol].drawMe();
                }
            }
        };

        that.drawBreadCrumbs = function(){
            if(showMazeCrumbs){
                for (var irow = 0; irow<datum.grid_size; irow++){
                    for(var jcol = 0; jcol<datum.grid_size; jcol++){
                        maze_Cell_Matrix[irow][jcol].showCrumb();
                    }
                }
            }
        }

        that.drawFinishPath = function(){
            if(showMazePath){
                for (var irow = 0; irow<datum.grid_size; irow++){
                    for(var jcol = 0; jcol<datum.grid_size; jcol++){
                        maze_Cell_Matrix[irow][jcol].showPath();
                    }
                }
            }
        }

        that.drawSingleHint = function(){
            if(showSingleHint){
                if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].hasNorthWall){
                    if(maze_Cell_Matrix[current_Player_Cell_Row - 1][current_Player_Cell_Col].is_SP_Cell){
                        maze_Cell_Matrix[current_Player_Cell_Row - 1][current_Player_Cell_Col].showHint();
                    }
                }
                if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].hasSouthWall){
                    if(maze_Cell_Matrix[current_Player_Cell_Row + 1][current_Player_Cell_Col].is_SP_Cell){
                        maze_Cell_Matrix[current_Player_Cell_Row + 1][current_Player_Cell_Col].showHint();
                    }
                }
                if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].hasEastWall){
                    if(maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col + 1].is_SP_Cell){
                        maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col + 1].showHint();
                    }
                }
                if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].hasWestWall){
                    if(maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col - 1].is_SP_Cell){
                        maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col - 1].showHint();
                    }
                }
                //console.log('showing hint');
            }
        }

        that.movePlayer = function(input){
            maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].is_BreadCrumb = true;

            if(input == 0){
                // up
                if(maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].hasNorthWall){
                    return;
                }
                if(!maze_Cell_Matrix[current_Player_Cell_Row - 1][current_Player_Cell_Col].is_SP_Cell){

                    if(!maze_Cell_Matrix[current_Player_Cell_Row - 1][current_Player_Cell_Col].has_been_scored){
                        score_And_Time.score = score_And_Time.score - 1;
                    }
                    else {
                        score_And_Time.score = score_And_Time.score - 1000;
                    }
                    
                    maze_Cell_Matrix[current_Player_Cell_Row - 1][current_Player_Cell_Col].is_SP_Cell = true;
                }
                else {
                    if(!maze_Cell_Matrix[current_Player_Cell_Row - 1][current_Player_Cell_Col].has_been_scored){
                        score_And_Time.score = score_And_Time.score + 5;
                    }
                    maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].is_SP_Cell = false;
                }
                
                current_Player_Cell_Row = current_Player_Cell_Row - 1;
                current_Player_y_pos = current_Player_y_pos - maze_Cell_Dimensions.yHeight;
                maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].has_been_scored = true;
                return;
            }


            if(input == 1){
                // down
                if(maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].hasSouthWall){
                    return;
                }
                if(!maze_Cell_Matrix[current_Player_Cell_Row + 1][current_Player_Cell_Col].is_SP_Cell){
                    if(!maze_Cell_Matrix[current_Player_Cell_Row + 1][current_Player_Cell_Col].has_been_scored){
                        score_And_Time.score = score_And_Time.score - 1;
                    }
                    else {
                        score_And_Time.score = score_And_Time.score - 1000;
                    }
                    maze_Cell_Matrix[current_Player_Cell_Row + 1][current_Player_Cell_Col].is_SP_Cell = true;
                }
                else {
                    if(!maze_Cell_Matrix[current_Player_Cell_Row + 1][current_Player_Cell_Col].has_been_scored){
                        score_And_Time.score = score_And_Time.score + 5;
                    }
                    maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].is_SP_Cell = false;
                }
                current_Player_Cell_Row = current_Player_Cell_Row + 1;
                current_Player_y_pos = current_Player_y_pos + maze_Cell_Dimensions.yHeight;
                maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].has_been_scored = true;
                return;
            }
            if(input == 2){
                // left
                if(maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].hasWestWall){
                    return;
                }
                if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col - 1].is_SP_Cell){
                    if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col - 1].has_been_scored){
                        score_And_Time.score = score_And_Time.score - 1;
                    }
                    else {
                        score_And_Time.score = score_And_Time.score - 1000;
                    }
                    maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col - 1].is_SP_Cell = true;
                }
                else {
                    if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col - 1].has_been_scored){
                        score_And_Time.score = score_And_Time.score + 5;
                    }
                    maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].is_SP_Cell = false;
                }
                current_Player_Cell_Col = current_Player_Cell_Col - 1;
                current_Player_x_pos = current_Player_x_pos - maze_Cell_Dimensions.xWidth;
                maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].has_been_scored = true;
                return;
            }
            if(input == 3){
                // right
                if(maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].hasEastWall){
                    return;
                }
                if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col + 1].is_SP_Cell){
                    if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col + 1].has_been_scored){
                        score_And_Time.score = score_And_Time.score - 1;
                    }
                    else {
                        score_And_Time.score = score_And_Time.score - 1000;
                    }
                    maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col + 1].is_SP_Cell = true;
                }
                else {
                    if(!maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col + 1].has_been_scored){
                        score_And_Time.score = score_And_Time.score + 5;
                    }
                    maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].is_SP_Cell = false;
                }
                current_Player_Cell_Col = current_Player_Cell_Col + 1;
                current_Player_x_pos = current_Player_x_pos + maze_Cell_Dimensions.xWidth;
                maze_Cell_Matrix[current_Player_Cell_Row][current_Player_Cell_Col].has_been_scored = true;
                return;
            }
            // console.log(current_Player_Cell_Row + ' ' + current_Player_Cell_Col
            //             + ' ' + current_Finish_Cell_Row + ' ' + current_Finish_Cell_Col);

        };

        that.drawPawns = function(){
            if (goal_Image_Flag) {
                context.save();
                context.translate(finish_Marker_x_pos, finish_Marker_y_pos);
                context.translate(-finish_Marker_x_pos, -finish_Marker_y_pos);
                context.drawImage(goal_Image,finish_Marker_x_pos,finish_Marker_y_pos,marker_Width,marker_Height);
                context.restore();
            }
            if (player_Image_Flag) {
                context.save();
                context.translate(current_Player_x_pos, current_Player_y_pos);
                context.translate(-current_Player_x_pos, -current_Player_y_pos);
                context.drawImage(player_Image,current_Player_x_pos,current_Player_y_pos,marker_Width,marker_Height);
                context.restore();
            }
            if(current_Player_Cell_Col == current_Finish_Cell_Col){
                if(current_Player_Cell_Row == current_Finish_Cell_Row){
                    master_Game_Over = true;
                    master_Game_Won = true;
                }
            }
        };

        that.isGameOver = function(){
            return master_Game_Over;
        }

        that.isGameWon = function(){
            return master_Game_Won;
        }

        that.drawTime = function(incoming_time){
            score_And_Time.time = score_And_Time.time + incoming_time;
            context.font = "30px Arial";
            context.fillText(((score_And_Time.time/1000).toFixed(3)).toString(),maze_Canvas_Dimensions.width 
            + maze_Canvas_Dimensions.start_offsetX,maze_Canvas_Dimensions.start_offsetY*2);
            context.fillText('Current High Score:',maze_Canvas_Dimensions.width 
            + maze_Canvas_Dimensions.start_offsetX,maze_Canvas_Dimensions.start_offsetY*8);
            context.fillText(currentHighScore,maze_Canvas_Dimensions.width 
            + maze_Canvas_Dimensions.start_offsetX,maze_Canvas_Dimensions.start_offsetY*10);
            if(showScore){
                context.fillText(score_And_Time.score,maze_Canvas_Dimensions.width 
                    + maze_Canvas_Dimensions.start_offsetX,maze_Canvas_Dimensions.start_offsetY*5);
            }
            //console.log(score_And_Time.time);
            
        }

        that.drawCreditsAndUIBoard = function(){
            if(master_Game_Won){
                context.font = "30px Arial";
                context.fillText("Congratulations!  You won the game!",
                maze_Canvas_Dimensions.width/2,maze_Canvas_Dimensions.start_offsetY*2);
                context.fillText("Your Final Score and time were: ",
                maze_Canvas_Dimensions.width/2,maze_Canvas_Dimensions.start_offsetY*4);
                context.fillText(('Score: ' + score_And_Time.score + ' Time: ' 
                + (score_And_Time.time/1000).toFixed(3).toString() + ' seconds'),
                maze_Canvas_Dimensions.width/2,maze_Canvas_Dimensions.start_offsetY*6);
                context.fillText("Credits:",
                maze_Canvas_Dimensions.width/2,maze_Canvas_Dimensions.start_offsetY*10);
                context.fillText("This game was written, by Brigham Michaelis",
                maze_Canvas_Dimensions.width/2,maze_Canvas_Dimensions.start_offsetY*12);
                context.fillText("If you want to try again press \"n\" for a new game",
                maze_Canvas_Dimensions.width/2,maze_Canvas_Dimensions.start_offsetY*16);

                //console.log('you won!');
            }
            else{
                //console.log('you lost!');
            }

        }

        that.toggleBreadCrumbs = function(){
            showMazeCrumbs = !showMazeCrumbs;
        }

        that.toggleFinishPath = function(){
            showMazePath = !showMazePath;
        }

        that.toggleHint = function(){
            showSingleHint = !showSingleHint;
        }

        that.toggleShowScore = function(){
            showScore = !showScore;
        }

        that.startNewGame = function(){
            if(currentHighScore < score_And_Time.score){
                currentHighScore = score_And_Time.score;
            }            
            //sessionStorage.setItem('currentHighScore',currentHighScore);
            localStorage.setItem('currentHighScore',currentHighScore);
            location.reload();
        }

        return that;
    }


    return{
        clear: clear,
        LabyrinthSet: LabyrinthSet
    };
    
}());