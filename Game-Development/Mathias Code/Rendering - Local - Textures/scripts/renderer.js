// ------------------------------------------------------------------
// 
// This is the graphics object.  The various rendering components
// are located here.
//
// ------------------------------------------------------------------
MyGame.graphics = (function() {
    'use strict';

    let canvas = document.getElementById('canvas-main');
    let context = canvas.getContext('2d');

    //------------------------------------------------------------------
    //
    // Public function that allows the client code to clear the canvas.
    //
    //------------------------------------------------------------------
    function clear() {
        context.save();
        context.setTransform(1, 0, 0, 1, 0, 0);
        context.clearRect(0, 0, canvas.width, canvas.height);
        context.restore();
    }

    //------------------------------------------------------------------
    //
    // This is used to create a triangle function that can be used by client
    // code for rendering.
    //
    //------------------------------------------------------------------
    function Triangle(spec) {
        //console.log('I AM HAPPENING');
        let that = {};

        that.updateRotation = function(angle) {
            spec.rotation += angle;
        };

        that.draw = function() {
            context.save();

            context.translate(spec.center.x, spec.center.y);
            context.rotate(spec.rotation);
            context.translate(-spec.center.x, -spec.center.y);

            context.beginPath();
            context.moveTo(spec.pt1.x, spec.pt1.y);
            context.lineTo(spec.pt2.x, spec.pt2.y);
            context.lineTo(spec.pt3.x, spec.pt3.y);
            context.closePath();
            
            context.fillStyle = spec.fill;
            context.fill();
            
            context.strokeStyle = spec.stroke;
            context.lineWidth = spec.lineWidth;
            context.stroke();
            
            context.restore();
        };

        return that;
    }

    //------------------------------------------------------------------
    //
    // This is used to create a rectangle function that can be used by client
    // code for rendering.
    //
    //------------------------------------------------------------------
    function Rectangle(spec) {
        var that = {};

        that.updateRotation = function(angle) {
            spec.rotation += angle;
        };

        that.draw = function() {
            context.save();

            context.translate(spec.x + spec.width / 2, spec.y + spec.height / 2);
            context.rotate(spec.rotation);
            context.translate(-(spec.x + spec.width / 2), -(spec.y + spec.height / 2));

            context.fillStyle = spec.fill;
            context.fillRect(spec.x, spec.y, spec.width, spec.height);
            
            context.strokeStyle = spec.stroke;
            context.strokeRect(spec.x, spec.y, spec.width, spec.height);

            context.restore();
        };

        return that;
    }

    //------------------------------------------------------------------
    //
    // This is used to create a texture object that can be used by client
    // code for rendering.
    //
    //------------------------------------------------------------------
    function Texture(spec) {
        var that = {},
            ready = false,
            image = new Image();
        
        //
        // Load the image, set the ready flag once it is loaded so that
        // rendering can begin.
        image.onload = function() { 
            ready = true;
        };
        image.src = spec.imageSrc;
        
        that.updateRotation = function(angle) {
            spec.rotation += angle;
        };
        
        that.draw = function() {
            if (ready) {
                context.save();
                
                context.translate(spec.center.x, spec.center.y);
                context.rotate(spec.rotation);
                context.translate(-spec.center.x, -spec.center.y);
                
                context.drawImage(
                    image, 
                    spec.center.x - spec.width/2,
                    spec.center.y - spec.height/2,
                    spec.width, spec.height);
                
                context.restore();
            }
        };
        
        return that;
    }

    return {
        clear : clear,
        Triangle : Triangle,
        Rectangle : Rectangle,
        Texture : Texture
    };
}());
