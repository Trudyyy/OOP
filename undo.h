#pragma once
#include "masina.h"
#include "masiniRepo.h"
using namespace std;

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga :public ActiuneUndo {
	Car masinaAdaugat;
	CarRepo &rep;
public:
	UndoAdauga(CarRepo&rep, const Car &car) :rep{ rep }, masinaAdaugat{ car } {}
	void doUndo() override
	{
		rep.del(masinaAdaugat.getnrInm());
	}
};

class UndoSterge :public ActiuneUndo {
	Car carSters;
	CarRepo &rep;
public:
	UndoSterge(CarRepo&rep, Car &carSters) : rep{ rep }, carSters{ carSters } {}
	void doUndo() override
	{
		rep.store(carSters);
	}
};

class UndoModifica :public ActiuneUndo {
	Car carModificat;

	CarRepo &rep;
	int index = -1;
public:
	UndoModifica(CarRepo &rep, Car &carModificat) : rep{ rep }, carModificat{ carModificat }{
	}
	void doUndo() override
	{
		rep.change(carModificat.getnrInm(), carModificat.getType(), carModificat.getProd(), carModificat.getMod());
	}
};