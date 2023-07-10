#pragma once

#include "customer.h"
#include "vector.h"
#include "string.h"

class Reservation
{
public:
	Reservation();
	Reservation(utils::string flightCode, utils::string timeOfBooking, utils::string timeOfDeparture,
		utils::string customerCode);
	utils::vector<utils::string> toString();
	utils::string getCustomerCode()
	{
		return customerCode;
	}
	utils::string getFlightCode()
	{
		return flightCode;
	}
private:
	utils::string flightCode;
	utils::string timeOfBooking;
	utils::string timeOfDeparture;
	utils::string customerCode;
};