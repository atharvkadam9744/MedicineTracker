#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>

using namespace std;

class User {

public:

    string username;
    string password;

    void registerUser() {

        cout << "\n===== REGISTER =====\n";

        cout << "Enter Username: ";
        cin >> username;

        cout << "Enter Password: ";
        cin >> password;

        ofstream file("users.txt", ios::app);

        file << username << " " << password << endl;

        file.close();

        cout << "\nRegistration Successful!\n";
    }

    bool loginUser() {

        string u, p;
        string storedUser, storedPass;

        cout << "\n===== LOGIN =====\n";

        cout << "Enter Username: ";
        cin >> u;

        cout << "Enter Password: ";
        cin >> p;

        ifstream file("users.txt");

        while(file >> storedUser >> storedPass) {

            if(u == storedUser && p == storedPass) {

                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }
};

class Medicine {

public:

    string name;
    string medTime;
    string dose;

    void addMedicine() {

        cin.ignore();

        cout << "\n===== ADD MEDICINE =====\n";

        cout << "Enter Medicine Name: ";
        getline(cin, name);

        cout << "Enter Time (Example 09:00AM): ";
        getline(cin, medTime);

        cout << "Enter Dose: ";
        getline(cin, dose);

        ofstream file("medicines.txt", ios::app);

        file << name << "|"
             << medTime << "|"
             << dose << endl;

        file.close();

        cout << "\nMedicine Added Successfully!\n";
    }

    void viewMedicines() {

        ifstream file("medicines.txt");

        string line;

        cout << "\n===== MEDICINE LIST =====\n";

        bool empty = true;

        while(getline(file, line)) {

            cout << line << endl;
            empty = false;
        }

        if(empty) {

            cout << "No Medicines Found.\n";
        }

        file.close();
    }

    void checkReminder() {

        time_t now = std::time(0);

        tm *ltm = localtime(&now);

        int hour = ltm->tm_hour;
        int minute = ltm->tm_min;

        string ampm = "AM";

        if(hour >= 12) {

            ampm = "PM";
        }

        if(hour > 12) {

            hour -= 12;
        }

        if(hour == 0) {

            hour = 12;
        }

        string currentTime;

        if(minute < 10) {

            currentTime =
                to_string(hour) + ":0" +
                to_string(minute) + ampm;
        }

        else {

            currentTime =
                to_string(hour) + ":" +
                to_string(minute) + ampm;
        }

        ifstream file("medicines.txt");

        string line;

        bool found = false;

        while(getline(file, line)) {

            int first = line.find('|');

            int second =
                line.find('|', first + 1);

            string medName =
                line.substr(0, first);

            string medicineTime =
                line.substr(first + 1,
                second - first - 1);

            string medDose =
                line.substr(second + 1);

            if(currentTime == medicineTime) {

                cout << "\n===========================\n";

                cout << " MEDICINE REMINDER ALERT\n";

                cout << "===========================\n";

                cout << "Medicine : "
                     << medName << endl;

                cout << "Dose     : "
                     << medDose << endl;

                cout << "Time     : "
                     << medicineTime << endl;

                cout << "===========================\n";

                found = true;
            }
        }

        if(!found) {

            cout << "\nNo medicine reminder at this time.\n";
        }

        file.close();
    }

    void deleteMedicine() {

        ifstream file("medicines.txt");

        ofstream temp("temp.txt");

        string line;

        string deleteName;

        cin.ignore();

        cout << "\nEnter Medicine Name to Delete: ";

        getline(cin, deleteName);

        bool found = false;

        while(getline(file, line)) {

            int first = line.find('|');

            string medName =
                line.substr(0, first);

            if(medName != deleteName) {

                temp << line << endl;
            }

            else {

                found = true;
            }
        }

        file.close();

        temp.close();

        remove("medicines.txt");

        rename("temp.txt", "medicines.txt");

        if(found) {

            cout << "\nMedicine Deleted Successfully!\n";
        }

        else {

            cout << "\nMedicine Not Found.\n";
        }
    }

    void updateMedicine() {

        ifstream file("medicines.txt");

        ofstream temp("temp.txt");

        string line;

        string updateName;

        cin.ignore();

        cout << "\nEnter Medicine Name to Update: ";

        getline(cin, updateName);

        bool found = false;

        while(getline(file, line)) {

            int first = line.find('|');

            string medName =
                line.substr(0, first);

            if(medName == updateName) {

                found = true;

                string newName;
                string newTime;
                string newDose;

                cout << "\nEnter New Medicine Name: ";
                getline(cin, newName);

                cout << "Enter New Time: ";
                getline(cin, newTime);

                cout << "Enter New Dose: ";
                getline(cin, newDose);

                temp << newName << "|"
                     << newTime << "|"
                     << newDose << endl;
            }

            else {

                temp << line << endl;
            }
        }

        file.close();

        temp.close();

        remove("medicines.txt");

        rename("temp.txt", "medicines.txt");

        if(found) {

            cout << "\nMedicine Updated Successfully!\n";
        }

        else {

            cout << "\nMedicine Not Found.\n";
        }
    }
};

void menu() {

    cout << "\n========== MEDICINE TRACKER ==========\n";

    cout << "1. Add Medicine\n";

    cout << "2. View Medicines\n";

    cout << "3. Check Reminder\n";

    cout << "4. Delete Medicine\n";

    cout << "5. Update Medicine\n";

    cout << "6. Exit\n";
}

int main() {

    User user;

    Medicine med;

    int choice;

    cout << "========== MEDICINE TRACKER ==========\n";

    cout << "1. Register\n";

    cout << "2. Login\n";

    cout << "Enter Choice: ";

    cin >> choice;

    if(choice == 1) {

        user.registerUser();
    }

    else if(choice == 2) {

        if(user.loginUser()) {

            cout << "\nLogin Successful!\n";

            int option;

            while(true) {

                menu();

                cout << "\nEnter Option: ";

                cin >> option;

                if(option == 1) {

                    med.addMedicine();
                }

                else if(option == 2) {

                    med.viewMedicines();
                }

                else if(option == 3) {

                    med.checkReminder();
                }

                else if(option == 4) {

                    med.deleteMedicine();
                }

                else if(option == 5) {

                    med.updateMedicine();
                }

                else if(option == 6) {

                    cout << "\nThank You For Using Medicine Tracker!\n";

                    break;
                }

                else {

                    cout << "\nInvalid Option.\n";
                }
            }
        }

        else {

            cout << "\nInvalid Username or Password.\n";
        }
    }

    else {

        cout << "\nInvalid Choice.\n";
    }

    return 0;
}