

#ifndef HEALTHCARE_MANAGEMENT_SYSTEM_FILES_AVAILABLELIST_H
#define HEALTHCARE_MANAGEMENT_SYSTEM_FILES_AVAILABLELIST_H

#include "Doctor.h"
class AvailableList {
public:
    static short header;

    AvailableList() {

    }

    static int get_header() {
        return header;
    };

    static void set_header(int value) {
        header = value;
    }
};

short AvailableList::header = -1;

#endif //HEALTHCARE_MANAGEMENT_SYSTEM_FILES_AVAILABLELIST_H
