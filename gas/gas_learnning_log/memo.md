- 出力結果がなんでそうなるか分からない
```js
let a = ['a', 'b', 'c'];
let b = a.entries();

console.log(a); // ['a', 'b', 'c']
console.log(b); // {}
console.log(b.next().value); // [0. 'a']
console.log(typeof b); // object
```

- forEachとfor ofの違い


- Active = スクリプトを実行したシート？

- スクリプトのトリガーの記述

- 以下の効率の良い書き方
```js
function merging() {
  let sheet = SpreadsheetApp.getActive().getSheetByName("シート1");
  let range = sheet.getDataRange();
  let num = range.getNumColumns();
  for(let row = 1; row <= range.getLastRow(); row++) {
    let scope = sheet.getRange(row, 1, 1, range.getLastColumn());
    scope.merge();
  }
}
```
