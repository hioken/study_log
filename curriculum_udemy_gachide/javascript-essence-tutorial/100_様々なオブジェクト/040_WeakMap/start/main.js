let weakMap = new WeakMap();
let obj = { key: "value" };

weakMap.set(obj, "data"); 
console.log(weakMap); 

obj = { key: "value2"}; 
setTimeout(() => {
  console.log(weakMap); 
}, 8000)
