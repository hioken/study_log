## project
### ローカル同期
* `vercel env pull .env.local`: プロジェクトに紐づいた環境変数を読み込む
### project.json
* `{"projectId","orgId","projectName"}`
* Vercel APIへのリクエストヘッダーにこのファイルの情報が使われる

## project preparation
### 立ち上げ
* 依存関係の静的解析: Vercel CLIがローカルの`package.json`を解析
  * `dependencies` or `devDependencies`に`next`が存在し依存を確認、ビルド設定がVercelの環境設定にアサイン
* CLIからVercelのコントロールブレーンに対して、HTTP POSTリクエストが発行
  * REST APIの`/v9/projects`エンドポイント
  * `projectID`, `orgID`が発行: DBやデプロイメントを紐づけるための識別子
### ローカル
* メタデータの書き込み: `.vercel/`が生成
  * `project.json`: `{"projectId","orgId","projectName"}`
* `.env.local`: ローカルディレクトリとクラウド上の論理プロジェクトを紐づける
  * そのための環境変数(`VERCEL_OIDC_TOKEN`)

## project deployment
### 生成
1. ソースコードをメモリ上で圧縮(Tarball化 ※Next.js16~)し、vercelのBuild API EpへHTTP POST通信でアップロード
2. VercelがBuild Containerをスピンアップ、コンテナ内で`package.json`が読み込まれ、パッケージをインストール
3. TurbopackがAST解析とアセットグラフの構築を行う(静的部分のコンパイルやRCCの切り分け等)
4. ルートの動静の評価とAPIエンドポイント化(Server Actionsの変換等も)
* デプロイに最適化されたアーティファクトが完成
### アロケーション
1. 静的アセット: CDNへ伝搬
2. 動的コンポーネントやServer Actionsの実体は、Vercel Serverless Functionsとしてプロビジョニングされる
3. 全てのアセットの配置が完了すると、Vercel Edge Routerのルーティングテーブルが更新される
* このテーブルによって、リクエストによって、CDN Edge, CDN cache, NodeServerのどこにアクセスすべきか振り分ける
  * 直接Nodeに行くのはServer Actions等

## Neon DB
### プロビジョニング
* VercelのコントロールプレーンからNeonのREST APIへプロビジョニング要求(Webhook)
  * OIDC認証を利用
* 論理データベース、ロール、PgBouncer(コネクションプーラー)とその接続クレデンシャルがNeonのインフラストラクチャー上で自動生成される
  * 上記のインスタンス化と、分散ストレージ上の論理ボリュームの割り当て

## CI/CD
### Preview Deployments
* 作業ブランチがPushされるたび、独立した新しいサーバーインスタンスとURLを自動生成
* 本番環境のテストが行える

# 機能/設定(2026/07/18)
## Domains, Environment Variables
### ドメインの設定
* Project > Settings > Domains
## Observability
### Web Analytics
* Project > Analytics > Enable
* PV, ユニークビジター数等, アクセス系の情報
### Speed Insights
* Project > Speed Insights > Enable
* Core Web Vitalsのスコア化
### Runtime Logs
* Project > Logs
## Usage Limits
### Usage
* アカウント名 > uxdev Usage
* 無料上限に対して何%消費しているか
* Bandwidth: サイトのフロントダウンロード量
* Functions: バックエンド処理の実行回数
* Image Optimization: Next.jsの`<Image>`コンポーネントなどで圧縮した元画像の枚数