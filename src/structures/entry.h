#include <vector>
using namespace std;

template<class T> 
class entry {

    private:
        entry<T>* parent;
        T token;
        vector<entry<T>*> children;
    public:

        entry();

        entry::entry(entry<T>* parent, T token): parent(parent), token(token)
        {
            children = new vector();
        }

        entry::~entry()
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

        vector<entry<T>*> addChild(T token) {
            auto entry = new entry<T>(this, token);
            children.push_back(entry);
            return entry;
        }

        string printEntry(int level) {
            
            for (int i = 0; i < level - 1; ++i) {
                cout << "      ";
            }

            if (level != 0) {
                cout << "--->";
            }

            cout << "[" << token << "]";

            for (int i = 0; i < children.size(); i++) {
                children.at(i)->printEntry(level + 1);
            }
            
        }
};