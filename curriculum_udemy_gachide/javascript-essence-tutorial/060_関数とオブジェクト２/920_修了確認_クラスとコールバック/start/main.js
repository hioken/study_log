/**
 * 問題：
 * Person.helloメソッドをsetTimeoutで１秒後に
 * 実行しようとしましたが、"hello Bob"と表示されませんでした。
 * 
 * setTimeoutに渡す方法がおかしそうなのですが、
 * どのようにすればよいでしょうか？
 * 
 * ※２通りの方法で実装してみてください。
 */
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
setTimeout(bob.hello.bind(bob), 1000);


// class Person {
//   constructor(name, age) {
//       this.name = name;
//       this.age = age;
//   }

//   hello(delayTime) {
//     const name = this.name;
//     if (delayTime) {
//       setTimeout.call(null, function() {console.log('hello ' + name)}, delayTime)
//     } else {
//       console.log('hello ' + name);
//     }
//   }
// }

// const bob = new Person('Bob', 23);
// bob.hello(1000);