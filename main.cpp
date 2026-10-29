#include <iostream>
#include <string>
using namespace std;

struct Vehicle
{
    string plate_number;
    string vehicle_type;
    bool is_occupied = false;

    int hour_in = 0;
    int minute_in = 0;
    int time_in = 0;

    int hour_out = 0;
    int minute_out = 0;
    int time_out = 0;

    int parking_duration = 0;
};

Vehicle parkingSpace[20];
float revenue = 0;
int occupiedSpaces = 0;
int availableSpaces = 20;
int completedParkingTransaction = 0;

void printChoiceMessage()
{
    cout << "Pilih hal yang ingin kamu lakukan:\n";
    cout << "[1] Kendaraan Masuk\n"
         << "[2] Kendaraan Keluar\n"
         << "[3] Tampilkan Laporan Harian\n"
         << "[4] Lihat Kondisi Parkiran Saat Ini\n"
         << "[5] Keluar Program\n";
    cout << "Pilih Opsi (1 - 5): ";

    return;
}

void choiceVehicleType(Vehicle &inputVehicle)
{
    int inputTypeVehicle;

    while (true)
    {
        cout << "Pilih Jenis Kendaraan:\n";
        cout << "[1] Motor\n"
             << "[2] Mobil\n";
        cout << "Pilih opsi (1/2): ";

        cin >> inputTypeVehicle;

        if (inputTypeVehicle == 1)
        {
            inputVehicle.vehicle_type = "Motor";
            break;
        }
        else if (inputTypeVehicle == 2)
        {
            inputVehicle.vehicle_type = "Mobil";
            break;
        }
        else
        {
            cout << "Invalid Options!!! Silakan coba lagi.\n\n";
        }
    }
}

void inputTimeIn(Vehicle &inputVehicle)
{
    char hourFormat = ':';
    cout << "Inputkan jam masuk kendaraan (HH:MM): ";
    cin >> inputVehicle.hour_in >> hourFormat >> inputVehicle.minute_in;
    inputVehicle.time_in = inputVehicle.hour_in * 60 + inputVehicle.minute_in;
}

void registerVehicle()
{
    Vehicle inputVehicle;

    cout << "Masukkan Nomor Plat Kendaraan: ";
    getline(cin >> ws, inputVehicle.plate_number);

    choiceVehicleType(inputVehicle);
    inputTimeIn(inputVehicle);
    inputVehicle.is_occupied = true;

    for (int i = 0; i < 20; i++)
    {
        if (parkingSpace[i].is_occupied == false)
        {
            parkingSpace[i] = inputVehicle;

            occupiedSpaces++;
            availableSpaces--;

            cout << "Kendaraan berhasil tercatat dalam sistem :>\n\n";
            return;
        }
    }

    cout << "Maaf, parkiran lagi penuh :(\n\n";
}

void inputTimeOut(Vehicle &inputVehicle)
{
    char hourFormat = ':';
    cout << "Inputkan jam keluar kendaraan (HH:MM): ";
    cin >> inputVehicle.hour_out >> hourFormat >> inputVehicle.minute_out;
    inputVehicle.time_out = inputVehicle.hour_out * 60 + inputVehicle.minute_out;
}

int calculateDurationParking(Vehicle currVehicle)
{
    int duration = 0;
    if (currVehicle.time_out < currVehicle.time_in)
    {
        duration = (1440 - currVehicle.time_in) + currVehicle.time_out;
    }
    else
    {
        duration = currVehicle.time_out - currVehicle.time_in;
    }

    if (duration % 60 != 0)
    {
        duration = duration / 60 + 1;
    }
    else
    {
        duration = duration / 60;
    }

    return duration;
}

float calculateParkingFees(int parkingDuration, string vehicleType)
{
    float fee = 0;
    if (vehicleType == "Motor")
    {
        if (parkingDuration < 2)
        {
            fee = 3000;
        }
        else
        {
            fee = 3000 + (parkingDuration - 2) * 2000;
        }
    }
    else if (vehicleType == "Mobil")
    {
        if (parkingDuration < 2)
        {
            fee = 5000;
        }
        else
        {
            fee = 5000 + (parkingDuration - 2) * 3000;
        }
    }

    if (parkingDuration > 8)
    {
        fee = fee - (fee * 0.10);
    }

    return fee;
}
void checkoutVehicle()
{
    bool isFound = false;
    string inputPlateNumber;

    cout << "Masukkan Nomor Plat Kendaraan: ";
    getline(cin >> ws, inputPlateNumber);

    Vehicle removeVehicle = {};

    for (int i = 0; i < 20; i++)
    {
        if (parkingSpace[i].plate_number == inputPlateNumber)
        {
            isFound = true;

            Vehicle currVehicle = parkingSpace[i];
            inputTimeOut(currVehicle);

            currVehicle.parking_duration = calculateDurationParking(currVehicle);
            int fee = calculateParkingFees(currVehicle.parking_duration, currVehicle.vehicle_type);

            revenue += fee;

            occupiedSpaces--;
            availableSpaces++;
            completedParkingTransaction++;

            parkingSpace[i] = removeVehicle;

            cout << "Checkout berhasil dengan total tarif: Rp " << fee << "\n";
            return;
        }
    }

    if (!isFound)
    {
        cout << "Kendaraan Tidak Ditemukan di Parkiran";
        return;
    }
}

void printDailyReport()
{
    cout << "Jumlah Slot Terisi       : " << occupiedSpaces << "\n"
         << "Jumlah Slot Kosong       : " << availableSpaces << "\n"
         << "Jumlah Transaksi Selesai : " << completedParkingTransaction << "\n"
         << "Total Pendapatan         : Rp" << revenue << "\n";
}

void printParkiran()
{
    for (int i = 0; i < 20; i++)
    {
        Vehicle now = parkingSpace[i];
        cout << i + 1 << "\t" << now.plate_number << "\t" << now.vehicle_type << "\t" << now.hour_in << "\t" << now.minute_in << "\t" << now.time_in << "\n";
    }
    cout << "\n";
    return;
}

int main()
{
    bool exit = false;
    cout << "=======================================\n";
    cout << "===== SISTEM REGISTRASI KENDARAAN =====\n";
    cout << "=======================================\n\n";

    while (!exit)
    {
        printChoiceMessage();
        int input;
        cin >> input;

        switch (input)
        {
        case 1:
            cout << "\n===== REGISTRASI KENDARAAN =====\n";
            registerVehicle();
            break;
        case 2:
            cout << "\n===== CHECKOUT KENDARAAN =====\n";
            checkoutVehicle();
            break;
        case 3:
            cout << "\n===== LAPORAN HARIAN PARKIR =====\n";
            printDailyReport();
            cout << "=================================\n\n";
            break;
        case 4:
            cout << "\n===== KONDISI PARKIRAN SAAR INI =====\n";
            printParkiran();
            break;
        case 5:
            cout << "byebye\n";
            exit = true;
            break;
        default:
            cout << "Invalid Options!!! Silakan pilih 1 - 5.\n\n";
            break;
        }
    }
}