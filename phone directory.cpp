#include <iostream>
#include <fstream>
#include <string>
#include <limits>

class PhoneBook {
    int srno;
    char name[25];
    char mobile[15];
    char email[30];
    char group[20];

public:
    int getSrNo() const { return srno; }

    void storeData() {
        std::cout << "\n...............CREATE NEW PHONE RECORD...............\n";
        std::cout << "Enter Serial Number: ";
        while (!(std::cin >> srno) || srno <= 0) {
            std::cout << "Invalid input. Enter a positive integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore();
        std::cout << "Enter Record Name: ";
        std::cin.getline(name, 25);
        std::cout << "Enter Mobile Number: ";
        std::cin.getline(mobile, 15);
        std::cout << "Enter E-Mail ID: ";
        std::cin.getline(email, 30);
        std::cout << "Enter Record Group: ";
        std::cin.getline(group, 20);
        std::cout << std::endl;
    }

    void showData() const {
        std::cout << "\n...............PHONE BOOK RECORD...............\n";
        std::cout << "Sr. No.    : " << srno << std::endl;
        std::cout << "Name       : " << name << std::endl;
        std::cout << "Mobile No. : " << mobile << std::endl;
        std::cout << "Email ID   : " << email << std::endl;
        std::cout << "Group      : " << group << std::endl;
    }
};

// Function to add a new contact to the binary file
void AddNumber() {
    PhoneBook record;
    std::ofstream fout("PhoneBook.dat", std::ios::out | std::ios::binary | std::ios::app);
    if (!fout) {
        std::cout << "Error opening file!\n";
        return;
    }
    record.storeData();
    fout.write(reinterpret_cast<char*>(&record), sizeof(record));
    fout.close();
    std::cout << "\nRecord Saved to File......\n";
}

// Function to display all contacts
void DisplayRecords() {
    PhoneBook record;
    std::ifstream fin("PhoneBook.dat", std::ios::in | std::ios::binary);
    if (!fin) {
        std::cout << "Error opening file or file does not exist!\n";
        return;
    }
    while (fin.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        record.showData();
    }
    fin.close();
    std::cout << "\nReading of Data File Completed......\n";
}

// Function to search for a contact by serial number
void SearchBySrNo() {
    PhoneBook record;
    int n, flag = 0;
    std::ifstream fin("PhoneBook.dat", std::ios::in | std::ios::binary);
    if (!fin) {
        std::cout << "Error opening file or file does not exist!\n";
        return;
    }
    std::cout << "Enter Serial Number of Record To Display: ";
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid input. Enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (fin.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        if (n == record.getSrNo()) {
            record.showData();
            flag++;
            std::cout << "\n\n.....Record Found and Displayed......\n";
        }
    }
    fin.close();
    if (flag == 0)
        std::cout << "\nThe Record of Serial Number " << n << " is not in file....\n";
    std::cout << "\nReading of Data File Completed......\n";
}

// Function to delete a contact by serial number
void deleteRecord() {
    PhoneBook record;
    int n, flag = 0;
    std::ifstream fin("PhoneBook.dat", std::ios::in | std::ios::binary);
    std::ofstream fout("temp.dat", std::ios::out | std::ios::binary);
    if (!fin || !fout) {
        std::cout << "Error opening file!\n";
        return;
    }
    std::cout << "Enter Serial Number of Record To Delete: ";
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid input. Enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (fin.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        if (n == record.getSrNo()) {
            std::cout << "\nThe Following record is deleted....\n";
            record.showData();
            flag++;
        } else {
            fout.write(reinterpret_cast<char*>(&record), sizeof(record));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        std::cout << "\nThe Record of Serial Number " << n << " is not in file....\n";
    else {
        remove("PhoneBook.dat");
        rename("temp.dat", "PhoneBook.dat");
    }
    std::cout << "\nReading of Data File Completed......\n";
}

// Function to modify a contact by serial number
void modifyRecord() {
    PhoneBook record;
    std::fstream fio("PhoneBook.dat", std::ios::in | std::ios::out | std::ios::binary);
    if (!fio) {
        std::cout << "Error opening file or file does not exist!\n";
        return;
    }
    int n, flag = 0;
    std::cout << "Enter Serial Number of Record To Modify: ";
    while (!(std::cin >> n) || n <= 0) {
        std::cout << "Invalid input. Enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (fio.read(reinterpret_cast<char*>(&record), sizeof(record))) {
        std::streampos pos = fio.tellg();
        if (n == record.getSrNo()) {
            std::cout << "\nThe Following record will be modified....\n";
            record.showData();
            flag++;
            std::cout << "\nRe-Enter the New Details.....\n";
            record.storeData();
            fio.seekp(pos - sizeof(record));
            fio.write(reinterpret_cast<char*>(&record), sizeof(record));
            std::cout << "\n....Data Modified Successfully....\n";
        }
    }
    fio.close();
    if (flag == 0)
        std::cout << "\nThe Record of Serial Number " << n << " is not in file....\n";
    std::cout << "\nReading of Data File Completed......\n";
}

// Function to display the menu and handle user choices
void menu() {
    int ch;
    do {
        system("cls"); // Use "clear" for Unix-based systems
        std::cout << "............................................\n";
        std::cout << "           PHONE BOOK MANAGEMENT\n";
        std::cout << "............................................\n\n";
        std::cout << "::::::::::::::: PROGRAM MENU :::::::::::::::\n";
        std::cout << "0. Exit\n";
        std::cout << "1. Save New Phone Record\n";
        std::cout << "2. Display All Saved Records\n";
        std::cout << "3. Search Specific Record\n";
        std::cout << "4. Delete Specific Record\n";
        std::cout << "5. Modify Existing Record\n";
        std::cout << "Enter Your Choice: ";
        while (!(std::cin >> ch)) {
            std::cout << "Invalid input. Enter a number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        system("cls"); // Use "clear" for Unix-based systems
        switch (ch) {
            case 1: AddNumber(); break;
            case 2: DisplayRecords(); break;
            case 3: SearchBySrNo(); break;
            case 4: deleteRecord(); break;
            case 5: modifyRecord(); break;
            case 0: std::cout << "Exiting Program...\n"; break;
            default: std::cout << "Invalid Choice!\n"; break;
        }
        if (ch != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (ch != 0);
}

int main() {
    menu();
    return 0;
}