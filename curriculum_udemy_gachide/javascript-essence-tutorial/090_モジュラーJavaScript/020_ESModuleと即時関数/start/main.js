const moduleA = (function () {

  console.log('IIFE called');

  // let privateVal = 1;
  let publicVal = 10;

  function publicFn() {
    console.log('publicFn called: ' + publicVal);
  }

  function privateFn() {

  }
  const a = {
    publicFn,
    publicVal
  }

  console.log('---in module---')
  console.log(a.publicVal++)
  console.log(a.publicVal++)
  a.publicFn()

  return {
    publicFn,
    publicVal
  }
})();


console.log('---out module---')
moduleA.publicFn();
console.log(moduleA.publicVal++);
console.log(moduleA.publicVal++);
moduleA.publicFn();

