class AggregationsController < ApplicationController
  include ActionController::Live  # SSE を使うために必要！

  def top
  end

  def index
  end

  def stream
    response.headers["Content-Type"] = "text/event-stream"
    response.headers["Cache-Control"] = "no-cache"
    response.headers["Connection"] = "keep-alive"

    sse = SSE.new(response.stream)

    begin
      6.times do |i|
        sse.write({ message: "処理 #{i + 1} 完了" }.to_json)
        response.stream.flush  # 🔥 ここでデータを即時送信
        sleep 5  # 🔥 5秒ごとにメッセージを送信
      end
    rescue IOError
      Rails.logger.info "SSE 接続がクライアント側で閉じられた"
    ensure
      sse.close
      response.stream.close
    end
  end
end
