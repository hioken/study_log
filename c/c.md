### ファイル
#### 種類
- NewFile : 最新の利用者ID
- OldFile : １世代前の利用者ID

#### 情報
- IDの昇順


### レコード
#### 本体
- 利用者ID : 1 ~ 8
- 利用者名 : 1 ~ 10
- 属性 : 1
- 最終使用日 : 8

#### 属性
- *ビット長*
- *16進数に変換される*
- 固定 : 0100
- s : 1 or 0
- o : 1 or 0
- gr(その他) : 1 or 0, 1 or 0



### 差異
- NewFile -> OldFile
  - 利用者ID追加
  - 権限付加
- OldFile -> NewFile
  - 利用者ID追加
  - 権限解除
- 量存在
  - 権限付加or解除
