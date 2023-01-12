// Name: Glenn Parreno
// Seneca Student ID: 115814196
// Seneca email: geparreno@myseneca.ca
// Date of completion: 02-12-22
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <iostream>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds
{
	extern std::deque<sdds::CustomerOrder> g_pending;
	extern std::deque<sdds::CustomerOrder> g_completed;
	extern std::deque<sdds::CustomerOrder> g_incomplete;

	class Workstation :public Station
	{
		std::deque<sdds::CustomerOrder> m_orders{};
		Workstation* m_pNextStation = nullptr;
	public:
		Workstation(const std::string&);

		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;

		void fill(std::ostream&);
		bool attemptToMoveOrder();
		void setNextStation(Workstation*);
		Workstation* getNextStation() const;
		void display(std::ostream&) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};
}
#endif // !SDDS_WORKSTATION_H
