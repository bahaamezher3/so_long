# get_next_line

A C library function that reads a file descriptor line by line, similar to the standard `getline()` function but with customizable buffer size and memory management.

## Description

The `get_next_line` function reads from a file descriptor (`fd`) and returns the next line from the file. It's designed to be efficient and memory-safe, using a static buffer to maintain state between calls. This is particularly useful for reading large files without loading the entire content into memory at once.

## Features

- **Line-by-line reading**: Reads one line at a time from a file descriptor
- **Configurable buffer size**: Default buffer size of 42 bytes (customizable via `BUFFER_SIZE` macro)
- **Memory efficient**: Uses dynamic memory allocation and proper cleanup
- **Static state management**: Maintains reading position between function calls
- **Error handling**: Returns `NULL` on errors or end of file
- **Cross-platform**: Works on Unix-like systems (Linux, macOS)

## Function Prototype

```c
char *get_next_line(int fd);
```

### Parameters
- `fd`: File descriptor to read from

### Return Value
- **Success**: Pointer to the next line (including newline character)
- **End of file**: `NULL`
- **Error**: `NULL`

## Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;
    
    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    // Read file line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Don't forget to free the memory!
    }
    
    close(fd);
    return (0);
}
```

## Implementation Details

### Core Functions

1. **`get_next_line(int fd)`** - Main function that orchestrates the line reading process
2. **`read_and_full(int fd, char *full)`** - Reads from file descriptor and fills the buffer
3. **`extract_line(char *full)`** - Extracts a single line from the buffer
4. **`new_full(char *full)`** - Updates the buffer after line extraction

### Utility Functions

1. **`ft_strlen(char *str)`** - Custom string length function
2. **`ft_strchr(char *str, int c)`** - Custom character search function
3. **`ft_strjoin(char *s1, char *s2)`** - Custom string concatenation function

### Buffer Management

- Uses a static variable to maintain the reading buffer between function calls
- Automatically handles buffer overflow and underflow
- Efficiently manages memory allocation and deallocation
- Supports reading files larger than the buffer size

## Compilation

To compile the project with your main file:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c your_main.c -o your_program
```

### Compilation Flags

- `-Wall -Wextra -Werror`: Enable all warnings and treat them as errors
- `-D BUFFER_SIZE=42`: Define buffer size (optional, defaults to 42)

## Buffer Size Configuration

You can customize the buffer size by defining `BUFFER_SIZE` before including the header:

```c
#define BUFFER_SIZE 1024
#include "get_next_line.h"
```

Or during compilation:

```bash
gcc -D BUFFER_SIZE=1024 get_next_line.c get_next_line_utils.c main.c
```

## Memory Management

⚠️ **Important**: The function allocates memory for each line returned. You **must** free this memory after use to prevent memory leaks:

```c
char *line = get_next_line(fd);
if (line)
{
    // Use the line
    printf("%s", line);
    free(line);  // Free the memory!
}
```

## Error Handling

The function handles several error conditions:

- Invalid file descriptor (`fd < 0`)
- Invalid buffer size (`BUFFER_SIZE <= 0`)
- Read errors from the file descriptor
- Memory allocation failures

## Performance Characteristics

- **Time Complexity**: O(n) where n is the line length
- **Space Complexity**: O(n) for the line buffer
- **Efficiency**: Optimized for sequential reading with minimal memory overhead

## Limitations

- Only works with text files (not binary files)
- Requires POSIX-compliant systems
- Static buffer means only one file can be read at a time per process
- Buffer size affects memory usage and performance

## Testing

You can test the function with various file types:

```c
// Test with regular text file
int fd1 = open("test.txt", O_RDONLY);

// Test with empty file
int fd2 = open("empty.txt", O_RDONLY);

// Test with very long lines
int fd3 = open("long_lines.txt", O_RDONLY);

// Test with stdin (fd = 0)
char *line = get_next_line(0);
```

## Author

**bmezher** - [@bmezher](https://github.com/bmezher)

## License

This project is part of the 42 school curriculum and follows their coding standards and guidelines.

## Contributing

This is an educational project, but suggestions and improvements are welcome. Please ensure any modifications maintain the existing coding style and functionality.

---

**Note**: This implementation is designed for educational purposes and follows specific coding standards. For production use, consider using standard library functions like `getline()` or `fgets()`.
