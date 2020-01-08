CC:= g++
FLAGS:= -c -Wall
OBJS:= stu.o main.o

main: ${OBJS}
	${CC} $^ -o $@

stu.o: stu.cpp
	${CC} ${FLAGS} $< -o $@

main.o: main.cpp
	${CC} ${FLAGS} $< -o $@

.PHONY: clean
clean:
	${RM} ${OBJS}