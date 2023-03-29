#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function

void checkChar(string word, string floating, const set<string>& dict, set<string>& answers, size_t pos, size_t empty, char c) {
    string ogword = word;
    string ogfloating = floating;
    if (pos == word.size() && empty == 0 && dict.find(word) != dict.end() && floating.size() == 0) {
            answers.insert(word);
            return;
    } else if (pos == word.size()) {
            return;
    }
    word[pos] = c;

    size_t num;
    num = floating.find_first_of(c);
    if (num != string::npos) {
        floating.erase(floating.find_first_of(c), 1);
    }

    if (empty < floating.size()) {
        return;
    }

    recurse(word, floating, dict, answers, pos+1, empty-1);

    if (c == 'z') {
        return;
    } else {
        checkChar(ogword, ogfloating, dict, answers, pos, empty, c+1);
    }
}

void recurse(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict, std::set<std::string>& answers, size_t pos, size_t empty) {
        string f = floating;
        string word = in;

        if (pos == in.size() && empty == 0 && dict.find(in) != dict.end() && f.size() == 0) {
            answers.insert(in);
            return;
        } else if (pos == in.size()) {
            return;
        }

        if (word[pos] == '-') {
            checkChar(word, f, dict, answers, pos, empty, 'a');
        } else {
            recurse(word, f, dict, answers, pos+1, empty);
        }

    }

size_t countNumEmpty(string s, size_t pos) {
    if (pos >= s.size()) {
        return 0;
    }
    size_t num = 0;
    if (s[pos] == '-') {
        num = 1;
    }
    return num + countNumEmpty(s, pos+1);
}

std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict) {
            set<string> answers;
            string s = in;
            size_t empty = countNumEmpty(s, 0);
            recurse(in, floating, dict, answers, 0, empty);
            return answers;

    }

// Define any helper functions here
