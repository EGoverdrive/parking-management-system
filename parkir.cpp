#include <iostream>
#include <string>
using namespace std;

struct kendaraan { 
    string plat;
    string tipe;
    int j_masuk; int m_masuk; int t_masuk;
    int j_keluar; int m_keluar; int t_keluar;
    int dur;
    int tarif;

    // j = jam, m = menit, t = total waktu (menit)
};

char formatjam = ':';
kendaraan kpa[20];
bool cek_slot[20];
int cuan = 0;
int total_checkout = 0;

void regis() {
   for (int i = 0; i < 20; i++) {
    if (cek_slot[i] == false) {
        cout << "Masukkan Plat Kendaraan: ";
        getline(cin, kpa[i].plat);

        cout << "Masukkan Tipe Kendaraan (Motor/Mobil): ";
        cin >> kpa[i].tipe;

        cout << "Masukkan Jam Masuk Kendaraan (HH:MM): ";
        cin >> kpa[i].j_masuk >> formatjam >> kpa[i].m_masuk;

        kpa[i].t_masuk = kpa[i].j_masuk * 60 + kpa[i].m_masuk;
        cek_slot[i] = true;
        break;
    }
   }
}

void checkout(string plat) {

    for (int i = 0; i < 20; i++) {
        if ((cek_slot[i] == true) && (plat == kpa[i].plat)) { //cek platnya valid & slotnya lagi dipake
            
            cout << "Masukkan Jam Keluar Kendaraan (HH:MM): ";
            cin >> kpa[i].j_keluar >> formatjam >> kpa[i].m_keluar; 

            kpa[i].t_keluar = kpa[i].j_keluar * 60 + kpa[i].m_keluar;

            if (kpa[i].t_keluar < kpa[i].t_masuk) {
                kpa[i].dur = (1440 - kpa[i].t_masuk) + kpa[i].t_keluar; //case kalo overlap (lewat tengah malem)
            } else { 
                kpa[i].dur = kpa[i].t_keluar - kpa[i].t_masuk; //normal case
            }     

            //ubah ke jam dan aturan pembulatan ke atas

            if (kpa[i].dur % 60 != 0) {
                kpa[i].dur =  kpa[i].dur / 60 + 1;
            } else {
                kpa[i].dur = kpa[i].dur / 60;
            }

            //kalkulasi tarif
            if (kpa[i].tipe == "Motor" || kpa[i].tipe == "motor") {
                if (kpa[i].dur <= 2) {
                    kpa[i].tarif = 3000;
                } else {
                    kpa[i].tarif = 3000 + (kpa[i].dur - 2) * 2000;
                }
            } else if (kpa[i].tipe == "Mobil" || kpa[i].tipe == "mobil") {
                if (kpa[i].dur <= 2) {
                    kpa[i].tarif = 5000;
                } else {
                    kpa[i].tarif = 5000 + (kpa[i].dur - 2) * 3000;
                }
            }

            //cek diskon
            if (kpa[i].dur > 8) {
                kpa[i].tarif = kpa[i].tarif - (kpa[i].tarif * 0.10);
            }
            
            total_checkout++;
            cuan += kpa[i].tarif;
            cek_slot[i] = false;

            cout << "Checkout berhasil dengan total tarif: Rp " << kpa[i].tarif << endl;
        }
    }
}

void report() {
    int isi = 0; 
    int kosong = 0;
    //cek berapa slot kosong dan terisi
    for (int i = 0; i < 20; i++) {
        if (cek_slot[i] == true){
            isi++;
        } else {
            kosong++;
        }
    }

    cout << "\n===== LAPORAN HARIAN PARKIR =====\n";
    cout << "Jumlah Slot Terisi     : " << isi << endl;
    cout << "Jumlah Slot Kosong     : " << kosong << endl;
    cout << "Total Transaksi Selesai: " << total_checkout << endl;
    cout << "Total Pendapatan       : Rp " << cuan << endl;
    cout << "=================================\n";
}

int main() {
    int opsi;
    string cek_plat;

    //set slot ke kosong semua
    for (int i = 0; i < 20; i++) {
        cek_slot[i] = false;
    }

    while (opsi != 4) {
        cout << "\n=========================================\n";
        cout << "      SISTEM MANAJEMEN PARKIR MALL       \n";
        cout << "=========================================\n";
        cout << "1. Registrasi Kendaraan Masuk\n";
        cout << "2. Checkout Kendaraan Keluar\n";
        cout << "3. Tampilkan Laporan Harian\n";
        cout << "4. Keluar Program\n";
        cout << "Opsi Anda (1-4): ";
        cin >> opsi;

    if (opsi == 1) {
            cout << "\n--- REGISTRASI KENDARAAN ---\n";
            cin.ignore();
            regis();
        } 
        else if (opsi == 2) {
            cout << "\n--- CHECKOUT KENDARAAN ---\n";
            cout << "Masukkan Plat Kendaraan: ";
            cin.ignore();
            getline(cin, cek_plat);
            checkout(cek_plat);
        } 
        else if (opsi == 3) {
            report();
        } 
        else if (opsi == 4) {
            cout << "\nTerima kasih!\n";
        } 
        else {
            cout << "\nOpsi tidak valid!\n";
        }
    }

    return 0;
}



