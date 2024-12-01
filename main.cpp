#include <bits/stdc++.h>
using namespace std;

const int MAX_DOCTORS = 5;
const int MAX_APPOINTMENTS = 10;
const char DELIMITER = '|';

// Define structures
struct Doctor {
    char doctorID[15];
    char doctorName[30];
    char address[30];
};

struct Appointment {
    char appointmentID[15];
    char appointmentDate[30];
    char doctorID[15];
};

// Define index structures
struct PrimaryIndex {
    char ID[15];
    int position;
    bool operator<(const PrimaryIndex &r) const {
        return strcmp(ID, r.ID) < 0;
    }
};

struct SecondaryIndexID {
    char ID[15];
    vector<Appointment> appointments;
    bool operator<(const SecondaryIndexID &r) const { // for the sort function
        return strcmp(ID, r.ID) < 0;

    }
};

struct SecondaryIndexName {
    char Name[30];
    vector <string> IDs;
    bool operator<(const SecondaryIndexName &r) const { // for the sort function
        return strcmp(Name, r.Name) < 0;

    }
};

// Globals
vector<Doctor> doctors;
vector<Appointment> appointments;
vector<PrimaryIndex> doctorPrimaryIndex;
vector<PrimaryIndex> appointmentPrimaryIndex;
vector<SecondaryIndexName> doctorNameSecondaryIndex;
vector<SecondaryIndexID> doctorIDSecondaryIndexForAppointments;
vector<int> doctorAvailList;
vector<int> appointmentAvailList;

// Function declarations
void addDoctor();
void addAppointment();
void updateDoctorName();
void updateAppointmentDate();
void deleteAppointment();
void deleteDoctor();
void printDoctorInfo();
void printAppointmentInfo();
void loadDoctors();
void loadAppointments();
void saveDoctors();
void saveAppointments();
int findDoctorIndex(const char* doctorID);
int findAppointmentIndex(const char* appointmentID);
void displayMenu();
void processQuery();
void buildIndexes();
void saveIndexes();
void loadIndexes();
void insertPrimaryIndex(vector<PrimaryIndex>& index, const char* key, int position);
int binarySearchPrimaryIndex(const vector<PrimaryIndex>& index, const char* key);
void insertSecondaryIndexIDDoc(vector<SecondaryIndexID>& index, const char* key, int position);
void insertSecondaryIndexName(vector<SecondaryIndexName>& index, const char* key, int position);
vector<int> searchSecondaryIndex(const vector<SecondaryIndexID>& index, const char* key);

int main() {
    loadDoctors();
    loadAppointments();
//    loadIndexes();
    buildIndexes();
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: addDoctor(); break;
            case 2: addAppointment(); break;
            case 3: updateDoctorName(); break;
            case 4: updateAppointmentDate(); break;
            case 5: deleteAppointment(); break;
            case 6: deleteDoctor(); break;
            case 7: printDoctorInfo(); break;
            case 8: printAppointmentInfo(); break;
            case 9: processQuery(); break;
            case 10: break; // Exit
            default: cout << "Invalid choice. Please try again." << "\n";
        }
    } while (choice != 10);

    saveDoctors();
    saveAppointments();
//    saveIndexes();
    return 0;
}

// Display menu
void displayMenu() {
    cout << "Welcome to the Healthcare Management System" << "\n";
    cout << "1. Add New Doctor" << "\n";
    cout << "2. Add New Appointment" << "\n";
    cout << "3. Update Doctor Name (Doctor ID)" << "\n";
    cout << "4. Update Appointment Date (Appointment ID)" << "\n";
    cout << "5. Delete Appointment (Appointment ID)" << "\n";
    cout << "6. Delete Doctor (Doctor ID)" << "\n";
    cout << "7. Print Doctor Info (Doctor ID)" << "\n";
    cout << "8. Print Appointment Info (Appointment ID)" << "\n";
    cout << "9. Write Query" << "\n";
    cout << "10. Exit" << "\n";
    cout << "Enter your choice: ";
}

// Load doctors from file
void loadDoctors() {
    ifstream file("doctors.txt");
    if (!file) return;

    Doctor doc;
    while (file.getline(doc.doctorID, 15, DELIMITER) &&
           file.getline(doc.doctorName, 30, DELIMITER) &&
           file.getline(doc.address, 30)) {
        doctors.push_back(doc);
    }
    file.close();
}

// Load appointments from file
void loadAppointments() {
    ifstream file("appointments.txt");
    if (!file) return;

    Appointment appt;
    while (file.getline(appt.appointmentID, 15, DELIMITER) &&
           file.getline(appt.appointmentDate, 30, DELIMITER) &&
           file.getline(appt.doctorID, 15)) {
        appointments.push_back(appt);
    }
    file.close();
}

// Save doctors to file
void saveDoctors() {
    ofstream file("doctors.txt");
    for (const auto& doc : doctors) {
        file << doc.doctorID << DELIMITER
             << doc.doctorName << DELIMITER
             << doc.address << "\n";
    }
    file.close();
}

// Save appointments to file
void saveAppointments() {
    ofstream file("appointments.txt");
    for (const auto& appt : appointments) {
        file << appt.appointmentID << DELIMITER
             << appt.appointmentDate << DELIMITER
             << appt.doctorID << "\n";
    }
    file.close();
}

// Find doctor index using primary index
int findDoctorIndex(const char* doctorID) {
    int index = binarySearchPrimaryIndex(doctorPrimaryIndex, doctorID);
    return (index == -1) ? -1 : doctorPrimaryIndex[index].position;
}

// Find appointment index using primary index
int findAppointmentIndex(const char* appointmentID) {
    int index = binarySearchPrimaryIndex(appointmentPrimaryIndex, appointmentID);
    return (index == -1) ? -1 : appointmentPrimaryIndex[index].position;
}

void insertPrimaryIndex(vector<PrimaryIndex>& primaryIndex, const char* key, int position) {
    int idx = binarySearchPrimaryIndex(primaryIndex, key);

    if (idx != -1) {
        cout << "Error: Primary key already exists in the index." << endl;
        return;
    }

    // Create a new PrimaryIndex entry
    PrimaryIndex newEntry;
    strcpy(newEntry.ID, key);
    newEntry.position = position;

    // Insert the new entry
    primaryIndex.push_back(newEntry);

    // Sort the primary index to maintain order by ID
    sort(primaryIndex.begin(), primaryIndex.end());

    cout << "Primary index updated successfully." << endl;
}


// Add new doctor
void addDoctor() {
    if (doctors.size() >= MAX_DOCTORS) {
        cout << "Cannot add more doctors. Maximum limit reached." << endl;
        return;
    }

    Doctor newDoctor;
    cout << "Enter Doctor ID: ";
    cin >> newDoctor.doctorID;
    if (findDoctorIndex(newDoctor.doctorID) != -1) {
        cout << "Doctor ID already exists." << endl;
        return;
    }
    cout << "Enter Doctor Name: ";
    cin.ignore();
    cin.getline(newDoctor.doctorName, 30);
    cout << "Enter Address: ";
    cin.getline(newDoctor.address, 30);

    int position;
    if (!doctorAvailList.empty()) {
        position = doctorAvailList.back();
        doctorAvailList.pop_back();
        doctors[position] = newDoctor;
    } else {
        position = doctors.size();
        doctors.push_back(newDoctor);
    }

    // Update indexes
    insertPrimaryIndex(doctorPrimaryIndex, newDoctor.doctorID, position);
    // replace with search with secondary index method
    auto it = find_if(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end(),
                      [&](const SecondaryIndexName &index) {
                          return strcmp(index.Name, newDoctor.doctorName) == 0;
                      });
    if (it != doctorNameSecondaryIndex.end()) {
        // If the name already exists, add the new doctor ID to the list
        it->IDs.emplace_back(newDoctor.doctorID);
    } else {
        // Otherwise, create a new entry
        SecondaryIndexName newNameEntry;
        strcpy(newNameEntry.Name, newDoctor.doctorName);
        newNameEntry.IDs.emplace_back(newDoctor.doctorID);
        doctorNameSecondaryIndex.push_back(newNameEntry);
    }
    sort(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end());

    // Update Secondary Index for Doctor IDs and Appointments

    SecondaryIndexID newIDEntry;
    strcpy(newIDEntry.ID, newDoctor.doctorID);
    doctorIDSecondaryIndexForAppointments.push_back(newIDEntry);

    sort(doctorIDSecondaryIndexForAppointments.begin(), doctorIDSecondaryIndexForAppointments.end());


    cout << "Doctor added successfully." << endl;
}


// Add new appointment
void addAppointment() {
    if (appointments.size() >= MAX_APPOINTMENTS) {
        cout << "Cannot add more appointments. Maximum limit reached." << "\n";
        return;
    }

    Appointment newAppointment;
    cout << "Enter Appointment ID: ";
    cin >> newAppointment.appointmentID;
    if (findAppointmentIndex(newAppointment.appointmentID) != -1) {
        cout << "Appointment ID already exists." << "\n";
        return;
    }
    cout << "Enter Appointment Date: ";
    cin.ignore();
    cin.getline(newAppointment.appointmentDate, 30);
    cout << "Enter Doctor ID: ";
    cin >> newAppointment.doctorID;
    if (findDoctorIndex(newAppointment.doctorID) == -1) {
        cout << "Doctor ID does not exist." << "\n";
        return;
    }

    int position;
    if (!appointmentAvailList.empty()) {
        position = appointmentAvailList.back();
        appointmentAvailList.pop_back();
        appointments[position] = newAppointment;
    } else {
        position = appointments.size();
        appointments.push_back(newAppointment);
    }

    // Update Primary Index for Appointments
    insertPrimaryIndex(appointmentPrimaryIndex, newAppointment.appointmentID, position);

    // Update Secondary Index for Doctor IDs and Appointments
    auto it = find_if(doctorIDSecondaryIndexForAppointments.begin(), doctorIDSecondaryIndexForAppointments.end(),
                      [&](const SecondaryIndexID &index) {
                          return strcmp(index.ID, newAppointment.doctorID) == 0;
                      });

    it->appointments.push_back(newAppointment);

    // Sort the Secondary Index
    sort(doctorIDSecondaryIndexForAppointments.begin(), doctorIDSecondaryIndexForAppointments.end());

    cout << "Appointment added successfully." << "\n";
}

// Update doctor name
void updateDoctorName() {
    char doctorID[15];
    cout << "Enter Doctor ID to update: ";
    cin >> doctorID;
    int index = findDoctorIndex(doctorID);
    if (index == -1) {
        cout << "Doctor ID not found." << "\n";
        return;
    }
    // Save the old name for updating the secondary index
    char oldDoctorName[30];
    strcpy(oldDoctorName, doctors[index].doctorName);

    cout << "Enter new Doctor Name: ";
    cin.ignore();
    cin.getline(doctors[index].doctorName, 30);
    // Update the secondary index for the doctor name
    // replace with secondary index for doctor name
    auto it = find_if(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end(),
                      [&](const SecondaryIndexName &entry) {
                          return strcmp(entry.Name, oldDoctorName) == 0;
                      });

    if (it != doctorNameSecondaryIndex.end()) {
        // Remove the doctor ID from the old name's entry
        auto &oldIDs = it->IDs;
        oldIDs.erase(remove(oldIDs.begin(), oldIDs.end(), doctorID), oldIDs.end());

        // If no more doctor IDs are associated with the old name, remove the entry
        if (oldIDs.empty()) {
            doctorNameSecondaryIndex.erase(it);
        }
    }

    // Add the doctor ID to the new name's entry
    auto newIt = find_if(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end(),
                         [&](const SecondaryIndexName &entry) {
                             return strcmp(entry.Name, doctors[index].doctorName) == 0;
                         });

    if (newIt != doctorNameSecondaryIndex.end()) {
        // If the new name already exists, add the doctor ID to its list
        newIt->IDs.push_back(doctorID);
    } else {
        // Otherwise, create a new entry for the new name
        SecondaryIndexName newEntry;
        strcpy(newEntry.Name, doctors[index].doctorName);
        newEntry.IDs.push_back(doctorID);
        doctorNameSecondaryIndex.push_back(newEntry);
    }

    // Sort the secondary index to maintain order
    sort(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end());

    cout << "Doctor Name updated successfully in records and indexes." << "\n";
}

// Delete doctor
void deleteDoctor() {
    char doctorID[15];
    cout << "Enter Doctor ID to delete: ";
    cin >> doctorID;
    int index = findDoctorIndex(doctorID);
    if (index == -1) {
        cout << "Doctor ID not found." << "\n";
        return;
    }

    doctors[index].doctorID[0] = '*'; // Mark as deleted
    doctorAvailList.push_back(index);
    cout << "Doctor marked as deleted." << "\n";
}

int binarySearchPrimaryIndex(const vector<PrimaryIndex>& primaryIndex, const char* key) {
    int low = 0;
    int high = primaryIndex.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Compare the key with the mid element
        int comparison = strcmp(primaryIndex[mid].ID, key);

        if (comparison == 0) {
            // Key found, return the position
            return mid;
        } else if (comparison < 0) {
            // Key is greater than mid element, search in the right half
            low = mid + 1;
        } else {
            // Key is smaller than mid element, search in the left half
            high = mid - 1;
        }
    }

    // Key not found
    return -1;
}
