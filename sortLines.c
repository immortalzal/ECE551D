#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

int main(int argc, char ** argv) {
    int count = 0;
    char ** temp_buff;
    char* line = NULL;
    char ** data = NULL;
    size_t length = 0;
    if(argc == 1){
        while(getline(&line,&length, stdin) >= 0){
            temp_buff = realloc(data, (count + 1) * sizeof(char *));
            if(temp_buff == NULL){
                fprintf(stderr, "realloc fail\n");
		        free(data);
		        free(line);
                exit(EXIT_FAILURE);
            }
            data = temp_buff;
            data[count] = strdup(line);
            if(data[count] == NULL){
                fprintf(stderr, "strdup fail\n");
		        for(int i = 0; i < count; i++){
                    free(data[i]);
                }
		        free(data);
		        free(line);
                exit(EXIT_FAILURE);
            }
            count++;
        }
        sortData(data, count);
        for(int i = 0; i < count; i++){
            printf("%s", data[i]);
        }
        for(int i = 0; i < count; i++){
            free(data[i]);
        }
	free(data);
	free(line);
    }else{
        for(int i = 1; i < argc; i++){
            const char* input_file = argv[i];
            count = 0; 
            data = NULL;
            line = NULL;
            length = 0;
            FILE* f = fopen(input_file, "r");
            if(f == NULL){
                fprintf(stderr, "empty file\n");
		        free(data);
                exit(EXIT_FAILURE);
            }
            while(getline(&line, &length, f) >= 0){
                temp_buff = realloc(data, (count + 1) * sizeof(char *));
                if(temp_buff == NULL){
                    fprintf(stderr, "realloc fail\n");
		            free(data);
		            free(line);
                    fclose(f);
                    exit(EXIT_FAILURE);
                }
                data = temp_buff;
                data[count] = strdup(line);
                if(data[count] == NULL){
                    fprintf(stderr, "strdup fail\n");
		            for(int i = 0; i < count; i++){
                        free(data[i]);
                    }
                    free(data);
		            free(line);
                    fclose(f);
                    exit(EXIT_FAILURE);
                }
                count++;
            }
            sortData(data, count);
            for(int i = 0; i < count; i++){
                printf("%s", data[i]);
            }
            for(int i = 0; i < count; i++){
                free(data[i]);
            }
	    free(data);
	    free(line);
        fclose(f);
        }
    }
  return EXIT_SUCCESS;
}
