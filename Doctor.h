
#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_FILES_DOCTOR_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_FILES_DOCTOR_H

#include <bits/stdc++.h>
#include <fstream>
#include "Index.h"
#include "AvailableList.h"
using namespace std;
fstream doctorstream("doctor.txt",ios::app | ios::binary);

class Doctor {
public:
    char id[15]; //primary
    char name[30]; // secondary
    char address[30];
    int recordsize;
    AvailableList Avail;
    Doctor(){}
    string returnlenghtindecator() {
        recordsize = strlen(name) + strlen(id) + strlen(address) + 4;
        string length = to_string(recordsize);
        if (recordsize < 10)length = "0" + to_string(recordsize);

        return length;
    }


    void add() {
        // add in data file
        string strlen = returnlenghtindecator();
        doctorstream << strlen << name << "|" << id << "|" << address;
        //add in index files
        secondary_name_doc secondaryNameDoc;
        secondaryNameDoc.write_sec_name(id,name);
        //exist error
        primary_doc_id primaryDocId;
        primaryDocId.writerecord(id,recordsize);
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



};


#endif //HEALTHCARE_MANAGEMENT_SYSTEM_FILES_DOCTOR_H
