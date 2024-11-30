
#include <iostream>
#include <fstream>
#include <cctype>
#include <ostream>
#include "Doctor.h"
#include "Appointments.h"
using namespace std;
#define iose ios::sync_with_stdio(false),cin.tie(nullptr),cout.tie(nullptr)


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
         << "12) Exit\n"
         << "Please Enter Your Choice :  " <<endl ;
//        cout.flush();
    cin >> choice;

    cin.ignore();

    if (choice == 1){

        cout << "Enter Doctor Name: "<<endl;
        cin.getline(d.name, 30);  /// get name

        cout << "Enter Doctor ID: " <<endl;
        cin.getline(d.id, 15); /// get id

        cout << "Enter Doctor Address: "<<endl;
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

        cout << "Enter Appointment ID: "<<endl;
        cin.getline(app.id, 15);

        cout << "Enter Doctor ID: "<<endl;
        cin.getline(app.doctorID, 15);

        cout << "Enter Appointment Date: "<<endl;
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

        cout << "Do you want to enter more ?"<<endl;
        cin >> more;
        cin.ignore();

    } while (toupper(more) == 'Y');

    return 0;
}
