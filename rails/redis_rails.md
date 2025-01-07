# チュートリアルメモ
## キャッシュとして
### 設定
- gem`redis`, `redis-rails`
- development.rb
  - gemを使わない場合は、Socket経由でコマンドを文字列として送りながらやり取り

`config/environments/development.rb`
```ruby
config.cache_store = :redis_cache_store, {
  url: ENV.fetch('REDIS_URL', 'redis://localhost:6379/1'),
  expires_in: 5.minutes
}
```

### 使用
- `Rails.cache`または`$redis`からcrudメソッドを呼び出す
- `<% cache "キー" ブロック %>; <% end %>`でブロック内のHTMLをキャッシュ

## セッション
### 設定
- `config/initializers/session_store.rb`
`session_store.rb`
```ruby
Rails.application.config.session_store :redis_store, {
  servers: [
    {
      host: ENV.fetch('REDIS_HOST', 'localhost'),
      port: ENV.fetch('REDIS_PORT', 6379),
      db: 2,
      namespace: 'session'
    }
  ],
  expire_after: 1.hour,
  key: '_myapp_session',
  threadsafe: true,
  secure: Rails.env.production?
}
```

### 使用
- 設定をすると、sessionの値がデフォルトのブラウザ(cookie)ではなくredisに保存される
- ブラウザにはsession_idのみ保存される

## ActionCableと連携
### 設定
`cable.yml`
```yml
development:
  adapter: redis
  url: redis://localhost:6379/1
  channel_prefix: myapp_development
```