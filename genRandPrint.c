/*
    This file, genRandPrint.c, is part of the GenRand utility.

    GenRand is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    GenRand is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GenRand.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "genRandCommon.h"

//Print the genRand help message.
void printDirections() {
    const char* messageIntro = "\n  Usage:\n\n\tgenRandom\t: No arguments.";
    const char* messageNoArgs_1 = " Outputs 1000 pseudorandom integers to random.txt ";
    const char* messageNoArgs_2 = "in the current directory.";
    const char* messageHelp = "\n\tgenRandom -h\t: Display this message.\n";
    const char* messageDispVersion = "\tgenRandom -v\t: Display the current version.\n";
    const char* messageOptions = "\n\tOptions:\n\n";
    const char* messageFileOpt = "\t\t-f <file name>\t:   Specify the output file.\n";
    const char* messageQuantityOpt_1 = "\t\t-n <integer>\t:   Specify the quantity ";
    const char* messageQuantityOpt_2 = "of pseudorandom numbers.\n";
    const char* messageDelimiterOpt_1 = "\t\t-d <delimiter>\t:   One character; This will ";
    const char* messageDelimiterOpt_2 = "override the default delimiter.\n";
    const char* messageSeedOpt_1 = "\t\t-s <seed value>\t:   Specify a seed for pseudorandom";
    const char* messageSeedOpt_2 = " generation manually.\n";
	const char* messageSeedRefreshOpt_1 = "\t\t-r <interval>\t:   Specify how often the";
	const char* messageSeedRefreshOpt_2 = " pseudorandom generator is refreshed with a new seed.\n";
	const char* messageLowBoundOpt_1 = "\t\t-l <low bound>\t:   Specify a pseudorandom ";
	const char* messageLowBoundOpt_2 = "generation lower bound.\n";
	const char* messageHighBoundOpt_1 = "\t\t-h <high bound>\t:   Specify a pseudorandom ";
	const char* messageHighBoundOpt_2 = "generation upper bound.\n";
	const char* messageBinaryWriteOpt_1 = "\t\t-b <true/false>\t:   Specify whether to write the";
	const char* messageBinaryWriteOpt_2 = " file in binary. Use only true/false, all lower case.\n";
    const char* messageVersion = "\n  GenRandom v. ";
    const char* messageAuthorLisc =
        "  Copyright 2013, Jonathan Hyry\n  Licensed under GNU General Public License (GPL) v. 3\n";
    
    printf("%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n%s\n",
                                        messageIntro, messageNoArgs_1, messageNoArgs_2,
                                        messageHelp, messageDispVersion, messageOptions,
                                        messageFileOpt, messageQuantityOpt_1, messageQuantityOpt_2,
                                        messageDelimiterOpt_1, messageDelimiterOpt_2,
                                        messageSeedOpt_1, messageSeedOpt_2, messageSeedRefreshOpt_1,
                                        messageSeedRefreshOpt_2, messageLowBoundOpt_1,
                                        messageLowBoundOpt_2, messageHighBoundOpt_1,
                                        messageHighBoundOpt_2, messageBinaryWriteOpt_1,
                                        messageBinaryWriteOpt_2, messageVersion, GENRAND_V,
                                        messageAuthorLisc);
}

//Print genRand version message
void printVersion() {

    const char* messageVersion = "\nGenRandom v. ";
    const char* messageAuthorLisc =
        "Copyright 2013, Jonathan Hyry\nLicensed under GNU General Public License (GPL) v. 3\n\n";
        
    printf("%s%s\n%s", messageVersion, GENRAND_V, messageAuthorLisc);
}
