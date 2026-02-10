#ifndef ANALYSER_H
#define ANALYSER_H

#include "parser.h"
#define MAX_ERROR_MESSAGE 10000

typedef struct {
    char message[MAX_MESSAGE_LEN];
    int count;

} ErrorEntry;

typedef struct {
    int total_line; // No of log lines processed
    int info_count; // No of info log lines
    int warn_count; // No of warn log lines
    int error_count;  // No of error log lines
    ErrorEntry *error_entries; // dynamic array for unique error message
    int error_count_unique; // No of unique error messages // "disk full" => uniquw counnt = 1
    int error_capacity; // capacity of the error_entries array
} AnalysisResult;

// intialize the analyser and return a pointer to the AnalysisResult structure

AnalysisResult* init_analyser(); 

// Function prototype for processing a log line. It takes a pointer to the AnalysisResult structure and a pointer to a LogEntry structure, and updates the analysis results based on the log entry.

void process_log_line(AnalysisResult *result , const LogEntry *entry); 

// Function prototype for retrieving the top N error messages. It takes a pointer to the AnalysisResult structure, the number of top errors to retrieve, and a pointer to an array of ErrorEntry structures to store the top errors.

void get_top_errors(const AnalysisResult *result , int top_n, ErrorEntry *top_errors);

// Function prototype for cleaning up the analyser. It takes a pointer to the AnalysisResult structure and frees any allocated resources.

void cleanup_analyser(AnalysisResult *result);



#endif 