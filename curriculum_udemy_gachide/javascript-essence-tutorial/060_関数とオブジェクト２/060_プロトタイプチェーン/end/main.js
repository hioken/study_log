// function Person(name, age) {
//     this.name = name;
//     this.age = age;
//     // this.hello = function() {
//     //     console.log('OwnProperty: hello ' + this.name);
//     // }
// }

// // Person.prototype.hello = function() {
// //     console.log('Person: hello ' + this.name);
// // }

// Object.prototype.hello = function() {
//     console.log('Object: hello ' + this.name);
// }

// const bob = new Person('Bob', 18);
// bob.hello();

// const result = bob.hasOwnProperty('name');
// console.log(result);



const a = {
    prop1: 'a'
}

const b = a.__proto__

console.log(a);
console.log(b);

function Fn1() {
    return 1;
}

const fn1V = new Fn1;

console.log(Fn1.prototype);
console.log(fn1V);
