module DeepFreezable
  def deep_freeze(array_or_hash)
    case array_or_hash
    when Array
      array_or_hash.each(&:freeze)
    when Hash
      array_or_hash.each{ |key, value| key.freeze; value.freeze }
    end
    array_or_hash.freeze
  end
end
