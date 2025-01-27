// let d = 0;
// function fn() {
// 	let d = 1;
// 	const fn1 = new Function('a', 'b', 'return a * b * d');
// 	return fn1;
// }

// const f = fn();
// const result = f(1,2);

// console.log(result);

// function fn2(a, b) {
// 	return a + b;
// }

// console.log(fn2 instanceof Function)

// const obj = new function() {
// 	this.a = 0;
// }
// const fn3 = new Function('this.a = 0;');
// const obj3 = new fn3()
// console.log(obj, obj3)


// const fnVar1 = function fn1 (a, b) {
// 	return a + b;
// }

// const fnVar2 = function fn2 (a) {
// 	return "hello " + a;
// }

// console.log(fnVar1.__proto__ === fnVar2.__proto__);
// console.log(fnVar1.__proto__ === Function.prototype);
// console.log(fnVar1 instanceof Function);
// console.log(fnVar1);
// console.log(fnVar1.prototype);
// console.log(fnVar1.__proto__);


let a = 0;
function fn() {
	let a = 1;
	const fn1 = new Function('return a');
	const fn2 = function() {
		return a
	};
	console.log(fn1());
	console.log(fn2());
	return [fn1, fn2];
}

const [fn1V, fn2V] = fn();

console.log(fn1V());
console.log(fn2V());