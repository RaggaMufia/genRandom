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

#define ARG_SPACE_COUNT 2
#define OPTION 0
#define ARG_STR 1

int parseCmdArgs(genRandPropsPtr props, int argv, char** argc) {
    
    int arg = 0;
    int argLen = 0;
    char** option;
    
    //Parse the argument list if there are more
    // arguments than just the executable string.
    for(arg = 1; arg <= argv-1; arg++) {
    
        //Check if we are just printing help or
        // version information.
        if(arg == 1) {
        
            //If it is either a request for the help
            // or version number, print that and exit.
            if(strstr(argc[arg], "-h") != NULL) {
                printDirections(); return 1;
            }
            else if(strstr(argc[arg], "-v") != NULL) {
                printVersion(); return 2;
            }
            //Otherwise try to parse the first argument
            // as an option.
            else {
                option = parseOption(argc, &arg);
            }
        }
        //If more than one argument and we have moved
        // past the first, parse it.
        else
            option = parseOption(argc, &arg);
        
        //If an argument was not formatted correctly,
        // skip to the next argument.
        if(option == NULL) {
            printf("Ignoring %s, improper argument format.\n", argc[arg++]);
            continue;
        }
            
        //Record the program parameter.
        switch(option[0][0]) {
        
            case 'f':
                argLen = strlen(option[1]);
                props->fileName = (char *)realloc(props->fileName, sizeof(char)*argLen);
                strcpy(props->fileName, option[1]);
                break;
            
            case 'n':
                if(atoi(option[1]) == 0)
                    printf("Invalid number format - Using default argument\n");
                else
                    props->elements = atoi(option[1]);
                break;
            
            case 'd':
                props->delimiter = option[1][0];
                break;
                
            case 's':
                if(atoi(option[1]) != 0) {
                    props->seedValue = atoi(option[1]);
                    props->seedType = 'm';
                }
                break;
                
            case 'r':
                if(atoi(option[1]) != 0) {
                    int newSeedRefreshInterval = atoi(option[1]);
                    if(newSeedRefreshInterval < props->elements)
                        props->randGenPeriod = newSeedRefreshInterval;
                    else
                        printf("Keeping default reinitialization period, invalid argument.\n");
                }
                else
                    printf("Invalid number.\n");
                break;
                
            case 'l':
                if(atoi(option[1]) != 0) {
                    int newLowerBound = atoi(option[1]);
                    if(newLowerBound >= 0)
                        props->randLowerBound = newLowerBound;
                    else
                        printf("Keeping default lower bound, invalid argument.\n");
                }
                else
                    printf("Invalid number.\n");
                break;
                
            case 'h':
                if(atoi(option[1]) != 0) {
                    int newUpperBound = atoi(option[1]);
                    if(newUpperBound <= RAND_MAX)
                        props->randUpperBound = newUpperBound;
                    else
                        printf("Keeping default upper bound, invalid argument.\n");
                }
                else
                    printf("Invalid number.\n");
                break;
                
            case 'b':
                if(strcmp(option[1], "true") == 0) {
                    props->fileMode = (char *)realloc(props->fileMode, sizeof(char)*2);
                    strcpy(props->fileMode, "wb");
                    printf("Will now write file in binary instead of text.\n");
                }
                else
                    printf("Writing text instead of binary\n");
                break;
                
            //If we don't know the option, report.
            default:
                printf("Invalid option: %c.\n", option[0][0]);
        }
        
        //Clean up.
        free(option[0]);
        free(option[1]);
        free(option);
    }
    
    return 0;
}

/*
 * This parses a command line option in the form
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
        memset(argument[ARG_STR], 0, sizeof(char)*argLen);
        
        //Manual strcpy
        for(argIndex = 0; argIndex < argLen; argIndex++)
            argument[ARG_STR][argIndex] = args[(*arg)][argIndex];
        
        return argument;
    }
    else
        return NULL;
}
