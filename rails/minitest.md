# Rails 7 における Minitest の使い方ガイド

## Fixture の設定方法
Fixture はテストデータを管理するために使用されます。Rails では `test/fixtures` ディレクトリ内に YAML ファイルを作成して設定します。

### 設定例
`test/fixtures/users.yml`:
```yaml
john:
  name: "John Doe"
  email: "john@example.com"
  created_at: <%= 10.days.ago %>

jane:
  name: "Jane Smith"
  email: "jane@example.com"
  created_at: <%= 5.days.ago %>
```

## def setup の使い方
テストクラス内で共通の初期設定を行いたい場合に `setup` メソッドを使用します。`setup` メソッド内に記述したコードは、各テストメソッドが実行される前に自動的に呼び出されます。

### 使用例
```ruby
require "test_helper"

class UserTest < ActiveSupport::TestCase
  def setup
    @user = users(:john)
  end

  test "user is valid" do
    assert @user.valid?
  end

  test "user email is present" do
    assert_not_nil @user.email
  end
end
```

## Fixture の読み込み
Fixture はデフォルトで `test_helper.rb` でロードされます。特定のフィクスチャを手動で読み込みたい場合、`fixtures` メソッドを使用します。

### 読み込み例
```ruby
class PostTest < ActiveSupport::TestCase
  fixtures :posts, :comments

  test "post has comments" do
    post = posts(:one)
    assert_not post.comments.empty?
  end
end
```

## Helper の読み込み方
Rails のヘルパーメソッドをテストで使用するには、`include` キーワードを使います。

### 設定例
```ruby
require "test_helper"

class UsersHelperTest < ActionView::TestCase
  include UsersHelper

  test "full name helper" do
    user = users(:john)
    assert_equal "John Doe", full_name(user)
  end
end
```

## テスト環境特有のメソッドとその目的
以下の表に、Minitest で使用されるテスト環境特有のメソッドをまとめました。

| メソッド名        | 引数 / ブロック                  | 引数とブロックの詳細                                                                                                                                             | メソッドの説明                                                                 |
|----------------|----------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------|
| `assigns`     | `:symbol`                 | インスタンス変数名をシンボルで指定します。例えば、`:user` を指定すると `@user` にアクセスします。                                                                  | コントローラのインスタンス変数を取得します。                                                  |
| `setup`       | `{ ... }`                 | 各テストの実行前に実行するコードブロックを指定します。                                                                                                      | 各テストの実行前に準備コードを実行します。                                                     |
| `teardown`    | `{ ... }`                 | 各テストの実行後に実行するコードブロックを指定します。                                                                                                      | 各テストの実行後にクリーンアップコードを実行します。                                             |

---

## アサーション一覧
以下に、Minitest で使用される主要なアサーションメソッドをまとめました。

| メソッド名           | 引数 / ブロック              | 引数、ブロックの詳細                                                                                                                                  | メソッドの説明                                                                 |
|-------------------|-----------------------|----------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------------------|
| `assert_response` | `status`               | `status` に期待する HTTP ステータス（例: `:success`, `:redirect`）を指定します。                                                             | HTTP ステータスを確認します。                                                      |
| `assert_redirected_to` | `url`                  | `url` に期待するリダイレクト先を指定します。                                                                                              | リダイレクトが期待通りであることを確認します。                                                 |
| `assert_template` | `template`             | `template` には期待するテンプレート名を指定します。                                                                                      | レンダリングされたテンプレートが期待通りであることを確認します。                                             |
| `assert_select`   | `selector`, `{ ... }`  | `selector` には CSS セレクタを指定し、ブロック内でその要素が正しいことを検証します。                                                           | レンダリングされた HTML の内容を確認します。                                                |
| `assert`          | `condition`, `{ ... }` | `condition` は評価されるべき真偽値を指定します。オプションでメッセージを指定可能。ブロックを渡す場合、ブロック内が評価されます。                                  | 条件が真であることを確認します。                                                       |
| `assert_not`      | `condition`, `{ ... }` | `condition` は評価されるべき真偽値を指定します。ブロックを渡す場合、ブロック内が評価されます。                                                   | 条件が偽であることを確認します。                                                       |
| `assert_equal`    | `expected, actual`     | `expected` に期待する値を、`actual` に実際の値を指定します。                                                                            | 値が等しいことを確認します。                                                         |
| `assert_nil`      | `object`               | `object` が `nil` であることを確認します。                                                                                      | 値が `nil` であることを確認します。                                                     |
| `assert_includes` | `collection, object`   | `collection` には配列やハッシュを指定します。`object` が `collection` に含まれていることを確認します。                                       | コレクションに特定の値が含まれていることを確認します。                                             |
| `assert_match`    | `regexp, string`       | `regexp` が `string` に一致することを確認します。                                                                                   | 正規表現が文字列に一致することを確認します。                                                     |
| `assert_no_match` | `regexp, string`       | `regexp` が `string` に一致しないことを確認します。                                                                                 | 正規表現が文字列に一致しないことを確認します。                                                   |
| `assert_operator` | `left, operator, right` | `left` と `right` を `operator`（例: `<`, `>=`）で比較します。                                                             | 2つの値の間に特定の演算子が成り立つことを確認します。                                                |
| `assert_not_operator` | `left, operator, right` | `left` と `right` を `operator`（例: `<`, `>=`）で比較します。                                                             | 2つの値の間に特定の演算子が成り立たないことを確認します。                                             |
| `assert_raises`   | `ExceptionClass`, `{ ... }` | `ExceptionClass` には期待する例外クラスを指定します。ブロック内で例外が発生することを確認します。                                               | ブロック内で特定の例外が発生することを確認します。                                                 |
| `assert_difference` | `expression, difference = 1`, `{ ... }` | `expression` は変化を確認したい式、`difference` は期待する変化量（デフォルトは1）。ブロック内で実行するコードを指定します。                             | 値が指定した量だけ変化することを確認します。                                                    |
| `assert_no_difference` | `expression`, `{ ... }`  | `expression` は変化を確認したい式。ブロック内で実行するコードを指定します。                                                                      | 値が変化しないことを確認します。                                                         |
| `assert_predicate` | `object, predicate`    | `object` は対象オブジェクト、`predicate` はメソッド名（例: `:empty?`）。                                                            | オブジェクトが特定の条件を満たすことを確認します。                                                |
| `assert_not_predicate` | `object, predicate`    | `object` は対象オブジェクト、`predicate` はメソッド名（例: `:empty?`）。                                                            | オブジェクトが特定の条件を満たさないことを確認します。                                             |
| `assert_broadcasts` | `stream, count`         | `stream` はブロードキャストするチャンネル名、`count` は期待するメッセージ数を指定します。                                                     | 指定したチャンネルに送信されるメッセージの数を確認します。                                             |
| `assert_no_broadcasts` | `stream`               | `stream` はブロードキャストするチャンネル名を指定します。                                                                            | 指定したチャンネルにメッセージが送信されないことを確認します。                                           |
| `assert_broadcast_on` | `stream, message`      | `stream` はブロードキャストするチャンネル名、`message` は期待するメッセージ内容を指定します。                                                 | 指定したチャンネルに特定のメッセージが送信されることを確認します。                                           |
| `assert_enqueued_with` | `params`, `{ ... }`    | `params` はジョブに渡されるパラメータを指定し、ブロック内でジョブがキューに追加されることを確認します。                                           | 指定したパラメータでジョブがキューに追加されることを確認します。                                           |
| `assert_performed_with` | `params`, `{ ... }`   | `params` はジョブに渡されるパラメータを指定し、ブロック内でジョブが実行されることを確認します。                                                | 指定したパラメータでジョブが実行されることを確認します。                                              |

これらのアサーションを使用して、テストの期待値を明確に記述できます。不明点があれば、遠慮なくお尋ねくださいね！

