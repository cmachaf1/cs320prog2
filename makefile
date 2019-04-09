F1=cache-sim
F2=Directmap

all: $(F1).o 
	g++ $(FLAGS) $(F1).o -o $(F1)

$(F1).o: $(F1).cpp $(F2).h 
	g++ -c $(FLAGS) $(F1).cpp -o $(F1).o

run: all
	./$(F1)

memcheck: all
	valgrind --leak-check=full ./$(F1)

clean: all
	rm -rf $(F1) *.o

