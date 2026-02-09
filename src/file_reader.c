#include "file_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FileReader* open_fileconst(const char *filename) {
    FileReader *reader = malloc(sizeof(FileReader));
    if(!reader)  return NULL;
    reader->file = fopen(filename, "r");
    if (!reader->file){
        free(reader);
        return NULL;
    }

    return reader;
    
}