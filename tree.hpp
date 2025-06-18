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
    
    void insert(const std::string& start, const std::string& end, const std::string& id);

    std::string find(const std::string& num) const;
};

void loadRanges(const std::string& filename, trie& trie);

void test(const std::string& filename, const trie& trie);
