#include "../src/structures/btree.h"
#include <string>
int main(int argc, char const *argv[])
{
    btree<string>* tree = new btree<string>("test");
    entry<string>* newIter;
    newIter = tree->addToken(tree->getIterator(), "test1");
    tree->addToken(newIter, "test1.1");
    tree->addToken(newIter, "test1.2");
    tree->addToken(newIter, "test1.3");
    tree->addToken(newIter, "test1.4");

    newIter = tree->addToken(tree->getRoot(), "test2");
    tree->addToken(newIter, "test2.1");
    tree->addToken(newIter, "test2.2");
    tree->addToken(newIter, "test2.3");
    tree->addToken(newIter, "test2.4"); 
    tree->printTree();
    return 0;
}
