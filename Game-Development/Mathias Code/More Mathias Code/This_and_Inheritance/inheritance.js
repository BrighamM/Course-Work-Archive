
let Mammal = function(spec) {
	let that = {};

	that.name = function() { return spec.name; };

	that.says = function() { return spec.sound || ''; };

	return that;
};

let Cat = function(spec) {
	let that = Mammal(spec);

	that.says = function() { return 'meow'; };

	return that;
};

let myCat = Cat({ name: 'Catly' });

console.log('name: ', myCat.name());
console.log('says: ', myCat.says());
