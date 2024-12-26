class Gate
  FARES = [140, 160, 170, 200, 260]
  DISTANCES = [0..10, 11..20, 21..30, 31..40, 41..100]
  STAITIONS = [[:shinagawa, 14], [:shinbashi, 7], [:tokyo, 6], [:akihabara, 3], [:ueno, 4], [:nippori, 4], [:tabata, 4], [:sugamo, 5], [:ikebukuro, 6], [:takadanobaba, 6], [:shinjuku, 6], [:harajuku, 8], [:ebisu, 9], [:gotanda, 9]]

  def initialize(name)
    @name = name
  end

  def enter(ticket)
    ticket.stamp(@name)
  end

  def exit(ticket)
    distance = distance_calc(ticket.stamped_at)
    fare = fare_calc(distance)
    fare <= ticket.fare
  end

  def distance_calc(from)
    station_only = STAITIONS.map { |station, distance| station }
    distance_only = STAITIONS.map { |station, distance| distance }
    station_1 = station_only.index(from)
    station_2 = station_only.index(@name)
    station_1, station_2 = station_2, station_1 if station_1 > station_2
    distance_1 =
      distance_only[station_1..(station_2 - 1)].inject(0) do |total, distance|
        total + distance
      end
    stations_array = distance_only[station_2..-1] + (station_1 == 0 ? [] : distance_only[0..(station_1 - 1)])
    distance_2 =
      stations_array.inject(0) do |total, distance|
        total + distance
      end
    [distance_1, distance_2].min
  end

  def fare_calc(distance)
    case distance
    when DISTANCES[0]
      FARES[0]
    when DISTANCES[1]
      FARES[1]
    when DISTANCES[2]
      FARES[2]
    when DISTANCES[3]
      FARES[3]
    when DISTANCES[4]
      FARES[4]
    else
      raise "プログラムに問題があります\n内容: 想定していないdistance\n原因のメソッド: distance_calc, fare_calc"
    end
  end
end
