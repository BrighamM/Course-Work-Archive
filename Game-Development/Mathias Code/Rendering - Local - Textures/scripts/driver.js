MyGame.main = (function(graphics){
    var myTriangle = graphics.Triangle( {
        center : {x : 150, y : 150 },
        pt1 : { x : 100, y : 100 },
        pt2 : { x : 200, y : 100 },
        pt3 : { x : 150, y : 200 },
        fill : 'rgba(150, 0, 0, 1)',
        stroke : 'rgba(255, 0, 0, 1)',
        lineWidth : 2,
        rotation : 0
    });
    //myTriangle.draw();
    var myBox = graphics.Rectangle( {
        x : 300, y : 100, width : 100, height : 100, 
        fill : 'rgba(255, 150, 50, 1)', 
        stroke : 'rgba(255, 0, 0, 1)',
        rotation : 0
    });
    var myTexture = graphics.Texture( {
        imageSrc: 'images/USU-Logo.png',
        center: { x: 100, y: 100 },
        width: 100,
        height: 100,
        rotation: 0
    });
    
    function update() {
        myBox.updateRotation(-.1);
        //myTriangle.updateRotation(0.1);
        //myTexture.updateRotation(0.1);
    }
    
    function render() {
        if(performance.now%5 == 0){
            graphics.clear();
        }
       
        myBox.draw();
        //myTriangle.draw();
        //myTexture.draw();
    }

    //------------------------------------------------------------------
    //
    // This is the Game Loop function!
    //
    //------------------------------------------------------------------
    function gameLoop(time) {

        update();
        render();

        requestAnimationFrame(gameLoop);
    }

    console.log('game initializing...');
    requestAnimationFrame(gameLoop); 

}(MyGame.graphics));

