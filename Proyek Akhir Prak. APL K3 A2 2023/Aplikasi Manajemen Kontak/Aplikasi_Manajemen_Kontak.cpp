#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <limits>
#include <conio.h>
#include <windows.h>

using namespace std;


// struct tipe data untuk menyimpan data kontak
struct kontak {
    string nama;
    string nomortelepon;
    string pekerjaan;
    string tag;
};

// prosedur untuk mengurutkan kontak dengan insertion sort
void insertionSort(kontak kt[], int count) {
    for (int i = 1; i < count; i++) {
        kontak key = kt[i];
        int j = i - 1;

        while (j >= 0 && kt[j].nama > key.nama) {
            kt[j + 1] = kt[j];
            j = j - 1;
        }
        kt[j + 1] = key;
    }
}

// sequential search untuk mencari kontak
int searchKontak(const kontak kt[], int count, const string& query) {
    for (int i = 0; i < count; i++) {
        if (kt[i].nama == query || kt[i].nomortelepon == query) {
            cout << "Kontak ditemukan: \n" << endl;
            cout << "Nama : " << kt[i].nama <<endl;
            cout << "Nomor Telepon : " << kt[i].nomortelepon <<endl;
            cout << "Pekerjaan : " << kt[i].pekerjaan <<endl;
            cout << "tag : " << kt[i].tag <<"\n"<<endl;
            return i;  // balikan i kalau ketemu
        }
    }
    cout << "Kontak tidak ditemukan." << endl;
    return -1; // kalau tidak ketemu
}

// prosedur untuk mengatur warna teks bawaan c++ (sebelumnya graphics.h)
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// buat struktur output menu program
void tampilanMenu(const string menuItems[], int itemCount, int currentSelection) {
    if (itemCount == 3) {
        setColor(10);
        cout << " ======| Selamat datang! |======\n" << endl;
        setColor(7);
    } 
    if (itemCount == 6){
        setColor(10);
        cout << " ======| Menu utama |======\n" << endl;
        setColor(7);
    }

    if (itemCount == 5){
         setColor(10);
        cout << " ======| Edit Kontak |====== \n" << endl;
        setColor(7);

    }

    for (int i = 0; i < itemCount; i++) {
        if (i == currentSelection) {
            setColor(2); // ijo wak
            cout << ">> " << menuItems[i] << " <<" << endl;
        } else {
            setColor(7); // default
            cout << menuItems[i] << endl;
        }
    }
        setColor(8);
        cout << "\n~~~~~ Manajemen Kontak by A2 - 5 ~~~~~\n" << endl;
        setColor(7);
    
}

// fungsi yang menangani pergantian pilihan berdasarkan keyboard key press (arrow up, down & enter)
int pilihanMenu(const string menuItems[], int itemCount, kontak kt[], int count) {
    int currentSelection = 0;
    char key;
    while (true) {
        system("cls");


        if (itemCount == 2) { // akali tampilkanKontak supaya opsi Yes No nya bisa navigasi pake arrow keys
            insertionSort(kt, count);
            setColor(10);
            cout << " ======| Daftar Kontak |======\n" << endl;
            setColor(2);
            cout << left << setw(20) << "Nama" << setw(20) << "Nomor Telepon" << setw(20) << "Pekerjaan" << setw(20) << "tag" << endl;
            cout << string(80, '-') << endl; 
            for (int i = 0; i < count; i++) {
                cout << left << setw(20) << kt[i].nama << setw(20) << kt[i].nomortelepon << setw(20) << kt[i].pekerjaan << setw(20) << kt[i].tag << endl;
            }
            setColor(7);
            cout << "\nApakah Anda ingin melakukan searching kontak?" << endl;
        }
        

        tampilanMenu(menuItems, itemCount, currentSelection);
        key = _getch(); // <conio> untuk mengambil input keyboard press

        if (key == 72) { // asciii code untuk arrow up
            currentSelection = (currentSelection - 1 + itemCount) % itemCount;
        } else if (key == 80) { // ascii code untuk arrow down
            currentSelection = (currentSelection + 1) % itemCount;
        } else if (key == 13) { // ascii code untuk Enter
            return currentSelection;
        }
    }
}

// fungsi error handling untuk memeriksa apakah string kosong atau hanya berisi spasi
bool kosong_space(const string& str) {
    return str.find_first_not_of(' ') == string::npos;
}

// fungsi error handling untuk special char 
bool char_spesial(const string& str) {
    for (char c : str) {
        if (!isalnum(c)) { // alphanumerical (huruf & angka only)
            return true;
        }
    }
    return false;
}

// prosedur registrasi user baru
void regis(const string& filename) {
    ofstream outFile("users.txt", ios_base::app); // mode append
    if (!outFile.is_open()) { // cek stream apakah file terbuka
        setColor(14);
        cerr << "Gagal membuka file untuk menulis." << endl;
        setColor(7);
        return;
    }

    string username, password;
    bool valid = false;
    int attemptCounter = 0;
    const int maxAttempts = 3; // 3 kesempatan login

    while (!valid) {
        if (attemptCounter >= maxAttempts) {
            setColor(14);
            cout << "Anda telah gagal registrasi 3 kali. Kembali ke menu login/registrasi.\n";
            setColor(7);
            outFile.close();
            return;
        }
        setColor(2);
        system("pause & cls");
        setColor(10);
        cout << " ======| Registrasi Akun Baru |======\n" << endl ;
        setColor(7);
        cout << "Masukkan username baru (min 3 karakter): ";
        getline(cin, username);
        if (username.length() < 3 || kosong_space(username) || char_spesial(username)) {
            setColor(14);
            cout << "Username harus minimal 3 karakter dan tidak boleh kosong atau hanya spasi atau mengandung karakter spesial.\n";
            setColor(7);
            attemptCounter++;
            continue;
        }

        ifstream inFile("users.txt");
        if (!inFile.is_open()) {
            setColor(14);
            cerr << "Gagal membuka file untuk membaca." << endl; // char error
            setColor(7);
            outFile.close();
            return;
        }

        string fileUser, filePassword;
        bool userExists = false;
        while (inFile >> fileUser >> filePassword) {
            if (fileUser == username) {
                userExists = true;
                break;
            }
        }
        inFile.close();

        if (userExists) {
            cout << "Username sudah digunakan. Silakan pilih username lain.\n";
            attemptCounter++;
            continue;
        }

        cout << "Masukkan password baru (min 8 karakter): ";
        getline(cin, password);
        setColor(8);
        cout << "\n~~~~~ Manajemen Kontak by A2 - 5 ~~~~~\n" << endl;
        setColor(7);
        if (password.length() < 8 || kosong_space(password)) {
            setColor(14);
            cout << "Password harus minimal 8 karakter dan tidak boleh kosong atau hanya spasi.\n";
            setColor(7);
            attemptCounter++;
            continue;
        }

        valid = true;
    }

    outFile << username << " " << password << endl;
    outFile.close();

    cout << "Registrasi berhasil!" << endl;
}

// low all untuk login
string kelower(const string& str) {
    string lowerStr;
    lowerStr.reserve(str.size()); 
    for (char c : str) {
        lowerStr += tolower(c);
    }
    return lowerStr;
}

// fungsi untuk login
bool login(const string& username, const string& password, const string& filename) {
    ifstream inFile("users.txt"); // buka file users.txt
    if (!inFile.is_open()) { // cek berhasil atau tidak
        cerr << "Gagal membuka file data user." << endl;
        return false;
    }
    string fileUser, filePassword;
    string lowUser = kelower(username);
    while (inFile >> fileUser >> filePassword) {
        string lowFileUser = kelower(fileUser);
        if (lowFileUser == lowUser && filePassword == password) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

// prosedur untuk memuat kontak dari file
void loadKontak(kontak kt[], int& count, const string& filename) {
    ifstream inFile(filename); // buka file username + .txt
    if (!inFile.is_open()) { // cek keberhasilan
        setColor(14);
        cerr << "Gagal membuka file kontak." << endl;
        setColor(7);
        return;
    }

    string line;
    count = 0;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string nama, nomortelepon, pekerjaan, tag;


        if (getline(ss, nama, ',') &&
            getline(ss, nomortelepon, ',') &&
            getline(ss, pekerjaan, ',') &&
            getline(ss, tag)) {
            
            if (count < 1000) {
                kt[count].nama = nama;
                kt[count].nomortelepon = nomortelepon;
                kt[count].pekerjaan = pekerjaan;
                kt[count].tag = tag;
                count++;
            }
        }
    }
    inFile.close();
}

// prosedur untuk menyimpan kontak ke file
void simpanKontak(const kontak kt[], int count, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        setColor(14);
        cerr << "Gagal membuka file untuk disimpan." << endl;
        setColor(7);
        return;
    }

    for (int i = 0; i < count; i++) {
        outFile << kt[i].nama << "," << kt[i].nomortelepon << "," << kt[i].pekerjaan << "," << kt[i].tag << endl;
    }
    outFile.close();
}

// prosedur untuk menambahkan kontak baru
void tambahKontak(kontak kt[], int& count, const string& filename) {
    if (count < 1000) {
        string nama, nomortelepon, pekerjaan, tag;
        int abnormalnam = 0;
        setColor(2);
        system("pause & cls");
        setColor(13);
        cout << " ======| Tambah Kontak |====== \n" << endl;
        setColor(7);
        cout << "Masukkan nama kontak: ";
        getline(cin, nama);
        while (kosong_space(nama)) {
            setColor(14);
            cout << "Nama tidak boleh kosong atau hanya spasi!" << endl;
            setColor(7);
            abnormalnam++;
            cout << "Masukkan nama kontak: ";
            getline(cin, nama);
            if (abnormalnam >= 12){
                setColor(14);
                cout << "Terdeteksi input yang tidak wajar secara berulang-ulang, kembali ke menu . . . .\n";
                setColor(7);
                return;
            }
        }

        bool validNumber = false;
        int abnormalnum = 0; // mencegah inputan ga guna yang terus-menerus. contoh tombol space yang ngestuck saat mengisi kontak
        while (!validNumber) {
            cout << "Masukkan nomor telepon: ";
            getline(cin, nomortelepon);
            if (abnormalnum >= 12 ) {
                setColor(14);
                cout << "Terdeteksi input yang tidak wajar secara berulang-ulang, kembali ke menu . . . .\n";
                setColor(7);
                return;
            }
            if (nomortelepon.length() >= 11 && nomortelepon.find_first_not_of("0123456789") == string::npos) {
                validNumber = true;
            } else {
                setColor(14);
                cout << "Nomor telepon harus minimal 11 karakter dan hanya berisi angka. Silakan coba lagi.\n";
                setColor(7);
                abnormalnum++;
            }
            

        }

        cout << "Masukkan pekerjaan (biarkan kosong jika tidak ada): ";
        getline(cin, pekerjaan);
        if (kosong_space(pekerjaan)) {
            pekerjaan = " - ";
        } else {pekerjaan = "[ " + pekerjaan + " ]";}


        cout << "Masukkan tag (biarkan kosong jika tidak ada): ";
        getline(cin, tag);
        if (kosong_space(tag)) {
            tag = " - ";
        } else { tag = "#" + tag;
            }

        kt[count].nama = nama;
        kt[count].nomortelepon = nomortelepon;
        kt[count].pekerjaan = pekerjaan;
        kt[count].tag = tag;

        ofstream outFile(filename, ios_base::app); // mode app (append) untuk menambahkan ke file yang sudah ada
        if (outFile.is_open()) {
            outFile << kt[count].nama << "," << kt[count].nomortelepon << "," << kt[count].pekerjaan << "," << kt[count].tag << endl;
            outFile.close();
            cout << "Kontak berhasil ditambahkan dan disimpan!" << endl;
            setColor(8);
            cout << "\n~~~~~ Manajemen Kontak by A2 - 5 ~~~~~\n" << endl;
            setColor(7);
        } else {
            setColor(14);
            cerr << "Gagal membuka file untuk disimpan." << endl;
            setColor(7);
        }
        count++;
    } else {
        setColor(14);
        cout << "Maaf, kapasitas kontak sudah penuh." << endl;
        setColor(7);
    }
}

// prosedur untuk menampilkan semua kontak
void tampilkanKontak(kontak kt[], int count, const string& filename) {
    if (count == 0) {
        setColor(14);
        cout << "Tidak ada kontak yang tersimpan." << endl;
        setColor(7);
        return;
    }
    
    ifstream inFile(filename); // buka file kontak
    if (!inFile.is_open()) { // cek keberhasilan membuka file
        setColor(14);
        cerr << "Gagal membuka file kontak." << endl;
        setColor(7);
        return;
    }

    string line;
    int existingContacts = 0; // cek kalau file user + .txt nya ada isinya atau tidak
    while (getline(inFile, line)) {
        existingContacts++;
    }
    inFile.close();

    if (existingContacts == 0) {
        setColor(14);
        cout << "Tidak ada kontak yang tersimpan." << endl;
        setColor(7);
        return;
    }

    const string menuItems[] = {
        "Yes",
        "No"
    };
    int itemCount = sizeof(menuItems) / sizeof(menuItems[0]);

    while (true) {
        int selectedOption = pilihanMenu(menuItems, itemCount, kt, count);

        if (selectedOption == 0) {
            string query;
            cout << "\nMasukkan nama atau nomor telepon yang ingin dicari: ";
            getline(cin, query);
            searchKontak(kt, count, query);
            break;
        } else if (selectedOption == 1) {
            break;
        }
    }
}

// prosedur untuk mengubah kontak
void ubahKontak(kontak kt[], int count, const string& filename) {
    if (count == 0) {
        setColor(14);
        cout << "Tidak ada kontak yang tersimpan." << endl;
        setColor(7);
        return;
    }
    
    ifstream inFile(filename); // buka file kontak
    if (!inFile.is_open()) { // cek keberhasilan membuka file
        setColor(14);
        cerr << "Gagal membuka file kontak." << endl;
        setColor(7);
        return;
    }

    string line;
    int existingContacts = 0;
    while (getline(inFile, line)) {
        existingContacts++;
    }
    inFile.close();

    if (existingContacts == 0) {
        setColor(14);
        cout << "Tidak ada kontak yang tersimpan." << endl;
        setColor(7);
        return;
    }

    string query;
    
    cout << "Masukkan nama atau nomor telepon yang ingin diedit: ";
    getline(cin, query);
    int index = searchKontak(kt, count, query);
    setColor(2);
    system("pause & cls");
    setColor(13);
    cout << " ======| Edit Kontak |====== \n" << endl;
    setColor(7);
    if (index != -1) {
        bool done = false;
        while (!done) {
            const string menuItems[] = {
                "1. Nama",
                "2. Nomor Telepon",
                "3. Pekerjaan",
                "4. Tag",
                "5. Selesai"
            };
            int itemCount = sizeof(menuItems) / sizeof(menuItems[0]);
            int selectedOption = pilihanMenu(menuItems, itemCount, kt, count);

            switch (selectedOption) {
                case 0: {
                    string nama;
                    cout << "Masukkan nama baru: ";
                    getline(cin, nama);
                    while (kosong_space(nama)) {
                        setColor(14);
                        cout << "Nama tidak boleh kosong atau hanya spasi. Masukkan nama baru: ";
                        setColor(7);
                        getline(cin, nama);
                    }
                    kt[index].nama = nama;
                    break;
                }
                case 1: {
                    string nomortelepon;
                    bool validNumber = false;
                    while (!validNumber) {
                        cout << "Masukkan nomor telepon baru: ";
                        getline(cin, nomortelepon); // error handling: input length harus >= 11 dan harus angka
                        if (nomortelepon.length() >= 11 && nomortelepon.find_first_not_of("0123456789") == string::npos) {
                            validNumber = true;
                        } else {
                            setColor(14);
                            cout << "Nomor telepon harus minimal 11 karakter dan hanya berisi angka. Silakan coba lagi.\n";
                            setColor(7);
                        }
                    }
                    kt[index].nomortelepon = nomortelepon;
                    break;
                }
                case 2: {
                    string pekerjaan;
                    cout << "Masukkan pekerjaan baru: ";
                    getline(cin, pekerjaan);
                    if (kosong_space(pekerjaan)) {
                        pekerjaan = " - ";
                    }
                    kt[index].pekerjaan = pekerjaan;
                    break;
                }
                case 3: {
                    string tag;
                    cout << "Masukkan tag baru: ";
                    getline(cin, tag);
                    if (kosong_space(tag)) {
                        tag = " - ";
                    } else {
                        tag = "#" + tag;
                    }
                    kt[index].tag = tag;
                    break;
                }
                case 4:
                    done = true;
                    break;
            }
        }
        simpanKontak(kt, count, filename);
        cout << "Kontak berhasil diubah!" << endl;
    }
}

// prosedur untuk menghapus kontak
void hapusKontak(kontak kt[], int& count, const string& filename) {
    if (count == 0) {
        setColor(14);
        cout << "Tidak ada kontak yang tersimpan." << endl;
        setColor(7);
        return;
    }
    
    ifstream inFile(filename); // buka file kontak
    if (!inFile.is_open()) { // cek keberhasilan membuka file
        setColor(14);
        cerr << "Gagal membuka file kontak." << endl;
        setColor(7);
        return;
    }

    string line;
    int existingContacts = 0;
    while (getline(inFile, line)) {
        existingContacts++;
    }
    inFile.close();

    string query;
    cout << "Masukkan nama atau nomor telepon yang ingin dihapus: ";
    getline(cin, query);
    int index = searchKontak(kt, count, query);
    if (index != -1) { // hapus satu line yang berkaitan dengan nama/nomor telepon, lalu line berikutnya -1
        for (int i = index; i < count - 1; i++) {
            kt[i] = kt[i + 1];
        }
        count--;
        simpanKontak(kt, count, filename);
        cout << "Kontak berhasil dihapus!" << endl;
    }
}

void login_regis();

// prosedur untuk membuat menu utama
void menu_utama(kontak kt[], int& count, const string& filename) {
    const string menuItems[] = {
        "1. Tambah Kontak",
        "2. Tampilkan Kontak",
        "3. Ubah Kontak",
        "4. Hapus Kontak",
        "5. Tentang Manajemen Kontak",
        "6. Keluar" 

    };
    int itemCount = sizeof(menuItems) / sizeof(menuItems[0]);

    while (true) {
        int selectedOption = pilihanMenu(menuItems, itemCount, kt, count);
        switch (selectedOption) {
            case 0:
                tambahKontak(kt, count, filename);
                break;
            case 1:
                tampilkanKontak(kt, count, filename);
                break;
            case 2:
                ubahKontak(kt, count, filename);
                break;
            case 3:
                hapusKontak(kt, count, filename);
                break;
            case 4:
                cout << "" <<endl;
                system("cls");
                setColor(13);
                cout << "\n===[ Deskripsi ]===\n" << endl;
                cout << "Manajemen Kontak by @A2 - 5, Demosa, Aiman & Farrel  " << endl;
                cout << "                                                     " << endl;
                cout << "       Program ini adalah aplikasi manajemen kontak  " << endl;
                cout << "   yang   memungkinkan  pengguna  untuk   melakukan  " << endl;
                cout << "   registrasi, login, dan  mengelola  daftar kontak  " << endl;
                cout << "   dengan mudah.\n                                   " << endl;
                cout << "                                Samarinda - 22/04/24 \n\n" << endl;
                setColor(2);
                break;
            case 5:
                login_regis();
        }
        system("pause");
    }
}

// prosedur untuk login atau registrasi
void login_regis() {
    const string menuItems[] = {
        "1. Login",
        "2. Registrasi",
        "3. Keluar"
    };
    int itemCount = sizeof(menuItems) / sizeof(menuItems[0]); // basjs selection

    while (true) {
        int selectedOption = pilihanMenu(menuItems, itemCount, nullptr, 0);
        switch (selectedOption) {
            case 0: {
                string username, password;
                int loginAttempts = 0;
                const int maxattempts = 3;

                while (loginAttempts < maxattempts){
                system("Pause & cls");
                setColor(2);
                cout << " ======| Halaman Login |======\n" << endl;
                setColor(7);
                cout << "Masukkan username: ";
                getline(cin, username);
                cout << "Masukkan password: ";
                getline(cin, password);
                setColor(8);
                cout << "\n~~~~~ Manajemen Kontak by A2 - 5 ~~~~~\n" << endl;
                setColor(7);

                if (login(username, password, "users.txt")) {
                    cout << "Login berhasil!" << endl;
                    system("pause & cls");
                    string contactsFilename = username + ".txt";
                    kontak kt[1000];
                    int count;
                    loadKontak(kt, count, contactsFilename);
                    menu_utama(kt, count, contactsFilename);
                } else {
                    setColor(14);
                    cout << "Username atau password salah. Silakan coba lagi." << endl;
                    setColor(7);
                    loginAttempts++;
                if (loginAttempts >= 3){
                    setColor(14);
                    cout << "terlalu banyak kesalahan. kembali ke menu awal . . . .\n" << endl;
                    setColor(7);
                }
                }
            }
        }
                break;
            case 1:
                regis("users.txt");
                break;
            case 2:
            setColor(13);
                cout << "Terima kasih telah menggunakan aplikasi ini." << endl;
                system("pause");
                setColor(7);
                exit(0);
                
        }
    
        system("pause & cls");
    }

}

// fungsi utama
int main() {
    login_regis();
    return 0;
}
