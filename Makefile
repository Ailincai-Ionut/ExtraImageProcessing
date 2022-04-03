OBJS	= Image.o ImageProcessing.o DrawModule.o main.o
SOURCE	= Image.cpp ImageProcessing.cpp DrawModule.cpp
HEADER	=Image.h ImageProcessing.h DrawModule.h
OUT	= main
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 =

all: clean $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Image.o:Image.cpp
	$(CC) $(FLAGS) Image.cpp

ImageProcessing.o:ImageProcessing.cpp
	$(CC) $(FLAGS) ImageProcessing.cpp

DrawModule.o:DrawModule.cpp
	$(CC) $(FLAGS) DrawModule.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

clean:
	rm -f $(OBJS) $(OUT) *.gch


smt.o:smt.cpp
	$(CC) $(FLAGS) smt.cpp
