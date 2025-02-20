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

# 作業ディレクトリの設定
WORKDIR /home/environment

# VSCodeの code コマンドをコンテナ内で使用できるようにする (code-server をインストール)
# RUN wget -qO- https://github.com/coder/code-server/releases/latest/download/code-server-linux-amd64.tar.gz | tar -xz -C /usr/local/bin --strip-components=1 \
#   && chmod +x /usr/local/bin/code-server \
#   && ln -s /usr/local/bin/code-server /usr/local/bin/code

# BundlerとRailsのインストール
RUN gem install bundler -v 2.4.22 && gem install rails -v 7.0.4.3

# ポートを開放
EXPOSE 3000

# コンテナ起動時に bundle install を実行
CMD ["bash"]
