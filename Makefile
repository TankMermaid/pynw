.PHONY: build test c

build:
	python setup.py build_ext --inplace

test:
	python test.py

c:
	gcc -o nw nw.c && ./nw TGCTGCCTCCCGTAGGAGTCTGGGCCGTGTCTCAGTCCCAGTGTGGCTGATCATCCTCTCAGACCAGCTAGGGATCGTCGCCTTGGTGAGCCATTACCTCACCAACTAGCTAATCCCATATGGGTTCATCCGATAGCGCAAGGACCGAAGTTCCCCTGCTTTGCTCCTTAGAGATTATGCGGTATTA TGCTGCCTCCCGTAGGAGTCTGGGCCGTATCTCAGTCCCAATGTGGCCGGTCGCCCTCTCAGGCCGGCTACCCGTCGAAGCCTTGGTGAGCCGTTACCTCACCAACAAGCTGATAGGACGCGACCCCATCCCACGCCGATAGAATCTTTCCCACAATCACATGCGATCATGTGGAACATCCGGCATT

compare:
	./gs.py TGCTGCCTCCCGTAGGAGTCTGGGCCGTGTCTCAGTCCCAGTGTGGCTGATCATCCTCTCAGACCAGCTAGGGATCGTCGCCTTGGTGAGCCATTACCTCACCAACTAGCTAATCCCATATGGGTTCATCCGATAGCGCAAGGACCGAAGTTCCCCTGCTTTGCTCCTTAGAGATTATGCGGTATTA TGCTGCCTCCCGTAGGAGTCTGGGCCGTATCTCAGTCCCAATGTGGCCGGTCGCCCTCTCAGGCCGGCTACCCGTCGAAGCCTTGGTGAGCCGTTACCTCACCAACAAGCTGATAGGACGCGACCCCATCCCACGCCGATAGAATCTTTCCCACAATCACATGCGATCATGTGGAACATCCGGCATT
