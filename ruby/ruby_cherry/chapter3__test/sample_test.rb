require 'minitest/autorun'
require './testfile.rb'

class SampleTest < Minitest::Test
  def test_sample
    hensu = sample_method
    assert_equal 'RUBY', hensu
  end

  def test_sample2
    hensu = sample_method
    assert_equal 'RUBy', hensu
  end

  def test_sample3
    hensu = sample_method
    assert_equal 'RUBY', hensu
  end
end
