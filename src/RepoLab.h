#pragma once
#include "FileMovieRepo.h"
#include <random>

/**
 * @brief Used for exception encountered in Repository
*/
class RepoLabException
{
    std::string msg;
public:
    RepoLabException(std::string m) : msg{m}
    {
    }

    //functie friend (vreau sa folosesc membru privat msg)
    friend std::ostream& operator<<(std::ostream& out, const RepoLabException& ex);
};

std::ostream& operator<<(std::ostream& out, const RepoLabException& ex);


class RepoLab : public Repo
{
private:
    std::map<std::pair<std::string, int>, Movie> data;
    double prob;
    std::mt19937 mt{std::random_device{}()};


public:
    explicit RepoLab(double p)
        : prob(p)
    {
        data = {};
    }

    ~RepoLab() = default;

    void store(const Movie& movie) override;

    void remove(const Movie& movie) override;

    void modify(const Movie& movie) override;

    std::vector<Movie> getAll() override;

    const Movie& find(const std::string title, const int year) const override;

    bool get_random_bool();
};

void testeRepoLab();

inline bool RepoLab::get_random_bool()
{
    std::uniform_int_distribution<> dist(0, 101);

    double generatedNumber = (dist(mt) * 1.0) / 100.0;

    //std::cout << generatedNumber <<' ' << prob<< '\n';
    if (generatedNumber <= prob * 1.0)
        return false;

    return true;
}
