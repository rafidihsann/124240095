#include <iostream>
#include <conio.h> // untuk getch()
using namespace std;

struct Buku
{
    char judul[100];
    char pengarang[100];
    int tahun;
    Buku *kiri, *kanan;

    Buku(char j[], char p[], int t)
    {
        int i = 0;
        while (j[i] != '\0' && i < 99)
        {
            judul[i] = j[i];
            i++;
        }
        judul[i] = '\0';

        i = 0;
        while (p[i] != '\0' && i < 99)
        {
            pengarang[i] = p[i];
            i++;
        }
        pengarang[i] = '\0';

        tahun = t;
        kiri = kanan = NULL;
    }
};

struct Stackundo
{
    char judul[50][100];
    char pengarang[50][100];
    int tahun[50];
    char aksi[50][20];
    int top;

    Stackundo() { top = -1; }

    void simpan(char j[], char p[], int t, char a[])
    {
        if (top >= 49)
            return;
        top++;

        int i = 0;
        while (j[i] != '\0' && i < 99)
        {
            judul[top][i] = j[i];
            i++;
        }
        judul[top][i] = '\0';

        i = 0;
        while (p[i] != '\0' && i < 99)
        {
            pengarang[top][i] = p[i];
            i++;
        }
        pengarang[top][i] = '\0';

        tahun[top] = t;

        i = 0;
        while (a[i] != '\0' && i < 19)
        {
            aksi[top][i] = a[i];
            i++;
        }
        aksi[top][i] = '\0';
    }

    bool kosong() { return top == -1; }
};

Stackundo undo;

int bandingkan(char a[], char b[]);
void salin(char tujuan[], char sumber[]);
Buku *cari(Buku *akar, char judul[]);
void tambah(Buku *&akar, char j[], char p[], int t);
void tampil(Buku *akar);
void hapus(Buku *&akar, char judul[]);
Buku *inorder(Buku *akar);
void aksiundo(Buku *&akar);

int main()
{
    Buku *akar = NULL;
    int menu;
    char j[100], p[100], h[100];
    int t;

    do
    {
        system("cls");
        cout << "\n=== MENU PERPUSTAKAAN ===\n";
        cout << "1. Tambah Buku\n";
        cout << "2. Lihat Semua Buku (Z-A)\n";
        cout << "3. Hapus Buku\n";
        cout << "4. Undo Aksi Terakhir\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> menu;
        cin.ignore();

        switch (menu)
        {
        case 1:
            system("cls");
            cout << "Judul: ";
            cin.getline(j, 100);
            cout << "Pengarang: ";
            cin.getline(p, 100);
            cout << "Tahun: ";
            cin >> t;
            cin.ignore();
            if (!cari(akar, j))
            {
                tambah(akar, j, p, t);
                undo.simpan(j, p, t, "tambah");
                cout << "Buku ditambahkan.\n";
            }
            else
            {
                cout << "Buku sudah ada.\n";
            }
            getch();
            break;
        case 2:
            system("cls");
            cout << "\n=== DAFTAR BUKU ===\n";
            tampil(akar);
            getch();
            break;
        case 3:
            system("cls");
            cout << "Judul buku yang dihapus: ";
            cin.getline(h, 100);
            {
                Buku *ditemukan = cari(akar, h);
                if (ditemukan)
                {
                    undo.simpan(ditemukan->judul, ditemukan->pengarang, ditemukan->tahun, "hapus");
                    hapus(akar, h);
                    cout << "Buku dihapus.\n";
                }
                else
                {
                    cout << "Buku tidak ditemukan.\n";
                }
            }
            getch();
            break;
        case 4:
            system("cls");
            aksiundo(akar);
            getch();
            break;
        case 5:
            cout << "Terima kasih.\n";
            return 0;
        default:
            cout << "Pilihan tidak valid.\n";
            getch();
        }
    } while (menu != 5);
}

int bandingkan(char a[], char b[])
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] < b[i])
            return -1;
        if (a[i] > b[i])
            return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0')
        return 0;
    return (a[i] == '\0') ? -1 : 1;
}

void salin(char tujuan[], char sumber[])
{
    int i = 0;
    while (sumber[i] != '\0' && i < 99)
    {
        tujuan[i] = sumber[i];
        i++;
    }
    tujuan[i] = '\0';
}

Buku *cari(Buku *akar, char judul[])
{
    if (!akar)
        return NULL;
    int banding = bandingkan(judul, akar->judul);
    if (banding == 0)
        return akar;
    return (banding < 0) ? cari(akar->kiri, judul) : cari(akar->kanan, judul);
}

void tambah(Buku *&akar, char j[], char p[], int t)
{
    if (!akar)
    {
        akar = new Buku(j, p, t);
        return;
    }
    int banding = bandingkan(j, akar->judul);
    if (banding < 0)
        tambah(akar->kiri, j, p, t);
    else
        tambah(akar->kanan, j, p, t);
}

void tampil(Buku *akar)
{
    if (!akar)
        return;
    tampil(akar->kanan);
    cout << akar->judul << " - " << akar->pengarang << " - " << akar->tahun << endl;
    tampil(akar->kiri);
}

Buku *inorder(Buku *akar)
{
    while (akar && akar->kiri)
        akar = akar->kiri;
    return akar;
}

void hapus(Buku *&akar, char judul[])
{
    if (!akar)
        return;
    int banding = bandingkan(judul, akar->judul);
    if (banding < 0)
    {
        hapus(akar->kiri, judul);
    }
    else if (banding > 0)
    {
        hapus(akar->kanan, judul);
    }
    else
    {
        if (!akar->kiri)
        {
            Buku *temp = akar;
            akar = akar->kanan;
            delete temp;
        }
        else if (!akar->kanan)
        {
            Buku *temp = akar;
            akar = akar->kiri;
            delete temp;
        }
        else
        {
            Buku *bantu = inorder(akar->kanan);
            salin(akar->judul, bantu->judul);
            salin(akar->pengarang, bantu->pengarang);
            akar->tahun = bantu->tahun;
            hapus(akar->kanan, bantu->judul);
        }
    }
}

void aksiundo(Buku *&akar)
{
    if (undo.kosong())
    {
        cout << "Tidak ada aksi untuk di-undo.\n";
        return;
    }

    if (bandingkan(undo.aksi[undo.top], "tambah") == 0)
    {
        hapus(akar, undo.judul[undo.top]);
        cout << "Undo tambah: Buku dihapus.\n";
    }
    else
    {
        tambah(akar, undo.judul[undo.top], undo.pengarang[undo.top], undo.tahun[undo.top]);
        cout << "Undo hapus: Buku ditambahkan kembali.\n";
    }

    undo.top--;
}