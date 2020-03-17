CC:=gcc
CFLAGS:=-c -Wall
OBJS:=op_linklist.o linklist_func.o io_func.o

linklist_save_load:${OBJS}
	${CC} $^ -o $@

op_linklist.o: op_linklist.c
	${CC} ${CFLAGS} $< -o $@

linklist_func.o: linklist_func.c
	${CC} ${CFLAGS} $< -o $@

io_func.o: io_func.c
	${CC} ${CFLAGS} $< -o $@

.PHONY: clean
clean:
	${RM} ${OBJS} linklist_save_load