#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include <locale>
// Kargo Bilgileri i�in Struct Tan�m�
struct Kargo {
    int id;
    char gonderici[50];
    char alici[50];
    char adres[100];
    char durum[20];
};

// Fonksiyon Prototipleri
void menu();
void yeniKargoEkle();
void kargoAra();
void kargoGuncelle();
void kargoSil();
void kargolariListele();

int main() {
	setlocale(LC_ALL, "Turkish");
    int secim;
    do {
        menu();
        cout << "Bir i�lem se�in (1-6): ";
        cin >> secim;
        cin.ignore();
        switch (secim) {
            case 1: yeniKargoEkle(); break;
            case 2: kargoAra(); break;
            case 3: kargoGuncelle(); break;
            case 4: kargoSil(); break;
            case 5: kargolariListele(); break;
            case 6: cout << "Programdan ��k�l�yor...\n"; break;
            default: cout << "Ge�ersiz se�im! Tekrar deneyin.\n";
        }
    } while (secim != 6);
    return 0;
}

// Men� Fonksiyonu
void menu() {
    cout << "\n=== Kargo Takip Otomasyonu ===\n";
    cout << "1. Yeni Kargo Kayd� Ekle\n";
    cout << "2. Kargo Bilgisi Ara\n";
    cout << "3. Kargo Bilgisi G�ncelle\n";
    cout << "4. Kargo Kayd� Sil\n";
    cout << "5. T�m Kargolar� Listele\n";
    cout << "6. ��k��\n";
}

// Yeni Kargo Kayd� Ekleme Fonksiyonu
void yeniKargoEkle() {
    ofstream dosya("kargo.dat", ios::binary | ios::app);
    Kargo yeniKargo;

    cout << "Kargo ID girin: ";
    cin >> yeniKargo.id;
    cin.ignore();

    cout << "G�nderici Ad�: ";
    cin.getline(yeniKargo.gonderici, 50);

    cout << "Al�c� Ad�: ";
    cin.getline(yeniKargo.alici, 50);

    cout << "Adres: ";
    cin.getline(yeniKargo.adres, 100);

    cout << "Durum: ";
    cin.getline(yeniKargo.durum, 20);

    dosya.write((char*)&yeniKargo, sizeof(Kargo));
    dosya.close();
    cout << "Kargo kayd� ba�ar�yla eklendi!\n";
}

// Kargo Bilgisi Arama Fonksiyonu
void kargoAra() {
	
    ifstream dosya("kargo.dat", ios::binary);
    if (!dosya) {
        cout << "Dosya bulunamad�!\n";
        return;
    }

    int arananID;
    cout << "Aramak istedi�iniz Kargo ID: ";
    cout<<"//------------------------------------------------------------------------"<<endl;
    cin >> arananID;

    Kargo okunan;
    bool bulundu = false;

    while (dosya.read((char*)&okunan, sizeof(Kargo))) {
        if (okunan.id == arananID) {
            cout << "Kargo Bulundu!\n";
            cout << "ID: " << okunan.id << "\n";
            cout << "G�nderici: " << okunan.gonderici << "\n";
            cout << "Al�c�: " << okunan.alici << "\n";
            cout << "Adres: " << okunan.adres << "\n";
            cout << "Durum: " << okunan.durum << "\n";
            bulundu = true;
            break;
        }
    }
    dosya.close();

    if (!bulundu) {
        cout << "Kargo bulunamad�!\n";
    }
}

// Kargo Bilgisi G�ncelleme Fonksiyonu
void kargoGuncelle() {
	cout<<"//------------------------------------------------------------------------"<<endl;
    fstream dosya("kargo.dat", ios::binary | ios::in | ios::out);
    if (!dosya) {
        cout << "Dosya bulunamad�!\n";
        return;
    }

    int arananID;
    cout << "G�ncellemek istedi�iniz Kargo ID: ";
    cin >> arananID;
    cin.ignore();

    Kargo okunan;
    bool bulundu = false;
    int pozisyon;

    while (dosya.read((char*)&okunan, sizeof(Kargo))) {
        if (okunan.id == arananID) {
            cout << "Kargo Bulundu! G�ncelleme bilgilerini girin:\n";

            cout << "G�nderici Ad�: ";
            cin.getline(okunan.gonderici, 50);

            cout << "Al�c� Ad�: ";
            cin.getline(okunan.alici, 50);

            cout << "Adres: ";
            cin.getline(okunan.adres, 100);

            cout << "Durum: ";
            cin.getline(okunan.durum, 20);

            pozisyon = dosya.tellg() - sizeof(Kargo);
            dosya.seekp(pozisyon);
            dosya.write((char*)&okunan, sizeof(Kargo));
            bulundu = true;
            cout << "Kargo bilgileri ba�ar�yla g�ncellendi!\n";
            break;
        }
    }
    dosya.close();

    if (!bulundu) {
        cout << "Kargo bulunamad�!\n";
    }
}

// Kargo Kayd� Silme Fonksiyonu
void kargoSil() {
	cout<<"//----------------------------------------------------------------------"<<endl;
    ifstream dosya("kargo.dat", ios::binary);
    ofstream geciciDosya("gecici.dat", ios::binary);

    if (!dosya) {
        cout << "Dosya bulunamad�!\n";
        return;
    }

    int silinecekID;
    cout << "Silmek istedi�iniz Kargo ID: ";
    cin >> silinecekID;

    Kargo okunan;
    bool silindi = false;

    while (dosya.read((char*)&okunan, sizeof(Kargo))) {
        if (okunan.id != silinecekID) {
            geciciDosya.write((char*)&okunan, sizeof(Kargo));
        } else {
            silindi = true;
        }
    }
    dosya.close();
    geciciDosya.close();

    remove("kargo.dat");
    rename("gecici.dat", "kargo.dat");

    if (silindi) {
        cout << "Kargo ba�ar�yla silindi!\n";
    } else {
        cout << "Kargo bulunamad�!\n";
    }
}

// T�m Kargolar� Listeleme Fonksiyonu
void kargolariListele() {
	cout<<"//----------------------------------------------------------------------------";

    ifstream dosya("kargo.dat", ios::binary);
    if (!dosya) {
        cout << "Dosya bulunamad�!\n";
        return;
    }

    Kargo okunan;
    cout << "\n--- T�m Kargolar ---\n";
    while (dosya.read((char*)&okunan, sizeof(Kargo))) {
        cout << "ID: " << okunan.id << ", G�nderici: " << okunan.gonderici
             << ", Al�c�: " << okunan.alici << ", Adres: " << okunan.adres
             << ", Durum: " << okunan.durum << "\n";
    }
    dosya.close();
}

