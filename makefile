CFLAGS=-Wall -g -Werror -std=c11
LIBS= -lm
LIBOUTPUT=lib_output/

CFLAG_LIB=-c -g -std=c11
all:
	gcc $(CFLAGS) program.c -o program $(LIBS)

prepare_lib:
	gcc $(CFLAG_LIB) source/array.c -o $(LIBOUTPUT)array.o $(LIBS)
	gcc $(CFLAG_LIB) source/map.c -o $(LIBOUTPUT)map.o $(LIBS)
	gcc $(CFLAG_LIB) source/string.c -o $(LIBOUTPUT)string.o $(LIBS)
	gcc $(CFLAG_LIB) source/file_reader.c -o $(LIBOUTPUT)file_reader.o $(LIBS)
	gcc $(CFLAG_LIB) source/array_list.c -o $(LIBOUTPUT)array_list.o $(LIBS)

lib:
	gcc $(CFLAG_LIB) secretCoder.c -o $(LIBOUTPUT)secretCoder.o
	ar rcs $(LIBOUTPUT)libsecretCoder.a $(LIBOUTPUT)secretCoder.o $(LIBOUTPUT)array.o $(LIBOUTPUT)file_reader.o $(LIBOUTPUT)map.o $(LIBOUTPUT)string.o $(LIBOUTPUT)array_list.o

clean:
	rm -f program
	rm -f string
	rm -f file_reader
	rm -f arraylist
	rm -f map
