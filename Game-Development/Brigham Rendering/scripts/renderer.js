// ------------------------------------------------------------------
// 
// This is the graphics object.  The various rendering components
// are located here.
//
// ------------------------------------------------------------------
MyGame.graphics = (function() {
    // cannot use undeclared variables
    'use strict';

    let canvas = document.getElementById('canvas-main');
    let context = canvas.getContext('2d');

    //------------------------------------------------------------------
    //
    // Public function that allows the client code to clear the canvas.
    //
    //------------------------------------------------------------------
    function clear() {
        console.log('Clear was called');
        context.save();
        context.setTransform(1, 0, 0, 1, 0, 0);
        context.clearRect(0, 0, canvas.width, canvas.height);
        context.restore();
    }
    console.log('Im in the renderer!');


    //------------------------------------------------------------------
    //
    // This is used to create a triangle function that can be used by client
    // code for rendering.
    //
    //------------------------------------------------------------------


    //------------------------------------------------------------------
    //
    // This is used to create a rectangle function that can be used by client
    // code for rendering.
    //
    //------------------------------------------------------------------


    //------------------------------------------------------------------
    //
    // This is used to create a texture object that can be used by client
    // code for rendering.
    //
    //------------------------------------------------------------------


    return {
        clear : clear
    };
}());
