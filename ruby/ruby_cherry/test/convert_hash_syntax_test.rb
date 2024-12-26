require 'minitest/autorun'
require_relative '../lib/convert_hash_syntax.rb'

class ConvertHashSyntaxTest < Minitest::Test
  def test_convert_hash_syntax
  old_syntax = <<~TEXT
    {
      :name => 'Anice',
      :age=>20,
      :gender  =>  :female
    }
TEXT

  expected = <<~TEXT
    {
      name: 'Anice',
      age: 20,
      gender: :female
    }
TEXT

    assert_equal expected, convert_hash_syntax(old_syntax)
  end
end
