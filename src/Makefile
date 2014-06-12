CC = g++
CFLAGS =  -g -Wall -funroll-loops -fstrict-aliasing -Wall -W -Wno-uninitialized
EXEC_NAME = fsaplf
INCLUDES = 
LIBS = -lboost_system -lboost_filesystem
OBJ_FILES = main.o library.o particles.o terminal.o options.o steps.o 
INSTALL_DIR = ../test/

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

install :
	make
	cp $(EXEC_NAME) $(INSTALL_DIR)
