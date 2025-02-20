const urlFetchTester = "https://script.google.com/macros/s/AKfycbyw0LWNZ7lQ3ESl4xmdPJAnBVCc8Ny4O0GmSziyFsT6rpPQ5byKX16c8wyC2T7Ur_3Cjw/exec";

const query1 = new URLSearchParams({prop1: "windowTest1", prop2: "遷移後にfetchが実行されるか確認"});
const query2= new URLSearchParams({prop1: "windowTest1", prop2: "動作確認"});

console.log("window1_1 遷移前同期処理");
console.log("queryの中身確認");
console.log(query1.toString());
console.log(query2.toString());
async function fetchTest() {
  const response = await fetch(urlFetchTester, { method: "POST", body: query2 })  
  const jsonObj = await response.json();
  console.log(jsonObj);
}
fetchTest();

window.addEventListener("beforeunload", (event) => {

  for (let i = 0; i < 1e9; i++) {} // 約5秒間の同期処理
  const query = new URLSearchParams({ prop1: "windowTest1", prop2: "確実に送信" });
  navigator.sendBeacon(urlFetchTester, query);


  // setTimeout(() => {
  //   fetchDataButton.addEventListener("click", function() {
  //     fetch(urlFetchTester, { method: "POST", body: query1 })
  //   })}, 5000);
  // event.preventDefault();
});
