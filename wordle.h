#ifndef WORDLE_H
#define WORDLE_H

#ifndef RECCHECK
#include <set>
#include <string>
#endif


/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */

size_t countNumEmpty(std::string& s, size_t pos);

void checkChar(std::string& word, std::string& floating, const std::set<std::string>& dict, std::set<std::string>& answers, size_t pos, size_t empty, char c);

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict);

void recurse(
     std::string& in,
     std::string& floating,
    const std::set<std::string>& dict, std::set<std::string>& answers, size_t pos, size_t empty);

#endif