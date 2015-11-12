CC = g++ -fopenmp 
CFLAGS = -std=c++11 -O2 -funroll-loops -fstrict-aliasing -Wall -W -Wno-uninitialized 
EXEC_NAME = fsaplf
INCLUDES = 
LIBS = -lboost_system -lboost_filesystem -lboost_regex
OBJ_FILES = main.o Particles.o Pca.o terminal.o options.o Steps.o Averaging.o plane.o writing.o trajectories.o MixingIndex.o Rsd.o calc.o eigen_sym.o util.o Label.o
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
