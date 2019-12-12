CC:=gcc
CFLAGS:=-c -Wall
OBJS:=linklist_func.o test.o

linklist: ${OBJS}
	${CC} $^ -o $@

linklist_func.o: linklist_func.c
	${CC} ${CFLAGS} $< -o $@

test.o: test.c
	${CC} ${CFLAGS} $< -o $@

.PHONY: clean
clean: 
	rm ${OBJS} linklist