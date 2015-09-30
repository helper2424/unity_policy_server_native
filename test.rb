#!/usr/bin/ruby

require 'thread'
require 'socket'
require 'timeout'

class ResultEntry
	attr_reader :time
	def initialize time
		@time = time
	end
end

$server = {address: "", port: 843}
$threads = 100
$requests = 200
$requests_total = $threads*$requests
$receive_text = '<?xml version="1.0"?>
<cross-domain-policy>
  <allow-access-from domain="*" to-ports="*"/>
</cross-domain-policy>'

$result_array = []
$threads_array = []
$semaphore = Mutex.new

def add_result data
	$semaphore.synchronize {
		$result_array.concat data
		puts "#{$result_array.size} handled"
	}
end

puts "Calculate average server ping"

average_ping = `ping -c 10 #{$server[:address]} | tail -1| awk '{print $4}' | cut -d '/' -f 2`.to_f
puts "Average ping #{average_ping}"
puts "Start #{$requests_total} requests to server"
puts "..."

$threads.times {

	$threads_array << Thread.new {
		result_t = []

		$requests.times {
			begin
				beginning_time = Time.now
				s = TCPSocket.new $server[:address], $server[:port]

				# http://stackoverflow.com/questions/9853516/set-socket-timeout-in-ruby-via-so-rcvtimeo-socket-option
				s.setsockopt(Socket::SOL_SOCKET, Socket::SO_RCVTIMEO, 1)
				a = s.read $receive_text.bytesize
				end_time = Time.now

				raise "Incorrect response text #{a.to_s}" if a.to_s != $receive_text

				result_t << ResultEntry.new((end_time - beginning_time)*1000)
				
				s.close
			rescue Exception => e  
				puts e.message  
				puts e.backtrace.inspect 
			end
		}

		add_result result_t
	}
}

$threads_array.each {|thread| thread.join }

puts "Finish"
puts "Results: #{$requests_total} requests; #{($result_array.size.to_f / $requests_total * 100).floor}% success;"

time_array = $result_array.map {|item| item.time}
puts "Full time: Minimal #{time_array.min} milliseconds; Maximum #{time_array.max} milliseconds; Average #{time_array.size == 0 ? 0 : time_array.reduce(0, :+)/time_array.size } milliseconds;"
puts "Time without ping: Minimal #{time_array.min - average_ping} milliseconds; Maximum #{time_array.max - average_ping} milliseconds; Average #{time_array.size == 0 ? 0 : (time_array.reduce(0, :+)/time_array.size - average_ping)} milliseconds;"

