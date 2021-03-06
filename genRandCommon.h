/*
    This file, genRandCommon.h, is part of the GenRand utility.

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GENRAND_V "0.0.8"

//Properties for the wrapper
struct genRandProps {
    
        int elements;
        char delimiter;
        char* fileName;
        char* fileMode;
        int randGenPeriod;
        int randUpperBound;
        int randLowerBound;
        char seedType;
        int seedValue;
};

//Struct pointer typedef for convenience.
typedef struct genRandProps* genRandPropsPtr;
 
/*
 * Function prototypes.
 */

//Prints the help text if passed -h
void printDirections();

//Prints the version text if passed -v
void printVersion();

//Parses through the command line arguments.
int parseCmdArgs(genRandPropsPtr, int, char**);

//Parses a command line parameter into an understandable option.
char** parseOption(char**, int*);

//Sets the default program parameters.
void setDefaultProperties(genRandPropsPtr);
