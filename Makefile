WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla
GCC = gcc -std=c99 -g $(WARNING) $(ERROR)
VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

TESTFALGS = -DTEST_BUILDTREE

SRCS = main.c time.c path.c remove.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS)
	$(GCC) $(OBJS) -o pa4
.c.o:
	$(GCC) -c $*.c

test1:
	./pa4 -t examples/ex1.txt
	./pa4 -t examples/ex2.txt
	./pa4 -t examples/ex3.txt

test2:
	./pa4 -t examples/ex4.txt
	./pa4 -t examples/ex5.txt
	./pa4 -t examples/ex6.txt