/*
    This file, genRandom.c, is part of the GenRand utility.

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

#define ELEMENTS 1000
#define ELEMENT_SIZE 4
#define INPUT_BUFFER_SIZE 9
#define DEFAULT_FILE_NAME_LENGTH 10

#define RAND_OUT_FILE "random.txt"

#define DELIMITER '\n'

/**
 * Main program entry point that parses arguments,
 *  sets appropriate program parameters, and calls
 *  functions that do the heavy lifting.
 */
int main(int argv, char** argc) {

    //Set all program parameters to default,
    // then set to custom values as discovered
    // through argument parsing.
    int elements = ELEMENTS;
    char delimiter = DELIMITER;
    char* fileName = (char *)malloc(sizeof(char)*DEFAULT_FILE_NAME_LENGTH);
    strcpy(fileName, RAND_OUT_FILE);
    
    //Use default program parameters.
    if(argv<2) {
    
        printf("No file name argument; Will save file as %s with %d ", fileName, elements);
        printf("pseudorandom integers, and newline delimiter.\n");
    }
    //Parse program parameters.
    else {
    
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
                    fileName = (char *)realloc(fileName, sizeof(char)*argLen);
                    strcpy(fileName, option[1]);
                    break;
                
                case 'n':
                    if(atoi(option[1]) == 0)
                        printf("Invalid number format - Using default argument\n");
                    else
                        elements = atoi(option[1]);
                    break;
                
                case 'd':
                    if(strlen(option[1]) == 1)
                        delimiter = option[1][0];
                    else {
                        printf("Invalid delimiter.");
                        printf(" Delimiter can only be one character.\n");
                        printf(" Using default newline delimiter.\n");
                    }
                    break;
                //If we don't know the option, report.
                default:
                    printf("Invalid option.\n");
            }
            
            //Clean up.
            free(option[0]);
            free(option[1]);
            free(option);
        }
    }
    //Set up the pseudorandom number cache
    // and initialize the pseudorandom generator.
    printf("Allocating cache... ");
    unsigned int * randCache = (unsigned int *)calloc(elements, ELEMENT_SIZE);
    if(randCache != NULL)
        printf("Done.\nInitializing random generator...\n");
    else {
        printf("Fatal: Allocation failure.\n");
        return -1;
    }
    srand(time(NULL));
    printf("Random generator init successful.\n");
    
    int elementsWritten = 0;
    
    //Allows the user to specify if they want detailed output.
    printf("Batch read? (Offers no status while reading) y/n: "); 
    
    char batch = getchar();
    getchar();
    
    printf("Reading %d pseudorandom bytes...\n", (ELEMENT_SIZE*elements));
    
    int i = 0;
    
    //Don't output any details while reading.
    if(batch == 'y' || batch == 'Y') {
    
        printf("Batch read starting... ");
        for(i = 0; i < elements; randCache[i++] = rand())
            if(i % 50 == 0)
                srand(time(NULL));
        printf(" Reading completed.\n");
    }
    //Report progress while reading.
    else {
    
        for(i = 0; i < elements; i++) {
        
            randCache[i] = rand();
            
            if(i % 50 == 0) {
                printf("Reinitializing random generator with a new seed...\n");
                srand(time(NULL));
            }
            
            printf("Item read: %u\n", randCache[i]);
        }
    }
    
    printf("Successfully read %d elements.\nOutputting to file...\n", i);
    
    FILE * randOut = fopen(fileName, "w");
    
    if(randOut == NULL) {
    
        printf("\nError opening output file. Cleaning up and exiting.\n");
        free(randCache);
        return -2;
    }
    //Write to the file if no error in trying to open it.
    else {
    
        printf("Output file %s opened successfully for writing. Beginning write...\n", fileName);
        for(elementsWritten = 0; elementsWritten < elements;\
            fprintf(randOut, "%d%c", randCache[elementsWritten++], delimiter)) {
            
            //Uncomment if not getting expected results to see what is written.
            //printf(" Wrote %d%c ", randCache[elementsWritten], delimiter);
        }
    }
    
    printf("%d Elements written. Cleaning up and exiting.\n", elementsWritten);
    
    //Cleaning.
    fclose(randOut);
    free(randCache);
    
    return 0;
}
