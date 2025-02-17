const urlFetchTester = "https://script.google.com/macros/s/AKfycbyw0LWNZ7lQ3ESl4xmdPJAnBVCc8Ny4O0GmSziyFsT6rpPQ5byKX16c8wyC2T7Ur_3Cjw/exec";

const formElement = document.getElementById('testForm');
const fetchDataButton = document.getElementById('fetchData');
const startFetchButton = document.getElementById('startFetch');
const abortFetchButton = document.getElementById('abortFetch');

let fetchAbortController = new AbortController();
let signal = fetchAbortController.signal;
let isFetching = false
// const uploadButton = document.getElementById('uploadFile');


// 問題1
formElement.querySelector('button').addEventListener("click", function() {
  const formData = new FormData(formElement);
  fetch(urlFetchTester, {
    method: "POST",
    body: formData
  })
})


// 問題2
fetchDataButton.addEventListener("click", function() {
  const query = new URLSearchParams(fetchDataButton.dataset);
  console.log(query.toString);
  fetch(urlFetchTester, {
    method: "POST",
    body: query
  })
})


// 問題3
function waiting(time) {
  return new Promise((resolve, reject) => {
    setTimeout(() => { 
      console.log('waiting...');
      resolve();
    }, time)
  })
}

startFetchButton.addEventListener("click", async function() {
  if (signal.aborted) {
    fetchAbortController = new AbortController();
    signal = fetchAbortController.signal;
  }
  isFetching = true
  const response = await fetch(urlFetchTester, {signal});
  await waiting(1000);
  const jsonObj = await response.json();
  await waiting(1000);
  for(const key of Object.entries(jsonObj)) {
    await waiting(1000);
    await function () {
      return new Promise((resolve, reject) => {
        if (signal.aborted) {throw new Error('aborted!!')}
        console.log(`key: ${key}\nvalue: ${jsonObj[key]}`);
        resolve();
      })
    }();
  }
  await setTimeout(() => { console.log( 'fin!!') }, 1000);
})

abortFetchButton.addEventListener("click", function() {
  console.log('stop event click');
  if(isFetching) {
    console.log('stopping');
    fetchAbortController.abort();
    isFetching = false;
    console.log('stoped');
  }
});

// uploadButton.addEventListener("click", function() {
//   const fileData = new FormData()
//   fileData.append('file', document.getElementById('fileInput').files[0]);
//   fileData.append('postType', 1);

//   if(fileData.get('file')) {
//     console.log(fileData.get('file'))
//     console.log('image added')
//   } else {
//     throw new Error('file無し')
//   }
//   fetch(urlFetchTester, {
//     method: "POST",
//     body: fileData
//   })

// })

