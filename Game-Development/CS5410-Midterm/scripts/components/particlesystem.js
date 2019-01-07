MyGame.components.ParticleSystem = function(spec,context) {
    let that = {};
    
    let xLocation = spec.xLocation;
    let yLocation = spec.yLocation;
    let amount = spec.amount;
    let lifetime = spec.lifetime;
    let has_started = spec.has_started;
    let environment_height = spec.environment_height;
    let environment_width = spec.environment_width;
    let totalTime = 0;
    let is_alive = true;

    //Math.floor(Math.random() * 10);     // returns a number between 0 and 9

    let psarray = [];

    particle = {
        xPoint : 0,
        yPoint : 0,
        vel_x : 0,
        vel_y : 0,
        width : 0,
        height : 0
    };

    // build the particle array 
    for(var i = 0; i < amount; i++) {
        let newParticle = Object.create(particle);
        newParticle.xPoint = xLocation;
        newParticle.yPoint = yLocation;
        newParticle.vel_x = Math.random()*100;
        if(Math.floor(Math.random() * 2) == 0){
            newParticle.vel_x = -newParticle.vel_x;
        }
        newParticle.vel_y = Math.random()*100;
        if(Math.floor(Math.random() * 2) == 0){
            newParticle.vel_y = -newParticle.vel_y;
        }
        newParticle.width = environment_width/1000;
        newParticle.height = environment_height/1000;
        psarray.push(newParticle);
    }

    has_started = true;

    Object.defineProperty(that, 'psarray', {
        get: () => psarray
    });

    Object.defineProperty(that, 'totalTime', {
        get: () => totalTime,
        set: value => { totalTime = value; }
    });

    Object.defineProperty(that, 'lifetime', {
        get: () => lifetime
        //set: value => { totalTime = value; }
    });

    Object.defineProperty(that, 'is_alive', {
        get: () => is_alive
        //set: value => { totalTime = value; }
    });

    that.update = function(eltime) {
        totalTime += eltime;
        if(totalTime > lifetime){
            is_alive = false;
        }
        for(var i = 0; i < amount; i++) {
            psarray[i].xPoint = psarray[i].xPoint + (eltime*psarray[i].vel_x)
            psarray[i].yPoint = psarray[i].yPoint + (eltime*psarray[i].vel_y);
        }
    };

    that.draw = function() {
        for(var j = 0; j < psarray.length; j++){
            // draw each element in the particle array
            context.fillStyle = 'white';
            context.fillRect(psarray[j].xPoint, psarray[j].yPoint, psarray[j].width, psarray[j].height);
            context.strokeStyle = 'red';
            context.strokeRect(psarray[j].xPoint, psarray[j].yPoint, psarray[j].width, psarray[j].height);
        }
    };

    



    return that;
};