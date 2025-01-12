class MessagesController < ApplicationController
  def index
    # @messages = Message.all($redis_slave)
    @messages = Message.all_from_shards
  end

  def create
    message = Message.new(Message.generate_id, params[:content])
    # message.save($redis_master)
    message.save_to_shard
    redirect_to messages_path
  end
end