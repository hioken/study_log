# 基礎
## Commands
### 共通
- 列を指定する状況では代わりに式を指定できる ※`INSERT`等の処理が破綻する場合を除く
- NULL
  - `GROUP BY`では、一つの値として扱われる
  - `COUNT`では、強制で対象から除外される 
  - `IS NULL`系の以外の比較演算子では、強制で対象から除外される
- `true`, `false`, `NULL`, `1`, `0`以外の真偽値は、DBによって代わる
- クエリの実行順序
  1. WITH句  
  2. FROM句  
  3. WHERE句  
  4. GROUP BY句  
  5. HAVING句  
  6. SELECT句  
  7. ORDER BY句  
  - ※ SELECT句で指定したエイリアスはそれより前に使えない

### DML(Data Manipulation Language)
| ワード                     | 説明                                                                                  |
|----------------------------|---------------------------------------------------------------------------------------|
| SELECT                    | テーブルからデータを取得するためのコマンド。                                           |
| INSERT INTO               | テーブルに新しいデータを挿入するためのコマンド。SELECTをVALUESの代わりに使える                       |
| UPDATE                    | 既存データを更新するためのコマンド。                                                   |
| DELETE FROM               | テーブルからデータを削除するためのコマンド。                                           |

``` sql
<DML + table or columns> <DML_data>

SELECT <columns> FROM <table> !<where句>;
INSERT INTO <table> (<columns>) VALUES (<values>);
INSERT INTO <table> (<columns>) SELECT ~;
UPDATE <table> SET <updates> !<where句>;
DELETE FROM <table> !<where句>;
```

### Query support
#### Query Clauses
| 修飾句         | 説明                                                                                     |
|----------------|-----------------------------------------------------------------------------------------|
| WITH           | 共通テーブル式（CTE）を定義し、クエリ内で再利用可能な一時的な結果セットを作成する。         |
| WHERE          | 指定した条件に一致する行をフィルタリングする。                                             |
| GROUP BY       | 行をグループ化し、各グループに対して集約関数を適用する。                                   |
| HAVING         | GROUP BYでグループ化した後、グループ単位で条件をフィルタリングする。                       |
| ORDER BY       | 結果セットを指定したカラムや計算結果に基づいて並べ替える。                                 |
| LIMIT / OFFSET | 取得する行数を制限したり、結果の開始位置を指定する（MySQL, PostgreSQLなどで使用）。         |
| TOP            | SELECT文で取得する行数を制限する（SQL Serverなどで使用）。                                  |

#### Query Modifier
| 修飾子         | 説明                                     | 記述位置          |
|----------------|-----------------------------------------|-------------------|
| DISTINCT       | 結果セットから重複する行を排除する       | 対象カラム等の直前    |
| ALL            | 全ての行を返す（デフォルトで省略可能）   | 対象カラム等の直前    |
| LIMIT          | 結果セットの行数を制限                  | クエリの末尾      |
| OFFSET         | 結果セットの先頭n件をスキップする       | クエリの末尾      |
| FETCH          | 結果セットの一部を取得（SQL標準対応）   | クエリの末尾      |

### Alias Syntax
##### 概要
- `AS エイリアス名`で仮想テーブルや式の結果にエイリアスを付ける
``` sql
<table or columns or expression> AS <alias_name>
<table or columns or expression> <alias_name>

SELECT id, 'constant' FROM <table>; -- 定数
```
##### 補足
- 以下の仮想テーブルとして扱われる場面ではエイリアスが必須
  - FROM句（メイン用途）
  - WITH句（共通テーブル式）
  - サブクエリ（EXISTSやINなど）
  - マテリアライズドビュー
  - 一時テーブル
  - 分析関数のPARTITION BYや結合における特殊な構文（例: LATERAL）
- 有効な使い方
  - 式に名前を付ける
  - カラムの意味を明確にする
  - カラム名の被り防止(※エイリアス必須)

### Expressions(式)
#### Constant(定数)
##### 補足
- 列に定数を指定してエイリアスを付けていない場合、DBによって、列名が定数の値かNo Columnsになる

#### Logical Operators / Arithmetic Operators / Predicates
| 条件式                  | trueの条件                               |
|-------------------------|-----------------------------------|
| NOT (式)             | 否定、()で囲えば論理演算子にも適応 |
| AND, OR             | いつもの |
| +, -, *, /, %  | いつもの            |
| =, <>or!=, >, >=, <, <=  | いつもの            |
| BETWEEN ... AND ...      | 値が指定した範囲内にある場合      |
| IN (..., ..., ...)       | 値が指定リスト内にある場合        |
| LIKE 'str'              | 文字列が指定パターンに一致する場合|
| IS NULL                 | 値がNULLの場合                   |
| IS NOT NULL             | 値がNULLでない場合               |
| EXISTS (サブクエリ)      | サブクエリが結果を返す場合        |
| ANY (サブクエリ)         | サブクエリ結果のいずれかと一致する場合 |
| ALL (サブクエリ)         | サブクエリ結果のすべてと一致する場合 |

##### 保続
- LIKE/NOT LIKEの補足
  - ワイルドカード
    - `%` 任意の文字列
    - `_` 任意の一文字
- EXISTSの補足
  - 基本相関サブクエリとしてのCTEと一緒に使う

#### Scalar Functions
| 関数                        | データ型      | 説明                                         |
|-----------------------------|---------------|---------------------------------------------|
| LENGTH(column)              | 文字列        | 文字列の長さを取得                          |
| UPPER(column)               | 文字列        | 文字列を大文字に変換                        |
| LOWER(column)               | 文字列        | 文字列を小文字に変換                        |
| CONCAT(column1, column2)    | 文字列        | 文字列を結合                                |
| ROUND(column, int)          | 数値          | 数値を指定した桁数で丸める                  |
| ABS(column)                 | 数値          | 数値の絶対値を取得                          |
| NOW()                       | 日時          | 現在の日時を取得                            |
| CURDATE()                   | 日時          | 現在の日付を取得                            |
| DATE_ADD(column, interval)  | 日時          | 日付に指定した期間を加算                    |
| EXTRACT(part FROM column)   | 日時          | 日付や時間から特定の部分（年、月、日など）を抽出 |
| CAST(column AS data_type)   | 変換          | データ型を指定した型に変換する              |
| COALESCE(column1, column2, ...) | NULL処理      | NULLをデフォルト値に置き換える              |

#### Aggregate Function
| 関数          | 説明                             |
|---------------|---------------------------------|
| COUNT         | 行数を数える                     |
| SUM           | 数値列の合計を計算               |
| AVG           | 数値列の平均を計算               |
| MIN           | 列の最小値を取得                 |
| MAX           | 列の最大値を取得                 |
| VARIANCE      | 数値列の分散を計算               |
| STDDEV        | 数値列の標準偏差を計算           |
| GROUP_CONCAT  | グループ内の値を連結する（MySQL限定） |
| STRING_AGG    | グループ内の値を連結する（PostgreSQL）|
| MEDIAN        | 中央値を取得（PostgreSQL対応環境で利用可能） |
```sql
SELECT <aggregate>(<column>) FROM <table>
```
##### 補足
- 集約関数は呼び出されるたびに、現在の結果の全レコードを対象に引数の式を評価していくループ処理を行う

#### CASE式
##### Syntax
```sql
-- 単純形式 case後の値が、条件と一致するか
CASE <column etc>
  WHEN <expression1> THEN <value>
  WHEN <expression2> THEN <value>

-- 検索形式 式がtrueかどうか
CASE
  WHEN <expression1> THEN <value>
  WHEN <expression2> THEN <value>
  ELSE <value>
```
##### 概要
- ELSEを書かなかった場合 `ELSE NULL`が追加される



### DDL(Data Definition Language)
| ワード          | 対象                       | 説明                                |
|------------------|----------------------------|-------------------------------------|
| CREATE           | DATABASE, TABLE, VIEW      | 対象を作成                         |
| DROP             | DATABASE, TABLE, VIEW      | 対象を削除                         |
| ALTER            | TABLE, VIEW                | 対象の構造を変更                   |
| ADD COLUMN       | TABLE                      | 新しいカラムを追加                 |
| DROP COLUMN      | TABLE                      | 既存カラムを削除                   |
| MODIFY COLUMN    | TABLE                      | カラムのデータ型や制約を変更       |
| RENAME COLUMN    | TABLE                      | カラムの名前を変更                 |
| CHANGE COLUMN    | TABLE                      | カラム名とデータ型/制約を変更       |
| ADD CONSTRAINT   | TABLE                      | 制約を追加                         |
| DROP CONSTRAINT  | TABLE                      | 制約を削除                         |

```sql
-- target = DATABASE or TABLE
<DDL> <target> <target_name>

CREATE TABLE <table> (
  <column_name> <data_type> <constraint>,
  <colun_2> <data_type>
)

ALTER TABLE <table> <option> <target_column>
ALTER TABLE <table> <option> <old_column> !<to> <new_column> <new column> <constraints>

```

### DCL (Data Control Language)
#### 権限
| ワード                     | 説明                                                                                  |
|----------------------------|---------------------------------------------------------------------------------------|
| GRANT                     | 特定の操作に対する権限を付与する。                                                     |
| REVOKE                    | 付与した権限を削除する。                                                               |
| DENY                      | 特定の権限を明示的に拒否する。                                                         |
```sql
<DCL> <table> <TO or FROM> <user_name>
```

#### ユーザー管理
| ワード                     | 説明                                                                                  |
|----------------------------|---------------------------------------------------------------------------------------|
| CREATE USER               | 新しいユーザーを作成する。                                                             |
| ALTER USER                | 既存ユーザーの設定を変更する。                                                         |
| DROP USER                 | ユーザーを削除する。                                                                   |
```sql
<COMMAND> 'user_name' [IDENTIFIED BY 'password' | WITH PASSWORD 'new_password']
```

#### 権限確認と削除
| ワード                     | 説明                                                                                  |
|----------------------------|---------------------------------------------------------------------------------------|
| SHOW GRANTS               | ユーザーに付与された権限を確認する。                                                   |
| REVOKE ALL PRIVILEGES     | すべての権限を削除する。                                                               |
| REVOKE GRANT OPTION       | 権限付与のオプションを削除する。                                                       |
| GRANT OPTION              | 他のユーザーに権限を付与するためのオプション。                                         |
| REVOKE WITH GRANT OPTION  | 権限付与オプションを削除する。                                                         |
| SET PASSWORD              | ユーザーのパスワードを設定または変更する。                                             |
```sql
<COMMAND> <privileges> ON <table> <TO or FROM> <user_name>

SET PASSWORD FOR <user_name> = PASSWORD(<new_password>);
```

| ワード                     | 説明                                                                                  |
|----------------------------|---------------------------------------------------------------------------------------|
| CREATE ROLE               | 新しいロール（権限の集合）を作成する。                                                 |
| DROP ROLE                 | 既存のロールを削除する。                                                               |
```sql
<COMMAND> role_name;
```

### TCL (Transaction Control Language)
#### トランザクション制御
| ワード                     | 説明                                                                                  |
|----------------------------|---------------------------------------------------------------------------------------|
| COMMIT                    | トランザクションを確定する。                                                           |
| ROLLBACK                  | トランザクションを取り消す。                                                           |
| SAVEPOINT                 | 復帰ポイントを設定する。                                                              |
| RELEASE SAVEPOINT         | 設定された復帰ポイントを解除する。                                                    |
| ROLLBACK TO SAVEPOINT     | 指定された復帰ポイントまでロールバックする。                                           |
| SET TRANSACTION           | トランザクションの分離レベルなどの特性を設定する。                                     |
```sql
<COMMAND> [SAVEPOINT <savepoint_name> | TRANSACTION ISOLATION LEVEL <level>]
```

### Meta Commends
| Command                       | 概要                                                            |
|-------------------------------|-----------------------------------------------------------------|
| SHOW DATABASESorTABLESorCOLUMNS FROM table_name | 利用可能なDB, テーブル, 構造一覧を表示           |
| DESCRIBE table_name           | 指定テーブルの構造を表示（SHOW COLUMNSと同じ）               |
| EXPLAIN SELECT query          | クエリの実行計画を表示しパフォーマンス最適化に利用           |
| SHOW STATUS                   | サーバーの統計情報（接続数やクエリ数など）を表示             |
| SHOW VARIABLES                | 設定値（タイムゾーンや文字セットなど）を表示                 |
| SET variable = value          | セッションやグローバル設定を変更                             |



## Object
### Data Object
#### 本体オブジェクト
| 名称                     | 説明                                                                                  |
|--------------------------|---------------------------------------------------------------------------------------|
| TABLE                   | データを格納する基本単位。                                                             |
| VIEW                    | 仮想的なテーブルで、SQLクエリの結果をテーブルのように扱える。                           |
#### 補助オブジェクト
| 名称                     | 説明                                                                                  |
|--------------------------|---------------------------------------------------------------------------------------|
| INDEX                   | データ検索を高速化する補助的な仕組み。                                                 |
| TRIGGER                 | 特定のイベント（INSERT、UPDATE、DELETE）が発生した際に自動実行される処理。             |
| SEQUENCE                | 一意な値を生成するための仕組み（オートインクリメントのカスタム版のようなもの）。         |
| SYNONYM                 | テーブルやビューなどのオブジェクトに対する別名を設定する仕組み。                         |
| FUNCTION                | パラメータを受け取り、特定の処理を実行して値を返す再利用可能なカスタムロジック。         |
| PROCEDURE               | 処理を実行する再利用可能なカスタムロジック（値を返さない場合が多い）。                   |
##### 補足
- index
  - 予め整列させた索引を作成
    - キャッシュへのアクセスを効率化
    - 比較演算をする際に、走査するべきレコードの位置へ適切にジャンプし、無駄な走査を減らす

### Data Type
| データ型                | 説明                                                                                   |
|-------------------------|---------------------------------------------------------------------------------------|
| INT                    | 整数型（符号付き: -2,147,483,648～2,147,483,647）。                                    |
| BIGINT                 | 非常に大きな整数型（符号付き: -2^63～2^63-1、符号なし: 0～2^64-1）。                   |
| DECIMAL (NUMERIC)      | 固定小数点型。精度とスケールを指定して正確な値を扱う（例: DECIMAL(10,2)）。             |
| FLOAT                  | 浮動小数点型（近似値、精度に制限がある）。                                              |
| VARCHAR(n)             | 可変長文字列型。文字列の長さに応じた領域を使用（最大長を指定）。                       |
| TEXT                   | 大きなテキストデータ用。最大65,535文字を格納可能（MySQLの場合）。                       |
| DATE                   | 年月日を扱う型（YYYY-MM-DD形式）。                                                      |
| DATETIME               | 年月日と時刻を扱う型（YYYY-MM-DD HH:MM:SS形式）。                                       |
| TIMESTAMP              | 年月日と時刻を扱う型（UNIXタイムスタンプとして保持）。                                  |
| JSON                   | JSON形式でデータを格納する型（主にMySQL 5.7以降）。                                     |
| BOOLEAN (BOOL)         | 真偽値型（MySQLではTINYINT(1)として実装される）。                                        |

### Constraint
#### テーブル対象の制約
| 制約 (Constraint)      | 説明                                                                                 |
|-------------------------|-------------------------------------------------------------------------------------|
| PRIMARY KEY            | テーブル内の各行を一意に識別するための制約。通常、最も重要でよく使われる。          |
| FOREIGN KEY            | 他のテーブルのカラムを参照し、リレーションを定義する制約。                           |
| UNIQUE (複数カラム)    | 複数カラムを組み合わせた重複禁止ルール（1カラムの場合はカラム対象）。                |
| CHECK                  | テーブルレベルで条件を指定することも可能（例: 複数カラム間の条件）。                  |
| ON DELETE / ON UPDATE  | FOREIGN KEYに関連し、参照先データの削除/更新時の挙動を指定する。                     |

#### カラム対象の制約
| 制約 (Constraint)      | 説明                                                                                 |
|-------------------------|-------------------------------------------------------------------------------------|
| PRIMARY KEY            | 単一カラムに設定される場合（テーブル全体を定義する場合もある）。                     |
| AUTO_INCREMENT         | 主に数値型カラムに適用され、新しい行の値を自動でインクリメントする制約。             |
| UNIQUE                 | そのカラムの値が一意である必要がある制約。                                           |
| NOT NULL               | カラムがNULL値を許さない制約。データ整合性のために非常に多用される。                 |
| DEFAULT                | カラムに値が指定されなかった場合にデフォルト値を設定する制約。                       |
| CHECK                  | カラムの値が特定の条件を満たすかを検証する制約（例: 値が0以上であること）。          |
| GENERATED (計算カラム) | 特定の計算式でカラムの値を生成する制約（MySQLやPostgreSQLでサポート）。               |


# 応用機能
## 仮想テーブル
### Subquery
#### Scalar Subquery(スカラサブクエリ)
- サブクエリの結果が単一の値(1列/1行)の場合、サブクエリを、その結果の値として式の中で扱える
#### Correlated Subquery(相関サブクエリ)
```sql
SELECT * FROM employees AS e1
WHERE salary > (
  SELECT AVG(salary) FROM employees AS e2
  WHERE e1.department_id = e2.department_id
);
```
##### 補足
- CTE+joinの処理がほぼ上位互換のため、使いどころはない

### CTE
##### 作成
```sql
WITH <ctename> AS (<selectクエリ>) <通常のselectクエリ>
```
##### 概要
- 再利用性、デバッグ性や可読性等を上げる
- 使いどころ
  - 相関サブクエリの代わりとして使う(後述)
  - union等、複数のクエリがつながる場合に再利用性を高める
  - サブクエリをJOINしたい時に、サブクエリをCTEとして定義して効率化を計る
- WHERE条件で、事前に求めた結果を基に判断する場合、クエリの最初にその結果をまとめた表を作る。
  - 例：「同一ジャンルの平均よりカラムが高い」など
  - 相関サブクエリの上位互換

### View
##### 作成
```sql
CREATE VIEW <view_name> (<view_columns>) AS <select句>
```
##### 概要
- select句をviewとして保存
  - 後述の機能がある理由で完全なエイリアスとは行けないけど、エイリアスとしての意味合いが強い
- 条件を満たしたviewに対してはDMLを実行可能
  - この際、viewの参照元のテーブルが更新される
- viewを元のにしたviewを作成可能

## 結合
### 列結合(JOIN)
##### 概要
- 特定条件で横方向に複数のテーブルを結合
- ON句の式がtrueだと結合される
  - 実際は最低各テーブル一つ以上のカラムを比較演算する
- 冗長化を防ぐため、FROM句でエイリアスを指定するのが一般的
- 外部結合では、結合したレコードを全て出力した後、起点のテーブルの結合しなかったレコードを出力
##### Syntax
| JOINの種類       | 説明                                |
|-------------------|-------------------------------------|
| INNER JOIN        | 両方のテーブルで条件に一致する行のみを取得 |
| LEFT JOIN         | 左側のテーブルの全行と、条件に一致する右側の行を取得 |
| RIGHT JOIN        | 右側のテーブルの全行と、条件に一致する左側の行を取得 |
| FULL OUTER JOIN   | 両方のテーブルの全行を取得、条件に一致しない部分はNULL |
| SELF JOIN         | 同じテーブル同士でJOINを行う |
| CROSS JOIN        | 両方のテーブルのすべての行を組み合わせる（デカルト積） |
| NATURAL JOIN      | 同名のカラムを条件に自動的に結合 |
```sql
SELECT <t1.culumn> <t2.column> <etc>
FROM table1 t1 <JOIN> table2 t2
ON <expression> -- CROSS JOIN と NUTURAL JOIN は不要
<query supports>
```



### 行結合(集合演算)
##### 概要
- 特定条件で縦方向に複数のテーブルを結合する
- 結合する列それぞれのデータ型が一致している必要がある
- デフォルトでは重複行は削除され、ALLオプションを付けると重複行も表示する
- 基本的な設計では、ほとんどの場合`WHERE + ORDER BY`や列結合(`JOIN`)の方が優秀
- 行結合が有効な特殊な設計
  - Partial Indexを組み込んだ特殊なIndex管理
  - 膨大なデータの効率化のために、年間売上/月間売上, オンライン販売商品/オフライン販売商品等を分けている大規模なDB
##### Syntax
| 演算子       | 説明                                      |
|--------------|-------------------------------------------|
| UNION        | 複数のクエリ結果を結合する                |
| INTERSECT    | 複数のクエリ結果の共通部分を取得する      |
| EXCEPT       | 最初のクエリ結果から2番目を除外する       |
| ALLオプション| 重複行を含めて処理を行う                 |
```sql
<Query>
<集合演算子>
<Query>
```

## 高度知識
### メタデータストア
- テーブル、カラム、ビュー等を保存している領域の名称
### index詳細
##### list
| 種類               | 概要                                | 有効なシナリオ                     | 呼び出す際に使う句                       |
|--------------------|-------------------------------------|-----------------------------------|-----------------------------------------|
| Clustered Index   | データの物理的な並び順を決定する索引 | 自動的にPRIMARY KEYに適用  |                |
| Unique Index      | カラムの値の一意性を保証する索引      | 重複を防ぎたいカラム              |  |
| B-tree            | B-treeアルゴリズムに基づく一般的な索引 | 等価・範囲検索、JOIN              | WHERE column = ? / WHERE column > ?     |
| Hash Index        | ハッシュテーブルを使った索引         | 完全一致の検索                    | WHERE column = ?                        |
| Partial Index     | 特定の条件を満たす行に対する索引      | 条件に偏りがあるクエリ、UNION     | WHERE column = ? AND condition / UNION  |
| Full-text Index   | テキストデータの全文検索用索引       | テキストの部分一致や全文検索      | WHERE MATCH(column) AGAINST(?)          |
| Spatial Index     | 空間データ向けの索引                | 地理情報や2D/3D空間データ          | WHERE ST_Contains(column, ?)            |
| Non-clustered Index | 物理データの順序に影響しない索引   | 頻繁に特定カラムが検索される場合   | WHERE column = ?                        |
| Bitmap Index      | ビットマップを使ってデータを管理     | カーディナリティが低いカラム      | WHERE column IN (?, ?)                  |
| Covering Index    | 必要なカラムを全て含む索引          | 特定カラムだけ参照するクエリ      | SELECT specific_columns                 |
| Descending Index  | 降順で並び替えられる索引            | ORDER BY DESCを多用する場合        | ORDER BY column DESC                    |
| Composite Index   | 複数カラムを組み合わせた索引        | 複合条件検索、複数カラムでのソート | WHERE column1 = ? AND column2 = ?       |

##### 前提知識（I/Oやキャッシュ）
###### I/O（Input/Output）とは？
- I/O: Input/Output（入力/出力）の略。  
- 役割: ストレージ（HDDやSSD）とメモリ（RAM）間でデータを読み書きする処理。  
- ポイント:  
   - メモリ: 超高速だが容量が限られる。  
   - ストレージ: 大容量だがメモリより遥かに遅い。  
- ボトルネック: I/Oコスト（ディスクI/O）が発生するとクエリのパフォーマンスが大幅に低下する。  
###### キャッシュ効率とは？
- キャッシュ: 頻繁にアクセスされるデータをメモリ上に保持する仕組み。  
- 役割: ストレージからの読み込みを最小限に抑え、データを高速に提供。  
- ポイント:  
   - インデックスがあると、連続したデータ範囲をメモリに「ごっそり」キャッシュしやすい。  
   - I/Oの回数を減らし、無駄なディスクアクセスを回避する。  
##### indexの役割
- データが階層構造で整理され、効率的にデータを検索・取得できる。  
  - 具体的には、想定されているアルゴリズム用の索引やそれに近い階層構造の索引を作成しておく事で、B-treeやその派生のアルゴリズムを使い、少ない読み込み回数で目的のレコードに到達できる
  - 検索条件や、join等に合わせて最適な各アルゴリズムが用意されている
  - データ型やFK等のカラムの状態によってindexの管理構造が最適化されている
    - FKの場合は、各FKに対応したレコードのアドレスが索引になっている等
- **indexはレコードのCUD毎に更新されるため、索引が多いとCUD処理は重くなる**
- また、複数のindexがある場合はどのindexを使うか判断する処理が必要になるため、多いと逆にR処理まで重くなっています

##### 1側とN側のインデックス3パターンまとめ
| パターン               | 1側へのアクセス    | N側へのアクセス       | パフォーマンス      |
|-------------------------|--------------------|------------------------|--------------------|
| index無し × index無し   | キャッシュ効率が悪い | 全レコードを走査        | 最悪               |
| indexあり × index無し   | キャッシュ効率が良い | 全レコードを走査        | 部分的に改善       |
| indexあり × indexあり   | キャッシュ効率が良い | 必要なレコードだけ走査  | 劇的に改善         |

# 記述例まとめ
- CTE + EXISTS
```sql
WITH HighSalaryDepartments AS (
    SELECT department_id
    FROM employees
    GROUP BY department_id
    HAVING AVG(salary) > 100000
)
SELECT e.employee_id, e.employee_name
FROM employees e
WHERE EXISTS (
    SELECT 1
    FROM HighSalaryDepartments hsd
    WHERE e.department_id = hsd.department_id
);
```