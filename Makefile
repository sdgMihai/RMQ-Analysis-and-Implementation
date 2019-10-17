CC = g++
CFLAGS = -Wall -Wextra -O2
LDLIBS = -lm

run: tester
	./tester
build_best: algo.o tester.o
	g++ algo.o tester.o -o tester $(CFLAGS)
build_sparse_table: algo1.o tester.o
	g++ algo1.o tester.o -o tester $(CFLAGS)	
build_seg_tree: algo3.0 tester
	g++ algo3.o tester.o -o tester $(CFLAGS)
build_lca: algo2.o tester.o
	g++ algo2.o tester.o -o tester $(CFLAGS)
build_gen: gen.o algo1.o
	g++ algo1.o gen.o -o generator $(CFLAGS)
algo.o: algo.cpp
	g++ algo.cpp -c $(CFLAGS)
algo1.o: algo1.cpp
	g++ algo1.cpp -c $(CFLAGS)
algo2.o: algo2.cpp
	g++ algo2.cpp -c $(CFLAGS)
algo3.o: algo3.cpp
	g++ algo3.cpp -c $(CFLAGS)
tester.o: Main.cpp
	g++ Main.cpp -c $(CFLAGS) -o tester.o
gen.o: testGen.cpp
	g++ testGen.cpp -c $(CFLAGS) -o gen.o
.PHONY: clean
clean:
	rm -rf *.o