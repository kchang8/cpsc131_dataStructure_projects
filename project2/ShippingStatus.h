#ifndef ShippingStatus_h
#define ShippingStatus_h

#pragma once

#include <string>
using namespace std;

class ShippingStatus {
public:
    ShippingStatus(); //set variables to equal null
    ShippingStatus(const string& status, const string& location, const time_t& timeUpdated);
    ~ShippingStatus(); //destructor
    string m_getStatus();
    string m_getLocation();
    time_t m_getTime();

private:
  string _status;
  string _location;
  time_t _timeUpdated;
};


#endif
