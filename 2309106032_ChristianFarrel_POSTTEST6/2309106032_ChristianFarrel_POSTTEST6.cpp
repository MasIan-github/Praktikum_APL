#include <iostream>
#include <string>
#include <cstdlib> // system("PAUSE") and system("cls")
using namespace std;

// Struktur untuk nampung nama item dan jumlah spare part yang berbeda tipe data
struct Quality {
    string designation; // rating tertulis kualitas sparepart.
    int rate; // rating numerik kualitas sparepart (1-10)
};

struct SparePart {
    string sparepart;
    int jumlah;
    Quality quality; // Struct Quality berada di dalam struct SparePart, jadinya nested struct
};

// Prototype fungsi-fungsi yang digunakan.
void displayMenu();
void createSparePart(SparePart inventory[], int& size);
void readSparePart(const SparePart inventory[], int size, int sortMethod);
void updateSparePart(SparePart inventory[], int size);
void deleteSparePart(SparePart inventory[], int& size);
void searchAscending(const SparePart inventory[], int size);
void searchDescending(const SparePart inventory[], int size);
void recursivemenu(SparePart inventory[], int size);
void handlerecursive(SparePart inventory[], int size);
string goodbye();
bool login();

// Fungsi utama
int main() {
    const int max_size = 250; // Konstanta ukuran maksimal array inventory. Bisa di ubah sesuka hati.
    SparePart inventory[max_size]; // Array yang nampung struktur SparePart
    int size = 0;

    if (!login()) { // memastikan bahwa return dari login harus True, jika tidak maka program berhenti.
        cout << "Login gagal. Silahkan coba lagi di lain waktu." << endl; 
        return 0; 
    }
    handlerecursive(inventory, size);

    return 0;
}

// prosedur untuk menampilkan menu yang ada
void displayMenu() {
    cout << "\n|| Inventori Spare Part Laptop ||" << endl;
    cout << "1. Tambah Inventori" << endl;
    cout << "2. Lihat Inventori" << endl;
    cout << "3. Update Spare Part Laptop" << endl;
    cout << "4. Hapus Spare Part Laptop" << endl;
    cout << "5. Exit" << endl;
}

void recursivemenu(SparePart inventory[], int size) { // rekursifitas
    char choice;

    displayMenu();
    cout << "Pilihan: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case '1':
            createSparePart(inventory, size);
            break;
        case '2':
            int sortMethod;
            cout << "Pilih cara penampilan:" << endl;
            cout << "0. Tampilkan tanpa sorting" << endl;
            cout << "1. Sorting berdasarkan huruf (descending)" << endl;
            cout << "2. Sorting berdasarkan angka (ascending)" << endl;
            cout << "3. Sorting berdasarkan angka (descending)" << endl;
            cout << "Pilihan: ";
            cin >> sortMethod;
            readSparePart(inventory, size, sortMethod);
            break;
        case '3':
            updateSparePart(inventory, size);
            break;
        case '4':
            deleteSparePart(inventory, size);
            break;
        case '5':
            cout << goodbye();
            return; 
        default:
            cout << "Pilihan tidak valid! Mohon coba lagi." << endl;
    }
    system("PAUSE");
    system("cls");
    recursivemenu(inventory, size);
}

// prosedur untuk Create spare part baru untuk dimasukan ke array
void createSparePart(SparePart inventory[], int& size) {
    if (size >= 100) {
        cout << "Inventori penuh! Mohon kosongkan beberapa space terlebih dahulu." << endl;
        return;
    }

    cout << "Nama Spare Part Laptop: ";
    getline(cin, inventory[size].sparepart);
    cout << "Jumlah : ";
    cin >> inventory[size].jumlah;
    cout << "Designation: ";
    cin.ignore();
    getline(cin, inventory[size].quality.designation);
    cout << "Rate: ";
    cin >> inventory[size].quality.rate;
    size++;
}

// prosedur untuk Read isi array
void readSparePart(const SparePart inventory[], int size, int sortMethod) {
    if (size == 0) {
        cout << "Inventori kosong ... ..." << endl;
        return;
    }

    cout << "\n--- Inventory ---" << endl;

    // Declare temp array within the scope
    SparePart temp[250]; // Assuming max_size is 250

    // copy array buat sorting agar tidak berdampak ke array struct aslinya
    for (int i = 0; i < size; ++i) {
        temp[i] = inventory[i];
    }

    // switchcase buat sorting
    switch (sortMethod) {
        case 0: // rasa ori
            for (int i = 0; i < size; ++i) {
                cout << "Item: " << inventory[i].sparepart << ", Jumlah: " << inventory[i].jumlah 
                    << ", Designation: " << inventory[i].quality.designation 
                    << ", Rate: " << inventory[i].quality.rate << endl;
    }
        case 1: // rasa insert simplified
            for (int i = 1; i < size; ++i) {
                SparePart key = temp[i];
                int j = i - 1;
                while (j >= 0 && temp[j].sparepart < key.sparepart) {
                    temp[j + 1] = temp[j];
                    --j;
                }
                temp[j + 1] = key;
            }
            break;

        case 2: // rasa bubble
            for (int i = 0; i < size - 1; ++i) {
                for (int j = i + 1; j < size; ++j) {
                    if (temp[i].jumlah > temp[j].jumlah) {
                        swap(temp[i], temp[j]);
                    }
                }
            }
            break;
        case 3: // rasa selection
            for (int i = 0; i < size - 1; ++i) {
                int maxIndex = i;
                for (int j = i + 1; j < size; ++j) {
                    if (temp[j].jumlah > temp[maxIndex].jumlah) {
                        maxIndex = j;
                    }
                }
                if (maxIndex != i) {
                    swap(temp[i], temp[maxIndex]);
                }
            }
            break;

        default:
            cout << "Invalid sort method." << endl;
            return;
    }

    
    for (int i = 0; i < size; ++i) {
        cout << "Item: " << temp[i].sparepart << ", Jumlah: " << temp[i].jumlah 
             << ", Designation: " << temp[i].quality.designation 
             << ", Rate: " << temp[i].quality.rate << endl;
    }

    // search wak
    searchAscending(temp, size);
    searchDescending(temp, size);
}

// prosedur untuk Update
void updateSparePart(SparePart inventory[], int size) {
    if (size == 0) {
        cout << "Inventory kosong." << endl;
        return;
    }

    string searchspare;
    cout << "Masukkan nama item yang ingin update: ";
    getline(cin, searchspare);

    for (int i = 0; i < size; ++i) {
        if (inventory[i].sparepart == searchspare) { // mencari nama sparepart yang di input di dalam array
            cout << "Masukan jumlah baru: ";
            cin >> inventory[i].jumlah;
            cout << "Jumlah item "<< searchspare << " berhasil di update!" << endl;
            return;
        }
    }

    cout << "Item tidak ditemukan." << endl;
}

// prosedur untuk Delete
void deleteSparePart(SparePart inventory[], int& size) {
    if (size == 0) {
        cout << "Inventori kosong ... ..." << endl;
        return;
    }

    string searchspare;
    cout << "Masukkan nama item yang ingin di hapus: ";
    getline(cin, searchspare);

    for (int i = 0; i < size; ++i) {
        if (inventory[i].sparepart == searchspare) {
            for (int j = i; j < size - 1; ++j) {
                inventory[j] = inventory[j + 1];
            }
            size--;
            cout << "Item "<< searchspare <<" berhasil dihapus." << endl;
            return;
        }
    }

    cout << "Item tidak ditemukan." << endl;
}

// prsd untuk mencari item pada data terurut secara ascending
void searchAscending(const SparePart inventory[], int size) {
    string searchItem;
    cout << "Search secara ascending ..." << endl;
    cout << "Enter nama item: ";
    cin.ignore();
    getline(cin, searchItem);

    int low = 0;
    int high = size - 1;
    int found = -1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (inventory[mid].sparepart == searchItem) {
            found = mid;
            break;
        } else if (inventory[mid].sparepart < searchItem) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (found != -1) {
        cout << "Item "<< searchItem << "ditemukan di indeks ke-"<<found << " (data tersortir secara ascending)." << endl;
    } else {
        cout << "Item tidak tidemukan." << endl;
    }
}

// prsd untuk mencari item pada data terurut secara descending
void searchDescending(const SparePart inventory[], int size) {
    string searchItem;
    cout << "Search secara descending  ..." << endl;
    cout << "Enter nama item: ";
    getline(cin, searchItem);

    int found = -1;
    for (int i = 0; i < size; ++i) {
        if (inventory[i].sparepart == searchItem) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        cout << "Item '" << searchItem << "' ditemukan pada index ke-" << found << " (data tersortir secara descending." << endl;
    } else {
        cout << "Item tidak ditemukan." << endl;
    }
}


// fungsi login
bool login() {
    string user = "ChristianFarrel";
    string pass = "2309106032";
    string input_username;
    string input_password;
    int counter = 3;
    int *counterPtr = &counter;
   

    while (*counterPtr > 0) {
        cout << "Welcome!" << endl;
        cout << "|| Login Page ||" << endl;
        cout << "Enter user: ";
        cin >> input_username;
        cout << "Enter password: ";
        cin >> input_password;

        if (input_username == user && input_password == pass) {
            cout << "Login berhasil" << endl;
            system ("PAUSE");
            system ("cls");
            return true;
        } else {
            (*counterPtr)--;
            cout << "Login gagal. Tersisa " << *counterPtr << " Kesempatan lagi." << endl;
            system ("PAUSE");
            system ("cls");
        }
    }

    if (*counterPtr == 0){
        cout << "Kesempatan telah habis, silahkan coba lagi di lain waktu. " << endl;
        return false;
    }
}

// starter rekursifitas di dalam fungsi utama
void handlerecursive(SparePart inventory[], int size) {
    recursivemenu(inventory, size);
}

string goodbye(){
    string bye;
    bye = "Keluar Program ... ...";
    return bye;
}
