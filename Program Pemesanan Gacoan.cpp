#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <cctype>
using namespace std;

// Struktur menu makanan dan minuman
struct Menu {
    string nama;
    double harga;
};

// Struktur untuk menyimpan detail pesanan
struct Pesanan {
    string namaMakanan;
    int jumlah;
    Pesanan* next;
};

// Struktur data untuk pembayaran menggunakan e-wallet
struct EWallet {
    string namaPemilik;
    double saldo;
};

// Struktur data untuk pembayaran menggunakan voucher
struct Voucher {
    string kodeVoucher;
    double nilai;
};
const int MAX_MENU = 20;    // jumlah maksimum menu yang dapat disimpan
Menu daftarMenu[MAX_MENU] = {   // Array untuk menyimpan daftar menu dan harganya
    {"Mie Suit", 9500},
    {"Mie Hompimpa Lv 1-4", 9500},
    {"Mie Hompimpa Lv 6-8", 10500},
    {"Mie Gacoan Lv 0-4 ", 9500},
    {"Mie Gacoan Lv 6-8", 10500},
    {"Siomay", 8600},
    {"Udang Rambutan", 8600},
    {"Udang Keju", 8600},
    {"Lumpia Udang", 8600},
    {"Pangsit Goreng", 9500},
    {"Es Gobak Sodor", 9100},
    {"Es Teklek", 5900},
    {"Es Sluku Bathok", 5900},
    {"Es Petak Umpet", 9100},
    {"Es Tea", 4100},
    {"Orange", 5000},
    {"Lemon Tea", 5900},
    {"Milo", 8200},
    {"Vanila Latte", 8200},
    {"Teh Tarik", 6400}
};

Pesanan* head = nullptr;    // Pointer kepala linked list untuk pesanan

// Variabel global untuk menyimpan informasi e-wallet
EWallet ewallet = {"John Doe", 50000}; // Contoh saldo awal

// Variabel global untuk menyimpan informasi voucher
Voucher voucher = {"ABC123", 50000}; // Contoh nilai voucher

// fungsi untuk pause
void pause() {
    cout << "Tekan tombol Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

// Menampilkan saldo e-wallet
void tampilkanSaldoEWallet() {
    cout << "Saldo e-wallet Anda saat ini: Rp" << ewallet.saldo << endl;
}

// Fungsi untuk memproses pembayaran dengan e-wallet
void bayarEWallet(double totalPembayaran) {
    // Menampilkan saldo e-wallet
    tampilkanSaldoEWallet();

    // Memeriksa apakah saldo e-wallet mencukupi
    if (ewallet.saldo < totalPembayaran) {
        cout << "Saldo e-wallet tidak mencukupi. Silakan menggunakan metode pembayaran lain." << endl;
        return;
    }

    // Proses pembayaran menggunakan e-wallet
    ewallet.saldo -= totalPembayaran;
    cout << "Pembayaran berhasil menggunakan e-wallet. Sisa saldo e-wallet: Rp" << ewallet.saldo << endl;
}

// Fungsi untuk memproses pembayaran dengan voucher
void bayarVoucher(double totalPembayaran) {
    // Menampilkan nilai voucher
    cout << "Nilai voucher yang tersedia: Rp" << voucher.nilai << endl;

    // Memeriksa apakah nilai voucher mencukupi
    if (voucher.nilai < totalPembayaran) {
        cout << "Nilai voucher tidak mencukupi. Silakan menggunakan metode pembayaran lain." << endl;
        return;
    }

    // Proses pembayaran menggunakan voucher
    voucher.nilai -= totalPembayaran;
    cout << "Pembayaran berhasil menggunakan voucher. Sisa nilai voucher: Rp" << voucher.nilai << endl;
}

// Fungsi untuk menambahkan pesanan baru ke linked list
void tambahPesanan(string namaMakanan, int jumlah) {
    Pesanan* newNode = new Pesanan; // node pesanan baru
    newNode->namaMakanan = namaMakanan; // detail pesanan
    newNode->jumlah = jumlah;
    newNode->next = nullptr; // Menjadikan newNode sebagai node terakhir

    if (head == nullptr) { // untuk jika linked list kosong, newNode menjadi kepala
        head = newNode;
    } else {    // Jika tidak maka mencari node terakhir dan menambahkan newNode
        Pesanan* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Fungsi untuk menampilkan daftar menu
void tampilkanMenu() {
    cout << "------------------------------------------------------------" << endl;
    cout << setw(6) << left << "| No." << setw(30) << left << "| Menu" << setw(16) << right << "| Harga " << setw(8) << "|" << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < MAX_MENU; ++i) {
        cout << "| " << setw(2) << right << i+1 << ". | " << setw(35) << left << daftarMenu[i].nama << " | Rp" << setw(10) << right << fixed << setprecision(2) << daftarMenu[i].harga << " |" << endl;
    }
    cout << "------------------------------------------------------------" << endl;
}

// Fungsi untuk menampilkan ringkasan pesanan dan total pembayaran
void tampilkanRingkasanDanTotalPembayaran(double totalPembayaran) {
    cout << "-------------------------------------------------------------------------------------------" << endl;
    cout << "| No |       Menu Pesanan      |  Jumlah Menu  | Total Harga Per menu  | Total Pembayaran |" << endl;
    cout << "-------------------------------------------------------------------------------------------" << endl;
    Pesanan* temp = head;
    int nomor = 1;
    while (temp != nullptr) {
        double totalHarga = 0.0;
        for (int i = 0; i < MAX_MENU; ++i) {
            if (daftarMenu[i].nama == temp->namaMakanan) {
                totalHarga = daftarMenu[i].harga * temp->jumlah;
                break;
            }
        }
        cout << "| " << setw(2) << left << nomor << " | " << setw(24) << left << temp->namaMakanan << "| " << setw(14) << left << temp->jumlah << "| Rp" << setw(20) << fixed << setprecision(2) << totalHarga << "| Rp" << setw(14) << fixed << setprecision(2) << totalPembayaran << " |" << endl;
        temp = temp->next;
        nomor++;
    }
    cout << "-------------------------------------------------------------------------------------------" << endl;
}

// Fungsi untuk menampilkan semua pesanan dan total pembayaran
void tampilkanPesananDanTotalPembayaran() {
    double totalPembayaran = 0.0;
    Pesanan* temp = head;
    while (temp != nullptr) {
        for (int i = 0; i < MAX_MENU; ++i) {
            if (daftarMenu[i].nama == temp->namaMakanan) {
                totalPembayaran += daftarMenu[i].harga * temp->jumlah;
                break;
            }
        }
        temp = temp->next;
    }
    tampilkanRingkasanDanTotalPembayaran(totalPembayaran);
}

// Fungsi untuk membatalkan pesanan berdasarkan nomor pesanan
void batalkanPesanan(int nomorPesanan) {
    Pesanan* temp = head;
    Pesanan* prev = nullptr;
    int nomor = 1;

    // Mencari node pesanan yang akan dibatalkan
    while (temp != nullptr && nomor < nomorPesanan) {
        prev = temp;
        temp = temp->next;
        nomor++;
    }

    // Jika nomor pesanan tidak valid
    if (temp == nullptr) {
        cout << "Nomor pesanan tidak valid." << endl;
        return;
    }

    // Menghapus node pesanan dari linked list
    if (prev == nullptr) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    // Menghapus memori yang dialokasikan untuk node pesanan
    delete temp;
    cout << "Pesanan nomor " << nomorPesanan << " berhasil dibatalkan." << endl;
}

// Fungsi untuk memproses pembayaran
void bayarPesanan(double totalPembayaran) {
    // Menampilkan saldo e-wallet
    tampilkanSaldoEWallet();

    string metodePembayaran;
    cout << "Silakan pilih metode pembayaran (tunai/kartu kredit/e-wallet/voucher): ";
    cin >> metodePembayaran;

    if (metodePembayaran == "tunai") {
        cout << "Silahkan datang langsung ke gacoan!" << endl;
        // Mengosongkan pesanan
        while (head != nullptr) {
            Pesanan* temp = head;
            head = head->next;
            delete temp;
        }
    } else if (metodePembayaran == "e-wallet") {
        bayarEWallet(totalPembayaran);
        // Mengosongkan pesanan
        while (head != nullptr) {
            Pesanan* temp = head;
            head = head->next;
            delete temp;
        }
    } else if (metodePembayaran == "voucher") {
        bayarVoucher(totalPembayaran);
        // Mengosongkan pesanan
        while (head != nullptr) {
            Pesanan* temp = head;
            head = head->next;
            delete temp;
        }
    } else {
        cout << "Metode pembayaran tidak valid." << endl;
    }
}

int main() {
    char pilihan;
    cout << "================= Selamat datang di Gacoan! ================" << endl; 
    cout << "============== Silahkan tentukan pilihan anda ==============" << endl;

    // Loop utama untuk mengambil pesanan 
    do {
        // Inisialisasi saldo e-wallet
        ewallet.saldo = 50000; // Misalnya, saldo awal adalah Rp 50.000

        int menu;
        int jumlah;
        tampilkanMenu();

        cout << "Silakan Masukkan nomor menu pilihan anda    : "; 
        cin >> menu;

        // Memeriksa validitas input menu
        if (menu < 1 || menu > MAX_MENU) {
            cout << "Input tidak valid. Silakan coba lagi." << endl;
            pause();
            system("cls");
        }
        cout << "Masukkan jumlah yang ingin anda pesan       : "; cin >> jumlah;
        pause();
        system("cls");

        // Memeriksa validitas input jumlah
        if (jumlah <= 0) {
            cout << "Input tidak valid. Silakan coba lagi." << endl;
            pause();
            system("cls");
        }
        // Menambahkan pesanan baru ke linked list
        tambahPesanan(daftarMenu[menu - 1].nama, jumlah);
        cout << "Berikut adalah menu yang anda pilih sebelumnya." << endl;
        tampilkanPesananDanTotalPembayaran();
        
        // menampilkan opsi untuk memesan lagi
        cout << "Apakah Anda ingin memesan lagi? (y/n)       : "; cin >> pilihan;
        pause();
        system("cls");
    } while (pilihan == 'y' || pilihan == 'Y');

    // Menampilkan opsi untuk membatalkan pesanan
     if (pilihan == 'n' || pilihan == 'N') {
        char opsiHapus;
        do {
            cout << "Apakah ada pesanan yang ingin anda batalkan? (y/n): "; cin >> opsiHapus;
            if (opsiHapus == 'y' || opsiHapus == 'Y') {
                tampilkanPesananDanTotalPembayaran();
                int nomorPesanan;
                cout << "Masukkan nomor pesanan yang ingin anda batalkan: ";
                cin >> nomorPesanan;
                batalkanPesanan(nomorPesanan);

                // Konfirmasi pembatalan pesanan
                cout << "Apakah Anda ingin membatalkan pesanan lain? (y/n) : ";
                cin >> opsiHapus;
            }
        } while (opsiHapus == 'y' || opsiHapus == 'Y');
    }

    // Menampilkan ringkasan pesanan dan total pembayaran
    if (head == nullptr) {
        cout << "Anda tidak memesan apapun." << endl;
        pause();
        return 0;
    }

    system("cls"); //membersihkan layar
    tampilkanPesananDanTotalPembayaran();

    // Meminta metode pembayaran dari pengguna
    string metodePembayaran;
    cout << "Silakan pilih metode pembayaran (tunai/e-wallet/voucher): "; cin >> metodePembayaran;
    // Memproses pembayaran sesuai metode yang dipilih
    if (metodePembayaran == "tunai") {
        // Memproses pembayaran tunai
        cout << "Silahkan datang langsung ke gacoan!" << endl;
        char konfirmasi;
        cout << "Apakah pembayaran telah diselesaikan secara tunai? (y/n): ";
        cin >> konfirmasi;
        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            // Mengosongkan pesanan
            while (head != nullptr) {
                Pesanan* temp = head;
                head = head->next;
                delete temp;
            }
            cout << "Pembayaran tunai telah berhasil. Pesanan telah dibayar secara tunai." << endl;
        } else {
            cout << "Pembayaran tunai belum diselesaikan. Silakan selesaikan pembayaran." << endl;
        }
    } else if (metodePembayaran == "e-wallet") {
        // Memproses pembayaran menggunakan e-wallet
        double totalPembayaran = 0.0;
        Pesanan* temp = head;
        while (temp != nullptr) {
            for (int i = 0; i < MAX_MENU; ++i) {
                if (daftarMenu[i].nama == temp->namaMakanan) {
                    totalPembayaran += daftarMenu[i].harga * temp->jumlah;
                    break;
                }
            }
            temp = temp->next;
        }
        bayarEWallet(totalPembayaran);
    } else if (metodePembayaran == "voucher") {
        // Memproses pembayaran menggunakan voucher
        double totalPembayaran = 0.0;
        Pesanan* temp = head;
        while (temp != nullptr) {
            for (int i = 0; i < MAX_MENU; ++i) {
                if (daftarMenu[i].nama == temp->namaMakanan) {
                    totalPembayaran += daftarMenu[i].harga * temp->jumlah;
                    break;
                }
            }
            temp = temp->next;
        }
        bayarVoucher(totalPembayaran);
    } else {
        cout << "Metode pembayaran tidak valid." << endl;
        while (head != nullptr) {
            Pesanan* temp = head;
            head = head->next;
            delete temp;
        }
    }

    return 0;
}



