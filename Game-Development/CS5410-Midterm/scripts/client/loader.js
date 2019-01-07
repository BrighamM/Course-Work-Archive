let MyGame = {
    input : {},
    graphics : {},
    components : {},
    game : {},
    screens : {},
};


//------------------------------------------------------------------
//
// Purpose of this code is to bootstrap (maybe I should use that as the name)
// the rest of the application.  Only this file is specified in the index.html
// file, then the code in this file gets all the other code and assets
// loaded.
//
//------------------------------------------------------------------
MyGame.loader = (function() {
    'use strict';
    // Loader is loading all of the scripts it is going to need.
    // 
    let scriptOrder = [
        {
            scripts: ['./../input/input'],
            message: 'Input loaded',
            onComplete: null
        },
        {
            scripts: ['./../graphics'],
            message: 'Graphics loaded',
            onComplete: null
        },
        {
            scripts: ['./../components/particlesystem'],
            message: 'particle system loaded',
            onComplete: null
        },
        {
            scripts: ['./../game'],
            message: 'Game Loaded',
            onComplete: null
        },
        {
            scripts: ['./../screens/mainmenu'],
            message: 'loaded main menu screen',
            onComplete: null
        },  
        {
            scripts: ['./../screens/gameplay'],
            message: 'loaded game play screen',
            onComplete: null
        },
        {
            scripts: ['./../screens/highscores'],
            message: 'loaded high scores screen',
            onComplete: null
        },  
        {
            scripts: ['./../screens/help'],
            message: 'loaded help screen',
            onComplete: null
        },
        {
            scripts: ['./../screens/about'],
            message: 'loaded about screen',
            onComplete: null
        },  
    ]
  
 










    
    //------------------------------------------------------------------
    //
    // Helper function used to load scripts in the order specified by the
    // 'scripts' parameter.  'scripts' expects an array of objects with
    // the following format...
    //    {
    //        scripts: [script1, script2, ...],
    //        message: 'Console message displayed after loading is complete',
    //        onComplete: function to call when loading is complete, may be null
    //    }
    //
    //------------------------------------------------------------------
    function loadScripts(scripts, onComplete) {
        //
        // When we run out of things to load, that is when we call onComplete.
        if (scripts.length > 0) {
            let entry = scripts[0];
            require(entry.scripts, function() {
                console.log(entry.message);
                if (entry.onComplete) {
                    entry.onComplete();
                }
                scripts.splice(0, 1);
                loadScripts(scripts, onComplete);
            });
        } else {
            onComplete();
        }
    }

    //------------------------------------------------------------------
    //
    // Called when all the scripts are loaded, it kicks off the demo app.
    //
    //------------------------------------------------------------------
    function mainComplete() {
        console.log('it is all loaded up');
        MyGame.game.initialize();
    }

    console.log('Starting to dynamically load project scripts');
    loadScripts(scriptOrder, mainComplete);

}());
