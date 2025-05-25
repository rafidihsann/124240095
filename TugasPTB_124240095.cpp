#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

struct Mahasiswa
{
    int nim;
    char nama[50];
    Mahasiswa *kiri, *kanan;
};

Mahasiswa *akar = NULL;

Mahasiswa *buatNode(int nim, char nama[])
{
    Mahasiswa *baru = new Mahasiswa;
    baru->nim = nim;
    int i = 0;
    while (nama[i] != '\0')
    {
        baru->nama[i] = nama[i];
        i++;
    }
    baru->nama[i] = '\0';
    baru->nama[i] = '\0';
    baru->kiri = baru->kanan = NULL;
    return baru;
}

void tambah()
{
    int nim;
    char nama[50];
    system("cls");
    cout << "Masukkan NIM  : ";
    cin >> nim;
    cin.ignore();
    cout << "Masukkan Nama : ";
    cin.getline(nama, 50);

    Mahasiswa *baru = buatNode(nim, nama);
    if (akar == NULL)
    {
        akar = baru;
        cout << "Data ditambahkan sebagai akar\n";
        getch();
        return;
    }

    Mahasiswa *bantu = akar;
    while (true)
    {
        if (nim < bantu->nim)
        {
            if (bantu->kiri == NULL)
            {
                bantu->kiri = baru;
                cout << "Data berhasil ditambahkan\n";
                break;
            }
            else
            {
                bantu = bantu->kiri;
            }
        }
        else if (nim > bantu->nim)
        {
            if (bantu->kanan == NULL)
            {
                bantu->kanan = baru;
                cout << "Data berhsil ditambahkan\n";
                break;
            }
            else
            {
                bantu = bantu->kanan;
            }
        }
        else
        {
            cout << "NIM sudah ada\n";
            delete baru;
            break;
        }
    }
    cout << "Tekan apa saja untuk kembali ke menu..\n";
    getch();
}

void inorder(Mahasiswa *node)
{
    if (node != NULL)
    {
        inorder(node->kiri);
        cout << "\nNIM: " << node->nim;
        cout << "\nNama: " << node->nama << endl;
        inorder(node->kanan);
    }
}

void tampil()
{
    system("cls");
    if (akar == NULL)
    {
        cout << "Belum ada data\n";
        getch();
    }
    else
    {
        cout << "\nData Mahasiswa:\n";
        inorder(akar);
        cout << "Tekan apa saja untuk kembali ke menu..\n";
        getch();
    }
}

void carimhs()
{
    int nim;
    system("cls");

    if (akar == NULL)
    {
        cout << "Belum ada data\n";
        getch();
    }
    else
    {
        cout << "Masukkan NIM yang dicari: ";
        cin >> nim;
        Mahasiswa *temp = akar;
        while (temp != NULL)
        {
            if (temp->nim == nim)
            {
                cout << " Dsta Ditemukan:\n";
                cout << "NIM  : " << temp->nim << "\n";
                cout << "Nama : " << temp->nama << "\n";
                cout << "Tekan apa saja untuk kembali ke menu..\n";
                getch();
                return;
            }
            else if (nim < temp->nim)
            {
                temp = temp->kiri;
            }
            else
            {
                temp = temp->kanan;
            }
        }
        cout << "Data tidak ditemukan\n";
        getch();
    }
}

Mahasiswa *carinodekiri(Mahasiswa *n)
{
    while (n->kiri != NULL)
    {
        n = n->kiri;
    }
    return n;
}

Mahasiswa *hapus(Mahasiswa *node, int nim)
{
    if (node == NULL)
        return NULL;

    if (nim < node->nim)
    {
        node->kiri = hapus(node->kiri, nim);
    }
    else if (nim > node->nim)
    {
        node->kanan = hapus(node->kanan, nim);
    }
    else
    {
        if (node->kiri == NULL && node->kanan == NULL)
        {
            delete node;
            return NULL;
        }
        else if (node->kiri == NULL)
        {
            Mahasiswa *temp = node->kanan;
            delete node;
            return temp;
        }
        else if (node->kanan == NULL)
        {
            Mahasiswa *temp = node->kiri;
            delete node;
            return temp;
        }
        else
        {
            Mahasiswa *nodekiri = carinodekiri(node->kanan);
            node->nim = nodekiri->nim;

            int i = 0;
            while (nodekiri->nama[i] != '\0')
            {
                node->nama[i] = nodekiri->nama[i];
                i++;
            }
            node->nama[i] = '\0';

            node->kanan = hapus(node->kanan, nodekiri->nim);
        }
    }

    return node;
}

void hapusmhs()
{
    int nim;
    system("cls");

    if (akar == NULL)
    {
        cout << "Belum ada data\n";
        getch();
    }
    else
    {
        cout << "Masukkan NIM yang ingin dihapus: ";
        cin >> nim;

        Mahasiswa *temp = akar;
        bool found = false;
        while (temp != NULL)
        {
            if (temp->nim == nim)
            {
                found = true;
                break;
            }
            else if (nim < temp->nim)
            {
                temp = temp->kiri;
            }
            else
            {
                temp = temp->kanan;
            }
        }

        if (!found)
        {
            cout << "Data tidak ditemukan\n";
        }
        else
        {
            akar = hapus(akar, nim);
            cout << "Data berhasil dihapus\n";
        }
        cout << "Tekan apa saja untuk kembali ke menu..\n";
        getch();
    }
}

int main()
{
    int pilihan;
    do
    {
        system("cls");
        cout << "===== MENU =====\n";
        cout << "1. Tambah Mahasiswa\n";
        cout << "2. Cari Mahasiswa\n";
        cout << "3. Tampilkan Semua\n";
        cout << "4. Hapus Mahasiswa\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambah();
            break;
        case 2:
            carimhs();
            break;
        case 3:
            tampil();
            break;
        case 4:
            hapusmhs();
            break;
        case 0:
            cout << "Keluar dari program...\n";
            break;
        default:
            cout << "Pilihan salah\n";
            getch();
        }
    } while (pilihan != 0);
}
