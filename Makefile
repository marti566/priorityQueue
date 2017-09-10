###################################
# OS COURSE - 2006
# 
###################################
CC = gcc			# use g++ for compiling c++ code or gcc for c code
CFLAGS = -g -O3 -Wall -std=gnu11		# compilation flags: -g for debugging. Change to -O or -O2 for optimized code.
LIB = -lm			# linked libraries	
LDFLAGS = -L.			# link flags
PROG = priorityQ			# target executable (output)
SRC = Main.c functions.c      # .c or .cpp source files.
OBJ = $(SRC:.c=.o) 	# object files for the target. Add more to this and next lines if there are more than one source files.

all : $(PROG)

$(PROG): $(OBJ) 
	$(CC) -o $(PROG) $(OBJ) $(LDFLAGS) $(LIB)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

# cleanup
clean:
	/bin/rm -f *.o 
# $(PROG)

# DO NOT DELETE
