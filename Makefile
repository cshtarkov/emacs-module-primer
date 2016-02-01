CC=gcc
MODULE=module

default: $(MODULE).so

$(MODULE).so: $(MODULE).o
	$(CC) -shared -o $(MODULE).so $(MODULE).o
	rm $(MODULE).o

$(MODULE).o:
	$(CC) -Wall -c -fPIC $(MODULE).c -o $(MODULE).o

clean:
	rm *.o *.so

