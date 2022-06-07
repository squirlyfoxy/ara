#include "utils_data.h"

namespace ara {

    // ****************************************

    // *
    // * This will save custom data into RAM
    // *

    CustomerData::CustomerData() {

    }

    CustomerData::~CustomerData() {
        
    }

    // See utils.cpp
    // Name of the db, content
    std::map<std::string, CustomerData> gCustomerData;

    // ****************************************

} // ara