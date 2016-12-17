CC=gcc
CFLAGS=-c -Wall -I./ 
LDFLAGS=
SOURCES=demo.c MemoryManager.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=demo

all: $(SOURCES) $(EXECUTABLE)
    
run: all
	./demo

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o demo
