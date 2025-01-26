// const a = {
//     prop: 0
// }

// let { prop } = a;
// prop = 1;
// console.log(a, prop);

// let b = a.prop;
// console.log(b);
// b = 1;
// console.log(b);
// console.log(a);





// function fn({ prop }) {
//     prop = 1;
//     console.log(a, prop);
// }

// fn(a);
// const c = {
//     prop1: {
//         prop2: 0
//     }
// }
// let { prop1 } = c;
// prop1.prop2 = 1;
// console.log(c, prop1);




// const obj = { a: { b: { c: 42 } } };

// const { a: { b: { c } } } = obj;
// const d = obj.a.b.c;
// console.log(c); // 42
// console.log(d); // 42
// console.log(a); // error

const a = {prop: [1, 2]}
let [b, c] = a.prop;

console.log(b); 
console.log(c); 