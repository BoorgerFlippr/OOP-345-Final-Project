// Name: Glenn Parreno
// Seneca Student ID: 115814196
// Seneca email: geparreno@myseneca.ca
// Date of completion: 02-12-22
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "WorkStation.h"

using namespace std;
namespace sdds
{
	std::deque<sdds::CustomerOrder> g_pending;
	std::deque<sdds::CustomerOrder> g_completed;
	std::deque<sdds::CustomerOrder> g_incomplete;

	Workstation::Workstation(const string& str) : Station(str) {};

	void Workstation::fill(ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool moveGood = false;

		if (m_orders.empty() == false)
		{
			if (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0)
			{
				if (m_pNextStation == nullptr)
				{
					if (m_orders.front().isOrderFilled())
						g_completed.push_back(std::move(m_orders.front()));
					else
						g_incomplete.push_back(std::move(m_orders.front()));
				}
				else
					*m_pNextStation += std::move(m_orders.front());

				m_orders.pop_front();
				moveGood = true;
			}
			
		}
		     

		return moveGood;
	}

	void Workstation::setNextStation(Workstation* station = nullptr)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}

	void Workstation::display(ostream& os) const
	{
		os << this->getItemName() << " --> ";
		if (m_pNextStation == nullptr)
			os << "End of line" << endl;
		else
			os << m_pNextStation->getItemName() << endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}