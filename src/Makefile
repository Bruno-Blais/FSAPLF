CC = g++
CFLAGS =  -g -Wall -funroll-loops -fstrict-aliasing -Wall -W -Wno-uninitialized
EXEC_NAME = main
INCLUDES = 
LIBS =
OBJ_FILES = main.o library.o particles.o terminal.o options.o 
INSTALL_DIR = ../

all : $(EXEC_NAME)

clean :
	rm $(EXEC_NAME) $(OBJ_FILES)

$(EXEC_NAME) : $(OBJ_FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

install :
	  cp $(EXEC_NAME) $(INSTALL_DIR)
