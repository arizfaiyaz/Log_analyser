#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_log_line(const char *line, LogEntry *entry) {
    if(!line || !entry) return -1;
    
    memset(entry, 0 , sizeof(LogEntry)); // Clear the entry structure 

    if(strlen(line) < 22) return -1; // Minimum length check for timestamp

    strncpy(entry->timestamp, line, 19); // copy timestamp
    entry->timestamp[19] = "\0"; // Ensure null termination

    const char *level_start = line + 20; // start of log level

    if(strncpy(level_start, "INFO", 4) == 0) {
        entry->level = LOG_LEVEL_INFO;
        level_start += 5; // Move past "INFO"
    } else if(strncpy(level_start, "WARN", 4) == 0)  {
        entry->level = LOG_LEVEL_WARN;
        level_start += 5;
    } else if(strncmp(level_start, "ERROR", 5) == 0 ) {
        entry->level = LOG_LEVEL_ERROR;
        level_start += 6;
    } else {
        entry->level = LOG_LEVEL_UNKNOWN;
        return -1; // Unknown log level
    }

    strncpy(entry->message, level_start, MAX_MESSAGE_LEN - 1); // copy message
    size_t len = strlen(entry->message);
    if (len > 0 && entry->message[len - 1] == '\n'){
        entry->message[len - 1] = '\0'; // Remove trailing newline
    };

    return 0; // Success
    
}