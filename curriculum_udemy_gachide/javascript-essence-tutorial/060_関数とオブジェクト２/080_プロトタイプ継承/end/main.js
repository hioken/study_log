// function Person(name, age) {
//     this.name = name;
//     this.age = age;
// }

// Person.prototype.hello = function() {
//     console.log('hello ' + this.name);
// }

// function Japanese(name, age, gender) {
//     Person.call(this, name, age);
//     this.gender = gender;
// }

// Japanese.prototype = Object.create(Person.prototype);

// Japanese.prototype.hello = function() {
//     console.log('Konnichiwa ' + this.name);
// }

// Japanese.prototype.bye = function() {
//     console.log('Sayonara ' + this.name);
// }

// const taro = new Japanese('Taro', 23, 'Male');
// console.log(taro);

// taro.hello();
// taro.bye();


// function A() {
//     this.prop1 = 'a';
// }

// function B() {
//     this.prop2 = 'b';
// }

// B.prototype = Object.create(A.prototype);

// console.log(B);
// bVar = new B;
// console.log(B);
// console.log(bVar);

// B();

// console.log(B.prop2);

// B.prop3 = 'c';
// console.log(B.prop3);



function ConstrA(prop1) {
    this.prop1 = prop1;
}

function ConstrB(prop1, prop2) {
    fnA.call(this, prop1);
    this.prop2 = prop2;
}

ConstrB.prototype = Object.create(ConstrA.prototype);