CXX = g++
SRC = findConvPt.cxx  mod1D.cxx  ray1d.cxx
OBJ = $(foreach src,${SRC},$(subst .cxx,.o,${src}))
EXEC = findConvPt
#DEBUG = -DDEBUG -g
DEBUG = -O3

all: ${OBJ} ${EXEC}


${OBJ}:%.o:%.cxx
	${CXX} -c -o $@ ${DEBUG} $<

findConvPt: ${OBJ}
	${CXX} -o $@ -lm ${OBJ}

install:
	mv findConvPt ${BIN_DIR}

clean:
	rm ${OBJ} ${EXEC}