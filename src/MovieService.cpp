#include "MovieService.h"

#include <algorithm>
#include <fstream>
#include <map>

#include "MovieMapDTO.h"

#define TEST_FILENAME "./test/test.data"

void MovieService::addMovie(const std::string& title, const int& year, const std::string& actor,
                            const std::string& genre)
{
    Movie p{title, year, actor, genre};
    validator.validate(p);
    repo->store(p);
    undoActions.push_back(std::make_unique<UndoAdd>(repo, p));
}

void MovieService::deleteMovie(const std::string& title, const int& year)
{
    const auto& movie = repo->find(title, year);
    undoActions.push_back(std::make_unique<UndoRemove>(repo, movie));
    repo->remove(movie);
}

void MovieService::modifyMovie(const std::string& title, const int& year, const std::string& actor,
                               const std::string& genre)
{
    const auto& movie = repo->find(title, year);
    //tmp.set_actor(actor);
    //tmp.set_genre(genre);

    undoActions.push_back(std::make_unique<UndoModify>(repo, movie));
    repo->modify({title, year, actor, genre});
}

bool isGoodByOption(int option, const std::string& value, const Movie& p)
{
    bool isGoodOption = false;
    switch (option)
    {
    case 1:
        isGoodOption = p.get_title().find(value) != std::string::npos ? true : false;
        break;
    case 2:
        isGoodOption = p.get_year() == std::stoi(value) ? true : false;
        break;
    case 3:
        isGoodOption = p.get_actor().find(value) != std::string::npos ? true : false;
        break;
    case 4:
        isGoodOption = p.get_genre().find(value) != std::string::npos ? true : false;
        break;
    }
    return isGoodOption;
}

std::vector<Movie> MovieService::searchMovie(int option, const std::string& value)
{
    const std::vector<Movie>& all = repo->getAll();
    std::vector<Movie> tmp(all.size());
    auto it = std::copy_if(all.begin(), all.end(), tmp.begin(), [option, value](const Movie& p)
    {
        return isGoodByOption(option, value, p);
    });
    tmp.resize(std::distance(tmp.begin(), it));
    return tmp;
}

bool isGoodFilterByOption(int option, const std::string& value, const Movie& p)
{
    bool isGoodOption = false;
    switch (option)
    {
    case 1:
        isGoodOption = p.get_title() == value ? true : false;
        break;
    case 2:
        isGoodOption = p.get_year() == std::stoi(value) ? true : false;
        break;
    case 3:
        isGoodOption = p.get_actor() == value ? true : false;
        break;
    case 4:
        isGoodOption = p.get_genre() == value ? true : false;
        break;
    }
    return isGoodOption;
}

std::vector<Movie> MovieService::filterMovie(int option, const std::string& value)
{
    const std::vector<Movie>& all = getAll();
    std::vector<Movie> tmp(all.size());
    auto it = std::copy_if(all.begin(), all.end(), tmp.begin(), [option, value](const Movie& p)
    {
        return isGoodFilterByOption(option, value, p);
    });
    tmp.resize(std::distance(tmp.begin(), it));
    return tmp;
}

std::vector<Movie> MovieService::sortMovie(int option)
{
    std::vector<Movie> tmp = repo->getAll();
    std::sort(tmp.begin(), tmp.end(), [option](const Movie& l, const Movie& r)
    {
        bool toSwap = false;
        switch (option)
        {
        case 1:
            if (l.get_title() == r.get_title())
                return false;
            return l.get_title().compare(r.get_title()) < 0 ? true : false;
            break;
        case 2:
            if (l.get_year() != r.get_year())
                toSwap = l.get_year() < r.get_year() ? true : false;
            else
                toSwap = l.get_genre().compare(r.get_genre()) < 0 ? true : false;
            return toSwap;
            break;
        case 3:
            return l.get_actor().compare(r.get_actor()) < 0 ? true : false;

            break;
        }
        return toSwap;
    });
    /*for (unsigned int i = 0; i < tmp.size(); ++i)
    {
        for (unsigned int j = i + 1; j < tmp.size(); ++j)
        {
            bool toSwap = false;
            switch (option)
            {
            case 1:
                toSwap = tmp.at(i).get_title().compare(tmp.at(j).get_title()) > 0 ? true : false;
                break;
            case 2:
                if (tmp.at(i).get_year() != tmp.at(j).get_year())
                    toSwap = tmp.at(i).get_year() > tmp.at(j).get_year() ? true : false;
                else
                    toSwap = tmp.at(i).get_genre().compare(tmp.at(j).get_genre()) > 0 ? true : false;
                break;
            case 3:
                toSwap = tmp.at(i).get_actor().compare(tmp.at(j).get_actor()) > 0 ? true : false;
                break;
            }
            if (toSwap)
            {
                std::swap(tmp.at(i), tmp.at(j));
            }
        }
    }*/
    return tmp;
}

void MovieService::emptyBasket()
{
    this->basketRepo.clear();

}

void MovieService::addMovieToBasket(const std::string& title, const int& year)
{
    this->basketRepo.store(this->repo->find(title, year));
}

void MovieService::populateBasket(const unsigned int& howMany)
{
    if (howMany > this->repo->getAll().size())
        throw MovieBasketRepoException("Not enough items to generate the basket !");

    this->emptyBasket();

    std::vector<int> basketUsed;

    int leftToAdd = howMany;
    while (leftToAdd > 0)
    {
        std::uniform_int_distribution<> dist(0, static_cast<int>(repo->getAll().size() - 1));
        int randomNr = dist(mt); // numar aleator intre [0,size-1]
        auto it = std::find(basketUsed.begin(), basketUsed.end(), randomNr);
        while (it != basketUsed.end())
        {
            randomNr = dist(mt); // numar aleator intre [0,size-1]
            it = std::find(basketUsed.begin(), basketUsed.end(), randomNr);
        }
        basketUsed.push_back(randomNr);
        this->basketRepo.store(this->repo->getAll().at(randomNr));
        leftToAdd = leftToAdd - 1;
    }
}

std::map<int, MovieMapDTO> MovieService::getMap()
{
    std::map<int, MovieMapDTO> map;
    for (const auto& it : this->repo->getAll())
    {
        if (map.find(it.get_year()) != map.end())
        {
            map[it.get_year()].set_count(map[it.get_year()].get_count() + 1);
        }
        else
        {
            map[it.get_year()] = MovieMapDTO(it.get_year(), 1);
        }
    }
    return map;
}

void MovieService::undo()
{
    if (undoActions.empty())
    {
        throw MovieRepoException("No more operations to undo !");
    }

    undoActions.back()->doUndo();
    undoActions.pop_back();
}

void MovieService::saveBasketToCSV(const std::string& output)
{
    this->basketRepo.saveToCSV(output + ".csv");
}

void MovieService::saveBasketToHTML(const std::string& output)
{
    this->basketRepo.saveToHTML(output + ".html");
}

const Movie& MovieService::findMovie(const std::string& title, const std::string& year)
{
    return this->repo->find(title, stoi(year));
}

void testAdaugaCtr()
{
    auto rep = std::make_unique<FileRepo>(TEST_FILENAME);
    FileMovieBasketRepo basketRepo;
    MovieValidator val;
    MovieService ctr{rep.get(), basketRepo, val};
    ctr.addMovie("a", 2, "a", "a");
    assert(ctr.getAll().size() == 1);
    assert(ctr.findMovie("a","2").get_actor()=="a");

    //adaug ceva invalid
    try
    {
        ctr.addMovie("", -2, "a", "b");
        assert(false);
    }
    catch (ValidateException&)
    {
        assert(true);
    }
    //incerc sa adaug ceva ce existadeja
    try
    {
        ctr.addMovie("a", 2, "a", "a");
        assert(false);
    }
    catch (MovieRepoException&)
    {
        assert(true);
    }

    ctr.modifyMovie("a", 2, "ccc", "ddd");
    assert(ctr.getAll().at(0).get_title() == "a");
    assert(ctr.getAll().at(0).get_year() == 2);
    assert(ctr.getAll().at(0).get_actor() == "ccc");
    assert(ctr.getAll().at(0).get_genre() == "ddd");


    try
    {
        ctr.modifyMovie("x", 2, "A", "a");
        assert(false);
    }
    catch (MovieRepoException&)
    {
        assert(true);
    }

    ctr.deleteMovie("a", 2);
    assert(ctr.getAll().size() == 0);
    remove(TEST_FILENAME);
};

void testFilterCtr()
{
    auto rep = std::make_unique<FileRepo>(TEST_FILENAME);
    FileMovieBasketRepo basketRepo;
    MovieValidator val;
    MovieService ctr{rep.get(), basketRepo, val};

    ctr.addMovie("b", 4, "b", "b");
    ctr.addMovie("a", 4, "b", "b");
    ctr.addMovie("x", 3, "y", "z");

    assert(ctr.filterMovie(1, "a").size() == 1);
    assert(ctr.filterMovie(2, "4").size() == 2);
    assert(ctr.filterMovie(3, "b").size() == 2);
    assert(ctr.filterMovie(4, "b").size() == 2);

    assert(ctr.searchMovie(1, "a").size() == 1);
    assert(ctr.searchMovie(2, "4").size() == 2);
    assert(ctr.searchMovie(3, "b").size() == 2);
    assert(ctr.searchMovie(4, "b").size() == 2);

    assert(ctr.sortMovie(1).at(0).get_title() == "a");
    assert(ctr.sortMovie(2).at(0).get_year() == 3);
    assert(ctr.sortMovie(3).at(0).get_actor() == "b");
    remove(TEST_FILENAME);
}


void testBasket()
{
    auto rep = std::make_unique<FileRepo>(TEST_FILENAME);
    FileMovieBasketRepo basketRepo;
    MovieValidator val;
    MovieService ctr{rep.get(), basketRepo, val};
    ctr.addMovie("b", 4, "b", "b");
    ctr.addMovie("a", 4, "b", "b");
    ctr.addMovie("x", 3, "y", "z");

    ctr.addMovieToBasket("a", 4);
    try
    {
        ctr.addMovieToBasket("a", 4);
        assert(false);
    }
    catch (MovieBasketRepoException&)
    {
        assert(true);
    }
    assert(ctr.getAllBasket().size() == 1);
    ctr.emptyBasket();
    assert(ctr.getAllBasket().empty());
    ctr.populateBasket(2);
    assert(ctr.getAllBasket().size() == 2);

    try
    {
        ctr.populateBasket(10);
        assert(false);
    }
    catch (MovieBasketRepoException&)
    {
        assert(true);
    }
    remove(TEST_FILENAME);
}

void testMap()
{
    auto rep = std::make_unique<FileRepo>(TEST_FILENAME);
    FileMovieBasketRepo basketRepo;
    MovieValidator val;
    MovieService ctr{rep.get(), basketRepo, val};
    ctr.addMovie("b", 4, "b", "b");
    ctr.addMovie("a", 4, "b", "b");
    ctr.addMovie("x", 3, "y", "z");
    assert(ctr.getMap().size() == 2);
    remove(TEST_FILENAME);
}

void testUndo()
{
    auto rep = std::make_unique<FileRepo>(TEST_FILENAME);
    FileMovieBasketRepo basketRepo;
    MovieValidator val;
    MovieService ctr{rep.get(), basketRepo, val};
    ctr.addMovie("b", 4, "b", "b");
    ctr.addMovie("a", 4, "b", "b");
    ctr.addMovie("x", 3, "y", "z");
    assert(ctr.getAll().size() == 3);
    ctr.undo();
    assert(ctr.getAll().size() == 2);
    ctr.deleteMovie("b", 4);
    assert(ctr.getAll().size() == 1);
    ctr.undo();
    assert(ctr.getAll().size() == 2);
    ctr.modifyMovie("b", 4, "c", "d");
    assert(ctr.getAll().size() == 2);
    ctr.undo();
    assert(ctr.getAll().size() == 2);
    remove(TEST_FILENAME);
}

void testExport()
{
    auto rep = std::make_unique<FileRepo>(TEST_FILENAME);
    FileMovieBasketRepo basketRepo;
    MovieValidator val;
    MovieService ctr{rep.get(), basketRepo, val};
    ctr.addMovie("b", 4, "b", "b");
    ctr.addMovie("a", 4, "b", "b");
    ctr.addMovie("x", 3, "y", "z");
    ctr.populateBasket(3);
    assert(ctr.getAllBasket().size() == 3);
    ctr.saveBasketToCSV("test");
    ctr.saveBasketToHTML("test");
    std::ifstream f("test.csv");
    assert(f.good() == true);
    f.close();
    f.open("test.html");
    assert(f.good() == true);
    f.close();
    remove(TEST_FILENAME);
}

void testCtr()
{
    testAdaugaCtr();
    testFilterCtr();
    testBasket();
    testMap();
    testUndo();
    testExport();
}
