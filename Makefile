CC=gcc
FLAGS=-Wall
INCLUDE=-I include
LIB_FILES =src/tetrahedral_utils.c src/tetrahedral_decomposition.c

install: test_equality_funs.x test_decomposition.x

test_equality_funs.x: test/test_same_cube.c  ${LIB_FILES}
	${CC} ${INCLUDE} ${FLAGS} $^ -o $@ 
test_decomposition.x: test/test_cube_decompose.c ${LIB_FILES}
	${CC} ${INCLUDE} ${FLAGS} $^ -o $@

clean:
	rm test_equality_funs.x test_decomposition.x
.PHONY: clean

