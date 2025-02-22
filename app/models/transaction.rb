class Transaction < ApplicationRecord
  belongs_to :user

  validates :amount, presence: true, numericality: true
  validates :transaction_type, presence: true
end
