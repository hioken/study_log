function sleep(callback, val) {
  setTimeout(function() {
    console.log(`before: ${val++}`);
    callback(val);
    console.log(`after: ${val}`);
  }, 1000);
}

sleep(function(val) {
  sleep(function(val) {
    sleep(function(val) {
      sleep(function(val) {
  
      }, val);
    }, val);
  }, val);
}, 0);