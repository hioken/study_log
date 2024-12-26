require 'minitest/autorun'
require_relative './rgb2.rb'

class RgbTest < Minitest::Test

  def test_to_hex
    assert_equal '#000000', to_hex(0, 0, 0)
    assert_equal '#0bcd0f', to_hex(11, 205, 15)
  end

  def test_to_ints
    assert_equal [0, 0, 0], to_ints('#000000')
    assert_equal [11, 205, 15], to_ints('#0bcd0f')
    #assert_equal 'カラーコードを入力してください', to_ints('aa')
  end

end
