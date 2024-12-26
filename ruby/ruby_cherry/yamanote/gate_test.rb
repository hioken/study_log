require 'minitest/autorun'
require_relative './gate.rb'
require_relative './ticket.rb'

class GateTest < Minitest::Test
  def setup
    @shinagawa = Gate.new(:shinagawa)
    @shinbashi = Gate.new(:shinbashi)
    @tokyo = Gate.new(:tokyo)
    @akihabara = Gate.new(:akihabara)
    @ueno = Gate.new(:ueno)
    @nippori = Gate.new(:nippori)
    @tabata = Gate.new(:tabata)
    @sugamo = Gate.new(:sugamo)
    @ikebukuro = Gate.new(:ikebukuro)
    @takadanobaba = Gate.new(:takadanobaba)
    @shinjuku = Gate.new(:shinjuku)
    @harajuku =Gate.new(:harajuku)
    @ebisu =Gate.new(:ebisu)
    @gotanda = Gate.new(:gotanda)
  end

  def test_shinagawa_to_gotanda_enough_ticket140
    ticket = Ticket.new(140)
    @shinagawa.enter(ticket)
    assert @gotanda.exit(ticket)
  end

  def test_shinagawa_to_shinbashi_not_enough_ticket140
    ticket = Ticket.new(140)
    @shinagawa.enter(ticket)
    refute @shinbashi.exit(ticket)
  end

  def test_shinagawa_to_tokyo_enough_ticket170
    ticket = Ticket.new(170)
    @shinagawa.enter(ticket)
    assert @tokyo.exit(ticket)
  end

  def test_shinagawa_to_ueno_enough_ticket200
    ticket = Ticket.new(200)
    @shinagawa.enter(ticket)
    assert @ueno.exit(ticket)
  end

  def test_shinagawa_to_tabata_enough_ticket260
    ticket = Ticket.new(260)
    @shinagawa.enter(ticket)
    assert @tabata.exit(ticket)
  end

  def test_nippori_to_ikebukuro_enough_ticket160
    ticket = Ticket.new(160)
    @nippori.enter(ticket)
    assert @ikebukuro.exit(ticket)
  end
end
