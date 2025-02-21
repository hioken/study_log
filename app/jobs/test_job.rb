class TestJob < ApplicationJob
  queue_as :default

  def perform(*args)
    puts "TestJob 実行: #{args.inspect}"
    sleep 5
    puts "TestJob 完了"
  end
end
