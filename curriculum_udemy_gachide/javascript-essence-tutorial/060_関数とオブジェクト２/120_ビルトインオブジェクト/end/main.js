const arry = new Array(1,2,3,4);
const obj  = { 10: 'a', prop: 'b' };
console.log(arry);
console.log(arry["0"] === arry[0]);
console.log(arry.hasOwnProperty(0));

arry.__proto__ = obj;
console.log(arry[10]);
console.log(arry.prop);

// console.log([1, 2])

// const obj = { 1: 'a' }

// console.log(obj[1])