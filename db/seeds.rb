# ユーザー5人作成
5.times do |i|
  user = User.create!(name: "ユーザー#{i + 1}")

  # 各ユーザーに12件のAggregationデータを追加
  12.times do
    user.transactions.create!(
      amount: rand(100..500),
      transaction_type: ["purchase", "refund"].sample
    )
  end
end
