# Log Analyser

A modular C-based tool designed to parse and analyze log files. It processes log entries to generate statistics on log levels (INFO, WARN, ERROR) and identifies the most frequent unique error messages.

## Project Structure

```
Log_analyser/
├── include/          # Header files defining the interfaces
│   ├── analyser.h    # Core logic for aggregating statistics
│   ├── file_reader.h # File I/O operations
│   ├── parser.h      # Log line parsing logic
│   └── report.h      # Reporting and output functions
├── src/              # Source code implementation (to be implemented)
├── logs/             # Directory for storing input log files
└── README.md         # Project documentation
```

## Modules

### 1. File Reader (`file_reader.h`)
Handles safe file operations.
- Opens log files.
- Reads files line-by-line using a buffered reader.
- Ensures proper resource cleanup.

### 2. Parser (`parser.h`)
Responsible for interpreting raw log lines.
- Parses timestamps, log levels, and messages.
- Supports standard log levels: `INFO`, `WARN`, `ERROR`.
- Converts raw strings into structured `LogEntry` objects.

### 3. Analyser (`analyser.h`)
The core processing engine.
- Aggregates total line counts.
- Counts occurrences of each log level.
- Tracks unique error messages to identify recurring issues.
- Capable of retrieving the top N most frequent errors.

### 4. Report (`report.h`)
Generates human-readable output.
- Prints analysis summaries.
- Lists top error patterns.

## Data Structures

- **LogEntry:** Represents a single parsed log line (Timestamp, Level, Message).
- **AnalysisResult:** Stores aggregate statistics (total lines, level counts) and a collection of unique error entries.
- **ErrorEntry:** Holds a unique error message and its occurrence count.

## Getting Started

### Prerequisites
- GCC Compiler (or any standard C compiler)
- Make (optional, for build automation)

### Building the Project
*Note: Source implementation files (`.c`) need to be created in the `src/` directory matching the headers in `include/`.*

Once implemented, you can compile the project using:

```bash
gcc -I./include src/*.c -o log_analyser
```

### Usage
Run the executable passing the log file as an argument (implementation dependent):

```bash
./log_analyser logs/app.log
```

## Future Improvements
- Add support for configuration files.
- Implement regex-based parsing for more complex log formats.
- Add support for multiple log file formats (JSON, CSV).
