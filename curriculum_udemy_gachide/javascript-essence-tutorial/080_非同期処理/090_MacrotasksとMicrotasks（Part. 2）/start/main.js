new Promise(function promise(resolve) {
  console.log('promise');

  setTimeout(function task1() {
    console.log('task1');
  });
  const a = []

  // for(let i = 0; i < 10000; i++) {
  //   a.push(i);
  //   i + 1
  //   i + 2
  // }

  // for(let i = 0; i < 10000; i++) {
  //   a.pop(i);
  // }
  
  resolve();
  // throw new Error("This is an intentional error");

  console.log('job0');

}).then(function job1() {

  console.log('job1');
})

console.log('global end');

// console.log(Promise.resolve());
// console.log(new Promise(function (){const a = 1}));