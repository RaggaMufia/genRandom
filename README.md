genRandom
=========

A simple, extremely light, fast, and easy-to-use rand() C Library function wrapper that outputs to a file.

Note: When writing out as a binary file, there is no delimiter inserted. n 4-byte integers are written.

Just build using the following command:

gcc genRandom.c genRandParseOption.c genRandPrint.c -o genRandom

Usage:
    genRandom    : use all default parameters.
    genRandom -h : View the directions of usage (basically the same as this.)
    genRandom -v : View version information.

Default parameters (run with no command arguments, or only some):
	random.txt as a file name.
	1000 pseudorandom numbers.
	Uses the system time as the seed by default.
	Lower pseudorandom generation bound is 0.
	Upper pseudorandom generation bound is RAND_MAX.
	Seed reinitialization interval is once every 50 numbers read.
	Writes text to file by default.
	newline delimiter.

Command line options are:

	-f <file name>  : Specify the output file.
	-n <quantity>   : Specify how many pseudorandom numbers you want to generate.
	-d <character>  : Specify a one-character delimiter to override the default newline delimiter.
	-s <seed value> : Specify a seed for pseudorandom generation manually.
	-r <interval>   : Specify how often the pseudorandom generator is refreshed with a new seed.
	-l <low bound>  : Specify a pseudorandom generation lower bound.
	-h <high bound> : Specify a pseudorandom generation upper bound.
	-b <true/false> : Specify whether to write the file in binary. Use only true/false, all lower case.
