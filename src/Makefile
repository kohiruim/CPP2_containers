CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wextra
TEST_LIBS = -lgtest
TEST_SRC = tests/*
OBJECTS = test


all: test check

test: $(TESTS)
	$(CC) $(CFLAGS) $(TEST_SRC) $(TEST_LIBS) -o $(OBJECTS) -L. --coverage
	./test

gcov_report: test
	$(CC) --coverage $(TEST_SRC) $(TEST_LIBS) -o gсov_report.o
	./gсov_report.o
	lcov --ignore-errors mismatch -t $(OBJECTS) -o s21_containers_tests.info --no-external -c -d .
	genhtml -o report s21_containers_tests.info
	open ./report/index.html

check:
	cp ../materials/linters/.clang-format .
	#clang-format -i *.h tests/* s21_array/* s21_vector/* s21_list/* s21_map/* s21_multiset/* s21_queue/* s21_set/* s21_stack/*
	clang-format -n *.h tests/* s21_array/* s21_vector/* s21_list/* s21_map/* s21_multiset/* s21_queue/* s21_set/* s21_stack/*
	rm -rf .clang-format

clean: 
	rm -rf test *.gcda  *.gcno *.o *.info report

rebuild: clean all
