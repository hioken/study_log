class MessagesController < ApplicationController
  def index
    @messages = Message.all($redis_slave)
  end

  def create
    message = Message.new(SecureRandom.uuid, params[:content])
    message.save($redis_master)
    redirect_to messages_path
  end
end
