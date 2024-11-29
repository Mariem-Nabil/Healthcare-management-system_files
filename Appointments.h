

#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_FILES_APPOINTMENTS_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_FILES_APPOINTMENTS_H

#include <bits/stdc++.h>
#include <fstream>

using namespace std;

class Appointments {
public:
    char id[15]; // primary
    char doctorID[15]; // secondary
    char date[30];
    int recordsize;
    Appointments(){}
    void add() {

    }

    void Delete() {

    }

    void update() {

    }

    void Display() {

    }

    void searchbyid() {

    }

    void writerecord(fstream &appstream) {
        string strlen = returnlenghtindecator();
        appstream << strlen << id << "|" << doctorID << "|" << date;
    }

    string returnlenghtindecator() {
        recordsize = strlen(doctorID) + strlen(id) + strlen(date) + 4;
        string length = to_string(recordsize);
        if (recordsize < 10)length = "0" + to_string(recordsize);

        return length;
    }
};


#endif //HEALTHCARE_MANAGEMENT_SYSTEM_FILES_APPOINTMENTS_H
