#include "BinaryTree.h"

template <class Key, class Value>
class BalancedTree : public BinaryTree<Key, Value> {
public:
BalancedTree();
BalancedTree(const BalancedTree<Key, Value>& orig);
virtual ~BalancedTree();
Position<Key, Value>* insert(const Key& key, const Value& value);
private:
/* Les rotacions, definiu-les aquí sota */
//fer 4 metodes per a cada rotació

BalancedTree<Key, Value>* moveRight(const BalancedTree<Key, Value>& arbol);
BalancedTree<Key, Value>* moveLeft(const BalancedTree<Key, Value>& arbol);
BalancedTree<Key, Value>* moveRight_Left(const BalancedTree<Key, Value>& arbol);
BalancedTree<Key, Value>* moveLeft_Right(const BalancedTree<Key, Value>& arbol);

};

template<class Key, class Value>
BalancedTree<Key, Value>::BalancedTree() {
    BinaryTree::BinaryTree();
}

template<class Key, class Value>
BalancedTree<Key, Value>::BalancedTree(const BalancedTree<Key, Value>& orig) {
    BinaryTree::BinaryTree(const BinaryTree<Key, Value>& orig);
}

template<class Key, class Value>
BalancedTree<Key, Value>::~BalancedTree() {
    binaryTree::~BinaryTree();
}



