function promisesFactory(num) {
  return Array.from({length: num}, (v, i) => () => new Promise((resolve, reject) => {
      setTimeout(() =>
        (Math.random() * 2 | 0) ? resolve(`Success!_${i}`) : reject(`Error!_${i}`)
      , 500)
    })
  )
}

// function retryPromise(promises, results) {
//   const returnResult = []
//   for (i in results){
//     if (results[i].status === "rejected") {
//       returnResult.push(promises[i]());
//     } else {
//       returnResult.push(results[i]);
//     }
//   }
//   return returnResult;
// }

function retryPromise(promises, results) {
  return results.map((result, i) => 
    result.status === "rejected" ? promises[i]() : result
  );
}


async function testing() {
  const promises = promisesFactory(4);
  let results = await Promise.allSettled(promises.map((f) => f()));
  for(let i = 0; i < 4 && results.some((v) => v.status === "rejected"); i++) {
    results = await Promise.allSettled(retryPromise(promises, results));
    console.log(results);
  }
}

testing();
