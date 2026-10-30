#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
    FILE* f = fopen(filename, "r");
    if(f == NULL){
        return NULL;
    }
    char* line = NULL; size_t length = 0;
    counts_t* ans = createCounts();
    if(ans == NULL){
        return NULL;
    }
    while(getline(&line, &length, f) >= 0){
        size_t length = strlen(line);
        if(length == 1 && line[length - 1] == '\n'){
            return NULL;
        }
        if(length - 1 >= 0 && line[length - 1] == '\n'){
            line[length - 1] = '\0';
        }
        char* value = lookupValue(kvPairs, line);
        addCount(ans, value);
    }
    free(line);
    fclose(f);
    return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
    if(argc < 3){
        fprintf(stderr, "err");
        exit(EXIT_FAILURE);
    }
    kvarray_t * kv = readKVs(argv[1]);
    if(kv == NULL){
        fprintf(stderr, "err");
        exit(EXIT_FAILURE);
    }
 //count from 2 to argc (call the number you count i)
    for(int i = 2; i < argc; i++){
        //count the values that appear in the file named by argv[i], using kv as the key/value pair
        //   (call this result c)
        counts_t* c = countFile(argv[i], kv);
        if(c == NULL){
            freeKVs(kv);
            fprintf(stderr, "err");
            exit(EXIT_FAILURE);
        }
        //compute the output file name from argv[i] (call this outName)
        char* outName = computeOutputFileName(argv[i]);
        if(outName == NULL){
            freeCounts(c);
            freeKVs(kv);
            fprintf(stderr, "err");
            exit(EXIT_FAILURE);
        }
        //open the file named by outName (call that f)
        FILE* f = fopen(outName, "w");
        if(f == NULL){
            free(outName);
            freeCounts(c);
            freeKVs(kv);
            fprintf(stderr, "err");
            exit(EXIT_FAILURE);
        }
        //print the counts from c into the FILE f
        printCounts(c, f);
        //close f
        fclose(f);
        //free the memory for outName and c
        free(outName);
        freeCounts(c);
    }
   //free the memory for kv
    freeKVs(kv);
    return EXIT_SUCCESS;
}
