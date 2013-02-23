/*
    This file, genRandParseOption.c, is part of the GenRand utility.

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

#define BUFFER_SIZE 1024
#define ARG_SPACE_COUNT 2
#define OPTION 0
#define ARG_STR 1

/*
 * This parses a comman line option in the form
 * -<character> <argument> and returns a fresh
 * string array with {<character>, <argument>} as
 * its structure. This function does not provide
 * cleanliness, so please make sure to clean up
 * after yourself if you use it.
 */
char ** parseOption(char** args, int* arg) {
    
    char** argument;
    
    //Ensures we have a properly formatted argument.
    if(strlen(args[(*arg)]) == 2 && args[(*arg)][0] == '-') {
        
        argument = (char **)malloc(sizeof(char *)*ARG_SPACE_COUNT);
        
        argument[OPTION] = (char *)malloc(sizeof(char));
        argument[OPTION][OPTION] = args[(*arg)][ARG_STR];
        
        int argLen = strlen(args[++(*arg)]);
        int argIndex = 0;
        
        argument[ARG_STR] = (char *)malloc(sizeof(char)*argLen);
        
        //Manual strcpy
        for(argIndex = 0; argIndex < argLen; argIndex++)
            argument[ARG_STR][argIndex] = args[(*arg)][argIndex];
        
        return argument;
    }
    else
        return (char **)-1;
}
