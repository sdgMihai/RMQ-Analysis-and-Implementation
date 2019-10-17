ID: Gheoace Mihai, 324 CA

Contents:

algo.h
Prototipul functiei generice rmq();

algo.cpp
Implementarea algoritmilor folosind sparse Table si segment Tree, in functie de n si m. (cea mai buna solutie aleasa).

algo1.cpp
Implementarea algoritmului rmq cu sparse Table.

algo2.cpp
Implementarea algoritmului rmq cu LCA.

algo3.cpp
Implementarea algoritmului rmq cu segmentTree.

Makefile

Acesta contine regulile:

run
ruleaza tester.

build_best:
compileaza executabilul care va testa cea mai buna solutie pe testele default.

build_sparse_table:
compileaza executabilul care va testa a 4 a cea mai buna solutie pe testele default.

build_seg_tree:
compileaza executabilul care va testa a 2 a cea mai buna solutie pe testele default.

build_lca:
compileaza executabilul care va testa a 3 a cea mai buna solutie pe testele default.

build_gen:
compileaza executabilul care va genera testele.

clean

Folder 'in' cu testele de intrare (25 teste)

Fiecare test este numit "testID.in", unde ID reprezinta numarul testului (e.g. test0.in)
Fiecare test este structurat în felul urmator:
Pe prima linie, N (int - numarul de elemente din secven?a),M nr de interogari N,M <= 10^6
N elemente (numere întregi - reprezentabile pe 32 biti)
M perechi de numere intregi (x, y) reprezentand pozitii din secventa

Folder 'out' cu testele de ie?ire

Fiecare test este numit "testID.out", unde ID reprezinta numarul testului (e.g. test0.out)
Fiecare test con?ine secven?a de elemente din testul de intrare corespunzator sortata ascendent.

Folder other_tests

Contine un test suplimentar (test_1.in, test_1.out), cu elemente identice, avand aceeasi structura ca testele default.

Mai sunt:
Main.cpp
- tester propriu
testGen.cpp
- generatorul de teste default.
