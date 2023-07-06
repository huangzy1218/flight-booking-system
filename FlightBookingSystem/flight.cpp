#include "flight.h"

Flight::Flight()
{}

Flight::Flight(string flightCode, string departureTime, string arrivalTime,
	string departAirport, string destAirport,
	string connections, int seatBooked, int seatAvailable, string callSign)
	: flightCode(flightCode)
	, departureTime(departureTime)
	, arrivalTime(arrivalTime)
	, depatureAirport(depatureAirport)
	, destinationAirport(destAirport)
	, connections(connections)
	, seatBooked(seatBooked)
	, seatAvailable(seatAvailable)
	, callSign(callSign)
{}