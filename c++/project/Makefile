CPP:= g++
CFLAG:= -c -Wall
OBJS:= comm.o coordinate.o shape.o pattern.o game.o main.o

start: ${OBJS}
	${CPP} $^ -o $@ -lpthread

comm.o: comm.cpp
	${CPP} ${CFLAG} $< -o $@

coordinate.o: coordinate.cpp
	${CPP} ${CFLAG} $< -o $@

shape.o: shape.cpp
	${CPP} ${CFLAG} $< -o $@

pattern.o: pattern.cpp
	${CPP} ${CFLAG} $< -o $@

game.o: game.cpp
	${CPP} ${CFLAG} $< -o $@

main.o: main.cpp
	${CPP} ${CFLAG} $< -o $@

.PHONY: clean
clean:
	${RM} ${OBJS}