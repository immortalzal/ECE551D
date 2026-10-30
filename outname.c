#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
   char* output = malloc((strlen(inputName) + 8) * sizeof(char));
   if(output == NULL){
        return NULL;
   }
   strcpy(output, inputName);
   strcat(output, ".counts");
   return output;
}