#include <vector>
#include <iostream>
using namespace std;

template<class T> 
class entry {

    private:
        entry<T>* parent;
        T token;
        vector<entry<T>*> children;
        bool isCorrect;
    public:

        entry();

        entry(entry<T>* parent, T token): parent(parent), token(token)
        {
            isCorrect = false;
        }

        ~entry()
        {
            for (int i = 0; i < children.size(); i++) {
                delete children.at(i);
            }
            delete token;
        }

        entry<T>* getParent() {
            return parent;
        }

        T getToken() {
            return token;
        }

        vector<entry<T>*> getChildren() {
            return children;
        }

        entry<T>* addChild(T token) {
            entry<T>* e = new entry<T>(this, token);
            children.push_back(e);
            return e;
        }

        bool getIsCorrect() {
            return isCorrect;
        }

        void setStatus(bool isCorrect) {
            this->isCorrect = isCorrect;
        }

        void printEntry(int level) {
            
            for (int i = 0; i < level; ++i) {
                cout << "      ";
            }

            if (level != 0) {
                cout << "|-->";
            }

            cout << "[" << token << ":" << isCorrect << "]" << endl;

            for (int i = 0; i < children.size(); i++) {
                children.at(i)->printEntry(level + 1);
            }
            
        }
};