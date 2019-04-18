#include "ShippingStatus.h"

ShippingStatus::ShippingStatus() {

  _timeUpdated = -1;

}

ShippingStatus::ShippingStatus(const string& status, const string& location, const time_t& timeUpdated) {

  _status = status;
  _location = location;
  _timeUpdated = timeUpdated;

}

ShippingStatus::~ShippingStatus(){

	_status.clear();
	_location.clear();


}

string ShippingStatus::m_getStatus(){

  return _status;
}

string ShippingStatus::m_getLocation(){

  return _location;
}

time_t ShippingStatus::m_getTime() {

  return _timeUpdated;
}
