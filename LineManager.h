// Name: Glenn Parreno
// Seneca Student ID: 115814196
// Seneca email: geparreno@myseneca.ca
// Date of completion: 02-12-22
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "WorkStation.h"

namespace sdds
{
	class LineManager
	{
		std::vector<sdds::Workstation*> m_activeLine{};
		size_t m_cntCustomerOrder = {0};
		Workstation* m_fistStation = nullptr;
	public:
		LineManager(const std::string&, const std::vector<Workstation*>&);
		void reorderStations();
		bool run(std::ostream&);
		void display(std::ostream&) const;
	};
}


#endif // !SDDS_LINEMANAGER_H
