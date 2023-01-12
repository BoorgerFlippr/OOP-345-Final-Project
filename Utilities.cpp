// Name: Glenn Parreno
// Seneca Student ID: 115814196
// Seneca email: geparreno@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

using namespace std;
namespace sdds
{
	void Utilities::rmSpace(string& str)
	{
		str.erase(str.find_last_not_of(' ') + 1);
		str.erase(0, str.find_first_not_of(' '));
	}

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		size_t width = str.find(m_delimeter, next_pos);
		string token = str.substr(next_pos, width - next_pos);

		if (str[next_pos] == m_delimeter)
		{
			more = false;
			throw next_pos;
		}

		if (!token.empty())
		{
			rmSpace(token);
			next_pos = width + 1;
			more = true;

			if (token.size() > m_widthField)
				m_widthField = token.size();
		}
		else
		{
			more = false;
		}

		if (width == string::npos)
			more = false;

		return token;
	}

	void Utilities::setDelimiter(char newDelimeter)
	{
		m_delimeter = newDelimeter;
	}

	char Utilities::getDelimeter()
	{
		return m_delimeter;
	}

	char Utilities::m_delimeter = '\0';
}