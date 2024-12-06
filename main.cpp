#include <bits/stdc++.h>
#include <fstream>
using namespace std;

struct Node
{
    short offset;
    int size;
    Node *next;
};

class availlist{
private:
    Node* head ;

public:
    availlist() : head(NULL){}
    bool is_empty(){
        return head==NULL;
    }

    void insertAtBeginning(short offset , int size) {
        Node* newNode = new Node();
        newNode->offset = offset;
        newNode->size = size;
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(short offset , int size) {
        Node* newNode = new Node();
        newNode->offset = offset;
        newNode->size = size;
        newNode->next = NULL;

        if (!head) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void deleteFromBeginning() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void deleteFromOffset(short offset) {
        int position = 0 ;
        Node* test = head;
        while (test){
            if (test->offset == offset) break;
            position++;
            test = test->next;
        }


        if (position < 1) {
            cout << "Avail list is Empty >= 1." << endl;
            return;
        }

        if (position == 1) {
            deleteFromBeginning();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position - 1 && temp; ++i) {
            temp = temp->next;
        }

        if (!temp || !temp->next) {
            cout << "The offset is not found" << endl;
            return;
        }
        // Save the node to be deleted
        Node* nodeToDelete = temp->next;
        // Update the next pointer
        temp->next = temp->next->next;
        // Delete the node
        delete nodeToDelete;
    }

    pair<short,int> getoffset(int size){
        Node* temp = head;
        while (temp) {
            if (temp->size >= size)return {temp->offset,temp->size};
            temp = temp->next;
        }
    }

    void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        while (temp) {
            cout << temp->offset << "  " << temp->size <<" \n";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    bool is_offset_exit(short offset){
        Node* temp = head;
        while (temp){
            if (temp->offset == offset)return true;
            temp = temp->next;
        }
        return false;
    }
};

class availlistdoc{
private:
    Node* head ;

public:
    availlistdoc() : head(NULL){}
    bool is_empty(){
        return head==NULL;
    }

    void insertAtBeginning(short offset , int size) {
        Node* newNode = new Node();
        newNode->offset = offset;
        newNode->size = size;
        newNode->next = head;
        head = newNode;
    }

    void insertAtEnd(short offset , int size) {
        Node* newNode = new Node();
        newNode->offset = offset;
        newNode->size = size;
        newNode->next = NULL;

        if (!head) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void deleteFromBeginning() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void deleteFromOffset(short offset) {
        int position = 0 ;
        Node* test = head;
        while (test){
            if (test->offset == offset) break;
            position++;
            test = test->next;
        }


        if (position < 1) {
            cout << "Avail list is Empty >= 1." << endl;
            return;
        }

        if (position == 1) {
            deleteFromBeginning();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position - 1 && temp; ++i) {
            temp = temp->next;
        }

        if (!temp || !temp->next) {
            cout << "The offset is not found" << endl;
            return;
        }
        // Save the node to be deleted
        Node* nodeToDelete = temp->next;
        // Update the next pointer
        temp->next = temp->next->next;
        // Delete the node
        delete nodeToDelete;
    }

    pair<short,int> getoffset(int size){
        Node* temp = head;
        while (temp) {
            if (temp->size >= size)return {temp->offset,temp->size};
            temp = temp->next;
        }
    }

    void display() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* temp = head;
        while (temp) {
            cout << temp->offset << "  " << temp->size <<" \n";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    bool is_offset_exit(short offset){
        Node* temp = head;
        while (temp){
            if (temp->offset == offset)return true;
            temp = temp->next;
        }
        return false;
    }
};

const char DELIMITER = '|';
short headerappointment;
short headerdoctor;

string convert(int size){
    string s="0";
    if (size<10){
        s+= to_string(size);
    }
    else s = to_string(size);

    return s;
}

// Define structures
struct Doctor {
    char doctorID[15];
    char doctorName[30];
    char address[30];
    short header;
    int length;
};

struct Appointment {
    char appointmentID[15];
    char appointmentDate[30];
    char doctorID[15];
    short header;
    int length;
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
    vector<string>IDs;
    bool operator<(const SecondaryIndexName &r) const {
        return strcmp(Name, r.Name) < 0;
    }
};

struct SecondaryIndexID {
    char ID[15] = " ";
    vector<string>appointmentsIDs; // Appointment offsets
    bool operator<(const SecondaryIndexID &r) const {
        return strcmp(ID, r.ID) < 0;
    }
};

vector<PrimaryIndex> doctorPrimaryIndex;
//vector<Doctor> doctors;
//vector<Appointment> appointments;
vector<PrimaryIndex> appointmentPrimaryIndex;
vector<SecondaryIndexName> doctorNameSecondaryIndex;
vector<SecondaryIndexID> doctorIDSecondaryIndexForAppointments;
//vector<Doctor>availList_Doctor;
//vector<Appointment>availList_Appointment;
//short headerDoctor;
//short headerAppointment;
availlist list0 = *new availlist;
availlistdoc listdoc = *new availlistdoc;



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
void  loadavaillist();
//void loadAppointments();
void printDoctorInfo();
void printAppointmentInfo();

int main() {
    loadIndexes();
    loadheader();
    loadavaillist();
    //loadDoctors();
    //loadAppointments();

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
//            case 9: processQuery(); break;
            case 10: break; // Exit
            default: cout << "Invalid choice. Please try again." << "\n";
        }
    } while (choice != 10);

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

    // Load Secondary Index for Doctor Names
    fstream doctorNameSecondaryIndexFile("doctor_name_secondary_index.txt", ios::in | ios:: app);
    if (!doctorNameSecondaryIndexFile.is_open()) {
        cerr << "Error: Could not open doctor name secondary index file!" << endl;
    } else {
        while (!doctorNameSecondaryIndexFile.eof()) {
            SecondaryIndexName tempIndex;
            string line;
            getline(doctorNameSecondaryIndexFile, line);
            if (line.empty()) continue;

            // Parse line: name|ID1,ID2,ID3
            size_t delimPos = line.find('|');
            if (delimPos != string::npos) {
                strcpy(tempIndex.Name, line.substr(0, delimPos).c_str());
                string idList = line.substr(delimPos + 1);

                // Split IDs by commas
                stringstream ss(idList);
                string id;
                while (getline(ss, id, ',')) {
                    tempIndex.IDs.push_back(id);
                }
            }
            doctorNameSecondaryIndex.push_back(tempIndex);
        }
        doctorNameSecondaryIndexFile.close();
        cout << "Loaded " << doctorNameSecondaryIndex.size() << " doctor name secondary index records." << endl;
    }

    // Load Secondary Index for Doctor IDs and Appointments
    fstream doctorIDSecondaryIndexFile("doctor_id_secondary_index.txt", ios::in);
    if (!doctorIDSecondaryIndexFile.is_open()) {
        cerr << "Error: Could not open doctor ID secondary index file!" << endl;
    } else {
        while (!doctorIDSecondaryIndexFile.eof()) {
            SecondaryIndexID tempIndex;
            string line;
            getline(doctorIDSecondaryIndexFile, line);
            if (line.empty()) continue;

            // Parse line: ID|Appointment1,Appointment2
            size_t delimPos = line.find('|');
            if (delimPos != string::npos) {
                strcpy(tempIndex.ID, line.substr(0, delimPos).c_str());
                string appointmentList = line.substr(delimPos + 1);

                // Split Appointments by commas
                stringstream ss(appointmentList);
                string app;
                while (getline(ss, app, ',')) {
                    tempIndex.appointmentsIDs.push_back(app);
                }
            }
            doctorIDSecondaryIndexForAppointments.push_back(tempIndex);
        }
        doctorIDSecondaryIndexFile.close();
        cout << "Loaded " << doctorIDSecondaryIndexForAppointments.size() << " doctor ID secondary index records." << endl;
    }

    cout << "All indexes loaded successfully." << endl;
}

void  loadavaillist(){
    fstream availfile("availlist.txt",ios::in | ios::app );
    availfile<<"";
    availfile.seekp(0,ios::end);
    if (availfile.tellp() != 0){
        availfile.seekg(0,ios::beg);
        while (!availfile.eof()){
            short off; int size;
            availfile >> off >> size;
            list0.insertAtEnd(off,size);
        }
    }

    fstream availfiledoc("availlistdoc.txt",ios::app | ios::in );
    availfiledoc<<"";
    availfiledoc.seekp(0,ios::end);
    if (availfiledoc.tellp() != 0){
        availfiledoc.seekg(0,ios::beg);
        while (!availfiledoc.eof()){
            short off; int size;
            availfiledoc >> off >> size;
            listdoc.insertAtEnd(off,size);
        }
    }

}

void writeDoctorNameSecondaryIndex() {
    // Ensure no duplicates are in memory before writing
    std::sort(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end(),
              [](const SecondaryIndexName& a, const SecondaryIndexName& b) {
                  return strcmp(a.Name, b.Name) < 0;
              });

    auto last = std::unique(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end(),
                            [](const SecondaryIndexName& a, const SecondaryIndexName& b) {
                                return strcmp(a.Name, b.Name) == 0;
                            });
    doctorNameSecondaryIndex.erase(last, doctorNameSecondaryIndex.end());

    // Open the file with truncation
    fstream doctorNameSecondaryIndexFile("doctor_name_secondary_index.txt", ios::app | ios::trunc);
    if (!doctorNameSecondaryIndexFile.is_open()) {
        cerr << "Error: Could not open doctor_name_secondary_index.txt for writing!" << "\n";
        return;
    }

    // Write each entry to the file
    for (const auto &entry : doctorNameSecondaryIndex) {
        doctorNameSecondaryIndexFile << entry.Name <<" ";
        for (const auto &id : entry.IDs) {
            doctorNameSecondaryIndexFile << id <<" ";
        }
        doctorNameSecondaryIndexFile << "\n";
    }

    doctorNameSecondaryIndexFile.close();
    cout << "Doctor Name Secondary Index written successfully." << "\n";
}

void writeDoctorIDSecondaryIndex() {
    fstream doctorIDSecondaryIndexFile("doctor_id_secondary_index.txt", ios::app | ios::trunc);
    if (!doctorIDSecondaryIndexFile.is_open()) {
        cerr << "Error: Could not open doctor_id_secondary_index.txt for writing!" << "\n";
        return;
    }

    for (const auto &entry : doctorIDSecondaryIndexForAppointments) {
        doctorIDSecondaryIndexFile << entry.ID << " ";
        for (const auto &appointmentID : entry.appointmentsIDs) {
            doctorIDSecondaryIndexFile << appointmentID << "\n";
        }
        doctorIDSecondaryIndexFile << "\n";
    }

    doctorIDSecondaryIndexFile.close();
    cout << "Doctor ID Secondary Index written successfully." << "\n";
}
/*// Load doctors from file
void loadDoctors() {

    fstream file("doctors.txt",ios::out| ios::in);
    if (!file) return;

    Doctor doc;

    PrimaryIndex p;
    SecondaryIndexName secIndex;

    int header;
    file >> header;
    file.seekg(1, ios::cur);
    p.offset = file.tellg();

    string length;
    while (getline(file, length, DELIMITER) &&
           file.getline(doc.doctorID, 15, DELIMITER) &&
           file.getline(doc.doctorName, 30, DELIMITER) &&
           file.getline(doc.address, 30, DELIMITER)) {
        doc.length = stoi(length);
        doctors.push_back(doc);
        strcpy(p.ID, doc.doctorID);
        // push in primary index vector
        doctorPrimaryIndex.push_back(p);
        p.offset = file.tellg();

        strcpy(secIndex.Name, doc.doctorName);
        secIndex.IDs.push_back(doc.doctorID);

        auto it = find_if(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end(),
                          [&](const SecondaryIndexName& entry) {
                              return strcmp(entry.Name, secIndex.Name) == 0;
                          });

        if (it != doctorNameSecondaryIndex.end()) { // if name already exists
            it->IDs.push_back(doc.doctorID);
        } else {
            // push in secondary index vector
            doctorNameSecondaryIndex.push_back(secIndex);
        }


    }
    sort(doctorPrimaryIndex.begin(), doctorPrimaryIndex.end());
    sort(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end());

    file.close();
}

// Load appointments from file
void loadAppointments() {
    fstream file("appointments.txt",ios::out| ios::in);
    if (!file) return;

    Appointment appt;
    PrimaryIndex p;

    int header;
    file >> header;
    file.seekg(1, ios::cur);
    p.offset = file.tellg();

    string length;
    while (getline(file, length, DELIMITER) &&
           file.getline(appt.appointmentID, 15, DELIMITER) &&
           file.getline(appt.appointmentDate, 30, DELIMITER) &&
           file.getline(appt.doctorID, 15)) {
        appt.length = stoi(length);
        appointments.push_back(appt);
        strcpy(p.ID, appt.appointmentID);
        // push in primary index
        appointmentPrimaryIndex.push_back(p);
        p.offset = file.tellg();

        auto it = find_if(doctorIDSecondaryIndexForAppointments.begin(), doctorIDSecondaryIndexForAppointments.end(),
                          [&](const SecondaryIndexID &index) {
                              return strcmp(index.ID, appt.doctorID) == 0;
                          });

        it->appointmentsIDs.emplace_back(appt.appointmentID);


    }
    // Sort the Primary Index
    sort(appointmentPrimaryIndex.begin(), appointmentPrimaryIndex.end());
    // Sort the Secondary Index
    sort(doctorIDSecondaryIndexForAppointments.begin(), doctorIDSecondaryIndexForAppointments.end());
    file.close();
}*/
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

int findDoctorOffset(const char* doctorID) {
    // Return the result of binarySearchPrimaryIndex_doctor
    return binarySearchPrimaryIndex_doctor(doctorPrimaryIndex, doctorID);
}

int findAppointmentOffset(const char* appointmentID) {
    // Return the result of binarySearchPrimaryIndex_appointment
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
//            headerAppointment=-1;

        }

    }
    int size = 3 + strlen(newAppointment.appointmentID) + strlen(newAppointment.appointmentDate) +
               strlen(newAppointment.doctorID);


//    if (list0.is_empty()){
        appointmentFile << convert(size);
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
        // Add to Secondary Index
        auto it = find_if(doctorIDSecondaryIndexForAppointments.begin(), doctorIDSecondaryIndexForAppointments.end(),
                          [&](const SecondaryIndexID &s) { return strcmp(s.ID, newAppointment.doctorID) == 0; });

        if (it != doctorIDSecondaryIndexForAppointments.end()) {
            it->appointmentsIDs.push_back(newAppointment.appointmentID);
        } else {
            SecondaryIndexID newSecondary;
            strcpy(newSecondary.ID, newAppointment.doctorID);
            newSecondary.appointmentsIDs.push_back(newAppointment.appointmentID);
            doctorIDSecondaryIndexForAppointments.push_back(newSecondary);
        }
        writeDoctorIDSecondaryIndex();
        cout << "Appointment added successfully!" << "\n";

        appointmentFile<< record;
//    }
//    else{
//       short off ; int newsize;
//
//
//
//    }

    appointmentFile.close();
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
//            headerDoctor=-1;
        }

    }
    int size = 3 + strlen(newDoctor.doctorID) + strlen(newDoctor.doctorName) +
               strlen(newDoctor.address);

    doctorFile << convert(size);
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
    // Add to Secondary Index
    auto it = find_if(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end(),
                      [&](const SecondaryIndexName &s) { return strcmp(s.Name, newDoctor.doctorName) == 0; });

    if (it != doctorNameSecondaryIndex.end()) {
        it->IDs.push_back(newDoctor.doctorID);
    } else {
        SecondaryIndexName newSecondary;
        strcpy(newSecondary.Name, newDoctor.doctorName);
        newSecondary.IDs.push_back(newDoctor.doctorID);
        doctorNameSecondaryIndex.push_back(newSecondary);
    }
    writeDoctorNameSecondaryIndex();
    cout << "Doctor added successfully!" << "\n";

    doctorFile<< record;
    doctorFile.close();
}

//delete doctor
/*void deleteDoctor() {
    char doctorID[15];
    cout << "Enter Doctor ID: ";
    cin >> doctorID;

    int offset = findDoctorOffset(doctorID);
    headerdoctor=offset;
    if (offset == -1) {
        cout << "Doctor ID does not exist." << "\n";
        return;
    }

    fstream doctorFile("doctors.txt", ios::in | ios::out | ios::binary);

    if (!doctorFile.is_open()) {
        cerr << "Error: Could not open doctors.txt file." << endl;
        return;
    }
    doctorFile.seekp(offset , ios::beg);
    char deletionMarker = '*';
    doctorFile.write(&deletionMarker, 1);
    doctorFile.close();
    cout << "Doctor  deleted successfully." << endl;
    // Update primary index
    for (auto it = doctorPrimaryIndex.begin(); it != doctorPrimaryIndex.end(); ++it) {
        if (strcmp(it->ID, doctorID) == 0) {
            doctorPrimaryIndex.erase(it);
            break;
        }
    }

    // Update secondary index
    for (auto it = doctorNameSecondaryIndex.begin(); it != doctorNameSecondaryIndex.end(); ++it) {
        if (strcmp(it->ID, doctorID) == 0) {
            doctorNameSecondaryIndex.erase(it);
            break;
        }
    }
}*/
//update doctor name
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
    // Update the secondary index
    auto it = find_if(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end(),
                      [&](const SecondaryIndexName &entry) {
                          return strcmp(entry.Name, fields[1].c_str()) == 0;
                      });

    if (it != doctorNameSecondaryIndex.end()) {
        // Remove the doctor ID from the current name group
        auto &ids = it->IDs;
        ids.erase(remove(ids.begin(), ids.end(), string(doctorID)), ids.end());

        // If no IDs remain for this name, remove the name entry
        if (ids.empty()) {
            doctorNameSecondaryIndex.erase(it);
        }
    }

    // Add the doctor ID to the new name group
    auto newIt = find_if(doctorNameSecondaryIndex.begin(), doctorNameSecondaryIndex.end(),
                         [&](const SecondaryIndexName &entry) {
                             return strcmp(entry.Name, newDoctorName.c_str()) == 0;
                         });

    if (newIt != doctorNameSecondaryIndex.end()) {
        // Add to an existing group
        newIt->IDs.push_back(doctorID);
    } else {
        // Create a new group for the new name
        SecondaryIndexName newEntry;
        strcpy(newEntry.Name, newDoctorName.c_str());
        newEntry.IDs.push_back(doctorID);
        doctorNameSecondaryIndex.push_back(newEntry);
    }

    // Rewrite the secondary index file
    writeDoctorNameSecondaryIndex();
    doctorFile.close();
    cout << "Doctor name updated successfully.\n";
}

//update appointment
void updateAppointmentDate() {
    char AppointmentID[30];
    cout << "Enter Appointment ID to update: ";
    cin >> AppointmentID;

    // Find doctor offset
    int AppointmentOffset = findAppointmentOffset(AppointmentID);
    if (AppointmentOffset == -1) {
        cout << "Appointment ID not found.\n";
        return;
    }
    // Open file in read/write mode
    fstream AppointmentFile("appointments.txt", ios::in | ios::out);
    if (!AppointmentFile.is_open()) {
        cout << "Failed to open appointment file.\n";
        return;
    }
    AppointmentFile.seekg(AppointmentOffset, ios::beg);
    string record;
    getline(AppointmentFile, record);
    // Parse the record
    vector<string> fields;
    stringstream ss(record);
    string field;
    while (getline(ss, field, DELIMITER)) {
        fields.push_back(field);
    }
    if (fields.size() < 3) {
        cout << "Corrupted record found. Update aborted.\n";
        AppointmentFile.close();
        return;
    }
    // Display current doctor name and ask for the new name
    cout << "Current Appointment date: " << fields[1] << endl;
    int sizecurrent=fields[1].length();
    AppointmentFile.seekg(0, ios::beg);
    AppointmentFile.seekg(AppointmentOffset, ios::beg);
    string newAppointmentDate;
    cout << "Enter New Appointment Date: ";
    cin.ignore();
    getline(cin, newAppointmentDate);
    AppointmentFile<<AppointmentID<<"|"<<newAppointmentDate;
    sizecurrent-=newAppointmentDate.length();
    while(sizecurrent>0){
        AppointmentFile<<' ';
        sizecurrent--;
    }
    AppointmentFile.close();
    cout << "Appointment Date updated successfully.\n";
}
//doctor info
void printDoctorInfo() {
    char id[15];
    cout << "Enter the doctor's ID: ";
    cin >> id;
    cin.ignore();
    int offset = findDoctorOffset(id);

    if (offset != -1) {
//        cout << offset << "\n";
        // Read the doctor's record from the file
        ifstream infile("doctors.txt");
        infile.seekg(offset, ios::beg);
        string  doctorID, doctorName, doctorAddress;
        getline(infile, doctorID, DELIMITER);
        getline(infile, doctorName, DELIMITER);
        getline(infile, doctorAddress, DELIMITER);
        infile.close();
        // Display the doctor's information
        cout << "Doctor's ID: " << doctorID << "\n";
        cout << "Doctor's Name: " << doctorName << "\n";
        cout << "Doctor's Address: " << doctorAddress << "\n";
    } else {
        cout << "No doctor exists with this ID." << endl;
    }
}

//appointment
void printAppointmentInfo() {
    char id[15];
    cout << "Enter the Appointment's ID: ";
    cin >> id;
    cin.ignore();
    int offset = findAppointmentOffset(id);
    if (offset != -1) {
        // Read the appointment's record from the file
        ifstream infile("appointments.txt");
        infile.seekg(offset, ios::beg);


        string  appointmentID, appointmentData, doctorID;
        getline(infile, appointmentID, DELIMITER);
        getline(infile, appointmentData, DELIMITER);
        getline(infile, doctorID, DELIMITER);
        infile.close();
        // Display the doctor's information
        cout << "Appointment's ID: " << appointmentID << "\n";
        cout << "Appointment's Date: " << appointmentData << "\n";
        cout << "Doctor's ID: " << doctorID << "\n";
    } else {
        cout << "No appointment exists with this ID." << "\n";
    }
}

void deleteAppointment(){
    fstream file("appointments.txt", ios::in | ios::out);
    file.seekg(0,ios::end);
    if (file.tellg() == 0){
        cout<<"Appointment is empty\n";
        return;
    }
    char id[15];
    cout<<"Enter ID: "<<endl;
    cin>>id;

    short offset = findAppointmentOffset(id);
    if (list0.is_offset_exit(offset) || offset == -1){
        cout<<"ID is not found\n";
        return;
    }

    file.seekg(offset-2,ios::beg);
    char sizerec[3];
    file.get(sizerec,3);


    list0.insertAtEnd(offset, stoi(sizerec));
    fstream availfile("availlist.txt",ios::app );
    availfile<<offset<<" "<<sizerec<<"\n";

    file.seekp(offset-2,ios::beg);
    file<<'*';

    file.seekp(0,ios::beg);
    if (offset<10)file<<0;
    file<<offset;

    fstream appointmentPrimaryIndexFile("appointment_primary_index.txt", ios::in | ios::out);
    string check , off ;
    while (!appointmentPrimaryIndexFile.eof()){
        appointmentPrimaryIndexFile>>check;
        if (check == id){
            appointmentPrimaryIndexFile<<" #";
            break;
        }
        appointmentPrimaryIndexFile>>off;
    }

    fstream doctorIDSecondaryIndexFile("doctor_id_secondary_index.txt", ios::in | ios::out);
    string idoc,check0 ;
    while (!doctorIDSecondaryIndexFile.eof()){
        doctorIDSecondaryIndexFile>>idoc>>check0;
        if (check0 == id){
            int index = doctorIDSecondaryIndexFile.tellp();
            index-=2;
            doctorIDSecondaryIndexFile.seekp(index,ios::beg);
            doctorIDSecondaryIndexFile<<" #";
            break;
        }
    }

cout<<"Deleted Appointment "<<"\n";


}

void deleteDoctor(){
    fstream outfile("doctors.txt", ios::in | ios::out);
    outfile.seekg(0,ios::end);
    if (outfile.tellg() == 0){
        cout<<"Doctor is empty\n";
        return;
    }
    char id[15];
    cout<<"Enter ID: "<<endl;
    cin>>id;

    short offset = findDoctorOffset(id);
    if (listdoc.is_offset_exit(offset) || offset == -1){
        cout<<"ID is not found\n";
        return;
    }

    outfile.seekg(offset-2,ios::beg);
    char sizerec[3];
    outfile.get(sizerec,3);


    listdoc.insertAtEnd(offset, stoi(sizerec));
    fstream availfiledoc("availlistdoc.txt",ios::app | ios::in );
    availfiledoc<<offset<<" "<<sizerec<<"\n";

    outfile.seekp(offset-2,ios::beg);
    outfile<<'*';

    outfile.seekp(0,ios::beg);
    if (offset<10)outfile<<0;
    outfile<<offset;

    fstream doctorPrimaryIndexFile("doctor_primary_index.txt", ios::in | ios::out);
    string check , off ;
    while (!doctorPrimaryIndexFile.eof()){
        doctorPrimaryIndexFile>>check;
        if (check == id){
            doctorPrimaryIndexFile<<" #";
            break;
        }
        doctorPrimaryIndexFile>>off;
    }

    fstream doctorNameSecondaryIndexFile("doctor_name_secondary_index.txt", ios::in | ios::out);
    string name,check0, space ;
    while (!doctorNameSecondaryIndexFile.eof()){
        doctorNameSecondaryIndexFile>>name;
        doctorNameSecondaryIndexFile>>check0;
        if (check0 == id){
            int ind = doctorNameSecondaryIndexFile.tellp();
            ind-=2;
            doctorNameSecondaryIndexFile.seekp(ind,ios::beg);
            doctorNameSecondaryIndexFile<<" #";
            break;
        }
    }

    cout<<"Deleted Doctor "<<"\n";

}
