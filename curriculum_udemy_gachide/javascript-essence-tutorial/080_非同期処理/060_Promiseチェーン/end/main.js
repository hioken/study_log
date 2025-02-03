
// function sleep(val) {
//   return new Promise(function(resolve) {
//     console.log('flg1')
//     setTimeout(function() {
//       console.log(val++);
//       resolve(val);
//     }, 1000);
//   });
// }

// sleep(0).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// })

// console.log('flg2');


// function sleep(val) {
//   return new Promise(function(resolve) {
//     console.log('----------')
//     setTimeout(function() {
//       console.log(val++);
//       resolve(val);
//     }, 1000);
//   });
// }

// sleep(0).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   sleep(val);
//   return val;
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// });


// function sleep(val) {
//   return new Promise(function(resolve) {
//     console.log('----------')
//     console.log(`val1: ${val[1]++}`);
//     setTimeout(function() {
//       console.log(`val0: ${val[0]++}`);
//       resolve(val);
//     }, 1000);
//   });
// }

// sleep([0, 0]).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   sleep(val);
//   return val;
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// });


// function sleep(val) {
//   return new Promise(function(resolve) {
//     console.log('----------')
//     console.log(`val1: ${val[1]++}`);
//     console.log(`val0: ${val[0]++}`);
//     resolve(val);
//   });
// }

// sleep([0, 0]).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   sleep(val);
//   return val;
// }).then(function(val) {
//   return sleep(val);
// }).then(function(val) {
//   return sleep(val);
// });



function sleep(val) {
  return new Promise(function(resolve) {
    setTimeout(function() {
      console.log(val++);
      resolve(val);
    }, 3000);
  });
}

sleep(0).then(function(val) {
  return sleep(val);
}).then(function(val) {
  // new Promise(function(resolve) {
    setTimeout(function() {
      console.log(val++);
      // resolve(val);
    }, 3000);
  // });
  return 100;
}).then(function(val) {
  return sleep(val);
}).then(function(val) {
  return sleep(val);
});