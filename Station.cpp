// Name: Glenn Parreno
// Seneca Student ID: 115814196
// Seneca email: geparreno@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"

using namespace std;
namespace sdds
{
	Station::Station(const string& str)
	{
		id_generator++;
		sdds::Utilities ut;
		char delim = ut.getDelimeter();
		size_t pos = 0;
		bool more = true;

		m_stationId = id_generator;

		m_itemHandled = ut.extractToken(str, pos, more);
		m_serialNum = stoul(ut.extractToken(str, pos, more));
		m_numItemInStock = stoul(ut.extractToken(str, pos, more));

		if (ut.getFieldWidth() > m_widthField)
			m_widthField = ut.getFieldWidth();

		ut.setDelimiter('\n');
		more = false;

		m_desc = ut.extractToken(str, pos, more);
		ut.setDelimiter(delim);
	}

	const string& Station::getItemName() const
	{
		return m_itemHandled;
	}

	size_t Station::getNextSerialNumber()
	{
		unsigned int num = m_serialNum;
		m_serialNum++;
		return num;
	}

	size_t Station::getQuantity() const
	{
		return m_numItemInStock;
	}

	void Station::updateQuantity()
	{
		if (m_numItemInStock > 0)
		{
			m_numItemInStock--;
		}
	}

	void Station::display(ostream& os, bool full) const
	{
		os << right << setw(3) << setfill('0') << m_stationId << " | ";
		os << left << setw(m_widthField + 1) << setfill(' ') << m_itemHandled << " | ";
		os << right << setw(6) << setfill('0') << m_serialNum << " | ";

		if (full)
		{
			os << right << setw(4) << setfill(' ') << m_numItemInStock << " | " << m_desc << endl;
		}
		else
			os << endl;
	}

	size_t Station::m_widthField = 0;
	int Station::id_generator = 0;
}