genRandom
=========

A simple, extremely light, fast, and easy-to-use rand() C Library function wrapper that outputs to a file.

Just build using the following command:

gcc genRandom.c genRandParseOption.c genRandPrint.c -o genRandom

Usage:
    genRandom    : use all default parameters.
    genRandom -h : View the directions of usage (basically the same as this.)
    genRandom -v : View version information.

Default parameters (run with no command arguments, or only some):
	random.txt as a file name
	1000 pseudorandom numbers between 0 and RAND_MAX
	newline delimiter

Command line options are:

	-f <file name> : Specify the output file.
	-n <quantity>  : Specify how many pseudorandom numbers you want to generate.
	-d <character> : Specify a one-character delimiter to override the default newline delimiter.
