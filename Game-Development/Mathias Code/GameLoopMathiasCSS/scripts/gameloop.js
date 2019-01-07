/*jslint browser: true, white: true */
// ------------------------------------------------------------------
// 
// This is the game object.  Everything about the game is located in 
// this object.
//
// ------------------------------------------------------------------
var MyGame = (function() {
	var lastTimeStamp = performance.now();
	// ------------------------------------------------------------------
	//
	// This function is called by the 'Add Event' button to add a new event to
	// the game.
	//
	//------------------------------------------------------------------
	function addEvent() {
		'use strict';
		var name,
			count,
			interval;
		
		name = document.getElementById('id-event-name').value;
		count = document.getElementById('id-event-count').value;
		interval = document.getElementById('id-event-interval').value;

		MyGame.events.add(name, interval, count);
	}
	
	//------------------------------------------------------------------
	//
	// Update everything in the game
	//
	//------------------------------------------------------------------
	function update(elapsedTime) {
		'use strict';

		MyGame.events.update(elapsedTime);
		
	}
	
	//------------------------------------------------------------------
	//
	// Render everything in the game
	//
	//------------------------------------------------------------------
	function render() {
		'use strict';

		MyGame.events.render();
	}
	
	//------------------------------------------------------------------
	//
	// This is the Game Loop function!
	//
	//------------------------------------------------------------------
	function gameLoop(time) {
		'use strict';
		
		update(time - lastTimeStamp);
		render();
		lastTimeStamp = time;
		
		requestAnimationFrame(gameLoop);
	}

	//------------------------------------------------------------------
	//
	// Perform the one-time game initialization.
	//
	//------------------------------------------------------------------
	function initialize() {
		'use strict';

		console.log('game initializing...');
		requestAnimationFrame(gameLoop);
	}
	
	return {
		initialize: initialize,
		addEvent: addEvent
	};
}());

//------------------------------------------------------------------
//
// All of the code and data related to handling of the events is located
// in this function.
//
//------------------------------------------------------------------
MyGame.events = (function () {
	'use strict';
	var events = [],		// Array of the currently active events.
		renderThese = [];

	// ------------------------------------------------------------------
	//
	// Allows a new event to be added to the array
	//
	// ------------------------------------------------------------------
	function add(name, interval, count) {
		events.push( {
			name: name,
			interval: interval,
			count: count,
			startTime: performance.now(),
			elapsed: 0
		});
	}
	
	// ------------------------------------------------------------------
	//
	// This is used to report the event to the browser
	//
	// ------------------------------------------------------------------
	function reportEvent(event) {
		var node = document.getElementById('div-console');
		node.innerHTML += ('Event: ' + event.name + ' (' + event.count + ' remaining)' + '<br/>');
		node.scrollTop = node.scrollHeight;
	}

	// ------------------------------------------------------------------
	//
	// Updates the status of all events in the game.
	//
	// ------------------------------------------------------------------
	function update(elapsedTime) {
		var event,
			deleteMe = [];
		
		for (event = 0; event < events.length; event++) {
			events[event].elapsed += elapsedTime;
			if (events[event].elapsed >= events[event].interval) {
				events[event].elapsed = (events[event].elapsed - events[event].interval);
				events[event].count--;
				//
				// Debugging statement, not a rendering...in other words, I'm doing what I say
				console.log(events[event].name + ' - event hit! (' + events[event].count + ' remaining)');
				//
				// Add the event to the list of those that need rendering
				renderThese.push(events[event]);

				if (events[event].count === 0) {
					deleteMe[deleteMe.length] = event;
				}
			}
		}

		//
		// Clean up any events that have expired
		if (deleteMe.length > 0) {
			for (event = deleteMe.length - 1; event >= 0; event -= 1) {
				events.splice(deleteMe[event], 1);
			}
		}
	}
	
	// ------------------------------------------------------------------
	//
	// Renders each of the events that need reporting to the console
	//
	// ------------------------------------------------------------------
	function render() {
		var event;
		
		for (event = 0; event < renderThese.length; event++) {
			reportEvent(renderThese[event]);
		}

		renderThese.length = 0;
	}

	return {
		add: add,
		update: update,
		render: render
	};
}());

//
// Get the game started
MyGame.initialize();
