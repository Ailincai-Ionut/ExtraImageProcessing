
run:
	g++ -g Image.o main.o -o main

Image.o: Image.cpp
	g++ -g Image.cpp
