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
        cout << "|-------Hoþgeldiniz------|" << endl;
        cout << "|      Seçim Yapýnýz     |" << endl;
        cout << "|   1- Stok Ekleme       |" << endl;
        cout << "|   2- Stok Listeleme    |" << endl;
        cout << "|     3- Stok Arama      |" << endl;
        cout << "|    4- Stok Sil         |" << endl;
        cout << "|    5- Stok Düzenle     |" << endl;
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
                cout << "Geçersiz seçim! Lütfen tekrar deneyiniz.\n";
        }

        cout << "Ana menüye dönmek için: a basýn, çýkmak için: c" << endl;
        anamenu = getche();
    } while (anamenu == 'a' || anamenu == 'A');

    return 0;
}

void StokEkle() {
    ofstream yaz("stok.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do {
        cout << "Stok Adý Giriniz: \n ";
        cin >> stok.stokAdi;
        cout << "Stok Miktarý Giriniz: \n ";
        cin >> stok.stokMiktari;
        cout << "Stok ID Giriniz: \n";
        cin >> stok.stokID;

        yaz.write((char*)&stok, sizeof(stok));
        adet++;

        cout << "Baþka kayýt eklemek ister misiniz (E/H)? ";
        secim = getche();
        cout << endl;
    } while (secim == 'e' || secim == 'E');

    cout << adet << " adet stok eklendi.\n";
    yaz.close();
}

void StokListeleme() {
    ifstream oku("stok.dat", ios::binary);
    if (!oku) {
        cout << "Dosya açýlýrken bir hata oluþtu!" << endl;
        return;
    }

    oku.seekg(0, ios::end);
    int kayitSayisi = oku.tellg() / sizeof(stok);
    cout << "Toplam stok kayýt sayýsý: " << kayitSayisi << endl;

    if (kayitSayisi > 0) {
        oku.seekg(0, ios::beg);
        for (int i = 0; i < kayitSayisi; ++i) {
            oku.read((char*)&stok, sizeof(stok));

            cout << i + 1 << ". Stok Bilgileri:\n";
            cout << "Stok Adý: " << stok.stokAdi << endl;
            cout << "Stok Miktarý: " << stok.stokMiktari << endl;
            cout << "Stok ID: " << stok.stokID << endl;
        }
    } else {
        cout << "Kayýt bulunamadý...\n";
    }
    oku.close();
}

void StokArama() {
    ifstream oku("stok.dat", ios::binary);
    if (!oku) {
        cout << "Dosya açýlýrken bir hata oluþtu!" << endl;
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
                cout << "Stok Adý: " << stok.stokAdi << endl;
                cout << "Stok Miktarý: " << stok.stokMiktari << endl;
                cout << "Stok ID: " << stok.stokID << endl;
                oku.close();
                return;
            }
        }
    } else {
        cout << "Kayýt bulunamadý...\n";
    }
    oku.close();
}

void StokSil() {
    char stokID[80];
    bool bulundu = false;

    ifstream oku("stok.dat", ios::binary);
    if (!oku) {
        cout << "Dosya açýlýrken bir hata oluþtu!" << endl;
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
        cout << "Kayýt silindi.\n";
    } else {
        remove("yedek.dat");
        cout << "Kayýt bulunamadý.\n";
    }
}

void StokDuzenle() {
    char stokID[80];
    bool bulundu = false;

    ifstream oku("stok.dat", ios::binary);
    if (!oku) {
        cout << "Dosya açýlýrken bir hata oluþtu!" << endl;
        return;
    }

    ofstream yedekYaz("yedek.dat", ios::binary);

    cout << "Düzenlenecek stok ÝD giriniz: ";
    cin >> stokID;

    oku.seekg(0, ios::end);
    int kayitSayisi = oku.tellg() / sizeof(stok);

    for (int i = 0; i < kayitSayisi; ++i) {
        oku.seekg(i * sizeof(stok));
        oku.read((char*)&stok, sizeof(stok));

        if (strcmp(stok.stokID, stokID) == 0) {
            cout << "Mevcut Stok Bilgileri:\n";
            cout << "Stok Adý: " << stok.stokAdi << endl;
            cout << "Stok Miktarý: " << stok.stokMiktari << endl;
            cout << "Stok ID: " << stok.stokID << endl;

            cout << "Yeni stok adý giriniz: ";
            cin >> stok.stokAdi;
            cout << "Yeni stok miktarý giriniz: ";
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
        cout << "Kayýt düzenlendi.\n";
    } else {
        remove("yedek.dat");
        cout << "Kayýt bulunamadý.\n";
    }
}

