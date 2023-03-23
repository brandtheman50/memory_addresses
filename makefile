dump: dump.o
 # We must rename a.out to dump 

# We are using g++ Since we are using C++i(TAB)CC = g++
	g++ dump.o -o dump

dump.o: dump.cpp
	g++ -c dump.cpp

clean:
	rm *.o dump

# Compiler Flags
# -g adds debugging informationto the execurable file
# -wall turns on most, but not all, compiler warnings
