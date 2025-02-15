const targetParent = document.querySelector('.container');
const createBox = function () {
  const boxElement = targetParent.children[targetParent.children.length - 2]
  const boxId = boxElement.id.replace(/\d+$/, "");
  const boxText = boxElement.textContent.replace(/\d+$/, "");
  let currentIdNum = Number(boxElement.id.replace(/^\D+/, ""));

  return () => {
      const referenceElement = document.getElementById(boxId + currentIdNum);
      ++currentIdNum;
      const addElement = boxElement.cloneNode(true);
      addElement.id = boxId + currentIdNum;
      addElement.textContent = boxText + currentIdNum;
      return [referenceElement, addElement];
    }
}();


document.querySelector('.container').addEventListener("click", function(event) {
  if (event.target.matches('.box')) {
    console.log(event.target.textContent);
  }
});

document.getElementById('box1').addEventListener("click", function(event) {
  event.stopPropagation();
  console.log('コンテナのイベント発火！')
})

document.getElementById('addBox').addEventListener("click", function(event) {
  event.stopPropagation();
  const [referenceElement, addElement] = createBox();
  referenceElement.after(addElement);
})