all: main logic_tests database_tests

main: main.o Person.o Trip.o Transactions.o Database.o
	g++ -o main.out main.o Person.o Trip.o Transactions.o Database.o

logic_tests: logic_tests.o Person.o Trip.o
	g++ -o logic_tests.out logic_tests.o Person.o Trip.o

database_tests: database_tests.o Person.o Trip.o Transactions.o Database.o
	g++ -o database_tests.out database_tests.o Person.o Trip.o Transactions.o Database.o

database_tests.o: database_tests.o
	g++ -c -g database_tests.cpp

main.o: main.o
	g++ -c -g main.cpp

Trip.o: Trip.o
	g++ -c -g Trip.cpp

Person.o: Person.o
	g++ -c -g Person.cpp

logic_tests.o: logic_tests.o
	g++ -c -g logic_tests.cpp

Transactions.o: Transactions.o
	g++ -c -g Transactions.cpp

Database.o: Database.o
	g++ -c -g Database.cpp

clean:
	rm -r main.o main.out Trip.o Person.o logic_tests.o logic_tests.out Transactions.o
	rm -r Database.o database_tests.o database_tests.out