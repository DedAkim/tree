#include "tree.hpp"

int main()
{
    trie trie;

    load_ranges("range.csv", trie);
    test("test.csv", trie);
    
    return 0;
}