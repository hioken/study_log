STATIONS = [[:shinagawa, 14], [:shinbashi, 7], [:tokyo, 6], [:akihabara, 3], [:ueno, 4], [:nippori, 4], [:tabata, 4], [:sugamo, 5], [:ikebukuro, 6], [:takadanobaba, 6], [:shinjuku, 6], [:harajuku, 8], [:ebisu, 9], [:gotanda, 9]]

p station_only = STATIONS.map { |station, distance| station }
p distance_only = STATIONS.map { |station, distance| distance }
p [] + station_only[1..1]


a = 4
case a
when 1..3
  p '1'
when 4..6
  p '2'
else
  p '3'
end
