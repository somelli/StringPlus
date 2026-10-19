CC=gcc

CFLAGS=-Wall -Wextra -Werror -std=c11

all: s21_string.a

s21_string.a: s21_string.o s21_sprintf.o s21_sprintf_int.o s21_sprintf_float.o

	ar rcs s21_string.a s21_string.o s21_sprintf.o s21_sprintf_int.o s21_sprintf_float.o

s21_string.o: s21_string.c s21_string.h

	$(CC) $(CFLAGS) -c s21_string.c -o s21_string.o

s21_sprintf.o: s21_sprintf.c s21_string.h

	$(CC) $(CFLAGS) -c s21_sprintf.c -o s21_sprintf.o

s21_sprintf_int.o: s21_sprintf_int.c s21_string.h

	$(CC) $(CFLAGS) -c s21_sprintf_int.c -o s21_sprintf_int.o

s21_sprintf_float.o: s21_sprintf_float.c s21_string.h

	$(CC) $(CFLAGS) -c s21_sprintf_float.c -o s21_sprintf_float.o

clean:
	rm -f s21_string.o s21_string.a s21_sprintf.o s21_sprintf_int.o s21_sprintf_float.o test_s21_string gcov_test
	rm -f *.gcno *.gcda coverage.info coverage_filtered.info
	rm -rf gcov_report

rebuild: clean all

test: s21_string.a

	$(CC) $(CFLAGS) test_s21_string.c s21_string.a \
	$(shell pkg-config --cflags --libs check) \
	-o test_s21_string
	./test_s21_string

gcov_report:
	$(CC) $(CFLAGS) --coverage s21_string.c s21_sprintf.c s21_sprintf_int.c s21_sprintf_float.c test_s21_string.c \
	$(shell pkg-config --cflags --libs check) \
	-o gcov_test
	./gcov_test
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '*test_s21_string.c' -o coverage_filtered.info
	genhtml coverage_filtered.info --output-directory gcov_report

style:
	clang-format -n -Werror s21_string.c s21_sprintf.c s21_sprintf_int.c s21_sprintf_float.c s21_string.h test_s21_string.c

stylefix:

	clang-format -i s21_string.c s21_sprintf.c s21_sprintf_int.c s21_sprintf_float.c s21_string.h test_s21_string.c

valgrind: test
	valgrind --tool=memcheck --leak-check=full \
	--show-leak-kinds=all --track-origins=yes \
	./test_s21_string

leaks: test
	leaks --atExit -- ./test_s21_string