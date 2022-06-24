// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void useFloat (std::string in, std::string floating, std::set<std::string>& floatUsed);
void insertRandom (std::string in, std::string alphabet, std::set<std::string>& allCombos);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    if (in.size() == 0) {
        std::set<std::string> empty;
        return empty;
    }

    // First, create all combinations possible using the floating letters
    std::set<std::string> floatUsed;
    useFloat (in, floating, floatUsed);

    // Then, fill the remaining spaces with random letters
    std::set<std::string> allCombos;
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    for (std::set<std::string>::iterator it = floatUsed.begin(); it != floatUsed.end(); ++it) {
        insertRandom(*it, alphabet, allCombos);
    }
    
    // Finally, compare all combinations created with the dictionary and only keep those that are real words
    std::set<std::string> realWords;
    for (std::set<std::string>::iterator it = allCombos.begin(); it != allCombos.end(); ++it) {
        if (dict.find(*it) != dict.end()) {
            realWords.insert(*it);
        }
    }
    return realWords;


}

// Define any helper functions here
void useFloat (std::string in, std::string floating, std::set<std::string>& floatUsed) {
    int length = in.size();
    int numFloat = floating.size();

    // No floating letters remain
    if (numFloat == 0) {
        // Means that all floating letters have been used, so insert into the set and return
        floatUsed.insert(in);
        return;
    }

    for (int j=0; j < length; j++) {
        // If there is an empty space in the word
        if (in[j] == '-') {
            // Fill in the blank space with the first floating letter given
            in[j] = floating[0];
            // Make a substring without the letter used
            std::string reducedFloating = floating.substr(1, numFloat-1);
            // Recurse using the substring
            useFloat(in, reducedFloating, floatUsed);
            // Reset the used space
            in[j] = '-';
        }
    }
}

void insertRandom (std::string in, std::string alphabet, std::set<std::string>& allCombos) {
    int length = in.size();
    int numAlphabet = alphabet.size();

    // If all blank spaces have been filled
    if (in.find('-') == std::string::npos) {
        // Insert word into set and return
        allCombos.insert(in);
        return;
    }

    for (int i=0; i < length; i++) {
        // If there is a blank space
        if (in[i] == '-') {
            // Go through the alphabet
            for (int j=0; j < numAlphabet; j++) {
                // Insert letter into blank space
                in[i] = alphabet[j];
                // Reduce the alphabet string
                std::string reducedAlphabet = alphabet.substr(j, numAlphabet-1);
                // Recurse using the substring
                insertRandom(in, reducedAlphabet, allCombos);
                // Reset space
                in[i] = '-';
            }
        }
    }

    
}