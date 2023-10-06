
build_real:
	gcc build/lex.o build/util.o build/main.o -o build/silk

build: build_dir make_objects build_real cleanup

build_dir:
	mkdir -p build

make_objects: src/lex/lex.c src/lex/lex.h src/util/util.h src/util/util.c src/main.c
	gcc -c src/lex/lex.c   -o build/lex.o 
	gcc -c src/util/util.c -o build/util.o 
	gcc -c src/main.c      -o build/main.o 

cleanup:
	rm build/*.o
