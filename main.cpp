#include <bits/stdc++.h>
#include <fstream>
using namespace std;

const char DELIMITER = '|';
short headerappointment;
short headerdoctor;

// Define structures
struct Doctor {
    char doctorID[15];
    char doctorName[30];
    char address[30];
    short header;
};

struct Appointment {
    char appointmentID[15];
    char appointmentDate[30];
    char doctorID[15];
    short header;
};

// Define index structures
struct PrimaryIndex {
    char ID[15];
    int offset; // Offset in the data file
    bool operator<(const PrimaryIndex &r) const {
        return strcmp(ID, r.ID) < 0;
    }
};

struct SecondaryIndexName {
    char Name[30] = " ";
    char ID[15];
    bool operator<(const SecondaryIndexName &r) const {
        return strcmp(Name, r.Name) < 0;
    }
};

struct SecondaryIndexID {
    char ID[15] = " ";
    char appointmentsID[15] ; // Appointment offsets
    bool operator<(const SecondaryIndexID &r) const {
        return strcmp(ID, r.ID) < 0;
    }
};



vector<PrimaryIndex> doctorPrimaryIndex;
vector<PrimaryIndex> appointmentPrimaryIndex;
vector<SecondaryIndexName> doctorNameSecondaryIndex;
vector<SecondaryIndexID> doctorIDSecondaryIndexForAppointments;



// Function declarations
void addDoctor();
void addAppointment();
void updateDoctorName();
void updateAppointmentDate();
void deleteAppointment();
void deleteDoctor();
int findDoctorOffset(const char* doctorID);
int findAppointmentOffset(const char* appointmentID);
void displayMenu();
void processQuery();
void loadIndexes();
void loadheader();
int main() {
    loadIndexes();
    loadheader();

    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1: addDoctor(); break;
            case 2: addAppointment(); break;
            case 3: updateDoctorName(); break;
//            case 4: updateAppointmentDate(); break;
//           case 5: deleteAppointment(); break;
//            case 6: deleteDoctor(); break;
                //  case 7: printDoctorInfo(); break;
                //case 8: printAppointmentInfo(); break;
//            case 9: processQuery(); break;
            case 10: break; // Exit
            default: cout << "Invalid choice. Please try again." << "\n";
        }
    } while (choice != 10);
    cout<<headerdoctor<<" "<<headerdoctor<<"";

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
//load header
void loadheader(){
    fstream file("appointments.txt", ios::in);
    fstream outfile("doctors.txt", ios::in);
    file>>headerappointment;
    outfile>>headerdoctor;
}
//load indexs
void loadIndexes() {
    // Open Primary Index File for Doctors
    fstream doctorPrimaryIndexFile("doctor_primary_index.txt", ios::in | ios::binary);
    if (!doctorPrimaryIndexFile.is_open()) {
        cerr << "Error: Could not open appointment primary index file!" << endl;
        return;
    }
    while (!doctorPrimaryIndexFile.eof()) {
        PrimaryIndex tempIndex;
        doctorPrimaryIndexFile >> tempIndex.ID >> tempIndex.offset;

        if (doctorPrimaryIndexFile.fail()) break; // Handle EOF or bad input

        doctorPrimaryIndex.push_back(tempIndex);
    }
    doctorPrimaryIndexFile.close();
    cout << "Loaded " << doctorPrimaryIndex.size() << " doctor primary index records." << endl;

    // Open Primary Index File for Appointments
    fstream appointmentPrimaryIndexFile("appointment_primary_index.txt", ios::in | ios::binary);
    if (!appointmentPrimaryIndexFile.is_open()) {
        cerr << "Error: Could not open appointment primary index file!" << endl;
        return;
    }

    while (!appointmentPrimaryIndexFile.eof()) {
        PrimaryIndex tempIndex;
        appointmentPrimaryIndexFile >> tempIndex.ID >> tempIndex.offset;

        if (appointmentPrimaryIndexFile.fail()) break; // Handle EOF or bad input

        appointmentPrimaryIndex.push_back(tempIndex);
    }

    appointmentPrimaryIndexFile.close();

    cout << "Loaded " << appointmentPrimaryIndex.size() << " appointment primary index records." << endl;

    // Open Secondary Index File for Doctor Names
    fstream doctorNameSecondaryIndexFile("doctor_name_secondary_index.txt", ios::in | ios::binary);
    if (!doctorNameSecondaryIndexFile.is_open()) {
        cerr << "Error: Could not open doctor Name Secondary Index File!" << endl;
        return;
    }

    while (!doctorNameSecondaryIndexFile.eof()) {
        SecondaryIndexName temdoctor;
        doctorNameSecondaryIndexFile >> temdoctor.Name>> temdoctor.ID;

        if (doctorNameSecondaryIndexFile.fail()) break; // Handle EOF or bad input

        doctorNameSecondaryIndex.push_back(temdoctor);
    }

    doctorNameSecondaryIndexFile.close();

    cout << "Loaded " << doctorNameSecondaryIndex.size() << " doctor name secondary index records." << endl;

    // Open Secondary Index File for Doctor IDs and Appointments
    fstream doctorIDSecondaryIndexFile("doctor_id_secondary_index.txt", ios::in | ios::binary);
    if (!doctorIDSecondaryIndexFile.is_open()) {
        cerr << "Error: Could not open doctor id Secondary Index File!" << endl;
        return;
    }

    while (!doctorIDSecondaryIndexFile.eof()) {
        SecondaryIndexID temapp;
        doctorNameSecondaryIndexFile >> temapp.appointmentsID>> temapp.ID;
        if (doctorNameSecondaryIndexFile.fail()) break; // Handle EOF or bad input

        doctorIDSecondaryIndexForAppointments.push_back(temapp);
    }

    doctorNameSecondaryIndexFile.close();

    cout << "Loaded " << doctorIDSecondaryIndexForAppointments.size() << " doctor id secondary index records." << endl;



    cout << "All indexes loaded successfully." << endl;
}
//return offset of appointment
int binarySearchPrimaryIndex_appointment(const vector<PrimaryIndex>& primaryIndex,const string &appointmentID) {

    int low = 0, high = primaryIndex.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        int comparison = strcmp(appointmentID.c_str(), primaryIndex[mid].ID);

        if (comparison == 0) {
            return primaryIndex[mid].offset;
        } else if (comparison < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}
//return offset of doctor
int binarySearchPrimaryIndex_doctor(const vector<PrimaryIndex>& primaryIndex,const string &doctorID) {

    int low = 0, high = primaryIndex.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        int comparison = strcmp(doctorID.c_str(), primaryIndex[mid].ID);

        if (comparison == 0) {
            return primaryIndex[mid].offset;
        } else if (comparison < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}
// Find doctor index using primary index
int findDoctorOffset(const char* doctorID) {
    return  binarySearchPrimaryIndex_doctor(doctorPrimaryIndex, doctorID);
}

// Find appointment index using primary index
int findAppointmentOffset(const char* appointmentID) {

    return binarySearchPrimaryIndex_appointment(appointmentPrimaryIndex, appointmentID);
}
static bool comparePrimaryIndexByID(const PrimaryIndex& a, const PrimaryIndex& b) {
    return strcmp(a.ID, b.ID) < 0; // Compare IDs lexicographically
}
// Add new appointment
void addAppointment() {
    Appointment newAppointment;
    cout << "Enter Appointment ID: ";
    cin >> newAppointment.appointmentID;
    if (findAppointmentOffset(newAppointment.appointmentID) != -1) {
        cout << "Appointment ID already exists." << "\n";
        return;
    }
    cout << "Enter Appointment Date: ";
    cin.ignore();

    cin.getline(newAppointment.appointmentDate, 30);
    cout << "Enter Doctor ID: ";
    cin.getline(newAppointment.doctorID, 15);
    if (findDoctorOffset(newAppointment.doctorID) == -1) {
        cout << "Doctor ID does not exist." << "\n";
        return;
    }

    string record =  string(newAppointment.appointmentID) + DELIMITER +
                     string(newAppointment.appointmentDate) + DELIMITER +
                     string(newAppointment.doctorID)+ DELIMITER;
    fstream appointmentFile("appointments.txt",ios::app);
    if(appointmentFile.is_open()){
        appointmentFile.seekp(0,ios::end);
        int sizefile=appointmentFile.tellg();
        if(sizefile==0){
            appointmentFile<<-1<<'|';
            headerappointment=-1;

        }

    }
    short size = 3 + strlen(newAppointment.appointmentID) + strlen(newAppointment.appointmentDate) +
               strlen(newAppointment.doctorID);

    appointmentFile << size;
    appointmentFile.seekp(0, ios::end);
    int offset = appointmentFile.tellp();
    //search
    sort(appointmentPrimaryIndex.begin(), appointmentPrimaryIndex.end(), comparePrimaryIndexByID);
    //primary
    fstream appointmentPrimaryIndexFile("appointment_primary_index.txt", ios::out | ios::app | ios::binary);
    PrimaryIndex newIndex;
    strcpy(newIndex.ID, newAppointment.appointmentID);
    newIndex.offset = offset;
    appointmentPrimaryIndex.push_back(newIndex);
    appointmentPrimaryIndexFile<<newAppointment.appointmentID<<" "<<offset<<endl;
    //secondary
    fstream appointmentSecondaryIndexFile("doctor_id_secondary_index.txt", ios::out | ios::app | ios::binary);
    SecondaryIndexID newapp;
    strcpy(newapp.appointmentsID, newAppointment.appointmentID);
    strcpy(newapp.ID, newAppointment.doctorID);
    doctorIDSecondaryIndexForAppointments.push_back(newapp);
    appointmentSecondaryIndexFile<<newapp.appointmentsID<<" "<<newAppointment.doctorID<<endl;
    appointmentFile<< record;

}



//add doctor
void addDoctor() {
    Doctor newDoctor;
    cout << "Enter Doctor ID: ";
    cin >> newDoctor.doctorID;
    if (findDoctorOffset(newDoctor.doctorID) != -1) {
        cout << "Doctor ID already exists." << "\n";
        return;
    }
    cout << "Enter Doctor Name: ";
    cin.ignore();

    cin.getline(newDoctor.doctorName, 30);
    cout << "Enter Doctor Address: ";
    cin.getline(newDoctor.address, 30);

    string record =  string(newDoctor.doctorID) + DELIMITER +
                     string(newDoctor.doctorName) + DELIMITER +
                     string(newDoctor.address)+ DELIMITER;
    fstream doctorFile("doctors.txt",ios::app);
    if(doctorFile.is_open()){
        doctorFile.seekp(0,ios::end);
        int sizefile=doctorFile.tellg();
        if(sizefile==0){
            doctorFile<<-1<<'|';
            headerdoctor=-1;
        }

    }
    int size = 3 + strlen(newDoctor.doctorID) + strlen(newDoctor.doctorName) +
               strlen(newDoctor.address);
    doctorFile << size;
    doctorFile.seekp(0, ios::end);
    int offset = doctorFile.tellp();
    //search
    sort(doctorPrimaryIndex.begin(), doctorPrimaryIndex.end(), comparePrimaryIndexByID);
    //primary
    fstream doctorPrimaryIndexFile("doctor_primary_index.txt", ios::out | ios::app | ios::binary);
    PrimaryIndex newIndex;
    strcpy(newIndex.ID, newDoctor.doctorID);
    newIndex.offset = offset;
    doctorPrimaryIndex.push_back(newIndex);
    doctorPrimaryIndexFile<<newDoctor.doctorID<<" "<<offset<<endl;
    //secondary name
    fstream doctorNameSecondaryIndexFile("doctor_name_secondary_index.txt", ios::out | ios::app | ios::binary);
    SecondaryIndexName newSecondary;
    strcpy(newSecondary.Name, newDoctor.doctorName);
    strcpy(newSecondary.ID, newDoctor.doctorID);
    doctorNameSecondaryIndex.push_back(newSecondary);
    doctorNameSecondaryIndexFile<<newSecondary.Name<<" "<<newSecondary.ID<<endl;
    doctorFile<< record;
}




void updateDoctorName() {
    char doctorID[15];
    cout << "Enter Doctor ID to update: ";
    cin >> doctorID;

    // Find doctor offset
    int doctorOffset = findDoctorOffset(doctorID);
    if (doctorOffset == -1) {
        cout << "Doctor ID not found.\n";
        return;
    }

    // Open file in read/write mode
    fstream doctorFile("doctors.txt", ios::in | ios::out);
    if (!doctorFile.is_open()) {
        cout << "Failed to open doctor file.\n";
        return;
    }
    doctorFile.seekg(doctorOffset, ios::beg);
    string record;
    getline(doctorFile, record);

    // Parse the record
    vector<string> fields;
    stringstream ss(record);
    string field;
    while (getline(ss, field, DELIMITER)) {
        fields.push_back(field);
    }

    if (fields.size() < 3) {
        cout << "Corrupted record found. Update aborted.\n";
        doctorFile.close();
        return;
    }

    // Display current doctor name and ask for the new name
    cout << "Current Doctor Name: " << fields[1] << endl;
    int sizecurrent=fields[1].length();
    doctorFile.seekg(0, ios::beg);
    doctorFile.seekg(doctorOffset, ios::beg);
    string newDoctorName;
    cout << "Enter New Doctor Name: ";
    cin.ignore();
    getline(cin, newDoctorName);
    doctorFile<<doctorID<<"|"<<newDoctorName;
    sizecurrent-=newDoctorName.length();
    while(sizecurrent>0){
        doctorFile<<' ';
        sizecurrent--;
    }
    doctorFile.close();
    cout << "Doctor name updated successfully.\n";



}








