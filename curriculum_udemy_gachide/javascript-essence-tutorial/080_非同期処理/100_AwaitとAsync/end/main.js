function sleep(val) {
  return new Promise(function(resolve) {
    setTimeout(function() {
      console.log(val++);
      resolve(val);
    }, 1000);
  });
}

// function sleep2(val) {
//   new Promise(function(resolve) {
//     setTimeout(function() {
//       console.log(val++);
//       resolve(val);
//     }, 1000);
//   });
//   return 100;
// }

// async function init() {
//   let val = await sleep(0);
//   val = await sleep(val);
//   val = await sleep(val);
//   val = await sleep2(val);
//   val = await sleep(val);
//   // throw new Error();
//   return val;
// }

// init()
// .then(function(val) {
//   console.log('hello' + val)
// }).catch(function(e) {
//   console.error(e);
// });
// console.log(init())

// sleep(0).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// })


// async function a() {

// }

// let aVar = a();

// console.log(aVar);

// async function asyncFn1() {
//   let val = await sleep(0);
//   val = await sleep(val);
//   return val;
// }

// async function asyncFn2(val) {
//   val = await sleep(val);
//   val = await sleep(val);
// }

// asyncFn1().then(asyncFn2)

new Promise((resolve) => { resolve() }).then(function() {
  return sleep(0)
}).then(function(val) {
  return sleep(val);
}).then(function(val) {
  return new Promise(function(resolve){
    resolve(val);
  })
}).then(function(val) {
  return new Promise((resolve) => { resolve() }).then(function() {
    return sleep(val);
  }).then(function(val) {
    return sleep(val);
  }).then(function(val) {
    return new Promise(function(resolve){
      resolve(val)
    });
  });
});