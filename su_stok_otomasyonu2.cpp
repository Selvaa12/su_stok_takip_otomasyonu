#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <conio.h>
#include<locale.h>


using namespace std;

	

struct SuStogu {
    char stokAdi[80];
    int stokMiktari;
    char stokID[5];
};

void StokEkle();
void StokListeleme();
void StokArama();
void StokSil();
void StokDuzenle();
SuStogu stok;

int main() 
{
		setlocale(LC_ALL,"Turkish");
    char anamenu;

    do {
        system("cls");
        cout << "|-------Ho�geldiniz------|" << endl;
        cout << "|      Se�im Yap�n�z     |" << endl;
        cout << "|   1- Stok Ekleme       |" << endl;
        cout << "|   2- Stok Listeleme    |" << endl;
        cout << "|     3- Stok Arama      |" << endl;
        cout << "|    4- Stok Sil         |" << endl;
        cout << "|    5- Stok D�zenle     |" << endl;
        cout << "|------------------------|" << endl;
        char secim;
        cin >> secim;

        switch (secim) {
            case '1':
                StokEkle();
                break;
            case '2':
                StokListeleme();
                break;
            case '3':
                StokArama();
                break;
            case '4':
                StokSil();
                break;
            case '5':
                StokDuzenle();
                break;
            default:
                cout << "Ge�ersiz se�im! L�tfen tekrar deneyiniz.\n";
        }

        cout << "Ana men�ye d�nmek i�in: a bas�n, ��kmak i�in: c" << endl;
        anamenu = getche();
    } while (anamenu == 'a' || anamenu == 'A');

    return 0;
}

void StokEkle() {
    ofstream yaz("stok.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do {
        cout << "Stok Ad� Giriniz: \n ";
        cin >> stok.stokAdi;
        cout << "Stok Miktar� Giriniz: \n ";
        cin >> stok.stokMiktari;
        cout << "Stok ID Giriniz: \n";
        cin >> stok.stokID;

        yaz.write((char*)&stok, sizeof(stok));
        adet++;

        cout << "Ba�ka kay�t eklemek ister misiniz (E/H)? ";
        secim = getche();
        cout << endl;
    } while (secim == 'e' || secim == 'E');

    cout << adet << " adet stok eklendi.\n";
    yaz.close();
}

void StokListeleme() {
    ifstream oku("stok.dat", ios::binary);
    if (!oku) {
        cout << "Dosya a��l�rken bir hata olu�tu!" << endl;
        return;
    }

    oku.seekg(0, ios::end);
    int kayitSayisi = oku.tellg() / sizeof(stok);
    cout << "Toplam stok kay�t say�s�: " << kayitSayisi << endl;

    if (kayitSayisi > 0) {
        oku.seekg(0, ios::beg);
        for (int i = 0; i < kayitSayisi; ++i) {
            oku.read((char*)&stok, sizeof(stok));

            cout << i + 1 << ". Stok Bilgileri:\n";
            cout << "Stok Ad�: " << stok.stokAdi << endl;
            cout << "Stok Miktar�: " << stok.stokMiktari << endl;
            cout << "Stok ID: " << stok.stokID << endl;
        }
    } else {
        cout << "Kay�t bulunamad�...\n";
    }
    oku.close();
}

void StokArama() {
    ifstream oku("stok.dat", ios::binary);
    if (!oku) {
        cout << "Dosya a��l�rken bir hata olu�tu!" << endl;
        return;
    }

    oku.seekg(0, ios::end);
    int kayitSayisi = oku.tellg() / sizeof(stok);

    cout << "Aranan stok ID giriniz: ";
    char stokID[80];
    cin >> stokID;

    if (kayitSayisi > 0) {
        oku.seekg(0, ios::beg);
        for (int i = 0; i < kayitSayisi; ++i) {
            oku.read((char*)&stok, sizeof(stok));

            if (strcmp(stok.stokID, stokID) == 0) {
                cout << "Bulunan Stok Bilgileri:\n";
                cout << "Stok Ad�: " << stok.stokAdi << endl;
                cout << "Stok Miktar�: " << stok.stokMiktari << endl;
                cout << "Stok ID: " << stok.stokID << endl;
                oku.close();
                return;
            }
        }
    } else {
        cout << "Kay�t bulunamad�...\n";
    }
    oku.close();
}

void StokSil() {
    char stokID[80];
    bool bulundu = false;

    ifstream oku("stok.dat", ios::binary);
    if (!oku) {
        cout << "Dosya a��l�rken bir hata olu�tu!" << endl;
        return;
    }

    ofstream yedekYaz("yedek.dat", ios::binary);

    cout << "Silinecek stok ID giriniz: ";
    cin >> stokID;

    oku.seekg(0, ios::end);
    int kayitSayisi = oku.tellg() / sizeof(stok);

    for (int i = 0; i < kayitSayisi; ++i) {
        oku.seekg(i * sizeof(stok));
        oku.read((char*)&stok, sizeof(stok));

        if (strcmp(stok.stokID, stokID) != 0) {
            yedekYaz.write((char*)&stok, sizeof(stok));
        } else {
            bulundu = true;
        }
    }

    oku.close();
    yedekYaz.close();

    if (bulundu) {
        remove("stok.dat");
        rename("yedek.dat", "stok.dat");
        cout << "Kay�t silindi.\n";
    } else {
        remove("yedek.dat");
        cout << "Kay�t bulunamad�.\n";
    }
}

void StokDuzenle() {
    char stokID[80];
    bool bulundu = false;

    ifstream oku("stok.dat", ios::binary);
    if (!oku) {
        cout << "Dosya a��l�rken bir hata olu�tu!" << endl;
        return;
    }

    ofstream yedekYaz("yedek.dat", ios::binary);

    cout << "D�zenlenecek stok �D giriniz: ";
    cin >> stokID;

    oku.seekg(0, ios::end);
    int kayitSayisi = oku.tellg() / sizeof(stok);

    for (int i = 0; i < kayitSayisi; ++i) {
        oku.seekg(i * sizeof(stok));
        oku.read((char*)&stok, sizeof(stok));

        if (strcmp(stok.stokID, stokID) == 0) {
            cout << "Mevcut Stok Bilgileri:\n";
            cout << "Stok Ad�: " << stok.stokAdi << endl;
            cout << "Stok Miktar�: " << stok.stokMiktari << endl;
            cout << "Stok ID: " << stok.stokID << endl;

            cout << "Yeni stok ad� giriniz: ";
            cin >> stok.stokAdi;
            cout << "Yeni stok miktar� giriniz: ";
            cin >> stok.stokMiktari;
            cout << "Yeni stok ID giriniz: ";
            cin >> stok.stokID;

            bulundu = true;
        }

        yedekYaz.write((char*)&stok, sizeof(stok));
    }

    oku.close();
    yedekYaz.close();

    if (bulundu) {
        remove("stok.dat");
        rename("yedek.dat", "stok.dat");
        cout << "Kay�t d�zenlendi.\n";
    } else {
        remove("yedek.dat");
        cout << "Kay�t bulunamad�.\n";
    }
}

