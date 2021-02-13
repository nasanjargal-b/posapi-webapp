//
// Created by nasanjargal on 10/7/15.
//

#ifndef POSAPI_POSAPI_H
#define POSAPI_POSAPI_H

#include <string>
#include "ExportLib.h"

#ifdef WIN32
typedef std::wstring UString;
#else
typedef std::string UString;
#endif

using namespace std;

namespace vatps {
    class DLL_PUBLIC PosAPI {
    public:

        static UString checkApi();

        static UString getInformation();

        static UString callFunction(UString funcName, UString param);

        static UString put(UString param);

        static UString returnBill(UString param);

        static UString sendData();
    };
}


#endif //POSAPI_POSAPI_H
