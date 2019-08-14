/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
    /* Reads a line from `wordsFile` into `word` until the file ends. */
      while (getline(wordsFile, word)) {
        string sortedWord = word;
        std::sort(sortedWord.begin(), sortedWord.end());

        auto found = dict.find(sortedWord);
        if (found != dict.end()) {
          for (size_t i = 0; i < found -> second.size(); i++) {
            if (dict[sortedWord][i] == word) {
              return;
            }
          }
        } else {
          dict[sortedWord].push_back(word);
        }
      }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for (size_t i = 0; i < words.size(); i++) {
      string sortedWord = words[i];
      std::sort(sortedWord.begin(), sortedWord.end());

      auto found = dict.find(sortedWord);
      if (found != dict.end()) {
        for (size_t j = 0; j < found -> second.size(); j++) {
          if (dict[sortedWord][j] == words[i]) {
            return;
          }
        }

        dict[sortedWord].push_back(words[i]);
      } else {
        dict[sortedWord].push_back(words[i]);
      }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string inOrder = word;
    std::sort(inOrder.begin(), inOrder.end());
    auto find = dict.find(inOrder);
    if (find != dict.end()) {
      return find -> second;
    }
    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> returnVal;
    for (auto it = dict.begin(); it != dict.end(); ++it) {
      if (it -> second.size() > 1) {
        returnVal.push_back(it -> second);
      }
    }
    return returnVal;
}
