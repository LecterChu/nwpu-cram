
ARISTOTLE_DIR = /nfs/spectre/u5/aristot/v3
CC = gcc
INCLUDE = -I$(ARISTOTLE_DIR)/headers 
LIB_BT = -L$(ARISTOTLE_DIR)/lib/sunos5/ -lIPF_bt -lglobalfunc -lfl
LIB_ST = -L$(ARISTOTLE_DIR)/lib/sunos5/ -lIPF_st -lglobalfunc -lfl
FLEXLIB = libfl.a

build:
	$(CC) $(COMPILE_PARAMETERS) -c -o flex.o flex.c
	$(CC) -o flex.exe flex.o $(FLEXLIB) lib_src/liballoc.o lib_src/libstring.o  

build-bt:
	cfe flex.c
	il-bt-2 flex.c
	$(CC) $(COMPILE_PARAMETERS) -g $(INCLUDE) -c -o flex.int.o flex.int.c
	$(CC) -g -o flex.bt.int.exe flex.int.o $(LIB_BT) $(FLEXLIB) 
	cp -f flex.bt.int.exe flex.int.exe
	chmod u+x flex.int.exe

build-st:
	cfe flex.c
	il-st-2 flex.c
	$(CC) $(COMPILE_PARAMETERS) -g $(INCLUDE) -c -o flex.int.o flex.int.c
	$(CC) -g -o flex.st.int.exe flex.int.o $(LIB_ST) $(FLEXLIB) 
	cp -f flex.st.int.exe flex.int.exe
	chmod u+x flex.int.exe

clean:
	rm *.o

