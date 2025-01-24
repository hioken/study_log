class Person {
  constructor(name) {
    this.name = name;
  }

    const sayHello = () => {
      // アロー関数は親スコープの`this`を参照
      console.log(`Hello, I'm ${this.name}`);
    };
    sayHello();
}

const alice = new Person("Alice");
alice.greet(); // 出力: Hello, I'm Alice
