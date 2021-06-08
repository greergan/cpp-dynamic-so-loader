main: libderived.so main.o
	$(CXX) -o main  main.o -ldl

libderived.so: libderived.cpp
	$(CXX) -fPIC -c libderived.cpp -o libderived.o
	$(CXX) -shared -o libderived.so libderived.o

clean:
	rm -f main *.o *.so
