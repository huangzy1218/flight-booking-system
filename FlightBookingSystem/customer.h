#pragma once

#include "string.h"
using utils::string;
class Customer
{
public:
	Customer();
	Customer(string customerCode, string customerName, string customerAddress,
		string customerPhone);
	string getCostomerName()
	{
		return customerName;
	}
private:
	string customerCode;
	string customerName;
	string customerAddress;
	string customerPhone;
};