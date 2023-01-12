// Name: Glenn Parreno
// Seneca Student ID: 115814196
// Seneca email: geparreno@myseneca.ca
// Date of completion: 26/11/22
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
//
//  CustomOrder.cpp - ms2 
//	Resubmit because I failed to implement the fact that only one of the specidic item is filled.

#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
	CustomerOrder::CustomerOrder()
	{
		m_name = {};
		m_product = {};
		m_cntItem = { 0 };
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const string& str)
	{
		sdds::Utilities ut;
		size_t pos = 0, tPos;
		bool more = true;
		int cnt = 0;
		string item{};

		if (ut.getDelimeter() == '\0')
			ut.setDelimiter('|');

		m_name = ut.extractToken(str, pos, more);
		m_product = ut.extractToken(str, pos, more);
		tPos = pos;

		while (more)
		{
			string token = ut.extractToken(str, tPos, more);
			if (!token.empty())
				cnt++;
		}

		more = true;
		m_lstItem = new Item * [cnt];

		int i = 0;
		while (more)
		{
			item = ut.extractToken(str, pos, more);
			if (!item.empty())
			{
				m_lstItem[i] = new Item(item);
				i++;
			}
		}

		if (ut.getFieldWidth() > m_widthField)
			m_widthField = ut.getFieldWidth();
		m_cntItem = cnt;

		ut.setDelimiter('\0');
		
		/*cout << "-------------------------\n";
		cout << "name: " << m_name << endl;
		cout << "prod: " << m_product << endl;
		cout << "cnt : " << m_cntItem << endl;
		cout << "list: " << endl;
		for (auto i = 0; i < m_cntItem; i++)
		{
			cout << m_lstItem[i]->m_itemName << m_lstItem[i]->m_serialNumber << endl;
		}
		cout << "-------------------------\n";*/
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& src)
	{
		throw
			"must delete";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept
	{
		m_lstItem = nullptr;
		*this = move(src);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept
	{
		if (this != &src)
		{
			for (size_t i = 0; i < m_cntItem; i++)
				delete m_lstItem[i];
			delete[] m_lstItem;

			m_name = src.m_name;
			m_product = src.m_product;
			m_cntItem = src.m_cntItem;

			m_lstItem = src.m_lstItem;

			src.m_lstItem = nullptr;
			src.m_name = {};
			src.m_product = {};
			src.m_cntItem = { 0 };
		}

		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		if (m_lstItem != nullptr)
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				delete m_lstItem[i];
				m_lstItem[i] = nullptr;
			}
		}

		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		int flag = 1;

		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_isFilled == false)
			{
				flag = 0;
				break;
			}
		}

		return flag;

	}

	bool CustomerOrder::isItemFilled(const string& itemName) const
	{
		int flag = 1;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
				if (m_lstItem[i]->m_isFilled == false)
				{
					flag = 0;
					break;
				}
		}

		return flag;

		
	}

	void CustomerOrder::fillItem(Station& station, ostream& os)
	{

		bool cont = true;

		for (size_t i = 0; i < m_cntItem && cont; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isFilled == false)
			{
//				if (str != m_lstItem[i]->m_itemName)
				{
					if (station.getQuantity() > 0)
					{
						station.updateQuantity();
						m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
						m_lstItem[i]->m_isFilled = true;
						os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
						cont = false;
					}
					else
					{
						os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					}

	//				str = m_lstItem[i]->m_itemName;
				}
				
			}
		}
	}

	void CustomerOrder::display(ostream& os) const
	{
		//os << "this is item " << m_cntItem << endl;
		os << m_name << " - " << m_product << endl;
		std::for_each(m_lstItem, m_lstItem + m_cntItem, [&os](Item* it) 
			{
				os << "[";
				os << right << setw(6) << setfill('0') << it->m_serialNumber << "] ";
				os << left << setw(m_widthField + 1) << setfill(' ') << it->m_itemName;
				if (it->m_isFilled)
					os << "  - FILLED" << endl;
				else
					os << "  - TO BE FILLED" << endl;
			});
	}

	size_t CustomerOrder::m_widthField = 0;
}