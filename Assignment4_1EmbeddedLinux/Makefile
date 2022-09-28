BUILD=build
# This is the default target, which will be built when 
# you invoke make
.PHONY: all
all: main_fifo
# This rule tells make how to build the file hello from hello.cpp

hello: src/hello.cpp
	g++ -o hello src/hello.cpp

# build source files into objects files
$(BUILD)/%.o : src/%.cpp
	g++ -pthread -o $@ -c $< -I include

main_count: $(BUILD)/main_count.o $(BUILD)/decrement.o $(BUILD)/increment.o
	g++ -pthread -o $@ $^
#	g++ -pthread -o main src/main.cpp -I include

main_fifo: $(BUILD)/main_fifo.o $(BUILD)/decrement_fifo.o $(BUILD)/increment_fifo.o
	g++ -pthread -o $@ $^
# This rule tells make to copy hello to the binaries subdirectory,
# creating it if necessary
.PHONY: install
install:
	mkdir -p bin
	cp -p hello bin
# This rule tells make to delete hello 
.PHONY: clean 
clean:
	rm -f hello
	rm -f $(BUILD)/*.o
	rm -f main
