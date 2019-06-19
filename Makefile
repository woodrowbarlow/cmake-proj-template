ifeq (, $(shell which cmake))
	$(error "Failed to find cmake.")
endif

all: build dist

build: CMakeLists.txt inc/config.h.in
	mkdir -p build
	cd build && cmake ..

dist: build $(wildcard src/*.c) $(wildcard inc/*.h)
	cd build && make
	cp -rf build/dist dist

.PHONY: clean
clean:
	rm -rf build dist
