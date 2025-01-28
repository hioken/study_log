// const a = new String('hello');
// console.log(a.toUpperCase());

// const b = new Number(100);
// console.log(b);

const a = 'hello';
const b = new String('hello');

console.log(a);
console.log(b);
console.log(a === b);
console.log(a === b);

const c = 'xy';
const d = new String('xy');
console.log(c === (d[0] + d[1]));

console.log('a'.__proto__)
console.log(new String('a').__proto__ === 'a'.__proto__)