class Ticket
  attr_reader :fare, :stamped_at

  def initialize(fare)
    @fare = fare
  end

  def stamp(station)
    @stamped_at = station
  end
end
