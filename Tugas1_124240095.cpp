#include <iostream>
#include <conio.h>
using namespace std;

struct barang
{
    string nama;
    int harga;
};
barang barank[50];
void input();
void sorting();
void searching();
int pilih;
int jumlahbrg = 0;

int main()
{
    do
    {
        system("cls");
        cout << "=================" << endl;
        cout << "       Menu" << endl;
        cout << "=================" << endl;
        cout << "1. Input Data" << endl;
        cout << "2. Tampilan Data" << endl;
        cout << "3. Searching Data" << endl;
        cout << "4. Keluar       " << endl;
        cout << "=================" << endl;
        cout << "\nPilih Menu: "; cin >> pilih;
        cin.ignore();
        switch (pilih)
        {
        case 1:
            input();
            break;
        case 2:
            sorting();
            break;
        case 3:
            searching();
            break;
        case 4:
            exit(0);
        default:
            system("cls");
            cout << "Pilih angka sesuai menu!";
            cout << "\nTekan apa saja untuk melanjutkan..";
            getch();
            break;
        }
    } while (pilih != 4);
}

void input(){
    int brp;
    system("cls");
    cout << "--INPUT DATA BARANG--" << endl;
    cout << "Banyak barang yang akan ditambah: "; cin >> brp;
    cin.ignore();
    for (int i = 0; i < brp; i++)
    {
    cout << "\nData barang ke-" << i+1 << endl;
    cout << "Nama Barang : "; getline(cin, barank[jumlahbrg].nama);
    cout << "Harga Barang: "; cin >> barank[jumlahbrg].harga;
    cin.ignore();
    jumlahbrg++;
    }
    cout << "\nTekan apa saja untuk melanjutkan..";
    getch();
}

void sorting(){
    system("cls");
    cout << "--LIHAT DATA BARANG--" << endl;
    if (jumlahbrg == 0) {
        cout << "Belum ada data barang." << endl;
    } else {
        for (int i = 0; i < jumlahbrg - 1; i++)
        {
            for (int j = 0; j < jumlahbrg - 1 - i; j++)
            {
                if (barank[j].nama > barank[j + 1].nama)
                {
                swap(barank[j].nama, barank[j + 1].nama);
                }
            }
        }
        }
        for (int i = 0; i < jumlahbrg; i++) {
            cout << "\nData Barang ke-" << i + 1 << endl;
            cout << "Nama : " << barank[i].nama << endl;
            cout << "Harga: " << barank[i].harga << endl;
        }
    cout << "\nTekan apa saja untuk melanjutkan..";
    getch();
}

void searching(){
    int cari;
    string nyarinama;
    int nyariharga;
    bool found = false;
    int awal, tengah, akhir;
    system("cls");
    if (jumlahbrg == 0) {
        cout << "Belum ada data barang." << endl;
    } else {
    cout << "--PENCARIAN BARANG--" << endl;
    cout << "1. Berdasarkan Nama" << endl;
    cout << "2. Berdasarkan Harga" << endl;
    cout << "\nPIlih Metode Cari: "; cin >> cari;
    cin.ignore();
    switch (cari)
    {
    case 1:
        system("cls");
        cout << "--CARI BERDASARKAN NAMA--" << endl;
        cout << "Masukkan Nama Barang Yang Dicari: "; getline(cin, nyarinama);
        awal = 0;
        akhir = jumlahbrg - 1;
        while (awal <= akhir)
        {
            tengah = (awal + akhir) / 2;
            if (barank[tengah].nama == nyarinama)
            {
                found = true;
                cout << "\nBarang Ditemukan!" << endl;
                cout << "Nama Barang : " << barank[tengah].nama << endl;
                cout << "Harga Barang: " << barank[tengah].harga << endl;
            }
             if (nyarinama < barank[tengah].nama)
             {
                akhir = tengah - 1;
             } else awal = tengah + 1;
        }
        if (!found)
             {
                cout << "\nTidak ada stok barang tersebut saat ini." << endl;
             }
        break;
    case 2:
        system("cls");
        cout << "--CARI BERDASARKAN HARGA--" << endl;
        cout << "Masukkan Harga Barang Yang Dicari: "; cin >> nyariharga;
        cin.ignore();
        for (int i = 0; i < jumlahbrg; i++)
        {
            if (barank[i].harga == nyariharga)
                {
                    found = true; 
                    cout << "\nBarang Ditemukkan!" << endl;
                    cout << "Harga Barang: " << barank[i].harga << endl;
                    cout << "Nama Barang : " << barank[i].nama << endl;
                    break; 
                }
            }
            if (!found) 
            {
                cout << "\nTidak ada barang dengan harga segitu. " << endl;
            }
        break;
    default:
        system("cls");
        cout << "Pilih angka sesuai menu!";
        break;
    }
    cout << "\nTekan apa saja untuk melanjutkan..";
    getch();
    }
}
