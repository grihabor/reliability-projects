SRC=2017_420_borodin.cpp

all: run

task_1: $(SRC)
	g++ -O2 -Werror -Wall \
		-o task_1 \
		-std=c++11 \
		$(SRC)
 
run: task_1
	./task_1
	./task_1 1 2 3 4
	./task_1 -1 -2 -3 -4 -count -file custom.txt

сlean:
	rm -f task_1
	rm -f states.txt

.PHONY: run clean
