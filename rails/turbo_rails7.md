# Fetch API
**概要**
- `fetch`関数はHTTPリクエストを送信し、レスポンスを待たずに他の処理を並列で行うことで非同期処理を実現するJavaScriptの組み込み機能。
- Ajaxと基本的に同じことを行うが、jQueryに依存するAjaxよりもモダンなコーディングスタイルに適している。

---

# Hotwire
**概要**
- Railsに組み込まれた「高速でインタラクティブなユーザーインターフェースを構築するためのツールキット」。
- アーキテクチャが「ルール」ならば、Hotwireは「提案」に近い。
- Reactなどを用いたSPAではバックエンドとフロントエンドでデータ処理が二重になり、無駄が発生する。
- HotwireではHTMLをレスポンスとして返し、状態管理をサーバーサイドのみで行う。
- **Turbo**、**Stimulus**、**Strada**の3つの技術から構成される。
- **Turbo**はさらに以下の4つに分かれる：
  - **Drive**
  - **Frames**
  - **Streams**
  - **Native**: アプリケーション用

---

## Turbo
### Turbo概要
- JavaScriptライブラリ。
- 追加でJSを書くことなく、SPAのようなインタラクティブなアプリケーションを構築できる。
- **SPA (Single Page Application)**
  - インタラクティブ（双方向的）な動作。
  - 例: Gmail。
- HTTPメソッド**GET**では動作しない。
- 現在のページのCSS/JavaScriptをそのまま使用することで、高速な画面切り替えを実現。
- Driveは旧turbo-links
- frameとstreamは似ているが、使う場合の思想に違いがある
  - streamは画面全体に大きな影響を及ぼすため、他のフォーマットにも対応するアクションに使う
  - frameは基本このリクエストしか来ないものとして使う(respond_toがいらない設計にしたい)

| 機能         | 特徴       | 詳細                                         |
|--------------|------------|----------------------------------------------|
| **Turbo Drive** | **全体置換** | レスポンスされたHTMLの`<body>`要素を抜き出して置換する（`<head>`はマージされる）。 |
| **Turbo Frames**| **部分置換** | `<turbo-frame>`タグにのみレスポンスを適用する。          |
| **Turbo Streams**| **複数箇所の更新** | 追加、更新、削除が可能。指定の`<turbo-stream>`タグにレスポンスを適用する。 |

### 記述方法
#### Stream(レスポンスが全体)
1. `respond_to { |f| f.turbo_steam }`またはデフォルトで`app/views/controllers/action.turbo_stream.erb`が読み込まれる
2. レスポンス用のviewの`<turbo-stream>`タグのtarget属性の要素をaction属性に従って操作する
- 変数はlocalsで明示する
- 応用
```ruby
# 直接内容を記述
turbo_stream.アクション属性名("target", partial: "partial", locals: (variable: variable))

# 違うテンプレート
render :template
respond_to { |f| f.turbo_stream {render: :template}}
```
#### Frame(レスポンスがパーシャル)
0. 予め置換したい位置を`<turbo-frame id="">`で囲う
1. `render パーシャル内容`で指定した`<turbo-frame>`月のパーシャルを返す
2. `<turbo-frame>`の内容がレスポンスに置き換わる

- 変数はインスタンス変数とlocalsでの明示両対応

### Gem turbo-rails
- Turbo用のGem。
- Turbo自体はRailsから直接使用することも可能。

#### **メリット**
- 記述量の短縮。

---

## Stimulus

**概要**
- Hotwireの一部として設計されたJavaScriptフレームワーク。
- サーバーサイドで生成されたHTMLに、簡単に動的な振る舞いを追加する。
- フロントエンドロジックをシンプルに保ち、HTML中心のアプローチを実現。

**特徴**
- コントローラ単位で動作する。
- DOM要素に直接アクションを関連付ける。
- データ属性を使用して、動的な振る舞いを定義。

**使い方**
1. **コントローラの定義:** StimulusコントローラをJavaScriptで作成。
2. **HTML要素へのアタッチ:** `data-controller`属性を使用してコントローラを要素に関連付ける。
3. **アクションの定義:** `data-action`属性でイベントとアクションを指定。

**例**
```html
<div data-controller="example">
  <button data-action="click->example#hello">Click Me</button>
</div>
```
```javascript
// example_controller.js
import { Controller } from "@hotwired/stimulus"
export default class extends Controller {
  hello() {
    alert("Hello from Stimulus!");
  }
}
```

---

## Strada

- モバイルアプリケーション開発用のライブラリ。
- **未完成**の段階。

