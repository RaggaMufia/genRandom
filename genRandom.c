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
    genRandPropsPtr properties = (genRandPropsPtr)malloc(sizeof(struct genRandProps));
    
    setDefaultProperties(properties);
    
    int parseResult = 0;
    
    //Use default program parameters.
    if(argv<2) {
    
        printf("No file name argument; Will save file as %s with %d ",
                            properties->fileName, properties->elements);
        printf("pseudorandom integers, and newline delimiter.\n");
    }
    //Parse program parameters.
    else
        parseResult = parseCmdArgs(properties, argv, argc);
        
    if(parseResult != 0)
        return parseResult;
    //Correctly handle custom upper/lower bounds.
    else if(properties->randLowerBound > 0 &&
            properties->randLowerBound < properties->randUpperBound)
        properties->randUpperBound -= properties->randLowerBound;
        
    printf("File mode: %s\n", properties->fileMode);
    
    //Set up the pseudorandom number cache
    // and initialize the pseudorandom generator.
    printf("Allocating cache... ");
    unsigned int * randCache = (unsigned int *)calloc(properties->elements, ELEMENT_SIZE);
    
    if(randCache != NULL)
        printf("Done.\nInitializing random generator...\n");
    else {
        printf("Fatal: Allocation failure.\n");
        return -1;
    }
    
    if(properties->seedType == 't')
        srand(time(NULL));
    else
        srand(properties->seedValue);
        
    printf("Random generator init successful.\n");
    
    int elementsWritten = 0;
    
    //Allows the user to specify if they want detailed output.
    printf("Batch read? (Offers no status while reading) y/n: "); 
    
    char batch = getchar();
    getchar();
    
    printf("Reading %d pseudorandom bytes...\n", (ELEMENT_SIZE*properties->elements));
    
    int i = 0;
    
    //Don't output any details while reading.
    if(batch == 'y' || batch == 'Y') {
    
        printf("Batch read starting... ");
        for(i = 0; i < properties->elements;
            randCache[i++] = rand() % properties->randUpperBound + properties->randLowerBound)
            if(i % properties->randGenPeriod == 0) {
                
                if(properties->seedType == 't')
                    srand(time(NULL));
                else
                    srand(++properties->seedValue);
            }
        
        printf(" Reading completed.\n");
    }
    //Report progress while reading.
    else {
    
        for(i = 0; i < properties->elements; i++) {
        
            randCache[i] = rand() % properties->randUpperBound + properties->randLowerBound;
            
            if(i % properties->randGenPeriod == 0) {
            
                printf("Reinitializing random generator with a new seed...\n");
                
                if(properties->seedType == 't')
                    srand(time(NULL));
                else
                    srand(++properties->seedValue);
            }
            
            printf("Item read: %u\n", randCache[i]);
        }
    }
    
    printf("Successfully read %d elements.\nOutputting to file...\n", i);
    
    FILE * randOut = fopen(properties->fileName, properties->fileMode);
    
    if(randOut == NULL) {
    
        printf("\nError opening output file. Cleaning up and exiting.\n");
        free(randCache);
        return -2;
    }
    //Write to the file if no error in trying to open it.
    else {
    
        printf("Output file %s opened successfully for writing. Beginning write...\n",
                        properties->fileName);
        //Write text.
        if(strcmp(properties->fileMode, "w") == 0)
            for(elementsWritten = 0; elementsWritten < properties->elements;
                fprintf(randOut, "%d%c", randCache[elementsWritten++], properties->delimiter));
        //Write binary.
        else
            elementsWritten = fwrite(randCache, ELEMENT_SIZE, properties->elements, randOut);
    }
    
    printf("%d Elements written. Cleaning up and exiting.\n", elementsWritten);
    
    //Cleaning.
    fclose(randOut);
    free(randCache);
    
    return 0;
}

/*
 * Sets inital properties.
 */
void setDefaultProperties(genRandPropsPtr props) {

    props->elements = ELEMENTS;
    props->delimiter = DELIMITER;
    props->randGenPeriod = 50;
    props->randUpperBound = RAND_MAX;
    props->randLowerBound = 0;
    props->seedType = 't';
    props->seedValue = 0;
    
    props->fileName = (char *)malloc(sizeof(char)*DEFAULT_FILE_NAME_LENGTH);
    strcpy(props->fileName, RAND_OUT_FILE);
    
    props->fileMode = (char *)malloc(sizeof(char));
    props->fileMode[0] = 'w';
}
