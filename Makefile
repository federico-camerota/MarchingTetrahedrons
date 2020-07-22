CC=gcc
FLAGS=-Wall -ggdb
INCLUDE=-I include
LIB_FILES =src/tetrahedral_utils.c src/tetrahedral_decomposition.c src/cube5_decomposition.c

install: test_equality_funs.x test_decomposition.x

test_equality_funs.x: test/test_same_cube.c  ${LIB_FILES}
	${CC} ${INCLUDE} ${FLAGS} $^ -o $@ 

test_t6_decomposition.x: test/test_cube_decompose.c ${LIB_FILES}
	${CC} ${INCLUDE} ${FLAGS} $^ -o $@

test_t5_decomposition.x: test/test_t5_decomposition.c ${LIB_FILES}
	${CC} ${INCLUDE} ${FLAGS} $^ -o $@

clean:
	rm test_equality_funs.x test_t6_decomposition.x test_t5_decomposition.x
.PHONY: clean

