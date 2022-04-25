#pragma once
#include "FileRepo.h"
#include "Movie.h"
#include "MovieRepo.h"

class UndoAction
{
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction
{
	Movie addedMovie;
	Repo* rep;
public:
	UndoAdd(Repo* rep, const Movie& addedMovie): addedMovie{addedMovie}, rep{rep}
	{
	}

	void doUndo() override
	{
		rep->remove(addedMovie);
	}
};

class UndoRemove : public UndoAction
{
	Movie removedMovie;
	Repo* rep;
public:
	UndoRemove(Repo* rep, const Movie& removedMovie): removedMovie{removedMovie}, rep{rep}
	{
	}

	void doUndo() override
	{
		rep->store(removedMovie);
	}
};

class UndoModify : public UndoAction
{
	Movie modifedMovie;
	Repo* rep;
public:
	UndoModify(Repo* rep, const Movie& modifedMovie): modifedMovie{modifedMovie}, rep{rep}
	{
	}

	void doUndo() override
	{
		rep->modify(modifedMovie);
	}
};
