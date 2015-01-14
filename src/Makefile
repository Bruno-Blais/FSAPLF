CC = g++ -fopenmp
CFLAGS =  -O2 -funroll-loops -fstrict-aliasing -Wall -W -Wno-uninitialized 
EXEC_NAME = fsaplf
INCLUDES = 
LIBS = -lboost_system -lboost_filesystem
OBJ_FILES = main.o particles.o terminal.o options.o steps.o averaging.o boxes.o plane.o writing.o trajectories.o Pca.o calc.o
INSTALL_DIR = ../../test/

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
