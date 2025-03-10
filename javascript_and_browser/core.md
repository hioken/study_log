# 言語仕様
## 説明
- Jsというのは、コアのECMScriptと実行環境ごとの拡張機能を総称した者
## 拡張機能
| 実行環境          | 使われる拡張機能       | 機能の説明                                                                |
|-------------------|------------------------|---------------------------------------------------------------------------|
| 共通          | ECMScript               | Jsのコア機能、変数の宣言等。                                                     |
| ブラウザ          | Web APIs               | DOM操作、イベントリスナー、AJAX、`fetch`、`localStorage`など、ブラウザ特有の機能。  |
| Node.js           | Node.jsモジュール群    | サーバーサイド向けのファイル操作（`fs`）、HTTP通信（`http`）、プロセス管理（`process`）など。別名commonjs。 |
| Deno              | Deno標準ライブラリ     | セキュアで最新の環境。HTTPサーバーやファイル操作、型定義（TypeScript）をネイティブでサポート。 |
| Electron          | Web APIs + Node.js    | ブラウザとNode.jsを組み合わせ、デスクトップアプリを開発するための環境。                |
| Google Apps Script| GoogleサービスAPI     | Google Workspace（スプレッドシートやGmailなど）と連携するためのAPI群。               |
| React Native      | React Native API      | モバイルアプリ用。UIコンポーネント（`View`, `Text`）、ネイティブモジュール呼び出しなど。  |

# ECMAScriptとグローバルオブジェクト
- **ECMAScript単体では動作できない**:
  - ECMAScriptはJavaScriptの言語仕様を定義したもので、単体では実行環境を持たない。
  - 実行するには、実行環境がグローバルオブジェクトを設定する必要がある。

- **グローバルオブジェクトが必要な理由**:
  - ECMAScript仕様では、グローバル変数や関数は必ずグローバルオブジェクトのプロパティとして登録される。
  - 実行環境がこのオブジェクトを作成しないと、JavaScriptコードは動作しない。

- **例: ECMAScriptの仕様に基づく動作**
```javascript
var globalVar = "Hello, World!";
console.log(globalThis.globalVar); // "Hello, World!"
```