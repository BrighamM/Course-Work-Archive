let person = {
	name: {
		last: 'Doe',
		first: 'John'
	},
	age: 26,

	getName: function() { return this.name.first + ' ' + this.name.last; }
};

let factory = {
	name: {
		last: 'Generator',
		first: 'Function'
	},

	getName: function() {
		return function() {
			return this.name.first + ' ' + this.name.last;
		}
	}
};

let me = {
	name: {
		last: 'Mathias',
		first: 'Dean'
	},
	
	getName: factory.getName()
};

let you = {
	name: {
		last: 'Class',
		first: 'Cs 5410'
	},

	getName: me.getName
};

//console.log(person.getName());
console.log(factory.getName());
console.log(me.getName());
console.log(you.getName());
