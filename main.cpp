#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cctype>
#include <unordered_map>
#include <regex>
#include <iomanip> // Include for std::hex manipulator
#include <cstdlib> // Include for srand() and rand()

/**
 * @brief One way compiler for a hash function
 * 
 * @param filename Name of the file containing the dictionary.
 * @param myMap Reference to the unordered_map to store the dictionary.
 * @param code_book_array Array representing the relationship between integers and words.
 * @param array_size Size of the code_book_array.
 */
void load_dict_code_book(const std::string& filename, std::unordered_map<std::string, int>& myMap, int code_book_array[], int array_size);

/**
 * @brief Checks if a given string contains only alphabetic characters.
 * 
 * @param word The string to be checked.
 * @return true if the string contains only alphabetic characters, false otherwise.
 */
bool string_is_alpha(const std::string& word);

/**
 * @brief Converts a string to lowercase.
 * 
 * @param word The string to be converted.
 * @return The converted lowercase string.
 */
std::string to_lowercase(const std::string& word);

/**
 * @brief Prints each key-value pair in the unordered_map.
 * 
 * @param myMap The unordered_map to be printed.
 */
void printMap(const std::unordered_map<std::string, int>& myMap);

/**
 * @brief Main function.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 if successful, 1 otherwise.
 */
int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1; // Exit with error
    }

    std::unordered_map<std::string, int> myMap;
    int code_book_size = 26178;
    int code_bk[code_book_size];  // Initialize the code book or the relationship between an integer and a word
    for (int i = 0; i < code_book_size; ++i) {
        code_bk[i] = i + 1;
    }
    
    load_dict_code_book(argv[1], myMap, code_bk, code_book_size);
    std::string input;
    std::regex alphabetic("[a-z]+"); // Regular expression to match alphabetic characters

    while (true) {
        std::cout << "Enter a sentence (words separated by white spaces, only lower alphabetic characters allowed, no punctuation or apostrophes and enter *end* to exit program):\n";
        std::getline(std::cin, input); // Read the input line by line

        if (input == "*end*") {
            std::cout << "Exiting the program." << std::endl;
            break; // Exit the while loop
        }

        // Use istringstream to split the input line into words
        std::istringstream iss(input);
        std::string word;
        std::ostringstream oss;
        while (iss >> word) {
            // Check if the current word contains only alphabetic characters
            if (std::regex_match(word, alphabetic)) {
                std::cout << "Word accepted: " << word << std::endl;
                 if (myMap.count(word) > 0) {
                   //std::cout<<  std::hex <<myMap[word] << std::endl;
                   oss << std::hex << myMap[word]; // Set output to hexadecimal and append the value
                   //oss << std::hex;
                 }
            } else {
                std::cout << "Invalid word: " << word << ". Please enter words containing only alphabetic characters (a-z and A-Z)." << std::endl;
            }
        }
        std::string concatenatedHex = oss.str();
        std::cout << "Your hash value is as follows: " << concatenatedHex << std::endl;
    }
     
    return 0;
}

void load_dict_code_book(const std::string& filename, std::unordered_map<std::string, int>& myMap, int code_book_array[], int array_size) 
{
    // This function loads the dictionary into an unordered_map used to hash words from input
    std::ifstream file(filename);
    
    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    // Read and store the first word of each line of the file into the unordered_map
    std::string line;
    int counter = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string word;
        if (iss >> word) {
            if (string_is_alpha(word)) {
                if (myMap.count(to_lowercase(word)) == 0) { // Check for duplicate entries and avoid adding duplicates
                    myMap[to_lowercase(word)] = code_book_array[counter];
                    ++counter;
                }
            }
        }
    }

    // Close the file
    file.close();
}

bool string_is_alpha(const std::string& word) 
{
    // This function checks if a string contains only alphabetic characters
    const char* str = word.c_str();

    for (const char* ptr = str; *ptr; ++ptr) {
       if (!isalpha(*ptr)) {
            return false; // Return false as soon as a non-alphabetic character is found
       }
    }
    return true; // If all characters are alphabetic, return true
}

std::string to_lowercase(const std::string& word) 
{
    // This function converts a string to lowercase
    std::string result = word; // Create a copy of the input string to modify
    for (char& c : result) { // Iterate over each character in the copied string
        c = std::tolower(c); // Convert the character to lowercase
    }
    return result; // Return the modified string
}

void printMap(const std::unordered_map<std::string, int>& myMap) 
{
    // This function is used for debugging purposes to print each key-value pair in the unordered_map
    // Iterate over each key-value pair in the unordered_map
    for (const auto& pair : myMap) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}