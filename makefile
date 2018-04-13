CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -I$(THIRD_PARTY_INCLUDE_DIR) -std=c++11
OUTPUT_TARGET = compile

THIRD_PARTY_INCLUDE_DIR = ./cget/include
_THIRD_PARTY_INCLUDE = catch
THIRD_PARTY_INCLUDE = $(patsubst %, $(THIRD_PARTY_INCLUDE_DIR)/%, $(_THIRD_PARTY_INCLUDE))
THIRD_PARTY_LIB = ./cget/lib

INCLUDE_DIR = ./src/include
OBJS_DIR = src/build
LIBS = -lm -lstdc++

_DEPS = Scanner.h Parser.h
DEPS = $(patsubst %, $(INCLUDE_DIR)/%, $(_DEPS))

_OBJS = Scanner.o Parser.o
OBJS = $(patsubst %, $(OBJS_DIR)/%, $(_OBJS))

_MAIN = main.o
MAIN = $(patsubst %, $(OBJS_DIR)/%, $(_MAIN))

clean: 
	rm -f $(OBJS_DIR)/*.o $(OUTPUT_TARGET) *~ core $(INCLUDE_DIR)/*~

$(OUTPUT_TARGET): $(OBJS) $(MAIN)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(OBJS_DIR)/%.o: src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


# TEST CONFIG
	
.PHONY: clean-tests clean

_TEST_BUILD_DIR = tests/build
_TEST_DIR = tests
_TEST_INCLUDE_DIR = tests/include
_TEST_OUTPUT_TARGET = test
TEST_CFLAGS = -I$(_TEST_INCLUDE_DIR) -I$(INCLUDE_DIR) -I$(THIRD_PARTY_INCLUDE_DIR) -std=c++11

_TEST_OBJS = TestScanner.o TestParser.o Testpp.o main.o
TEST_OBJS = $(patsubst %, $(_TEST_BUILD_DIR)/%, $(_TEST_OBJS))

_TEST_H = TestScanner.h TestParser.h Testpp.h
TEST_DEPS = $(patsubst %, $(_TEST_INCLUDE_DIR)/%, $(_TEST_H))

clean-tests: 
	rm -f tests/build/*.o test *~ core $(INCLUDE_DIR)/*~

$(_TEST_OUTPUT_TARGET): $(TEST_OBJS) $(OBJS)
	$(CC) -o $@ $^ -L$(THIRD_PARTY_LIB) $(LIBS)

$(_TEST_BUILD_DIR)/%.o: $(_TEST_DIR)/%.cpp $(DEPS) $(TEST_DEPS)
	$(CC) -c -o $@ $< $(TEST_CFLAGS) 