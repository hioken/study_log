import {urlFetchTester} from './url.js'
const mainParent = document.querySelector('.container');
const createBox = function () {
  const boxId = 'box'
  let currentIdNum = 1;

  return (text) => {
    const div = document.createElement("div");
    div.className = "box";
    div.id = `box${currentIdNum}`;
    div.textContent = text;
    ++currentIdNum;
    return div;
  }
}();


document.getElementById('fetch-button').addEventListener("click", async function(event) {
  event.stopPropagation();
  const response = await fetch(urlFetchTester);
  const jsonObj = await response.json();
  console.log(jsonObj)
  for( key in jsonObj) {{
    mainParent.appendChild(createBox(`key: ${key}\nvalue: ${jsonObj[key]}`));
    // console.log(createBox(`key: ${key}\nvalue: ${jsonObj[key]}`))
  }}
});