class Person {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }

    hello() {
        console.log('hello ' + this.name);
    }
}

class Japanese extends Person {
    constructor(name, age, gender) {
        super(name, age);
        this.gender = gender;
    }

    // hello() {
    //     console.log('Konnichiwa ' + this.name);
    // }

    bye() {
        console.log('Sayonara ' + this.name);
    }
}

const taro = new Japanese('Taro', 23, 'Male');
console.log(Japanese)
console.log(taro);
taro.hello()
taro.bye()

console.log(Person.__proto__ === Function.prototype)
console.log(Function.prototype.__proto__ === Object.prototype)