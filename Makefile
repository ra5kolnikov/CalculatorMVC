.PHONY: all build install test clean gcov_report uninstall dist dvi linter linter_wow cppcheck

CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
TESTFILE = test
GCOV_FLAG = -lgcov --coverage

LIBS_FOR_CHECK_PCKG =
D_OS =
OS = $(shell uname -s)
ifeq ($(OS), Linux)
	LIBS_FOR_CHECK_PCKG = -lcheck -lsubunit -lm -lpthread -lrt
	D_OS = -D __My_Linux__
else
	LIBS_FOR_CHECK_PCKG = -lcheck -lm -lpthread
	D_OS = -D __My_APPLE__
endif

all: build

build: clean
	-mkdir Build 
	cd Build; qmake ../Calc/Calc.pro
	make -C Build > /dev/null 

install: build
	-mkdir Calculator
	mv Build/Calc.app Calculator

test:
	gcc -c Calc/ThirdParty/parser/parser.c -o parser.o
	gcc -c Calc/ThirdParty/stack/stack.c -o stack.o
	g++ -std=c++17 -c Tests/Tests.cpp -o Tests.o
	g++ -o TestsExecutable Tests.o parser.o stack.o -lgtest -lpthread
	./TestsExecutable

clean:
	rm -f *.a *.o *.so *.out $(TESTFILE) $(TESTFILE).c *.info *.gcno *.gcda leak.log *.gz
	rm -rf report
	rm -rf *.gch
	rm -rf Build
	rm -rf Coverage
	rm cov* stack.o parser.o Tests.o TestsExecutable

gcov_report:
	gcc -c -fprofile-arcs -ftest-coverage -O0 -fPIC Calc/ThirdParty/parser/parser.c -o parser.o
	gcc -c -fprofile-arcs -ftest-coverage -O0 -fPIC Calc/ThirdParty/stack/stack.c -o stack.o
	g++ -std=c++17 -c -fprofile-arcs -ftest-coverage -O0 -fPIC Tests/Tests.cpp -o Tests.o
	g++ -fprofile-arcs -ftest-coverage -O0 -fPIC -o coverage Tests.o parser.o stack.o -lgtest -lpthread
	./coverage
	gcovr -r . --html --html-details -o cov-info.html
	open cov-info.html
	rm -f *.gcda *.gcno *.o

uninstall:
	rm -rf Calculator

dist:
	tar -czf SmartCalc.install.tar.gz ./*

dvi:
	open smartcalc.html

linter:
	find ../src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format --style=google -n

linter_perform:
	find ../src/ -iname '*.h' -o -iname '*.cpp' | xargs clang-format --style=google -i

