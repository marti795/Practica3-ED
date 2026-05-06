#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "Position.h"
#include <stdexcept>
#include <iostream>

template <class Key, class Value>
class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree<Key, Value>& orig);
    virtual ~BinaryTree();
    bool isEmpty() const;
    Position<Key, Value>* getRoot() const;
    int size() const;
    int height() const;
    virtual Position<Key, Value>* insert(const Key& key, const Value& value);
    bool contains(const Key& key) const;
    const vector<Value>& getValues(const Key& key) const;
    void printPreOrder(const Position<Key, Value> *node = nullptr) const;
    void printPostOrder(const Position<Key, Value> *node = nullptr) const;
    bool identicalTree(const BinaryTree<Key, Value>& other) const;
    Position<Key, Value>* search(const Key& key) const
vector<Key> getLeaves() const; // NOU METODE FER A LA PRACTICA
    
protected:
    Position<Key, Value>* root;
private:
    int _size;

    Position<Key, Value>* searchRec(Position<Key, Value>* node, const Key& key) const;
    bool identicalRec(Position<Key, Value>* a, Position<Key, Value>* b) const;
void getLeavesAux(Position<Key,Value>* node, vector<Key>& leaves) const;
};

template <class Key, class Value>
BinaryTree<Key, Value>::BinaryTree() {
    root = nullptr;
    _size = 0;
}

template <class Key, class Value>
BinaryTree<Key, Value>::BinaryTree(const BinaryTree<Key, Value>& orig) {
    _size = orig._size;

    if (orig.root != nullptr)
        root = new Position<Key, Value>(*orig.root);
    else
        root = nullptr;
}

template <class Key, class Value>
BinaryTree<Key, Value>::~BinaryTree() {
    delete root;
}

template <class Key, class Value>
bool BinaryTree<Key, Value>::isEmpty() const {
    return root == nullptr;
}

template <class Key, class Value>
Position<Key, Value>* BinaryTree<Key, Value>::getRoot() const {
    return root;
}

template <class Key, class Value>
int BinaryTree<Key, Value>::size() const {
    return _size;
}

template <class Key, class Value>
int BinaryTree<Key, Value>::height() const {
    if (isEmpty())
        return -1;

    return root->height();
}

/* INSERT BST */
template <class Key, class Value>
Position<Key, Value>* BinaryTree<Key, Value>::insert(const Key& key, const Value& value) {

    if (isEmpty()) {
        root = new Position<Key, Value>(key);
        root->addValue(value);
        _size++;
        return root;
    }

    Position<Key, Value>* current = root;
    Position<Key, Value>* parent = nullptr;

    while (current != nullptr) {

        parent = current;

        if (key < current->getKey())
            current = current->getLeft();

        else if (key > current->getKey())
            current = current->getRight();

        else {
            current->addValue(value);
            return current;
        }
    }

    Position<Key, Value>* newNode = new Position<Key, Value>(key);
    newNode->addValue(value);
    newNode->setParent(parent);

    if (key < parent->getKey())
        parent->setLeft(newNode);
    else
        parent->setRight(newNode);

    _size++;

    return newNode;
}

/* ITERATIU */
template <class Key, class Value>
bool BinaryTree<Key, Value>::contains(const Key& key) const {

    Position<Key, Value>* current = root;

    while (current != nullptr) {

        if (key == current->getKey())
            return true;

        if (key < current->getKey())
            current = current->getLeft();
        else
            current = current->getRight();
    }

    return false;
}

template <class Key, class Value>
const vector<Value>& BinaryTree<Key, Value>::getValues(const Key& key) const {

    Position<Key, Value>* node = search(key);

    if (node == nullptr)
        throw runtime_error("Clau no trobada");

    return node->getValues();
}

/* SEARCH RECURSIU */
template <class Key, class Value>
Position<Key, Value>* BinaryTree<Key, Value>::search(const Key& key) const {
    return searchRec(root, key);
}

template <class Key, class Value>
Position<Key, Value>* BinaryTree<Key, Value>::searchRec(Position<Key, Value>* node, const Key& key) const {

    if (node == nullptr)
        return nullptr;

    if (key == node->getKey())
        return node;

    if (key < node->getKey())
        return searchRec(node->getLeft(), key);

    return searchRec(node->getRight(), key);
}

/* PREORDER */
template <class Key, class Value>
void BinaryTree<Key, Value>::printPreOrder(const Position<Key, Value>* node) const {

    if (root == nullptr)
        return;

    if (node == nullptr)
        node = root;

    cout << node->getKey() << " ";

    if (node->getLeft() != nullptr)
        printPreOrder(node->getLeft());

    if (node->getRight() != nullptr)
        printPreOrder(node->getRight());
}

/* POSTORDER */
template <class Key, class Value>
void BinaryTree<Key, Value>::printPostOrder(const Position<Key, Value>* node) const {

    if (root == nullptr)
        return;

    if (node == nullptr)
        node = root;

    if (node->getLeft() != nullptr)
        printPostOrder(node->getLeft());

    if (node->getRight() != nullptr)
        printPostOrder(node->getRight());

    cout << node->getKey() << " ";
}

/* IDENTICAL TREE */
template <class Key, class Value>
bool BinaryTree<Key, Value>::identicalTree(const BinaryTree<Key, Value>& other) const {
    return identicalRec(root, other.root);
}

template <class Key, class Value>
bool BinaryTree<Key, Value>::identicalRec(Position<Key, Value>* a, Position<Key, Value>* b) const {

    if (a == nullptr && b == nullptr)
        return true;

    if (a == nullptr || b == nullptr)
        return false;

    if (!(*a == *b))
        return false;

    return identicalRec(a->getLeft(), b->getLeft()) && identicalRec(a->getRight(), b->getRight());
}

template <class Key, class Value>
void BinaryTree<Key,Value>::getLeavesAux(Position<Key,Value>* node, vector<Key>& leaves) const {
    if (node == nullptr) return;
    if (node->isLeaf()) {
        leaves.push_back(node->getKey());  // guardamos la KEY no el nodo
    } else {
        getLeavesAux(node->getLeft(), leaves);
        getLeavesAux(node->getRight(), leaves);
    }
}

template <class Key, class Value>
vector<Key> BinaryTree<Key,Value>::getLeaves() const {
    vector<Key> leaves;
    getLeavesAux(root, leaves);
    return leaves;
}


#endif
