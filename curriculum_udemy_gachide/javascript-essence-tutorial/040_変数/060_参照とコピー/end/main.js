// let a = 'hello';
// let b = a;
// b = 'bye';
// console.log(a, b);

// let c = {
//     prop: 'hello'
// }
// let d = c;
// // d.prop = 'bye';
// d = {};
// console.log(c, d);


let p = 1;
let o1 = {
    prop: 'a'
};
let o2 = {
    prop: 'a'
};

function fc(v, obj1, obj2) {
    v = 200;
    obj1.prop = 'abc';
    obj2 = 'abc';
}

fc(p, o1, o2)+

console.log(p);
console.log(o1);
console.log(o2);