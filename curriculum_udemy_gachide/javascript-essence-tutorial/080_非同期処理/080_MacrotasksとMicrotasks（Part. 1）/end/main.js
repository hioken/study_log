setTimeout(function task1() {
  console.log('task1');
});

new Promise(function promise(resolve) {
  console.log('promise');
  setTimeout(() => {console.log('task1')}, 1000)
  resolve();
}).then(function job1() {
  console.log('job1');
}).then(function job2() {
  console.log('job2');
});

console.log('global end');