// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include <iostream>
#include <iomanip>
#include "Utilities.h"

namespace sdds
{
	class Station
	{
		int m_stationId = 0;
		std::string m_itemHandled{};
		std::string m_desc{};
		unsigned int m_serialNum = 0;
		unsigned int m_numItemInStock = 0;
		static size_t m_widthField;
		static int id_generator;
	public:
		Station();
		Station(const std::string&);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream&, bool) const;
	};

}
#endif // !SDDS_STATION_H
