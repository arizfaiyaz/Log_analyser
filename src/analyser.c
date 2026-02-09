#include "analyser.h"
#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

AnalysisResult* init_analyser() {
    AnalysisResult *result = malloc(sizeof(AnalysisResult));
    if (!result) return NULL;

    result->total_line = 0;
    result->info_count = 0;
    result->warn_count = 0;
    result->error_count_unique = 0;
    result->error_capacity = 100;

    result->error_entries = calloc(result->error_capacity, sizeof(ErrorEntry));
    if (!result->error_entries) {
        free(result);
        return NULL;
    }

    return result;

}

static void add_error_message(AnalysisResult *result, const char *message) {

    // Check if the error message already exists
    for (int i = 0; i < result->error_count_unique; i++) {
        if(strcmp(result->error_entries[i].message, message) == 0) {
            result->error_entries[i].count++;
            return;
        }
    }

    // new error message - check capacity
    if (result->error_count_unique >= result->error_capacity) {
        // double the capacity
        int new_capacity = result->error_capacity * 2;
        ErrorEntry *new_entries = realloc(result->error_entries, new_capacity * sizeof(ErrorEntry));
        if (!new_entries) {
            return; // handle realloc failure
        }
        result->error_entries = new_entries;
        result->error_capacity = new_capacity;
    }

    // Add new error message
    snprintf(result->error_entries[result->error_count_unique].message, MAX_MESSAGE_LEN, "%s", message);
    result->error_entries[result->error_count_unique].count = 1;
    result->error_count_unique++;

}

void process_log_line(AnalysisResult *result , const LogEntry *entry) {
    if (!result || !entry) return;

    result->total_line++;

    switch(entry->level) {
        case LOG_LEVEL_INFO:
        result->info_count++;
        break;

        case LOG_LEVEL_WARN:
        result->warn_count++;
        break;

        case LOG_LEVEL_ERROR:
        result->error_count++;
        add_error_message(result, entry->message);
        break;
    }
}

void get_top_errors(const AnalysisResult *result, int top_n, ErrorEntry *top_errors) {
    if(!result || !top_errors) return;

    int n = result->error_count_unique < top_n ? result->error_count_unique : top_n;

    // Create a copy to avoid modifying the original
    ErrorEntry *temp = malloc(result->error_count_unique *sizeof(ErrorEntry));
    if (!temp) return;

    memcpy(temp, result->error_entries, result->error_count_unique * sizeof(ErrorEntry));

    // Selection sort (decreasing by count)
    for (int i =0; i < n; i++) {
        int max_idx = i;
        for (int j = i + 1; j < result->error_count_unique; j++) {
            if (temp[j].count >  temp[max_idx].count) {
                max_idx = j;
            }
        }

        // swap
        ErrorEntry swap = temp[i];
        temp[i] = temp[max_idx];
        temp[max_idx] = swap;
    }
    // Copy top N to output
    memcpy(top_errors, temp, n * sizeof(ErrorEntry));
    free(temp);

}

void cleanup_analyser(AnalysisResult *result) {
    if (result) {
        if (result->error_entries) {
            free(result->error_entries);
        }
        free(result);
    }
}