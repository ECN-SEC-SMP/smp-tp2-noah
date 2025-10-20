# === Variables ===
EXEC_PROGRAM2 = folder_build
EXEC_PROGRAM1 = main_test
EXEC_PROGRAM3 = test_EntierLong


# === Règles ===

all: $(EXEC_PROGRAM2) $(EXEC_PROGRAM1)  $(EXEC_PROGRAM3)
 
# Compilation de l'exécutable

$(EXEC_PROGRAM2): 
	mkdir -p build

$(EXEC_PROGRAM1): ./build/main_test.o ./build/lit_ecrit.o ./build/utilitaires.o ./build/operations.o 
	g++ -o $(EXEC_PROGRAM1) ./build/main_test.o ./build/lit_ecrit.o ./build/utilitaires.o ./build/operations.o 

$(EXEC_PROGRAM3): ./build/test_EntierLong.o ./build/lit_ecrit.o ./build/utilitaires.o ./build/operations.o ./build/unity.o
	g++ -o $(EXEC_PROGRAM3) ./build/test_EntierLong.o ./build/lit_ecrit.o ./build/utilitaires.o ./build/operations.o ./build/unity.o

# Compilation des fichiers sources en fichiers objets
./build/main_test.o: ./src/main_test.cpp
	g++ -I./include -c ./src/main_test.cpp -o ./build/main_test.o

./build/lit_ecrit.o: ./src/lit_ecrit.cpp
	g++ -I./include -c ./src/lit_ecrit.cpp -o ./build/lit_ecrit.o

./build/utilitaires.o: ./src/utilitaires.cpp
	g++ -I./include -c ./src/utilitaires.cpp -o ./build/utilitaires.o

./build/operations.o: ./src/operations.cpp
	g++ -I./include -c ./src/operations.cpp -o ./build/operations.o	

#Cmpilation de Unity et test_EntierLong
./build/unity.o: ./test/unity.c
	g++ -I./include -c ./test/unity.c -o ./build/unity.o	

./build/test_EntierLong.o: ./test/test_EntierLong.cpp
	g++ -I./include -c ./test/test_EntierLong.cpp -o ./build/test_EntierLong.o
	
# Supprime les fichiers objets et l'exécutable
clean:
	rm -f build/*.o
	rm -f $(EXEC_PROGRAM1)

.PHONY: all clean

