
#include "test.hpp"
#include <iomanip>

using namespace std;
using namespace lasd;

template<typename Data>
void printHash(Data& data, void* other_par) {
    cout << "Value: " << setprecision(20) << data << endl;
}

template<typename Data>
void fold(const Data& data, const void* limit, void* accum) {}

template<>
void fold<int>(const int& data, const void* limit, void* accum) {
    if (data < (*(int*) limit)) {
        (*(int*) accum) *= data;
        std::cout << std::endl << "Accumulated value: " << (*(int*) accum);
    } else {
        (*(int*) accum) *= 1;
    }
}

template<>
void fold<double>(const double& data, const void* limit, void* accum) {
    if (data > (*(int*) limit)) {
        (*(double*) accum) += data;
        std::cout << std::endl << "Accumulated value: " << setprecision(20) << (*(double*) accum);
    } else {
        (*(double*) accum) += 0.0; 
    }
}

template<> 
void fold<string>(const string& data, const void* limit, void* accum) {
    if (data.length() <= (*(uint*) limit)) {
        (*(string*) accum) += data; 
        cout << endl << "Accumulated value: " << (*(string*) accum);
    } else {
        (*(string*) accum) += "";
    }
}

int getHashImplType() {
    int impltype = 0;
    while(impltype < 1 || impltype > 2) {
        cout << endl << "[1] Choose HashTable with closed addressing." << endl;
        cout << "[2] Choose HashTable with open addressing." << endl;
        cout << "Your choice: ";
        cin >> impltype;
    }
    return impltype;
}

int getHashSize() {
    int size = 0;
    while (cout << "Define structure dimension (size): " && !(cin >> size)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: non integer input, retry!" << endl;
    }
    return size; 
}

int getHashTypeData(){
    int typedata = 0;
    while(typedata < 1 || typedata > 3) {
        cout << endl << "[1] Use integer values." << endl;
        cout << "[2] Use double values." << endl;
        cout << "[3] Use string values." << endl;
        cout << "Your choice: ";
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
        cout << "Generated value: " << value << endl;
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
        cout << "Generated value: " << setprecision(20) << value << endl;
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
        cout << "Generated value: " << value << endl;
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

    while (cout << "Define what value you want to search: " && !(cin >> to_search)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: input not acceptable, retry!" << endl;
    }
    string output = container.Exists(to_search) ? ("Element is present!") : ("Element is not present!");
    cout << endl << output << endl;
}

template<typename Data>
void InsertElement(HashTable<Data>& hash) {
    Data elem;

    while (cout << endl << "Define what you want to insert: " && !(cin >> elem)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: input not acceptable, retry!" << endl;
    }
    string output = (hash.Insert(elem)) ? ("Element inserted correctly!") : ("Could not insert element!");
    cout << endl << output;
}

template<typename Data>
void RemoveElement(HashTable<Data>& hash) {
    Data elem;

    while (cout << endl << "Define what you want to remove: " && !(cin >> elem)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: input not acceptable, retry!" << endl;
    }
    string output = (hash.Remove(elem)) ? ("Element removed successfully!") : ("Could not remove element!");
    cout << endl << output;
}

int getNumber() {
    double n;
    while(cout << endl << "Enter the number by which to apply the function: " && !(cin >> n)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: input not acceptable, retry!" << endl;
    } 
    return (int) n;
}

template<typename Data>
void exampleTest(HashTable<Data>& hash, Data& first_element_typedata) {
    ushort choice = 0;
    cout << endl << "[0] Go back and try another example." << endl;
    cout << "[1] Visualize structure using Map."           << endl;
    cout << "[2] Try membership test."                     << endl;
    cout << "[3] Apply to structure its Fold function."    << endl;
    cout << "[4] Insert element."                          << endl;
    cout << "[5] Remove element."                          << endl;
    cout << "[6] Clear the structure."                     << endl;
    cout << "[7] Print size of the structure."             << endl;
    cout << "Your choice: ";
    cin >> choice;

    switch(choice) {
        case 0: {
            startTest();
            break;
        } case 1: {
            cout << endl << "(Map Pre-Order, Print) Here is the structure: " << endl;
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
                cout << "(Fold Pre-Order) Product for integers less than n:";
                hash.Fold(&fold<Data>, &n, &start);
            } else if (isDouble(first_element_typedata)) {
                double start = 0.0;
                cout << "(Fold Pre-Order) Sum for doubles greater than n:";
                hash.Fold(&fold<Data>, &n, &start);
            } else if (isString(first_element_typedata)) {
                string start = "";
                cout << "(Fold Pre-Order) Concatenation for strings with length less than or equal to n:";
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
            cout << endl << "HashTable is now empty!" << endl;
            exampleTest(hash, first_element_typedata);
            break;
        }
        case 7: {
            cout << endl << "(Number of elements) HashTable's size: " << hash.Size() << endl;
            exampleTest(hash, first_element_typedata);
            break;
        }
        default: 
            cout << "Error: not a valid input!" << endl;
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
        cout << "For demonstration purposes only, the structure size cannot be less than or equal to 0." << endl 
            << "(The HashTable is initialized via List)." << endl;
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