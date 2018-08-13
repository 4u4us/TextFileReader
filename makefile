
all: 
	g++ -std=c++11 -o text-file-reader text_file_reader.c

clean:
	rm -f *.o *~ core 
