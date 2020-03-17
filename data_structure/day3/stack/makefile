CC:= gcc
CFALGS:= -c -Wall
OBJS:= test.o stack_func.o

stack: ${OBJS}
	$(CC) $^ -o $@

test.o: test.c
	${CC} ${CFALGS} $< -o $@

stack_func.o: stack_func.c
	${CC} ${CFALGS} $< -o $@

.PHONY: clean
clean:
	${RM} ${OBJS} stack