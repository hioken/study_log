# DDL詳細
## テーブルの定義、カラムについて
- [定義について](./テーブル定義.md)

<br>

## CREATE TABLE詳細
- ~ テーブル名 (カラム名 データ型 制約)
```sql
CREATE TABLE table_name (
  id/*カラム名*/ INT/*データタイプ*/ PRIMARY KEY/*制約*/, /*複数レコードがある場合、,で区切る*/
  column_1 VARCHAR(10)/*文字数を指定*/ NOT NULL UNIQUE/*制約は複数選択可能*/,
)

/*制約は後からまとめて指定可能(not nullは別枠)*/
CREATE TABLE table_name (
  id INT,
  column_1 VARCHAR(10),
  column_2 VARCHAR(10),
  PRIMARY KEY(id), UNIQUE(column_1, column_2) /*制約*/
);
```

<br>

## ALTER TABLE詳細
- ~ テーブル名 命令 [対象の属性] (対象名) (追加or変更内容)
- 対象が限られている場合は対象を省略可能
- 命令
  - ADD: 追加、()でくくって,で区切ることで複数追加可能
  - DROP: 削除
  - CHANGE: 名前と定義を変更
  - MODIFY: 定義のみ変更
  - RENAME: 名前変更(MySQLでは使用不可)
  - AUTO_INCREMENT = 変更後: AUTO_INCREMENTのカウンタを変更する
- 対象の属性
  - COLUMN: カラム
  - INDEX: インデックス
  - 制約名: その制約
  - CONSTRAINT: 外部キー制約
- 複数選択
  - 命令文の文末に,を付けると、他の命令を続けられる
```sql
ALTER TABLE table_name
  CHANGE/*命令*/ COLUMN/*対象の属性(今回は省略可)*/ old_name/*対象名*/ new_name INT NULL/*変更内容*/
;

ALTER TABLE table_name
  ADD COLUMN (column_a INT, column_b INT), DROP COLUMN column_old;
```
