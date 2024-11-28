
#include <iostream>
#include <fstream>
#include <cctype>
#include <cmath>
#include <ostream>
#include <algorithm>
#include <chrono>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define iose ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)

    fstream prim_id_doc("primary_id_doc.txt",ios::app);
    fstream prim_id_app("primary_id_app.txt",ios::app);
    fstream sec_docid_app("secondary_doctorid_app.txt",ios::app);
    fstream sec_name_doc("secondary_name_doc.txt",ios::app);

class secondary_name_doc{
public:
static void write_sec_name(char id[15] ,char name[30] ){
    sec_name_doc<<name<<" "<<id<<"\n";
}
};

class secondary_doctorid_app{
public:
    static void write_sec_iddoc(char id[15] ,char docid[15]){
        sec_docid_app<<docid<<" "<<id<<"\n";
    }

};

class primary_doc_id{
public:
    char id[15];
    int statusflag;
    short offset;

    void writerecord(char id[15]){
        fstream prim_id_doc("primary_id_doc.txt",ios::app);
        prim_id_doc<<id<<" "<<"\n";
    }

};

class primary_id_app{
    char id[15];
    int statusflag;
    short offset;
};

class Doctor {
public:
     char id [15] ; //primary
    char name [30]; // secondary
     char address[30];
    int recordsize;

    void add(){

    }
    void Delete(){

    }

    void update(){

    }
    void Display(){

    }
    void searchbyid(){

    }
    void searchbyname(){

    }
    void writerecord(fstream &docstream){

       string strlen= returnlenghtindecator();
        docstream<<strlen<<name<<"|"<<id<<"|"<<address;
        secondary_name_doc::write_sec_name(id,name);
    }

    string returnlenghtindecator(){
        recordsize = strlen(name) + strlen(id) + strlen(address) + 4;
        string length = to_string(recordsize);
        if (recordsize<10)length="0"+ to_string(recordsize);

        return length;
    }
};

class Appointments {
public:
    char id[15]; // primary
    char doctorID[15]; // secondary
    char date[30];
    int recordsize;

    void add(){

    }
    void Delete(){

    }

    void update(){

    }
    void Display(){

    }
    void searchbyid(){

    }

    void writerecord(fstream &appstream){
        string strlen= returnlenghtindecator();
        appstream<<strlen<<id<<"|"<<doctorID<<"|"<<date;
    }
    string returnlenghtindecator(){
        recordsize = strlen(doctorID) + strlen(id) + strlen(date) + 4;
        string length = to_string(recordsize);
        if (recordsize<10)length="0"+ to_string(recordsize);

        return length;
    }

};



int main() { iose;

    fstream doctorstream("doctor.txt",ios::app | ios::binary);
      Doctor d ;

    fstream appionmentstream("appointments.txt",ios::app);
    Appointments app;

    short header = -1;
    doctorstream.write((char*)&header, sizeof(header));
    appionmentstream.write((char*)&header, sizeof(header));

    int choice;
    char more ='y';
    do{
    cout << "-------------------------------------\n\n"
         << "1)  Add New Doctor\n"
         << "2)  Update Doctor\n"
         << "3)  Delete Doctor\n"
         << "4)  Display Doctor\n"
         << "5)  Search by Doctor ID  \n"
         << "6)  search by Doctor name\n"
         << "7)  Add new Appointment\n"
         << "8)  Update Appointment \n"
         << "9)  Delete Appointment\n"
         << "10) Display Appointment \n"
         << "11) Search by Appointment ID \n"
         << "12) Exit\n\n"
         << "Please Enter Your Choice : ";
    cin >> choice;

    cin.ignore();

    if (choice == 1){

        cout << "Enter Appointment Name:\n";
        cin.getline(d.name, 30);  /// get name

        cout << "Enter Doctor ID:\n";
        cin.getline(d.id, 15); /// get id

        cout << "Enter Doctor Address:\n";
        cin.getline(d.address, 30); /// get address

        d.writerecord(doctorstream);
    }
    else if (choice == 2){
        d.update();
    }
    else if (choice == 3){
        d.Delete();

    }
    else if (choice == 4){
        d.Display();
    }
    else if (choice == 5){
       d.searchbyid();
    }
    else if (choice == 6)
    {
       d.searchbyname();
    }
    else if (choice==7) {

        cout << "Enter Doctor ID:\n";
        cin.getline(app.id, 15);

        cout << "Enter Doctor ID:\n";
        cin.getline(app.doctorID, 15);

        cout << "Enter Appointment Date:\n";
        cin.getline(app.date, 30);

        app.writerecord(doctorstream);

    }
    else if (choice == 8)
    {
        app.update();
    }
    else if (choice == 9)
    {
        app.Delete();
    }
    else if (choice == 10)
    {
       app.Display();
    }
    else if (choice == 11)
    {
        app.searchbyid();
    }
    else
        break ;

        cout << "Do you want to enter more students?";
        cin >> more;
        cin.ignore();

    } while (toupper(more) == 'Y');

    return 0;
}
