CC:=gcc
SERVER:=server
CLIENT:=
OBJ:=obj/
BIN:=bin/

.PHONY: all
all: ${addprefix ${OBJ},${addsuffix .o,${SERVER}}} ${addprefix ${OBJ},${addsuffix .o,${CLIENT}}}
	${CC} ${addprefix ${OBJ},${addsuffix .o,${SERVER}}} -o ${BIN}/${SERVER}

${OBJ}%.o: %.c
	${CC} -c $< -o $@

clean:
	rm -rf bin/* obj/*
