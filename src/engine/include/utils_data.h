#pragma once

#include <string>
#include <map>

#include "commons.h"

#define ARA_GET_CUSTOMER_DATA(name) ara::gCustomerData[name]
#define ARA_SET_CUSTOMER_DATA(name, data) ara::gCustomerData[name] = data

namespace ara {

    // ****************************************

    // *
    // * This will save custom data into RAM
    // *

    class ARA_API CustomerData {
    public:
        CustomerData();
        ~CustomerData();

        // key-value pair
        std::map<std::string, std::string> mData;
    };

    // See utils_data.cpp
    // Name of the db, content
    extern std::map<std::string, CustomerData> gCustomerData;

    // ****************************************

} // ara
