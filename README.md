# one_way_compiler_CMPE_152_project
CMPE 152 Class project

# Hash Function Compiler

This C++ program acts as a one-way compiler for a hash function.

## Functionality:

- **load_dict_code_book**: Loads a dictionary from a file into an unordered_map for hashing words from input.
- **string_is_alpha**: Checks if a given string contains only alphabetic characters.
- **to_lowercase**: Converts a string to lowercase.
- **printMap**: Prints each key-value pair in the unordered_map.
- **main**: The main function which orchestrates the process. It takes a filename as input and prompts the user to enter a sentence. The program then hashes words from the input sentence using the loaded dictionary.

## Usage:

Compile the program and execute it with a filename as argument: g++ -std=c++11 -O3 main.cpp -o main          

```bash
./main dictionar_file.txt

