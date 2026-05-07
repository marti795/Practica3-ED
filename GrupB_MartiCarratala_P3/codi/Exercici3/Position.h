#ifndef POSITION_H
#define POSITION_H

#include <vector>
using namespace std;
template <class Key, class Value>
class Position {
public:
    Position(const Key key);
    Position(const Position<Key, Value>& orig);
    virtual ~Position();
    /* Modificadors */
    // Declareu-hi aquí els modificadors (setters) dels atributs que manquen
    void setParent(Position<Key,Value>* parent);
    void setLeft(Position<Key,Value>* left);
    void setRight(Position<Key,Value>* right);
    
    /* Consultors */
    const Key& getKey() const;
    const vector<Value>& getValues() const;
    // Declareu-hi aquí els consultors (getters) dels atributs que manquen
    Position<Key,Value>* getParent() const;
    Position<Key,Value>* getLeft() const;
    Position<Key,Value>* getRight() const;



    /* Operacions */
    bool isRoot() const;
    bool isLeaf() const;
    int depth() const;
    int height() const;
    void addValue(const Value& value);
    bool operator==(const Position<Key, Value>& other) const;
    
private:
    Key key;
    vector<Value> values;
    // Afegiu-hi aquí els atributs que manquen
    Position<Key,Value>* parent;
    Position<Key,Value>* left;
    Position<Key,Value>* right;
};

template<class Key, class Value>
Position<Key,Value>::Position(const Key key){
    this->key = key;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

template<class Key, class Value>
Position<Key,Value>::Position(const Position<Key, Value>& orig){
    key = orig.key;
    values = orig.values;
    parent = nullptr;
    left = nullptr;
    right = nullptr;

    if (orig.left != nullptr) {
        left = new Position<Key, Value>(*orig.left);
        left->parent = this;
    }
    if (orig.right != nullptr) {
        right = new Position<Key, Value>(*orig.right);
        right->parent = this;
    }
}

template<class Key, class Value>
Position<Key,Value>::~Position(){
    delete left;
    delete right;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template<class Key, class Value>
void Position<Key,Value>::setParent(Position<Key,Value>* parent){
    this->parent = parent;
}

template<class Key, class Value>
void Position<Key,Value>::setLeft(Position<Key,Value>* left){
    this->left = left;
}

template<class Key, class Value>
void Position<Key,Value>::setRight(Position<Key,Value>* right){
    this->right = right;
}

template<class Key, class Value>
const Key& Position<Key,Value>::getKey() const{
    return key;
}

template <class Key, class Value>
const vector<Value>& Position<Key, Value>::getValues() const {
    return values;
}

template <class Key, class Value>
Position<Key, Value>* Position<Key, Value>::getParent() const {
    return parent;
}

template <class Key, class Value>
Position<Key, Value>* Position<Key, Value>::getLeft() const {
    return left;
}

template <class Key, class Value>
Position<Key, Value>* Position<Key, Value>::getRight() const {
    return right;
}

template <class Key, class Value>
bool Position<Key, Value>::isRoot() const{
    return parent == nullptr;
}

template <class Key, class Value>
bool Position<Key, Value>::isLeaf() const{
    return left == nullptr && right == nullptr;
}

template <class Key, class Value>
int Position<Key, Value>::depth() const {
    if (isRoot()){
        return 0;
    } else {
        return parent->depth() +1;
    }
}

template <class Key, class Value>
int Position<Key, Value>::height() const{
    if (isLeaf()) {
        return 0;
    } else if (left == nullptr) {
        return 1 + right->height();
    } else if (right == nullptr) {
        return 1 + left->height();
    } else {
        return 1 + max(left->height(), right->height());
    }
}

template <class Key, class Value>
void Position<Key, Value>::addValue(const Value& value){
    values.push_back(value);
}

template <class Key, class Value>
bool Position<Key, Value>::operator==(const Position<Key, Value>& other) const{
    return key == other.key && values == other.values;
}

#endif
