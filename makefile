.PHONY: default test clean
default:
	cd build/; make

test:
	cd tests/build/; make

clean:
	cd build/; make clean
	cd tests/build/; make clean
