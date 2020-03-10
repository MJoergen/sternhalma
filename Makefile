sternhalma: main.cpp board.cpp
	g++ main.cpp board.cpp -o $@

clean:
	rm -rf sternhalma
