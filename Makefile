EXEC= tp5
CXXFLAGS= -g -O0 -Wall -std=c++17

$(EXEC) : main.o utilitaires.o
	g++ -o $(EXEC) main.o utilitaires.o

main.o : main.cpp utilitaires.h
	g++ -c $(CXXFLAGS) main.cpp

utilitaires.o : utilitaires.cpp utilitaires.h type_def.h
	g++ -c $(CXXFLAGS) utilitaires.cpp

clean :
	rm -f $(EXEC) *.o