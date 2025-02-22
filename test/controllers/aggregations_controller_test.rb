require "test_helper"

class AggregationsControllerTest < ActionDispatch::IntegrationTest
  test "should get top" do
    get aggregations_top_url
    assert_response :success
  end

  test "should get index" do
    get aggregations_index_url
    assert_response :success
  end
end
