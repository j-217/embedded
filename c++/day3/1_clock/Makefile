CC:=g++
FLAGS:=-c -Wall
OBJS:=main.o clk.o

main: ${OBJS}
	${CC} $^ -o $@

clk.o: clk.cpp
	${CC} ${FLAGS} $< -o $@

main.o: main.cpp
	${CC} ${FLAGS} $< -o $@

.PHONY:clean
clean:
	${RM} ${OBJS}