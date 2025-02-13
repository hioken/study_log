// ==========================
// 🎯 問題 1: this の挙動を確認
// ==========================
// box1 をクリックしたときに `this` の値を確認する
document.getElementById("box1").addEventListener("click", function () {
  console.log("this (通常関数):", this); // 何が出る？
});
document.getElementById("box2").addEventListener("click", () => {
  console.log("this (アロー関数):", this); // 何が出る？
});

// ==========================
// 🎯 問題 2: イベントデリゲーション
// ==========================
// .container 内でクリックされた要素が `.box` なら「クリックされた！」とログを出す
document.querySelector(".container").addEventListener("click", (event) => {
  if (event.target.matches(".box")) {
    console.log("クリックされた要素:", event.target.textContent);
  }
});

// ==========================
// 🎯 問題 3: 伝播の制御
// ==========================
// box1 をクリックした時にバブリングを止める
document.getElementById("box1").addEventListener("click", (event) => {
  console.log("box1 のイベント発火！");
  event.stopPropagation(); // 伝播を止める
});
document.querySelector(".container").addEventListener("click", () => {
  console.log("コンテナのイベント発火！");
});

// ==========================
// 🎯 問題 4: 動的要素へのイベント適用
// ==========================
// #addBox クリック時、新しい .box を追加する
document.getElementById("addBox").addEventListener("click", () => {
  const newBox = document.createElement("div");
  newBox.className = "box";
  newBox.textContent = "追加ボックス";
  document.querySelector(".container").appendChild(newBox);
});

// → 追加したボックスにもクリックイベントが適用されるか確認する！

// ==========================
// 🎯 問題 5: preventDefault()
// ==========================
// ボックスをクリックしたら `preventDefault()` を試す
document.querySelector(".container").addEventListener("click", (event) => {
  if (event.target.matches(".box")) {
    event.preventDefault(); // 何か変化する？
    console.log("preventDefault() を適用！");
  }
});
