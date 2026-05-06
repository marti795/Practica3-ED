#include "BinaryTree.h"
#include "Tuple.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <algorithm>
class WordIndexer {
public:
 WordIndexer();
 WordIndexer(std::string path);
 WordIndexer(const WordIndexer& orig);
 virtual ~WordIndexer();
 int size() const;
 int height() const;
 bool contains(const std::string &word) const;
 void printOccurrences(const std::string &word) const;
 void printDictionary(Position<string, Tuple<int> > *node = nullptr) const;
protected:
 BinaryTree<string, Tuple<int> > *tree;
 void addText(std::string path);
private:
 void insertWord(const std::string &word, const int &line, const int &position);
 /* Metodes auxiliars, definiu-los aquí sota */
 void printDictionaryAux(Position<string, Tuple<int>>* node, int& count, bool& stop) const;
};

WordIndexer::WordIndexer() {
    tree = new BinaryTree<string, Tuple<int>>;
}

WordIndexer::WordIndexer(std::string path) {
    tree = new BinaryTree<string, Tuple<int>>;
    addText(path);

}

WordIndexer::WordIndexer(const WordIndexer& orig) {
    tree = new BinaryTree<string, Tuple<int>>(*orig.tree);
}

WordIndexer::~WordIndexer() {
    delete tree;
    tree = nullptr;
}

int WordIndexer::size() const {
    return tree->size();
}

int WordIndexer::height() const {
    return tree->height();
}

bool WordIndexer::contains(const std::string &word) const {
    return tree->contains(word);
}

void WordIndexer::printOccurrences(const std::string &word) const {
    if (!tree->contains(word)) {
       throw out_of_range("Paraula no trobada");
    }
    const vector<Tuple<int>>& tuples = tree->getValues(word);
    for (const Tuple<int>& t : tuples) {
        cout << " → Línia " << t.getLine() << ", paraula " << t.getPosition() << endl;
    }
}

void WordIndexer::printDictionaryAux(Position<string, Tuple<int>>* node, int& count, bool& stop) const {
    if (node == nullptr || stop) return;  // si stop=true, para todo
    
    printDictionaryAux(node->getLeft(), count, stop);
    
    if (stop) return;  // comprueba después de la recursión izquierda
    
    cout << node->getKey() << " → ";
    printOccurrences(node->getKey());
    count++;
    
    if (count % 40 == 0) {
        char resposta;
        cout << "Vols continuar? (S/N): ";
        cin >> resposta;
        if (resposta == 'N' || resposta == 'n') {
            stop = true;  // activa la parada
            return;
        }
    }
    
    printDictionaryAux(node->getRight(), count, stop);
}

void WordIndexer::printDictionary(Position<string, Tuple<int>>* node) const {
    int count = 0;
    bool stop = false;
    printDictionaryAux(tree->getRoot(), count, stop);
}

void WordIndexer::addText(std::string path) {
    ifstream file(path);  
    if (!file.is_open()) {
        throw runtime_error("No s'ha pogut obrir el fitxer");
    }
    
    string line;
    int numLine = 0;
    while (getline(file, line)) { 
        numLine++;
        istringstream iss(line);
        string word;
        int numWord = 0;
        while (iss >> word) {
            numWord++;
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
            if (!word.empty())
            insertWord(word, numLine, numWord);
        }
    }
    file.close();  
}

void WordIndexer::insertWord(const std::string &word, const int &line, const int &position) {
    Tuple<int> tuple(line,position);
    tree->insert(word,tuple);
}
