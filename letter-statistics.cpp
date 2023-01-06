#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int letterCounter (std::string letters, std::vector<int> &letterFrequency) {

    int highestCount = 0;
    highestCount = letterFrequency.at(1);

    for (int i = 1; i < letters.length(); i++) {

        char currentLetter = letters.at(i);

        if (letterFrequency.at(currentLetter - 'a') > highestCount) {
            highestCount = letterFrequency.at(currentLetter - 'a');
        } 
        
    }
    
    return highestCount;

}


char mostRepeatedLetter (std::string letters, std::vector<int> &letterFrequency) {

    char highestLetter;

    for (int i = 0; i < letters.length(); i++) {

        char currentLetter = letters.at(i);

        if (letterFrequency.at(currentLetter - 'a') == letterCounter(letters, letterFrequency)) {
            highestLetter = currentLetter;
        } 

    }

    return highestLetter;

}


void letterOutputter (std::string inputStatement) {

    std::string vowels = "uoiea";
    std::string consonants = "zyxwvtsrqpnmlkjhgfdcb";
    std::string alphabet = "zywvutsrqponmlkjihgfedcba"; 

    std::transform(inputStatement.begin(), inputStatement.end(), inputStatement.begin(), ::tolower);

    std::vector<int> letterFrequency(26, 0); //I create a vector of 26 elements, which are all initially 0s

    //Lowercase chars are stored from 97 to 122. I then loop through the vector and the input string (Resource: https://www.asciitable.com/)
    for (int i = 0; i < letterFrequency.size(); i++) {
        
        for (int j = 0; j < inputStatement.size(); j++) {

            char currentChar = inputStatement.at(j);

            if (currentChar == (i + 'a')) { //If the current character equals the numeric value of a given letter, I add 1 to the frequency of that letter at the corresponding index in the vector
                letterFrequency.at(i)++;
            }
        }
    }

    std::cout << "Most frequent vowel: " << mostRepeatedLetter(vowels, letterFrequency) << " (" << letterCounter(vowels, letterFrequency) << " times)" << std::endl;
    std::cout << "Most frequent consonant: " << mostRepeatedLetter(consonants, letterFrequency) << " (" << letterCounter(consonants, letterFrequency) << " times)" << std::endl;
    std::cout << "Most frequent letter, overall: " << mostRepeatedLetter(alphabet, letterFrequency) << " (" << letterCounter(alphabet, letterFrequency) << " times)" << std::endl;

}


std::string fileProcessor (std::string file) { 
    
    std::ifstream inFS;
    std::string fileWord;
    std::string fileContent;

    inFS.open(file);

    if (!inFS.is_open()) {

        throw std::runtime_error("cannot open input file " + file);

    }

    //Once file is open, now loop through file content and store the strings in fileContent
    while (!inFS.eof()) {

        inFS >> fileWord;

        if (inFS.fail()) {
            break;
        }

        fileContent += fileWord;

    }

    inFS.close();

    return fileContent;

}


int main (int argc, char* argv[]) {

    try {

        std::string inputStatement;
        std::vector<std::string> inputVector;

        if (argc > 2) {

            throw std::runtime_error("cannot handle parameter list");

        } else if (argc == 2) {

            inputStatement = fileProcessor(argv[1]);

        } else {

            while (getline(std::cin, inputStatement)) {
                inputVector.push_back(inputStatement);
            }

            inputStatement = "";

            for (int i = 0; i < inputVector.size(); i++) {
                inputStatement += inputVector.at(i);
            }

        }

        letterOutputter(inputStatement);
        
    } catch (std::runtime_error &excpt) {

        std::cout << excpt.what() << std::endl;

    }
    
    return 0;
}