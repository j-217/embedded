CC:=g++
FLAGS:=-c -Wall
OBJS:=main.o point.o line.o

main: ${OBJS}
	${CC} $^ -o $@

main.o: main.cpp
	${CC} ${FLAGS} $< -o $@

point.o: point.cpp
	${CC} ${FLAGS} $< -o $@

line.o: line.cpp
	${CC} ${FLAGS} $< -o $@

.PHONY:clean
clean:
	${RM} ${OBJS}
	