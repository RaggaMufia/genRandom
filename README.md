genRandom
=========

A simple, extremely light, fast, and easy-to-use  random number generator that outputs to a file.

Just build using the following command:

gcc genRandom.c genRandParseOption.c genRandPrint.c -o genRandom

Default parameters (run with no command arguments, or only some):
	random.txt as a file name
	1000 pseudorandom numbers between 0 and RAND_MAX
	newline delimiter

Command line options are:

	-f <file name> : Specify the output file.
	-n <quantity>  : Specify how many pseudorandom numbers you want to generate.
	-d <character> : Specify a one-character delimiter to override the default newline delimiter.
