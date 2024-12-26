class BookCommentsController < ApplicationController
  before_action :authenticate_user!
  def create
    @book = Book.find(params[:book_id])
    @comment = BookComment.new(comment_params)
    @comment.book_id = params[:book_id]
    @comment.user_id = current_user.id
    unless @comment.save
      render "books/show"
    end
  end

  def destroy
    @comment = BookComment.find(params[:id])
    @comment.destroy
  end

  private
  def comment_params
    params.require(:book_comment).permit(:body)
  end
end
