class Gate
  STAITIONS = [:umeda, :juso, :mikuni]
  FARES = [150, 190]

  def initialize(name)
    @name = name
  end

  def enter(ticket)
    ticket.stamp(@name)
  end

  def exit(ticket)
    ticket.fare >= exit_fare(ticket)
  end

private
  def exit_fare(ticket)
    distance = STAITIONS.index(@name) - STAITIONS.index(ticket.stamped_at)
    FARES[distance - 1]
  end
end
