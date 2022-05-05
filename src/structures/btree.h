#include "entry.h"

using namespace std;

template<class T> 
class btree {
    private:
        entry<T>* iterator;
        entry<T>* root;
    
    public:
        btree(T token) {
            this->root = new entry<T>(nullptr, token);
            this->iterator = root; 
        }
    
        entry<T>* getIterator() {
            return this->iterator;
        }

        entry<T>* getRoot() {
            return this->root;
        }
        //при рекурсивных вызовах можно добавлять токен и сохранять итератор прошлого, при этом запустить обработку следующего токена
        //тогда на нашем рекурсивном вызове останется старый итератор
        entry<T>* addToken(entry<T>* _iterator, T _token) {
            iterator = _iterator->addChild(_token);
            return iterator;
        }

        void printTree() {
            root->printEntry(0);
        }
};