require 'sidekiq/web'

Rails.application.routes.draw do
  mount Sidekiq::Web => "/sidekiq"  # http://localhost:3000/sidekiq で確認
end
