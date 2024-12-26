def to_hex(r, g, b)
  rgb = [r, g, b] #引数を配列化
  # 配列を一つ一つ16進数に変換
  rgb.map! do |color|
    if (0..15).include?(color)
      "0#{color.to_s(16)}"
    else
      color.to_s(16)
    end
  end

  "##{rgb.join}" # 配列をカラーコードの文字列に変換
end

def to_ints(rgb)
  return 'カラーコードを入力してください' if rgb.slice!(0) != '#' #カラーコードの#を取り除く、また#付きではなかった場合にエラーを返す
  rgb = rgb.scan(/../) # 文字列を2文字ずつ配列にする
  rgb.map!{ |color| color.to_i(16) } # 配列を一つ一つ10進数の数値に変換する、また結果を戻り値に設定
  # 1~9, a ~ f以外が含まれている場合、errorのコードを書きたいけど、文字列を配列にした後1文字ずつチェックする方法以外が思いつかない
end
