#include <QApplication>
#include <QLabel>

#include "CosCrudGui.h"
#include "CosReadOnlyGui.h"
#include "MovieService.h"
#include "MyGUI.h"

void run(int argc, char** argv)
{
	QApplication app(argc, argv);

	auto repo = std::make_unique<FileRepo>("./data.dat");
	FileMovieBasketRepo basketRepo;
	MovieValidator validator;
	MovieService service{repo.get(), basketRepo, validator};
	MyGUI gui = MyGUI(service);

	gui.show();


	


	app.exec();
}

int main(int argc, char* argv[])
{
	testeRepoLab();
	testMovie();
	testeRepo();
	testCtr();
	testValidator();
	testMovieMapDTO();

	run(argc, argv);

	return 0;
}
