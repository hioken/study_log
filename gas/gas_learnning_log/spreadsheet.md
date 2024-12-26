# class
## 一覧
|クラス名|説明|
|---|---|
|SpreadsheetApp|シート関連のトップレベルオブジェクト|
|Spreadsheet|シートを操作|
|Sheet|シートを操作する機能を提供|
|Range|セル範囲を操作する機能を提供|

- SpreadsheetApp > Spreadsheet > Sheet > Rangeの構造になっている

## SpreadSheetApp
### 概要
- トップレベルオブジェクト
- Spredsheet, その他サブクラスを取得/アクティブにするのがメイン
### メソッド
|メソッド名|説明|
|---|---|
|create(n)|名前nのシートの作成|
|flush()|スプレッドシートに保留中の変更を反映|
|getActive + ""/Sheet/Range|アクティブなスプレッドシート/シート/セル範囲を取得|
|setActive + SpreadSheet/Sheet/Range|指定したスプレッドシート/シート/セル範囲をアクティブにする|


## Spreadsheet
### 概要
- スプレッドシート自体が所属しているクラス
- シートの取得がメイン
- シートの削除も可能
### メソッド
|メソッド名|説明|
|---|---|
|get + Sheet/Range + ByName(name)|nameのシート/セル範囲を取得|
|getSheets|シート一覧を配列で取得|
|get + Id/Name/Url()||

## Sheet
### 概要
- シートが所属しているクラス
- セル範囲を取得するのがメイン
- 列, 行の削除や、画像の挿入も行える
### メソッド
|メソッド名|説明|
|---|---|
|getRange(range)|セル範囲を取得、rangeの指定方法が複数ある|
|getDateRange()|A1から値が入力されているセル範囲を取得、A1~最初の値までが空の場合もA1から範囲に含まれる|
|getLast + Row/Column||
|clear + Contents/Formats/""|シートの値/背景等/両方をクリアにする|
|appendRow(array)|array配列の要素をA列からの値として、最終行に追加|
### getRangeの引数
- row, column[, numRows, numColumns]の場合
  - インデックスで指定する(セルのインデックスは1から始まる)
  - row、columnのセル範囲を取得
  - num~がある場合、それぞれ、row, columnを開始位置として、num~行(列)のセル範囲を取得
- getRange(a1Notation)の場合
  - A1表記またはR1C1表記で指定する
```js
s = SpreadsheetApp.getActive().getSheetByName("シート1");

s.getRange(1, 2, 2, 2); // 1~2行目, b~c列を取得

s.getRange("A1"); // 1行目a列を取得
s.getRange("Invoices!A1:D4"); // 1~4行目, A~D列を取得
```

## Range
### 概要
- セル範囲を操作するクラス
### メソッド
|メソッド名|説明|
|---|---|
|get系||
|set系||
|merge / breakApart|セルの結合 / 結合解除|
|clear + Contents/Formats/""|セル範囲の値/背景等/両方をクリアにする|

# 実践
## カスタム関数
- ドキュメントに@customfunctionタグを付けると、シートで=FunctionName(cellを引数として指定)で呼び出せるようになる
  - タグは必須ではないが、付けないと候補に出なくなったりする


## テクニック
- データを操作する時は、配列上で操作してからシートに代入する
- filterで特定の情報を抽出して取得出来る
