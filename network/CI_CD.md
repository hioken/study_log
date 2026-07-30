## CI(Continuous Integration)
* プルリクエストなどをトリガーとした、統合前のチェックを指すアーキテクチャ
## CD(Continuous Delivery)
* 自動デプロイ
### Webhook
* VCS(git)ホスティングサービス(GitHub)とサーバーを繋げるサービス
* 設定を元に、リポジトリの更新情報を、サーバーにHTTP POSTリクエストとして伝える
### メインサーバー(setting)
* メインサーバーは、OAuthでGitHub APIにアクセスし、以下を登録
  * Webhookの送信先URL
  * 監視するイベント
* コントロールブレーンは、送られてきたリクエストのJSONをパースし、設定に基づいて再デプロイを実行