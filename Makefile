.PHONY: all
all: format build

.PHONY: format
format:
	clang-format src/*.cpp include/* test/*.cpp test/*.hpp -i

.PHONY: build
build:
	mkdir -p build
	cd build && \
	conan install .. --build missing && \
	cmake .. && \
	make

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
  	conan install .. --build missing && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build