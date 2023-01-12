// Name: Glenn Parreno
// Seneca Student ID: 115814196
// Seneca email: geparreno@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include<string>

namespace sdds
{
	class Utilities
	{
		size_t m_widthField = 1;
		static char m_delimeter;
		void rmSpace(std::string&);
	public:
		void setFieldWidth(size_t);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string&, size_t&, bool&);
		static void setDelimiter(char);
		static char getDelimeter();
	};
}
#endif // !SDDS_UTILITIES_H
