require 'sidekiq/web'

Rails.application.routes.draw do
  mount Sidekiq::Web => "/sidekiq"  # http://localhost:3000/sidekiq で確認
  root "aggregations#top"
  get "aggregations", to: "aggregations#index"
  get "aggregations/stream", to: "aggregations#stream"
end
