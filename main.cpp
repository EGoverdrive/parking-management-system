#include <iostream>
#include <string>

using namespace std;

struct Kendaraan {
    string plat;
    string jenis; 
    double jamMasuk;
    bool isi = false;
};

int main() {
    Kendaraan parkir[20];
    int totalTransaksi = 0;
    int totalPendapatan = 0;
    int pilihan;

    do {
        cout << "\n=== MENU SISTEM PARKIR ===" << endl;
        cout << "1. Registrasi Kendaraan Masuk" << endl;
        cout << "2. Checkout Kendaraan Keluar" << endl;
        cout << "3. Tampilkan Laporan Harian" << endl;
        cout << "4. Keluar Program" << endl;
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                int slotKosong = -1;
                for (int i = 0; i < 20; i++) {
                    if (!parkir[i].isi) {
                        slotKosong = i;
                        break;
                    }
                }

                if (slotKosong == -1) {
                    cout << "Maaf, slot parkir penuh! Registrasi ditolak." << endl;
                } else {
                    cout << "Masukkan Plat Nomor (tanpa spasi, misal B1234XY): ";
                    cin >> parkir[slotKosong].plat;
                    cout << "Masukkan Jenis (motor/mobil): ";
                    cin >> parkir[slotKosong].jenis;
                    cout << "Masukkan Jam Masuk (contoh 8.0 atau 9.5): ";
                    cin >> parkir[slotKosong].jamMasuk;

                    parkir[slotKosong].isi = true;
                    cout << "Berhasil! Kendaraan parkir di slot nomor " << (slotKosong + 1) << endl;
                }
                break;
            }

            case 2: {
                string cariPlat;
                cout << "Masukkan Plat Nomor yang akan keluar: ";
                cin >> cariPlat;

                int targetSlot = -1;
                for (int i = 0; i < 20; i++) {
                    if (parkir[i].isi && parkir[i].plat == cariPlat) {
                        targetSlot = i;
                        break;
                    }
                }

                if (targetSlot == -1) {
                    cout << "Kendaraan dengan plat " << cariPlat << " tidak ditemukan!" << endl;
                } else {
                    double jamKeluar;
                    cout << "Masukkan Jam Keluar (contoh 17.5): ";
                    cin >> jamKeluar;

                    double lamaParkir = jamKeluar - parkir[targetSlot].jamMasuk;
                    
                    if (lamaParkir < 0) {
                        lamaParkir += 24.0;
                    }

                    int durasiJam = (int)lamaParkir;
                    if (lamaParkir > durasiJam) {
                        durasiJam++;
                    }
                    
		    if (durasiJam < 1) {
			durasiJam = 1;
		    }

                    int biaya = 0;
                    string jenis = parkir[targetSlot].jenis;

                    if (jenis == "motor" || jenis == "Motor") {
                        if (durasiJam <= 2) biaya = 3000;
                        else biaya = 3000 + (durasiJam - 2) * 2000;
                    } else if (jenis == "mobil" || jenis == "Mobil") {
                        if (durasiJam <= 2) biaya = 5000;
                        else biaya = 5000 + (durasiJam - 2) * 3000;
                    }

                    if (durasiJam > 8) {
                        biaya = biaya * 90 / 100;
                    }

                    totalPendapatan += biaya;
                    totalTransaksi++;
                    parkir[targetSlot].isi = false;

                    cout << "--- Struk Checkout ---" << endl;
                    cout << "Slot Dikosongkan : Nomor " << (targetSlot + 1) << endl;
                    cout << "Durasi Parkir    : " << durasiJam << " jam" << endl;
                    cout << "Total Biaya      : Rp" << biaya << endl;
                }
                break;
            }

            case 3: {
                int terisi = 0;
                for (int i = 0; i < 20; i++) {
                    if (parkir[i].isi) terisi++;
                }
                int tersedia = 20 - terisi;

                cout << "\n--- LAPORAN PARKIR HARIAN ---" << endl;
                cout << "Ruang Terisi     : " << terisi << " slot" << endl;
                cout << "Ruang Tersedia   : " << tersedia << " slot" << endl;
                cout << "Transaksi Selesai: " << totalTransaksi << endl;
                cout << "Total Pendapatan : Rp" << totalPendapatan << endl;
                break;
            }

            case 4:
                cout << "Program selesai. Terima kasih!" << endl;
                break;

            default:
                cout << "Pilihan tidak valid, silakan coba lagi." << endl;
                break;
        }

    } while (pilihan != 4);

    return 0;
}
