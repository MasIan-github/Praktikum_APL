#include <iostream>
#include <string>

using namespace std;

// Struktur untuk nampung nama item dan jumlah spare part yang berbeda tipe data
struct SparePart {
    string sparepart;
    int jumlah;
};

// Prototype fungsi-fungsi yang digunakan.
void displayMenu();
void createSparePart(SparePart inventory[], int& size);
void readSparePart(const SparePart inventory[], int size);
void updateSparePart(SparePart inventory[], int size);
void deleteSparePart(SparePart inventory[], int& size);
bool login();

// Fungsi utama
int main() {
    const int max_size = 250; // Konstanta ukuran maksimal array inventory. Bisa di ubah sesuka hati.
    SparePart inventory[max_size]; // Array yang nampung struktur SparePart
    int size = 0;

    if (!login()) {
        cout << "Login gagal. Silahkan coba lagi di lain waktu." << endl;
        return 0;
    }

    char choice; 

    // Perulangan do-while untuk ketentuan program poin pertama dan juga isi nya memenuhi poin ke tiga
    do {
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
                cout << "Keluar program ... ... ..." << endl;
                break;
            default:
                cout << "Pilihan tidak valid! Mohon coba lagi." << endl;
        }
    } while (choice != '5');

    return 0;
}

// fungsi nampilkan menu
void displayMenu() {
    cout << "\n|| Inventori Spare Part Laptop ||" << endl;
    cout << "1. Tambah Inventori" << endl;
    cout << "2. Lihat Inventori" << endl;
    cout << "3. Update Spare Part Laptop" << endl;
    cout << "4. Hapus Spare Part Laptop" << endl;
    cout << "5. Exit" << endl;
}

// fungsi Create
void createSparePart(SparePart inventory[], int& size) {
    if (size >= 100) {
        cout << "Inventori penuh! Mohon kosongkan beberapa item terlebih dahulu." << endl;
        return;
    }

    cout << "Nama Spare Part Laptop: ";
    getline(cin, inventory[size].sparepart);
    cout << "Jumlah : ";
    cin >> inventory[size].jumlah;
    size++;
}

// fungsi Read
void readSparePart(const SparePart inventory[], int size) {
    if (size == 0) {
        cout << "Inventori kosong ... ..." << endl;
        return;
    }

    cout << "\n--- Inventory ---" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "Item: " << inventory[i].sparepart << ", Jumlah: " << inventory[i].jumlah << endl;
    }
}

// fungsi Update, hanya bisa mengupdate jumlah item.
void updateSparePart(SparePart inventory[], int size) {
    if (size == 0) {
        cout << "Inventory kosong." << endl;
        return;
    }

    string searchspare;
    cout << "Masukkan nama item yang ingin update: ";
    getline(cin, searchspare);

    for (int i = 0; i < size; ++i) {
        if (inventory[i].sparepart == searchspare) {
            cout << "Masukan jumlah baru: ";
            cin >> inventory[i].jumlah;
            cout << "Jumlah item "<< searchspare << " berhasil di update!" << endl;
            return;
        }
    }

    cout << "Item tidak ditemukan." << endl;
}

// fungsi Delete
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
// keempat fungsi diatas untuk memenuhi ketentuan program pin keempat


// fungsi dan validasi Login. User & Pass menggunakan nama dan nim saya.
// fungsi ini juga untuk memenuhi ketentuan program poin kedua.
bool login() {
    string user = "ChristianFarrel";
    string pass = "2309106032";
    string input_username;
    string input_password;
    int counter = 3;

    cout << "Welcome!" << endl;
    cout << "|| Login Page ||" << endl;

    while (counter > 0) {
        cout << "Enter user: ";
        cin >> input_username;
        cout << "Enter password: ";
        cin >> input_password;

        if (input_username == user && input_password == pass) {
            cout << "Login berhasil" << endl;
            return true;
        } else {
            counter--;
            cout << "Login gagal. Tersisa " << counter << " Kesempatan lagi." << endl;
        }
    }

    if (counter == 0){
        cout << "Kesempatan telah habis, silahkan coba lagi di lain waktu. " << endl;
        return false;
    }
}

