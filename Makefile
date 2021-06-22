CC:=gcc
SERVER:=server
CLIENT:=client
OBJ:=obj/
BIN:=bin/

.PHONY: all
all: ${addprefix ${OBJ},${addsuffix .o,${SERVER}}} ${addprefix ${OBJ},${addsuffix .o,${CLIENT}}}
	${CC} ${addprefix ${OBJ},${addsuffix .o,${SERVER}}} -o ${BIN}${SERVER}
	${CC} ${addprefix ${OBJ},${addsuffix .o,${CLIENT}}} -o ${BIN}${CLIENT}

${OBJ}%.o: %.c
	${CC} -c $< -o $@

clean:
	rm -rf bin/* obj/*
