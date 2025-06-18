#include "tree.cpp"

int main()
{
    trie trie;

    loadRanges("range.csv", trie);
    test("test.csv", trie);
    
    return 0;
}