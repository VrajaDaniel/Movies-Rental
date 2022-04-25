// Lab6_7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Movie.h"
#include "MovieBasketRepo.h"
#include "MovieService.h"
#include "MovieUI.h"
#include "RepoLab.h"


void start()
{
    std::cout << "Input repo type(1 - Memory, 2 - File, 3 - Lab): ";
    int option;
    std::cin >> option;
    while (option < 1 || option > 3)
    {
        std::cout << "Bad input!\n";
        std::cin >> option;
    }

    std::unique_ptr<Repo> repo;

    if (option == 1)
    {
        repo = std::make_unique<MovieRepo>();
    }
    else if (option == 2)
    {
            repo = std::make_unique<FileRepo>("./data.dat");
    }
    else
    {
        repo = std::make_unique<RepoLab>(1.0);
    }

    FileMovieBasketRepo basketRepo;
    MovieValidator validator;
    MovieService service{repo.get(), basketRepo, validator};
    MovieUI ui{service};
    ui.start();
}

int main()
{
    testeRepoLab();
    testMovie();
    testeRepo();
    testCtr();
    testValidator();
    testMovieMapDTO();

    start();


    _CrtDumpMemoryLeaks();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
*/