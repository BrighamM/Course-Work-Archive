const MAX_NUMBER = 42;

let data = [ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 ];

function isEven(value) {
	return value % 2 === 0;
}

let isEven2 = (value) => {
	return value % 2 === 0;
};

let isEven3 = value => { return value % 2 === 0; };

let isEven4 = value => value % 2 === 0;

let evens = data.filter(isEven);
let evens2 = data.filter(isEven2);
let evens3 = data.filter(isEven3);
let evens4 = data.filter(isEven4);
let evens5 = data.filter( value => value % 2 === 0 );

console.log(evens);
console.log(evens2);
console.log(evens3);
console.log(evens4);
console.log(evens5);

let double = data.map(value => value * 2);
console.log(double);
