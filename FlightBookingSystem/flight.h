#pragma once
#include "string.h"

using utils::string;
class Flight
{
public:
	// ¹¹Ôìº¯Êý
	Flight();
	Flight(string flightCode, string departureTime, string arrivalTime,
		string departAirport, string destAirport,
		string connections, int seatBooked, int seatAvailable, string callSign);
	~Flight();
	string getFlightCode()
	{
		return flightCode;
	}
	string getDepartureTime()
	{
		return departureTime;
	}
	string getArrivalTime()
	{
		return arrivalTime;
	}
	string getDepartAirport()
	{
		return depatureAirport;
	}
	string getDestAirport()
	{
		return destinationAirport;
	}
	int getSeatsBooked()
	{
		return seatBooked;
	}
	int getSeatsAvailable()
	{
		return seatAvailable;
	}
	string getCallSign()
	{
		return callSign;
	}
private:
	string flightCode;
	string departureTime;
	string arrivalTime;
	string connections;
	string depatureAirport;
	string destinationAirport;
	int seatBooked;
	int seatAvailable;
	string callSign;
};
