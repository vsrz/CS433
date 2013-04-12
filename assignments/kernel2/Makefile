CC      = gcc
PROF    = -O -g
DEBUG   = -DDEBUG
NOCRYPT =
C_FLAGS =  -Wall $(PROF) $(NOCRYPT)
L_FLAGS =  $(PROF)

O_FILES = kernel2.o test2.o


all: $(O_FILES)
	rm -f test2
	$(CC) $(L_FLAGS) -o test2 $(O_FILES)

.c.o: kernel2.h
	$(CC) -c $(C_FLAGS) $<

debug: $(O_FILES) 
	$(CC) $(DEBUG) $(L_FLAGS) -o test2 $(O_FILES)

clean: 
	rm -f $(O_FILES)
	
