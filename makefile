# === Variables ===
EXEC_PROGRAM1 = main_test

# === Règles ===

all: $(EXEC_PROGRAM1) 
 
# Compilation de l'exécutable

$(EXEC_PROGRAM1): ./build/main_test.o ./build/lit_ecrit.o ./build/utilitaires.o
	mkdir -p build
	g++ -o $(EXEC_PROGRAM1) ./build/main_test.o ./build/lit_ecrit.o ./build/utilitaires.o


./build/main_test.o: ./src/main_test.cpp
	g++ -I./include -c ./src/main_test.cpp -o ./build/main_test.o

./build/lit_ecrit.o: ./src/lit_ecrit.cpp
	g++ -I./include -c ./src/lit_ecrit.cpp -o ./build/lit_ecrit.o

./build/utilitaires.o: ./src/utilitaires.cpp
	g++ -I./include -c ./src/utilitaires.cpp -o ./build/utilitaires.o
	
# Supprime les fichiers objets et l'exécutable
clean:
	rm -f build/*.o

.PHONY: all clean

