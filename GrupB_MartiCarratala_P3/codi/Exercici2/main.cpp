#include "WordIndexer.h"
#include <chrono>
#include <iostream>
using namespace std;
int main() {
    WordIndexer* indexer = nullptr;
    int opcio;
    
    do {
        cout << "1. Carregar fitxer" << endl;
        cout << "2. Mostrar arbre ordenat" << endl;
        cout << "3. Cercar paraules del diccionari" << endl;
        cout << "4. Generar index de paraules" << endl;
        cout << "5. Mostrar profunditat de l'arbre" << endl;
        cout << "6. Sortir" << endl;
        cout << "Opcio: ";
        cin >> opcio;
        
        switch (opcio) {
            case 1: {
                char opcioFitxer;
                cout << "Quin fitxer vols (P/G)? ";
                cin >> opcioFitxer;
                string path;
                if (opcioFitxer == 'P' || opcioFitxer == 'p')
                path = "C:/Users/marti/Desktop/GrupB_MartiCarratala_P3/codi/Exercici2/shortText.txt";
                else
                path = "C:/Users/marti/Desktop/GrupB_MartiCarratala_P3/codi/Exercici2/longText.txt";
                auto begin = chrono::steady_clock::now();
                delete indexer;
                indexer = new WordIndexer(path);
                auto end = chrono::steady_clock::now();
                cout << "Temps de creació: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms." << endl;
                break;
            }

            case 2: {
                if (indexer == nullptr) {
                    cout << "Primer carrega un fitxer!" << endl;
                    break;
                }
                indexer->printDictionary();
                break;
            }

            case 3: {
                if (indexer == nullptr) {
                    cout << "Primer carrega un fitxer!" << endl;
                    break;
                }
                ifstream dict("C:/Users/marti/Desktop/GrupB_MartiCarratala_P3/codi/Exercici2/dictionary.txt");
                string word;
                auto begin = chrono::steady_clock::now();
                while (getline(dict, word)) {
                    if (indexer->contains(word))
                    cout << word << " trobada!" << endl;
                    else
                    cout << word << " no trobada." << endl;
                }
                auto end = chrono::steady_clock::now();
                cout << "Temps de cerca: "<< chrono::duration_cast<chrono::milliseconds>(end - begin).count()<< " ms." << endl;
                dict.close();
                break;
            }

            case 4: {
                if (indexer == nullptr) {
                    cout << "Primer carrega un fitxer!" << endl;
                    break;
                }
                auto begin = chrono::steady_clock::now();
                indexer->printDictionary();
                auto end = chrono::steady_clock::now();
                cout << "Temps: "<< chrono::duration_cast<chrono::milliseconds>(end - begin).count()<< " ms." << endl;
                break;
            }

            case 5: {
                if (indexer == nullptr) {
                    cout << "Primer carrega un fitxer!" << endl;
                    break;
                }
                cout << "Profunditat de l'arbre: " << indexer->height() << endl;
                break;
            }
            case 6: cout << "Sortint..." << endl; break;
        }
    } while (opcio != 6);
    
    delete indexer;
    return 0;
}