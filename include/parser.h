#ifndef PARSER_H
#define PARSER_H

#define MAX_MESSAGE_LEN 1024
#define LOG_LEVEL_INFO 0
#define LOG_LEVEL_WARN 1
#define LOG_LEVEL_ERROR 2
#define LOG_LEVEL_UNKNOWN -1

typedef struct {
    char timestamp[20]; // "2025-01-25 12:34:35" 
    int log_level; // error, info, warm, unknown
    char message[MAX_MESSAGE_LEN];  // "Database connection failed"

} LogEntry;

int parse_log_line(const char *line , LogEntry *entry); // "2025-01-25 12:34:35 error disk full"




#endif