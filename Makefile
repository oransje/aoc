CXX_FLAGS=-std=c++20
CXX=clang++

day00: ./day00/main.cxx
	$(CXX) $(CXX_FLAGS) -o ./day00.out ./day00/main.cxx

clean:
	rm -rf *.out