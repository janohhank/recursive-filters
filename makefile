all:
	g++ -std=c++17 src/sample.cpp -o Filter.bin -W -Wall -Wextra -pedantic
clean:
	rm Filter.bin
