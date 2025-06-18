#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <sstream>
#include <fstream>

struct info  
{
    std::string start;
    std::string end;
    std::string id;
    info(const std::string& s, const std::string& e, const std::string& i) : start(s), end(e), id(i) {}
};

struct TrieNode
{
    std::unordered_map<char, std::unique_ptr<TrieNode>> children;
    std::vector<info> ranges;
};

class trie
{
    std::unique_ptr<TrieNode> root;

public:
    trie() : root(std::make_unique<TrieNode>()){}
    
    void insert(const std::string& start, const std::string& end, const std::string& id)
    {
        TrieNode* node = root.get();

        for (size_t i = 0; i < start.size(); ++i)
        {
            char c = start[i];
            if (!node->children[c])
            {
                node->children[c] = std::make_unique<TrieNode>();
            }
            node = node->children[c].get();
            node->ranges.emplace_back(start, end, id);
        }
    }

    std::string find(const std::string& num) const
    {
        const TrieNode* node = root.get();
        std::string resultId;
        size_t maxLen = 0;

        if (num.size() != 15)
        {
            return "wrong number";
        }

        for (size_t i = 0; i < num.size(); ++i)
        {
            char c = num[i];
            if (!node->children.count(c)) break;
            node = node->children.at(c).get();
        
            for (const auto& range : node->ranges)
            {
                if (range.start <= num && num <= range.end)
                {
                    if (i + 1 > maxLen)
                    {
                        maxLen = i + 1;
                        resultId = range.id;
                    }
                }
            }
        }
        return resultId.empty() ? "null" : resultId;
    }
};


void load_ranges(const std::string& filename, trie& trie)
{
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string start, end, id;

        std::getline(ss, start, ',');
        std::getline(ss, end, ',');
        std::getline(ss, id, ',');
        trie.insert(start, end, id);
    }
}

void test(const std::string& filename, const trie& trie)
{
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string num, expectedId;

        std::getline(ss, num, ',');
        std::string foundId = trie.find(num);

        std::cout << "Number: " << num << ", Found: " << foundId << std::endl;
    }
}
