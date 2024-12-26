class FavoritesController < ApplicationController
  before_action :authenticate_user!
  # POST /books/:book_id/favorites
  # POST /favorites.json

  def create
    book = Book.find(params[:book_id])
    @favorite = book.favorites.new(user_id: current_user.id)
    @favorite.save
    # redirect_to request.referer
    # redirect_back(fallback_location: book_path(book))
  end

  def destroy
    book = Book.find(params[:book_id])
    @favorite = book.favorites.find_by(user_id: current_user.id)
    @favorite.destroy
    # redirect_to request.referer
    # redirect_back(fallback_location: book_path(book))
  end


  # def create
  #   if !Favorite.find(book_id: params[:book_id], user_id: current_user.id).exists?
  #     @favorite = current_user.favorites.new(:book_id => params[:book_id])
  #     @favorite.save
  #     redirect_to books_path
  #   end
  # end


  # # DELETE /books/:book_id/favorites/
  # def destroy
  #   if Favorite.find(book_id: params[:book_id], user_id: current_user.id).exists?
  #     @favorite = Favorite.find_by(user_id: current_user, book_id: params[:book_id])
  #     @favorite.destroy
  #     redirect_to books_path
  #   end
  # end
end
