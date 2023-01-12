// Name: Glenn Parreno
// Seneca Student ID: 115814196
// Seneca email: geparreno@myseneca.ca
// Date of completion: 02-12-22
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <fstream>
#include "LineManager.h"

using namespace std;
namespace sdds
{
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		ifstream myFile(file);
		sdds::Utilities ut;
		size_t pos = 0;
		bool more = true;
		string tk1, tk2, ln; // [tk1 | tk2]
		Workstation* curStn = nullptr; 
		Workstation* nxtStn = nullptr;
		Workstation* first = nullptr;

		if (!myFile)
			throw string("unable to open");
		else
		{
			while (!myFile.eof())
			{
				//extract from input file 2 string , names of 2 stations
				getline(myFile, ln);

				ut.setDelimiter('|');
				tk1 = ut.extractToken(ln, pos, more);
				curStn = *std::find_if(stations.begin(), stations.end(), [&](Workstation* w)
					{
						return w->getItemName() == tk1;
					}
				);
				m_activeLine.push_back(curStn);

				if (more)
				{
					tk2 = ut.extractToken(ln, pos, more);
					nxtStn = *std::find_if(stations.begin(), stations.end(), [&](Workstation* w)
						{
							return w->getItemName() == tk2;
						}
					);
					curStn->setNextStation(nxtStn);
				}
				else
					curStn->setNextStation(nullptr);

				pos = 0;
				more = true;
			}
			//determin first station
			for_each(stations.begin(), stations.end(), [&](Workstation* w1)
				{
					first = *std::find_if(stations.begin(), stations.end(), [&](Workstation* w2)
						{
							return w2->getNextStation() == first;
						});
				});

			m_fistStation = first;

		}
		myFile.close();

		m_cntCustomerOrder = g_pending.size();

		//cout << "-----------\n pending size : " << g_pending.size() << "\n active line size : " << m_activeLine.size() << "\n--------" << endl;



	}

	void LineManager::reorderStations()
	{
		Workstation* w = m_fistStation;
		int i = 0;

		do
		{
			m_activeLine[i] = w;
			w = w->getNextStation();
			i++;
		} while (w != nullptr);
	}

	bool LineManager::run(std::ostream& os)
	{
		static int iterat = 0;
		iterat++;
		size_t cnt;

		os << "Line Manager Iteration: " << iterat << endl;

		if (!g_pending.empty())
		{
			*m_fistStation += std::move(g_pending.front());
			g_pending.pop_front();
		}

		/*for (int i = 0; i < m_activeLine.size(); i++)
		{
			m_activeLine[i]->fill(os);
		}

		for (int i = 0; i < m_activeLine.size(); i++)
		{
			m_activeLine[i]->attemptToMoveOrder();
		}*/

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* w)
			{
				w->fill(os);
			});

		std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* w)
			{
				w->attemptToMoveOrder();
			});

		cnt = g_completed.size() + g_incomplete.size();

		if (m_cntCustomerOrder == cnt)
			return true;
		else
			return false;
	}

	void LineManager::display(std::ostream& os) const
	{
		for (auto& i : m_activeLine)
			i->display(os);
	}
}