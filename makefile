CC = g++
CFLAGS = -I$(INCLUDE_DIR) -I$(THIRD_PARTY_INCLUDE_DIR) -std=gnu++11
OUTPUT_TARGET = compile

THIRD_PARTY_INCLUDE_DIR = ./cget/include
_THIRD_PARTY_INCLUDE = catch
THIRD_PARTY_INCLUDE = $(patsubst %, $(THIRD_PARTY_INCLUDE_DIR)/%, $(_THIRD_PARTY_INCLUDE))
THIRD_PARTY_LIB = ./cget/lib

INCLUDE_DIR = ./include
OBJS_DIR = src/build
LIBS = -lm -lstdc++

_DEPS = Scanner.h Parser.h
DEPS = $(patsubst %, $(INCLUDE_DIR)/%, $(_DEPS))

_OBJS = Scanner.o Parser.o main.o
OBJS = $(patsubst %, $(OBJS_DIR)/%, $(_OBJS))

clean: 
	rm -f $(OBJS_DIR)/*.o $(OUTPUT_TARGET) *~ core $(INCLUDE_DIR)/*~

$(OUTPUT_TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(OBJS_DIR)/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# TEST CONFIG
	
.PHONY: clean-tests clean


_TEST_BUILD_DIR = tests/build
_TEST_DIR = tests
_TEST_OUTPUT_TARGET = test
TEST_CFLAGS = -I$(_TEST_DIR) -I$(INCLUDE_DIR) -I$(THIRD_PARTY_INCLUDE_DIR) -std=gnu++11


_TEST_OBJS = TestScanner.o
TEST_OBJS = $(patsubst %, $(_TEST_BUILD_DIR)/%, $(_TEST_OBJS))

_TEST_H = Parser.h
TEST_H = $(patsubst %, $(_TEST_DIR)/%, $(_TEST_H))

clean-tests: 
	rm -f tests/build/*.o test *~ core $(INCLUDE_DIR)/*~

$(_TEST_OUTPUT_TARGET): $(TEST_OBJS)
	$(CC) -o $@ $^ -L$(THIRD_PARTY_LIB)

$(_TEST_BUILD_DIR)/%.o: $(_TEST_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(TEST_CFLAGS)