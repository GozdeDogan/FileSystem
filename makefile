CC=g++
CFLAGS=-I.
DEPS = File.h Thread.h gtuos.h memory.h 8080emuCPP.h memoryBase.h File.cpp Thread.cpp gtuos.cpp 8080emu.cpp
OBJ = emulator.o


buildemulator:
	$(CC)  main.cpp $(DEPS) -o emulator.out $(CFLAGS) 

