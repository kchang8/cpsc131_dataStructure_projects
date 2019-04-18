#include "PackageTracking.h"

PackageTracking::PackageTracking(const string& strnum) {
  trackingNumber = strnum;
}

PackageTracking::~PackageTracking(){

	shipments.clear();
	trackingNumber.clear();

}

// add a new update
void PackageTracking::m_addUpdate(const string& status, const string& location, const time_t& timeUpdated)
{
  shipments.push_back(ShippingStatus( status, location, timeUpdated));
  m_setCurrent(timeUpdated);
}

bool PackageTracking::m_moveBackward()//move iterator one step earlier in time
{
	if(currShipment != shipments.begin())
	  {
	  	currShipment--;
	    return true;
	  }

	  return false;

}

bool PackageTracking::m_moveForward()//move iterator one step forward in time
{
	if(++currShipment != shipments.end())
	  {
	  	return true;
	  }

	  currShipment--;
	  return false;
}

string PackageTracking::m_getLocation( )//return the location of the current update
{
  return currShipment->m_getLocation();
}

time_t PackageTracking::m_getTime( )//return the time of the current update
{
  return currShipment-> m_getTime( );
}

string PackageTracking::m_getStatus( )//return the status of the current update
{
  return currShipment->m_getStatus();
}

int PackageTracking::m_getNumofUpdate() const // get the total numbers of shipping status updates
{
  return shipments.size();
}

void PackageTracking::m_printPreviousUpdates() //print all previous updates in the shipping chain when the package was shipped, all the way up to the current update you are viewing (may not be the most recent update)
{
  for (list<ShippingStatus>::iterator n = shipments.begin(); n != currShipment; n++){
    cout << "The status is:"<< n->m_getStatus()
      	 << "\n The location is: " << n->m_getLocation()
         << "\n The time is: " << n->m_getTime() << endl;
  }
}

//print all updates from the current update you are viewing to the last update in the tracking chain
void PackageTracking::m_printFollowingUpdates()
{
   for (list<ShippingStatus>::iterator n = currShipment; n != shipments.end(); n++){
      cout << "The status is:"<< n->m_getStatus()
      	   << "\n The location is: " << n->m_getLocation()
           << "\n The time is: " << n->m_getTime() << endl;
   }
}

void PackageTracking::m_printFullTracking()//print all the updates in the tracking chain.
{
  for (list<ShippingStatus>::iterator n = shipments.begin(); n != shipments.end(); n++){
      cout << "The status is:"<< n->m_getStatus()
      	   << "\n The location is: " << n->m_getLocation()
           << "\n The time is: " << n->m_getTime() << endl;
  }
}

bool PackageTracking::m_setCurrent(const time_t& timeUpdated)//view an update.
{
  for (list<ShippingStatus>::iterator n = shipments.begin(); n !=shipments.end(); n++)
  {
    if (n->m_getTime() == timeUpdated)
    {
      currShipment = n;
      return true;
    }
  }
  return false;
}


bool PackageTracking::m_readTrackingFile(string fileName){

  ifstream myfile(fileName);

  if (myfile.is_open()){
    string update;
    while (getline(myfile, update))
    {
      if (update == "new"){
        	string status;
        	string location;
        	time_t timeUpdated;
        	getline (myfile, status, ';');
        	getline (myfile, location, ';');
        	myfile >> timeUpdated;
        	myfile.ignore();
        	m_addUpdate(status, location, timeUpdated);
      }

      else if (update == "back"){
        m_moveBackward();
      }
      else if(update == "forward"){
        m_moveForward();
      }
    }
    myfile.close();
    return true;
  }
  else//file could not be opened
  {
    myfile.close();
    return false;
  }
}
