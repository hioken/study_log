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
