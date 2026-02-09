#ifndef FILE_READER_H  // Header guard to prevent multiple inclusions
#define FILE_READER_H  // Include necessary headers

#include <stdio.h>    // Standard I/O library for file operations

#define BUFFER_SIZE 4096 // Define a constant for the buffer size used in reading lines

// Define a structure to represent a file reader, which contains a FILE pointer and a buffer for reading lines
typedef struct {
    FILE *file;
    char buffer[BUFFER_SIZE];

} FileReader;


// Function prototype for opening a file and returning a pointer to a FileReader structure
FileReader* open_file(const char *filename); 

// Function prototype for reading a line from the file using the FileReader structure. It takes a pointer to a FileReader, a buffer to store the line, and the maximum length of the line to read. 
char* read_line(FileReader *reader, char *line , size_t max_length);

// Function prototype for closing the file associated with the FileReader structure and freeing any allocated resources.
void close_file(FileReader *reader); 


#endif // FILE_READER_H


