class Person {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }

    hello() {
        console.log('hello ' + this.name);
    }
}

const bob = new Person('Bob', 23);
console.log(bob);


function A(prop1) {
    this.prop1 = prop1;
}
A.prototype.hello = function() {
    console.log('hello');
}

const aVar = new A(100);
console.log(aVar);