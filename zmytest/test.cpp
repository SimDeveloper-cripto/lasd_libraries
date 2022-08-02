
#include "test.hpp"
#include <iomanip>

using namespace std;
using namespace lasd;

template<typename Data>
void printHash(Data& data, void* other_par) {
    cout << "Valore: " << setprecision(20) << data << endl;
}

template<typename Data>
void fold(const Data& data, const void* limit, void* accum) {}

template<>
void fold<int>(const int& data, const void* limit, void* accum) {
    if (data < (*(int*) limit)) {
        (*(int*) accum) *= data;
        std::cout << std::endl << "Accumulatore: " << (*(int*) accum);
    } else {
        (*(int*) accum) *= 1;
    }
}

template<>
void fold<double>(const double& data, const void* limit, void* accum) {
    if (data > (*(int*) limit)) {
        (*(double*) accum) += data;
        std::cout << std::endl << "Accumulatore: " << setprecision(20) << (*(double*) accum);
    } else {
        (*(double*) accum) += 0.0; 
    }
}

template<> 
void fold<string>(const string& data, const void* limit, void* accum) {
    if (data.length() <= (*(uint*) limit)) {
        (*(string*) accum) += data; 
        cout << endl << "Accumulatore: " << (*(string*) accum);
    } else {
        (*(string*) accum) += "";
    }
}

int getHashImplType() {
    int impltype = 0;
    while(impltype < 1 || impltype > 2) {
        cout << endl << "[1] Per scegliere HashTable con indirizzamento chiuso." << endl;
        cout << "[2] Per scegliere HashTable con indirizzamento aperto." << endl;
        cout << "Scelta: ";
        cin >> impltype;
    }
    return impltype;
}

int getHashSize() {
    int size = 0;
    while (cout << "Determinare la dimensione della struttura: " && !(cin >> size)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Errore: input non intero, ripetere!" << endl;
    }
    return size; 
}

int getHashTypeData(){
    int typedata = 0;
    while(typedata < 1 || typedata > 3) {
        cout << endl << "[1] Per scegliere lavorare con interi." << endl;
        cout << "[2] Per scegliere lavorare con double." << endl;
        cout << "[3] Per scegliere lavorare con stringhe." << endl;
        cout << "Scelta: "; 
        cin >> typedata;
    }
    return typedata;
}

template<typename Data>
Vector<Data> generateRandom(int size) {}

template<>
Vector<int> generateRandom(int size) {
    default_random_engine generator(random_device{}()); 
    uniform_int_distribution<int> dist(-200, 200); 

    Vector<int> vec = Vector<int>(size);

    for (int i = 0; i < size; ++i) {
        int value = dist(generator);
        cout << "Ho generato il valore: " << value << endl;
        vec.operator[](i) = value;
    }
    return vec;
}

template<>
Vector<double> generateRandom(int size) {
    default_random_engine generator(random_device{}()); 
    uniform_real_distribution<double> dist(0, 200); 

    Vector<double> vec = Vector<double>(size);;

    for (int i = 0; i < size; ++i) {
        double value = dist(generator);
        cout << "Ho generato il valore: " << setprecision(20) << value << endl;
        vec.operator[](i) = value;
    }
    return vec;
}

string generateRandomString() {
    const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@#*%$&";
    string random_string = "";

    default_random_engine generator(random_device{}());
    uniform_int_distribution<int> distr(1, charset.size() - 1);

    int random_lenght = distr(generator);

    for(size_t i = 0; i < random_lenght; ++i) {
        random_string += charset[distr(generator)];
    }
    return random_string;
}

template<>
Vector<string> generateRandom(int size) {
    Vector<string> vec = Vector<string>(size);;
    for(int i = 0; i < size; ++i) {
        string value = generateRandomString();
        cout << "Ho generato il valore: " << value << endl;
        vec.operator[](i) = value;
    }
    return vec;
}

template<typename Data>
void populateLinearContainer(List<Data>& list, int size) {
    Vector<Data> vec = generateRandom<Data>(size);
    for (ulong i = 0; i < vec.Size(); ++i) {
        list.InsertAtBack(vec.operator[](i));
    }
}

template<typename Data>
void ifExists(TestableContainer<Data>& container) {
    Data to_search;

    while (cout << "Dichiarare il valore di cui determinare la presenza: " && !(cin >> to_search)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Errore: valore non accettabile per la struttura, ripetere!" << endl;
    }
    string output = container.Exists(to_search) ? ("L'elemento esiste nella struttura!") : ("L'elemento non esiste nella struttura!");
    cout << endl << output << endl;
}

template<typename Data>
void InsertElement(HashTable<Data>& hash) {
    Data elem;

    while (cout << endl << "Dichiarare il valore da inserire: " && !(cin >> elem)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Errore: valore non accettabile per la struttura, ripetere!" << endl;
    }
    string output = (hash.Insert(elem)) ? ("L' elemento è stato inserito!") : ("L'elemento non è stato inserito!");
    cout << endl << output;
}

template<typename Data>
void RemoveElement(HashTable<Data>& hash) {
    Data elem;

    while (cout << endl << "Dichiarare il valore da rimuovere: " && !(cin >> elem)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Errore: valore non accettabile per la struttura, ripetere!" << endl;
    }
    string output = (hash.Remove(elem)) ? ("L' elemento è stato rimosso!") : ("L'elemento non è stato rimosso!");
    cout << endl << output;
}

int getNumber() {
    double n;
    while(cout << endl << "Digitare il numero secondo cui applicare la funzione: " && !(cin >> n)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Errore: valore non accettabile!" << endl;
    } 
    return (int) n;
}

template<typename Data>
void exampleTest(HashTable<Data>& hash, Data& first_element_typedata) {
    ushort choice = 0;
    cout << endl << "[0] Per tornare indietro e testare altro esempio."         << endl;
    cout << "[1] Per visualizzare la struttura tramite funzione Map."           << endl;
    cout << "[2] Per effetturare test di esistenza di un elemento."             << endl;
    cout << "[3] Per applicare alla struttura la sua rispettiva funzione Fold." << endl;
    cout << "[4] Per inserire un elemento."                                     << endl;
    cout << "[5] Per eliminare un elemento."                                    << endl;
    cout << "[6] Per effettuare il Clear della struttura."                      << endl;
    cout << "[7] Per stampare la dimensione della struttura."                   << endl;
    cout << "Scelta: ";
    cin >> choice;

    switch(choice) {
        case 0: {
            startTest();
            break;
        } case 1: {
            cout << endl << "(Map Pre-Order) Stampa della struttura: " << endl;
            hash.Map(&printHash<Data>, nullptr);
            exampleTest(hash, first_element_typedata);
            break;
        }
        case 2: {
            cout << endl;
            ifExists(hash);
            exampleTest(hash, first_element_typedata);
            break;
        }
        case 3: {
            int n = getNumber();
            cout << endl;

            if (isInteger(first_element_typedata)) {
                int start = 1;
                cout << "(Fold Pre-Order) Prodotto per gli interi minori di n:";
                hash.Fold(&fold<Data>, &n, &start);
            } else if (isDouble(first_element_typedata)) {
                double start = 0.0;
                cout << "(Fold Pre-Order) Somma per i double maggiori di n:";
                hash.Fold(&fold<Data>, &n, &start);
            } else if (isString(first_element_typedata)) {
                string start = "";
                cout << "(Fold Pre-Order) Concatenazione per le stringhe con lunghezza minore o uguale a n:";
                hash.Fold(&fold<Data>, &n, &start);
            }
            
            cout << endl;
            exampleTest(hash, first_element_typedata);
            break;
        }
        case 4: {
            InsertElement(hash);
            cout << endl;
            exampleTest(hash, first_element_typedata);
            break;
        }
        case 5: {
            RemoveElement(hash);
            cout << endl;
            exampleTest(hash, first_element_typedata);
            break;
        }
        case 6: {
            hash.Clear();
            cout << endl << "La struttura ora è vuota!" << endl; 
            exampleTest(hash, first_element_typedata);
            break;
        }
        case 7: {
            cout << endl << "Dimensione della struttura: " << hash.Size() << endl;
            exampleTest(hash, first_element_typedata);
            break;
        }
        default: 
            cout << "Errore: scelta non disponibile!" << endl;
    }
}

void startTest() {
    cout << endl;
    int typestruct = getHashImplType();
    cout << endl;
    int typedata = getHashTypeData();
    cout << endl;
    int structsize = getHashSize();

    while (structsize <= 0) {
        cout << "Per puro scopo dimostrativo, la dimensione della struttura non può essere minore o uguale a 0." << endl 
            << "(L'hashtable è inizializzata tramite lista)." << endl;
        structsize = getHashSize();
    }

    cout << endl;

    if (typestruct == 1) {
        if (typedata == 1) {
            List<int> lista;
            populateLinearContainer(lista, structsize);
            HashTableClsAdr<int> hclsadr = HashTableClsAdr<int>(structsize, lista);
            exampleTest(hclsadr, getTypeData(lista.Front()));
        } else if (typedata == 2) {
            List<double> lista;
            populateLinearContainer(lista, structsize);
            HashTableClsAdr<double> hclsadr = HashTableClsAdr<double>(structsize, lista);
            exampleTest(hclsadr, getTypeData(lista.Front()));
        } else if (typedata == 3) {
            List<string> lista; 
            populateLinearContainer(lista, structsize);
            HashTableClsAdr<string> hclsadr = HashTableClsAdr<string>(structsize, lista);
            exampleTest(hclsadr, getTypeData(lista.Front()));
        }
    } else if (typestruct == 2) {
        if (typedata == 1) {
            List<int> lista;
            populateLinearContainer(lista, structsize);
            HashTableOpnAdr<int> hopnadr = HashTableOpnAdr<int>(structsize, lista);
            exampleTest(hopnadr, getTypeData(lista.Front()));
        } else if (typedata == 2) {
            List<double> lista;
            populateLinearContainer(lista, structsize);
            HashTableOpnAdr<double> hopnadr = HashTableOpnAdr<double>(structsize, lista);
            exampleTest(hopnadr, getTypeData(lista.Front()));
        } else if (typedata == 3) {
            List<string> lista;
            populateLinearContainer(lista, structsize);
            HashTableOpnAdr<string> hopnadr = HashTableOpnAdr<string>(structsize, lista);
            exampleTest(hopnadr, getTypeData(lista.Front()));
        }
    }
}