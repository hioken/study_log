now = Time.zone.now
a = [
  {end_user_id: 2, ingredient_id: 1000, amount: 8, created_at: now, updated_at: now},
  {end_user_id: 2, ingredient_id: 1001, amount: 8, created_at: now, updated_at: now}
]
FridgeItem.insert_all(a, unique_by: %i[end_user_id ingredient_id])
