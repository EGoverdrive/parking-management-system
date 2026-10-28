
#include <iostream>
#include <string>

using namespace std;

struct Kendaraan {
    string PlatNomor;
    string JenisKendaraan;
    int JamMasuk;
    int MenitMasuk;
    int JamKeluar;
    int MenitKeluar;
    bool ApakahPenuh;
};

Kendaraan SlotParkir[20];
int TotalCheckout = 0;
long long TotalKeuangan = 0;

void MengosongkanSlot() {
    for(int i = 0; i < 20; i++) {
        SlotParkir[i].PlatNomor = "";
        SlotParkir[i].JenisKendaraan = "";
        SlotParkir[i].JamMasuk = 0;
        SlotParkir[i].MenitMasuk = 0;
        SlotParkir[i].JamKeluar = 0;
        SlotParkir[i].MenitKeluar = 0;
        SlotParkir[i].ApakahPenuh = false;
    }
}

int MencariSlot() {
    for(int i = 0; i < 20; i++) {
        if(SlotParkir[i].ApakahPenuh == false) {
            return i;
        }
    }

    return -1;
}

int MenghitungWaktu(int MasukJam, int MasukMenit, int KeluarJam, int KeluarMenit) {
    int TotalMenitMasuk = (MasukJam * 60) + MasukMenit;
    int TotalMenitKeluar = (KeluarJam * 60) + KeluarMenit;

    if(TotalMenitKeluar < TotalMenitMasuk) {
        TotalMenitKeluar += 1440;
    }

    int TotalMenitWaktuParkir = TotalMenitKeluar - TotalMenitMasuk;
    int TotalWaktuParkir = (TotalMenitWaktuParkir + 59) / 60;

    if(TotalWaktuParkir < 1) {
        TotalWaktuParkir = 1;
    }

    return TotalWaktuParkir;
}

long long MenghitungTotalTarif(int waktu, string type) {
    long long TotalBayar = 0;

    if(type == "Motor") {
        if(waktu <= 2) {
            TotalBayar = 3000;
        } else {
            TotalBayar = 3000 + (waktu - 2) * 2000;
        }
    } else if(type == "Mobil") {
        if(waktu <= 2) {
            TotalBayar = 5000;
        } else {
            TotalBayar = 5000 + (waktu - 2) * 3000;
        }
    }

    if(waktu > 8) {
        TotalBayar = TotalBayar * 90 / 100;
    }

    return TotalBayar;
}

void MemasukanKendaraan() {
    string PlatNomor;
    string JenisKendaraan;
    int JamMasuk;
    int MenitMasuk;

    cout << "\n===== REGISTRASI KENDARAAN =====\n";
    cout << "Masukkan nomor plat: ";
    cin >> PlatNomor;

    for(int i = 0; i < 20; i++) {
        if(SlotParkir[i].ApakahPenuh == true && SlotParkir[i].PlatNomor == PlatNomor) {
            cout << "\nKendaraan sudah terdaftar!\n";
            return;
        }
    }

    int SlotTersedia = MencariSlot();

    if(SlotTersedia == -1) {
        cout << "\nRegistrasi gagal, parkiran sudah penuh!\n";
        return;
    }

    cout << "Masukkan jenis kendaraan (Motor/Mobil): ";
    cin >> JenisKendaraan;

    if(JenisKendaraan != "Motor" && JenisKendaraan != "Mobil") {
        cout << "\nJenis kendaraan salah!\n";
        return;
    }

    cout << "Masukkan jam masuk (0-23): ";
    cin >> JamMasuk;

    cout << "Masukkan menit masuk (0-59): ";
    cin >> MenitMasuk;

    if(JamMasuk < 0 || JamMasuk > 23 || MenitMasuk < 0 || MenitMasuk > 59) {
        cout << "\nFormat jam masuk salah!\n";
        return;
    }

    SlotParkir[SlotTersedia].ApakahPenuh = true;
    SlotParkir[SlotTersedia].PlatNomor = PlatNomor;
    SlotParkir[SlotTersedia].JenisKendaraan = JenisKendaraan;
    SlotParkir[SlotTersedia].JamMasuk = JamMasuk;
    SlotParkir[SlotTersedia].MenitMasuk = MenitMasuk;
    SlotParkir[SlotTersedia].JamKeluar = 0;
    SlotParkir[SlotTersedia].MenitKeluar = 0;

    cout << "\nRegistrasi berhasil!\n";
    cout << "Nomor plat: " << PlatNomor << '\n';
    cout << "Jenis kendaraan: " << JenisKendaraan << '\n';
    cout << "Jam masuk: " << JamMasuk << ':';

    if(MenitMasuk < 10) {
        cout << '0';
    }

    cout << MenitMasuk << '\n';
    cout << "Slot parkir: " << SlotTersedia + 1 << '\n';
}

void CheckoutKendaraan() {
    int JamKeluar;
    int MenitKeluar;
    string PlatNomor;

    cout << "\n===== CHECKOUT KENDARAAN =====\n";
    cout << "Masukkan plat kendaraan: ";
    cin >> PlatNomor;

    int IndeksKendaraan = -1;

    for(int i = 0; i < 20; i++) {
        if(SlotParkir[i].ApakahPenuh == true && SlotParkir[i].PlatNomor == PlatNomor) {
            IndeksKendaraan = i;
            break;
        }
    }

    if(IndeksKendaraan == -1) {
        cout << "\nKendaraan tidak ditemukan!\n";
        return;
    }

    cout << "Masukkan jam keluar (0-23): ";
    cin >> JamKeluar;

    cout << "Masukkan menit keluar (0-59): ";
    cin >> MenitKeluar;

    if(JamKeluar < 0 || JamKeluar > 23 || MenitKeluar < 0 || MenitKeluar > 59) {
        cout << "\nFormat jam keluar salah!\n";
        return;
    }

    int WaktuParkir = MenghitungWaktu(SlotParkir[IndeksKendaraan].JamMasuk, SlotParkir[IndeksKendaraan].MenitMasuk, JamKeluar, MenitKeluar);
    long long BiayaParkir = MenghitungTotalTarif(WaktuParkir, SlotParkir[IndeksKendaraan].JenisKendaraan);

    SlotParkir[IndeksKendaraan].JamKeluar = JamKeluar;
    SlotParkir[IndeksKendaraan].MenitKeluar = MenitKeluar;

    cout << "\n===== STRUK PARKIR =====\n";
    cout << "Nomor plat: " << SlotParkir[IndeksKendaraan].PlatNomor << '\n';
    cout << "Jenis kendaraan: " << SlotParkir[IndeksKendaraan].JenisKendaraan << '\n';
    cout << "Slot parkir: " << IndeksKendaraan + 1 << '\n';
    cout << "Jam masuk: " << SlotParkir[IndeksKendaraan].JamMasuk << ':';

    if(SlotParkir[IndeksKendaraan].MenitMasuk < 10) {
        cout << '0';
    }

    cout << SlotParkir[IndeksKendaraan].MenitMasuk << '\n';
    cout << "Jam keluar: " << JamKeluar << ':';

    if(MenitKeluar < 10) {
        cout << '0';
    }

    cout << MenitKeluar << '\n';
    cout << "Total waktu: " << WaktuParkir << " jam\n";
    cout << "Total biaya: Rp" << BiayaParkir << '\n';

    TotalCheckout++;
    TotalKeuangan += BiayaParkir;

    SlotParkir[IndeksKendaraan].PlatNomor = "";
    SlotParkir[IndeksKendaraan].JenisKendaraan = "";
    SlotParkir[IndeksKendaraan].JamMasuk = 0;
    SlotParkir[IndeksKendaraan].MenitMasuk = 0;
    SlotParkir[IndeksKendaraan].JamKeluar = 0;
    SlotParkir[IndeksKendaraan].MenitKeluar = 0;
    SlotParkir[IndeksKendaraan].ApakahPenuh = false;

    cout << "\nCheckout berhasil. Slot kembali tersedia.\n";
}

void MenampilkanSlot() {
    cout << "\n===== STATUS SLOT PARKIR =====\n";

    for(int i = 0; i < 20; i++) {
        cout << "Slot ke-" << i + 1 << ": ";

        if(SlotParkir[i].ApakahPenuh == true) {
            cout << "Terisi oleh " << SlotParkir[i].PlatNomor << " (" << SlotParkir[i].JenisKendaraan << ")";
        } else {
            cout << "Tersedia";
        }

        cout << '\n';
    }
}

void LaporanParkir() {
    int SlotTerisi = 0;

    for(int i = 0; i < 20; i++) {
        if(SlotParkir[i].ApakahPenuh == true) {
            SlotTerisi++;
        }
    }

    int SlotTersedia = 20 - SlotTerisi;

    cout << "\n===== LAPORAN PARKIR =====\n";
    cout << "Slot tersedia: " << SlotTersedia << '\n';
    cout << "Slot terisi: " << SlotTerisi << '\n';
    cout << "Transaksi selesai: " << TotalCheckout << '\n';
    cout << "Jumlah pemasukan: Rp" << TotalKeuangan << '\n';
}

int main() {
    MengosongkanSlot();

    int Pilihan;

    do {
        cout << "\n====================\n";
        cout << "PARKING MANAGEMENT SYSTEM\n";
        cout << "====================\n";
        cout << "1. Registrasi kendaraan\n";
        cout << "2. Checkout transaksi\n";
        cout << "3. Melihat slot parkir\n";
        cout << "4. Melihat laporan keuangan\n";
        cout << "5. Keluar dari program\n";
        cout << "Pilih menu: ";
        cin >> Pilihan;

        if(Pilihan == 1) {
            MemasukanKendaraan();
        } else if(Pilihan == 2) {
            CheckoutKendaraan();
        } else if(Pilihan == 3) {
            MenampilkanSlot();
        } else if(Pilihan == 4) {
            LaporanParkir();
        } else if(Pilihan == 5) {
            cout << "\nProgram telah selesai.\n";
        } else {
            cout << "\nAnda salah memasukkan angka!\n";
        }
    } while(Pilihan != 5);

    return 0;
}
