CFLAGS=-Wall -g -Werror -std=c11
LIBS= -lm
LIBOUTPUT=lib_output/

CFLAG_LIB=-c -g -std=c11
all:
	gcc $(CFLAGS) unit_test.c -o unit_test $(LIBS)

prepare_lib:
	gcc $(CFLAG_LIB) source/array.c -o $(LIBOUTPUT)array.o $(LIBS)
	gcc $(CFLAG_LIB) source/array_list.c -o $(LIBOUTPUT)array_list.o $(LIBS)
	gcc $(CFLAG_LIB) source/crack_util.c -o $(LIBOUTPUT)crack_util.o $(LIBS)
	gcc $(CFLAG_LIB) source/file_reader.c -o $(LIBOUTPUT)file_reader.o $(LIBS)
	gcc $(CFLAG_LIB) source/map.c -o $(LIBOUTPUT)map.o $(LIBS)
	gcc $(CFLAG_LIB) source/search_util.c -o $(LIBOUTPUT)search_util.o $(LIBS)
	gcc $(CFLAG_LIB) source/string.c -o $(LIBOUTPUT)string.o $(LIBS)
	gcc $(CFLAG_LIB) source/string_util.c -o $(LIBOUTPUT)string_util.o $(LIBS)
	gcc $(CFLAG_LIB) source/exception_handler.c -o $(LIBOUTPUT)exception_handler.o $(LIBS)

lib:
	gcc $(CFLAG_LIB) secretCoder.c -o $(LIBOUTPUT)secretCoder.o
	ar rcs $(LIBOUTPUT)libsecretCoder.a \
	$(LIBOUTPUT)secretCoder.o \
	$(LIBOUTPUT)array.o \
	$(LIBOUTPUT)array_list.o \
	$(LIBOUTPUT)file_reader.o \
	$(LIBOUTPUT)map.o \
	$(LIBOUTPUT)string.o \
	$(LIBOUTPUT)crack_util.o \
	$(LIBOUTPUT)string_util.o \
	$(LIBOUTPUT)search_util.o \
	$(LIBOUTPUT)exception_handler.o


clean:
	rm -f program
	rm -f string
	rm -f file_reader
	rm -f array_list
	rm -f map
	rm -f search_util
	rm -f crack_util
	rm -f string_util
	rm -f exception_handler
	rm -f lib_example/main.c