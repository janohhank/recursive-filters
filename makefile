all:
	g++ -std=c++17 src/bin/RecursiveFilters.cpp -o RecursiveFilters.bin -W -Wall -Wextra -pedantic
clean:
	rm RecursiveFilters.bin
