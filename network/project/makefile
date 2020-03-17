CC:=gcc
CFLAGS:=-c -Wall
LINKLIB:=-l sqlite3

SRV_OBJ:=comm.o my_srv.o db_op.o server.o
CLT_OBJ:=comm.o my_clt.o client.o

.PHONY:all
all:server client

server: ${SRV_OBJ}
	${CC} $^ -o $@ ${LINKLIB}

client: ${CLT_OBJ}
	${CC} $^ -o $@ ${LINKLIB}

comm.o: comm.c
	${CC} ${CFLAGS} $< -o $@

db_op.o: db_op.c
	${CC} ${CFLAGS} $< -o $@

my_srv.o: my_srv.c
	${CC} ${CFLAGS} $< -o $@

my_clt.o: my_clt.c
	${CC} ${CFLAGS} $< -o $@

server.o: server.c
	${CC} ${CFLAGS} $< -o $@

client.o: client.c
	${CC} ${CFLAGS} $< -o $@

.PHONY: clean
clean:
	${RM} ${SRV_OBJ} ${CLT_OBJ}