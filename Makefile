CXX_FLAGS=-std=c++20
CXX=clang++

day00: ./day00/main.cxx 
	$(CXX) $(CXX_FLAGS) -o ./day00.out ./day00/main.cxx

day01: ./day01/main.cxx
	$(CXX) $(CXX_FLAGS) -o ./day01.out ./day01/main.cxx
	
day02: ./day02/main.cxx
	$(CXX) $(CXX_FLAGS) -o ./day02.out ./day02/main.cxx

clean:
	rm -rf *.out