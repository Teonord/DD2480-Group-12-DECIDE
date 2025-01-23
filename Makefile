all: build/decide

build/decide: src/main.cpp src/decide.cpp | build
	g++ -std=c++17 src/main.cpp src/decide.cpp -o build/decide

test: build/tests
	./build/tests

build/tests: tests/tests.cpp src/decide.cpp | build
	g++ -std=c++17 -I include tests/tests.cpp src/decide.cpp -o build/tests
	
build:
	mkdir -p build

clean:
	rm -rf build
