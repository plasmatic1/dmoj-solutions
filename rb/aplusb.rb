n = gets.to_i
n.times { 
    a, b = *gets.split.map{|x|x.to_i}
    puts a+b
}