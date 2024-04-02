#include <iostream>
#include <string>
#include <stdlib.h>
#include <exception>
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
void readSparePart(const SparePart inventory[], int size);
void updateSparePart(SparePart inventory[], int size);
void deleteSparePart(SparePart inventory[], int& size);
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
            readSparePart(inventory, size);
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
void readSparePart(const SparePart inventory[], int size) {
    if (size == 0) {
        cout << "Inventori kosong ... ..." << endl;
        return;
    }

    cout << "\n--- Inventory ---" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "Item: " << inventory[i].sparepart << ", Jumlah: " << inventory[i].jumlah 
             << ", Designation: " << inventory[i].quality.designation 
             << ", Rate: " << inventory[i].quality.rate << endl;
    }
}

// prosedur untuk Update, hanya bisa mengupdate jumlah item.
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