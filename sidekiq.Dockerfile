# Ruby イメージをベースにする
FROM ruby:3.2.5

# 必要なパッケージをインストール
RUN apt-get update -qq && apt-get install -y \
  build-essential \
  libsqlite3-dev \
  imagemagick \
  nodejs \
  yarn \
  vim \
  wget \
  curl \
  unzip \
  redis-tools

# 作業ディレクトリを設定
WORKDIR /home/environment

# Bundler をインストール
RUN gem install bundler -v 2.4.22

# Sidekiq を動かすために Rails の依存関係をインストール
COPY Gemfile ./
RUN bundle install

# Sidekiq を起動するコマンドを設定
CMD ["bundle", "exec", "sidekiq"]
