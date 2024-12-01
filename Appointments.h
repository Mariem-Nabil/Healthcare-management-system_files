

#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_FILES_APPOINTMENTS_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_FILES_APPOINTMENTS_H

#include <bits/stdc++.h>
#include <fstream>

using namespace std;
fstream appionmentstream("appointments.txt",ios::app);

class Appointments {
public:
    char id[15]; // primary
    char doctorID[15]; // secondary
    char date[30];
    int recordsize;
    Appointments(){}
    string returnlenghtindecator() {
        recordsize = strlen(doctorID) + strlen(id) + strlen(date) + 3;
        string length = to_string(recordsize);
        if (recordsize < 10)length = "0" + to_string(recordsize);

        return length;
    }
    void add() {
        // add in data file
        string strlen = returnlenghtindecator();
        appionmentstream << strlen << id << "|" << doctorID << "|" << date<<"|";
        //add in index files
        secondary_doctorid_app secondaryDoctoridApp;
        secondaryDoctoridApp.write_sec_iddoc( id,doctorID);
    }

    void Delete() {

    }

    void update() {

    }

    void Display() {

    }

    void searchbyid() {

    }



};


#endif //HEALTHCARE_MANAGEMENT_SYSTEM_FILES_APPOINTMENTS_H
