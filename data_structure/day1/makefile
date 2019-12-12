CC:=gcc
CFLAGS:=-c -Wall
OBJS:=list_func.o test_list.o 
RM:=rm

my_list:$(OBJS)
	$(CC) $^ -o $@

list_func.o:list_func.c
	$(CC) $(CFLAGS) $< -o $@

test_list.o:test_list.c
	$(CC) $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	$(RM) $(OBJS) my_list 

