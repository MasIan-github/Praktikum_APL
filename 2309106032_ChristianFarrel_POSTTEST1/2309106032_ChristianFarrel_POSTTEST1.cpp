#include <iostream>
#include <string>
#include <limits>

using namespace std;

void ind(float idr) {
    float usd = idr * 0.000064;
    float euro = idr * 0.00006;
    float yen = idr * 0.0096;
    cout << idr << " IDR setara dengan :" << endl;
    cout << usd << " USD." << endl;
    cout << euro << " Euro." << endl;
    cout << yen << " Yen." << endl;
}

void us(float usd) {
    float idr = usd * 15729;
    float euro = usd * 0.92;
    float yen = usd * 150.54;
    cout << usd << " USD setara dengan :" << endl;
    cout << idr << " IDR." << endl;
    cout << euro << " Euro." << endl;
    cout << yen << " Yen." << endl;
}

void eur(float euro) {
    float usd = euro * 1.09;
    float idr = euro * 17089.79;
    float yen = euro * 163.46;
    cout << euro << " Euro setara dengan :" << endl;
    cout << usd << " USD." << endl;
    cout << idr << " IDR." << endl;
    cout << yen << " Yen." << endl;
}

void jap(float yen) {
    float usd = yen * 0.0066;
    float idr  = yen * 104.56;
    float euro = yen * 0.0061;
    cout << yen << " Yen setara dengan :" << endl;
    cout << usd << " USD." << endl;
    cout << idr << " IDR." << endl;
    cout << euro << " Euro." << endl;
}

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


int main() {
    if (!login()) {
        return 0;
    }

    int choice;
    float idr;
    float usd;
    float euro;
    float yen;

    do {
        cout << "||Money Conversion||:" << endl;
        cout << "Available Currencies : " << endl;
        cout << "1.  IDR" << endl;
        cout << "2.  USD" << endl;
        cout << "3.  EURO" << endl;
        cout << "4.  YEN" << endl;
        cout << "5.  Show all" << endl;
        cout << "6.  Exit" << endl;
        cout << "Pilihan : ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 6) {
            cout << "Pilihan tidak valid, mohon pilih kembali." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // mencegah inputan asal. i.e 1d, 3p dst.
            cout << "Pilihan : ";
            cin >> choice;
        }

        switch (choice) {
            case 1:
                cout << "Masukkan jumlah IDR: ";
                cin >> idr;
                ind(idr);
                break;
            case 2:
                cout << "Masukkan jumlah USD: ";
                cin >> usd;
                us(usd);
                break;
            case 3:
                cout << "Masukkan jumlah EURO: ";
                cin >> euro;
                eur(euro);
                break;
            case 4:
                cout << "Masukkan jumlah YEN: ";
                cin >> yen;
                jap(yen);
                break;
            case 5:
                cout << "Masukkan jumlah IDR: ";
                cin >> idr;
                ind(idr);
                cout << "Masukkan jumlah USD: ";
                cin >> usd;
                us(usd);
                cout << "Masukkan jumlah EURO: ";
                cin >> euro;
                eur(euro);
                cout << "Masukkan jumlah YEN: ";
                cin >> yen;
                jap(yen);
                break;
            case 6:
                cout << "Exiting program . . ." << endl;
                break;
            default:
                cout << "Input tidak valid, mohon input dari 1 sampai 6." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
