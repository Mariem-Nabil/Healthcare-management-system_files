

#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_FILES_INDEX_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_FILES_INDEX_H
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

fstream prim_id_doc("primary_id_doc.txt", ios::app | ios::in | ios::out);
fstream prim_id_app("primary_id_app.txt", ios::app | ios::in | ios::out);
fstream sec_docid_app("secondary_doctorid_app.txt", ios::app | ios::in | ios::out);
fstream sec_name_doc("secondary_name_doc.txt", ios::app | ios::in | ios::out);

class secondary_name_doc {
public:
    static void write_sec_name(char id[15], char name[30]) {
        sec_name_doc << name << " " << id << "\n";
    }
};

class secondary_doctorid_app {
public:
    static void write_sec_iddoc(char id[15], char docid[15]) {
        sec_docid_app << docid << " " << id << "\n";
    }

};

class primary_doc_id {
public:
    char id[15];
    int offset; //refrence field
  static int lastAddress ;

    void writerecord(char id[15],int size) {
        offset=size;
        prim_id_doc << id << " " <<lastAddress<< "\n";
        update_lastAddress(size);
    }
    static void update_lastAddress(int value){
        lastAddress+=value;
    }

};
int primary_doc_id::lastAddress= sizeof(short);//size of header
class primary_id_app {
    char id[15];
    int statusflag;
    short offset;
};

#endif //HEALTHCARE_MANAGEMENT_SYSTEM_FILES_INDEX_H
