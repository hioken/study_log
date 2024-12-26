module LogSecretary
  def exception_log
    text = "\n"
    text << "\tError:    #{self.class}\n"
    text << "\tMassage:  #{self.message}\n"
    text << "\tBacktrace:\n"
    cnt = 0
    self.backtrace.each do |trace|
      text << "\t\t" + trace + "\n"
      cnt += 1
      if cnt > 20
        cnt = 'over 20'
        break
      end
    end
    text << "\ttrace_count: #{cnt.to_s}"
    Rails.application.config.another_loger.info(text)
  end
end

module ActiveRecord
  include LogSecretary
end

class Exception
  include LogSecretary
end
