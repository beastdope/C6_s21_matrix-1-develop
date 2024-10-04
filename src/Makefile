CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
CHECK_FLAG = -lcheck -lm -lsubunit
VALGRIND_FLAGS  = 	--log-file="valgrind.txt" --tool=memcheck --leak-check=yes --track-origins=yes

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))


SRC_TESTS = $(wildcard tests/*.c)
OBJ_TESTS = $(patsubst tests/%.c, tests/%.o, $(SRC_TESTS))

all: clean s21_matrix.a test

s21_matrix.a: $(OBJ)
	ar cr s21_matrix.a $(OBJ)

test: clean $(OBJ) $(OBJ_TESTS) 
	$(CC) $(CFLAGS) $(OBJ) $(OBJ_TESTS) $(CHECK_FLAG) -o test
	./test
		
gcov_report : test
	$(CC) $(CFLAGS) $(SRC) $(SRC_TESTS) $(CHECK_FLAG) --coverage -o test_coverage
	./test_coverage
	lcov -c -d . --output-file test_coverage.info
	genhtml test_coverage.info --output-directory html_report
	xdg-open ./html_report/index.html
	
valgrind: clean test
	valgrind $(VALGRIND_FLAGS) ./test
	grep -n "ERROR SUMMARY" valgrind.txt

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf tests/*.o
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf html_report
	rm -rf valgrind.txt
	rm -rf test_coverage
	rm -rf test

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c
	clang-format -n */*.c
	clang-format -n *.h
	# rm -f .clang-format

clang-i:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c
	clang-format -i */*.c
	clang-format -i *.h
	# rm -f .clang-format


