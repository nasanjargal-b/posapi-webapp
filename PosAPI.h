//
// Created by nasanjargal on 10/7/15.
//

#ifndef POSAPI_POSAPI_H
#define POSAPI_POSAPI_H

#include <string>

#if defined _WIN32 || defined __CYGWIN__
#ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllexport)
    #endif
  #endif
#else
#if __GNUC__ >= 4
#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#else
#define DLL_PUBLIC
#endif
#endif


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
