
all: 
	g++ -std=c++11 -o text-file-reader text_file_reader.c -ldl -lpthread -lsqlite3

clean:
	rm -f *.o *~ core 
