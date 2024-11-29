
#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_FILES_DOCTOR_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_FILES_DOCTOR_H

#include <bits/stdc++.h>
#include <fstream>
#include "Index.h"

using namespace std;

class Doctor {
public:
    char id[15]; //primary
    char name[30]; // secondary
    char address[30];
    int recordsize;
    Doctor(){}
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

    void searchbyname() {

    }

    void writerecord(fstream &docstream) {

        string strlen = returnlenghtindecator();
        docstream << strlen << name << "|" << id << "|" << address;
        secondary_name_doc::write_sec_name(id,name);
    }

    string returnlenghtindecator() {
        recordsize = strlen(name) + strlen(id) + strlen(address) + 4;
        string length = to_string(recordsize);
        if (recordsize < 10)length = "0" + to_string(recordsize);

        return length;
    }
};


#endif //HEALTHCARE_MANAGEMENT_SYSTEM_FILES_DOCTOR_H
