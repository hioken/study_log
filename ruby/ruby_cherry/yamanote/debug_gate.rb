require_relative './gate.rb'
require_relative './ticket.rb'

  def setup
    @shinjuku = Gate.new(:shinjuku)
    @harajuku =Gate.new(:harajuku)
    @ebisu =Gate.new(:ebisu)
    @shinagawa = Gate.new(:shinagawa)
    @gotanda = Gate.new(:gotanda)
    @shinbashi = Gate.new(:shinbashi)
    @tokyo = Gate.new(:tokyo)
    @nippori = Gate.new(:nippori)
    @sugamo = Gate.new(:sugamo)
  end

    setup
    ticket = Ticket.new(140)
    @shinagawa.enter(ticket)
    p @gotanda.exit(ticket)

    ticket = Ticket.new(140)
    @shinagawa.enter(ticket)
    p @shinbashi.exit(ticket)
