const moduleA = (function () {
  let publicVal = 10;

  function publicFn() {
    console.log('publicFn called: ' + publicVal);
  }
  return {
    publicFn,
    publicVal
  }
})();


const moduleB = (function({ publicFn, publicVal}){
  publicFn();
  console.log(publicVal++);
  console.log(publicVal++);
  publicFn();
})(moduleA);

