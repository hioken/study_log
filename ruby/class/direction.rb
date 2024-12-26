class Position
  attr_accessor :px, :py, :direction

  def initialize(px = 0, py = 0, direction = 0, stop_obj = nil, map = nil)
    @py = py
    @px = px
    @direction = direction
    @stop_obj = stop_obj
    @map = map
  end

  def turn(dir = 1)
    @direction = (@direction + dir) % 4
  end

  def walk(steps = 1, arg_map = @map)
    case dir
    when 0
      if @py > 0 + steps && stop(stop_obj, arg_map, @py - steps, @px)
        @py -= steps
      end
    when 1
      if @px < arg_map[0].size - 1 + steps && stop(stop_obj, arg_map, @py, @px + steps)
        @px += steps
      end
    when 2
      if @py < arg_map.size - 1 + steps && stop(stop_obj, arg_map, @py + steps, @px)
        @py += steps
      end
    when 3
      if @px > 0 + steps && stop(stop_obj, arg_map, @py, @px - steps)
        @px -= steps
      end
    else
      raise 'dirctionが想定されていない値です'
    end
  end

  def stop?(stop_obj, map = nil, y = nil, x = nil)
    if stop_obj.class == Array
      stop_obj.include?(map[y][x])
    else
      !(stop_obj) || map[y][x] == stop_obj
    end
  end

end
