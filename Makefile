.PHONY: build

build:
	python setup.py build_ext --inplace

test:
	python test.py
