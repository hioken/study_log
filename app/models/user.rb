class User < ApplicationRecord
  has_many :transactions

  def total_amount
    transactions.sum(:amount)
  end

  def transaction_count
    transactions.count
  end
end
