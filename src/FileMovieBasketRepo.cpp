#include "FileMovieBasketRepo.h"

#include <fstream>

void FileMovieBasketRepo::saveToCSV(const std::string& fileName) const
{
	std::ofstream f(fileName);

	f << "title,year,actor,genre\n";

	for (const auto& it : getAll())
	{
		f << it.get_title() << ','
			<< it.get_year() << ','
			<< it.get_actor() << ','
			<< it.get_genre() << ',' << '\n';
	}

	f.close();
}

void FileMovieBasketRepo::saveToHTML(const std::string& fileName)
{
	std::ofstream f(fileName);

	f << "<html>";
	f << "\n<table><thead><tr><td>Title</td><td>Year</td><td>Actor</td><td>Genre</td></tr></thead>";
	for (const auto& it : getAll())
	{
		f << "<tr>\n";
		f << "<td>" + it.get_title() << "</td>\n";
		f << "<td>" + std::to_string(it.get_year()) << "</td>\n";
		f << "<td>" + it.get_actor() << "</td>\n";
		f << "<td>" + it.get_genre() << "</td>\n";
		f << "\n</tr>\n";
	}
	f << "\n</tbody>";
	f << "\n</table>";
	f << "\n</html>";
	f.close();
}
