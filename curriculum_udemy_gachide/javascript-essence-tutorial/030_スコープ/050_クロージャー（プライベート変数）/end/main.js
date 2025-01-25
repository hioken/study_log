// function incrementFactory() {
    
//     let num = 0;

//     function a() {
//         num = num + 1;
//         console.log(num);
//     }

//     return a;
// }

// const increment = incrementFactory();

// increment();
// increment();
// increment();
// increment();


// function abc() {
//     a: 1;
//     console.log(this.a);
// }

// abc();


// abc = {
//     a: 1,
//     console.log(100);
// }
function incrementFactory() {
  let count = 0;
  this.increment = function() {
    count++;
    return count;
  }

  return this.increment;
}
const counter = incrementFactory();
console.log(counter())
console.log(counter())