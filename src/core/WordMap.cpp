#include <algorithm>
#include <locale>
#include "WordMap.h"

namespace core
{
	WordMap WordMap::Build(std::vector<std::string> &wordList)
	{
        WordMap wordMap; // 创建一个WordMap对象
        for (std::string word : wordList)
        {
            wordMap.AddWord(word); // 使用wordMap.来访问成员函数
        }

        return wordMap;
	}

	int WordMap::AddWord(const std::string &word)
	{
		if (_wordToId.find(word) != _wordToId.end())
		{
			return _wordToId[word];
		}

		++_wordCount;
		_wordToId.emplace(word, _wordCount);
		_idToWord.emplace(_wordCount, word);
		return _wordCount;
	}

	std::string WordMap::GetWord(int id)
	{
		assert(id > 0 && id <= _wordCount);
		return _idToWord[id];
	}

	int WordMap::GetId(const std::string &word)
	{
        assert(_wordToId.find(word) != _wordToId.end());
		return _wordToId[word];
	}

    std::vector<std::string> WordMap::GetAllWords() const {
        std::vector<std::string> keys;
        for (const auto& key : _wordToId) {
            keys.push_back(key.first);
        }
        return keys;
    }
}
