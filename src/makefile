# quick reference http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

CC = g++
CFLAGS = -I$(INCLUDE_DIR)
OUTPUT_TARGET = ac

INCLUDE_DIR = ../include
OBJS_DIR = objects
LIB_DIR = ../lib
LIBS = -lm

_DEPS = Scanner.h
DEPS = $(patsubst %, $(INCLUDE_DIR)/%, $(_DEPS))

_OBJS = Scanner.o main.o
OBJS = $(patsubst %, $(OBJS_DIR)/%, $(_OBJS))

$(OUTPUT_TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(OBJS_DIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# the above is the same as the following but more concise:	 
# helloWorld.o:
# 	$(CC) -c helloWorld.cpp -I.

# main.o:
	# $(CC) -c main.cpp -I.
	
.PHONY: clean

clean: 
	rm -f $(OBJS_DIR)/*.o $(OUTPUT_TARGET) *~ core $(INCLUDE_DIR)/*~


# notes: 
# 1) -c makes .o object files which are unlinked compiled files. g++ compiles and then links, but only links with already compiled files
# 2) -o names the output target file
# 3) $ dereferences the variable after it
# 4) @ is the name before the :
# 5) < is the first dependency which comes after the :
# 6) ^ is everything after the :
# 7) % is a wildcard
# 8) patsubst is patter substitution with notation $(patsubst pattern,replacement,text)
# 9) clean cleans all object files, any file ending in ~ which comes from the text editor creating a copy, core is the name of a file created
# from C seg faults where the error is dumped in to a file called core.
