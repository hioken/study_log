function forceRepaint() {
    const el = document.querySelector(".heavy-section"); // 重い要素を取得
    el.classList.remove("heavy-section"); // クラスを一旦削除
    void el.offsetWidth; // **ここがポイント**: ブラウザに「変化した」と認識させる
    el.classList.add("heavy-section"); // クラスを付け直し
}

for(let i = 0; i < 30; i++ ) {
  setInterval(forceRepaint, 1500);
}

