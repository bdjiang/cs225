/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold) const
{
    TextFile infile(filename);
    vector<pair<string, int>> ret;
    /**
     * @todo Implement this function.
     * @see char_counter.cpp if you're having trouble.
     */

    std::vector<std::pair<string, int>> allWords;

    while (infile.good()) {
      string word = infile.getNextWord();
      bool foundWord = false;
      for (size_t i = 0; i < allWords.size(); i++) {
        if (allWords[i].first == word) {
          allWords[i].second = allWords[i].second + 1;
          foundWord = true;
          break;
        }
      }
      if (!foundWord) {
        allWords.push_back(pair<string, int> (word, 1));
      }
    }

    for (size_t i = 0; i < allWords.size(); i++) {
      if (allWords[i].second >= threshold) {
        ret.push_back(allWords[i]);
      }
    }

    return ret;
}
