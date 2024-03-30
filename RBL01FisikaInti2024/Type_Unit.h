#ifndef TYPE_UNIT_H
#define	TYPE_UNIT_H

typedef int			INT;
typedef double		NUM;
typedef int			SIMRESULT;
typedef int			BOOL;
typedef void*		PVOID;

#define PPAR		Particle*

typedef enum
{
	J, MeV, GeV
} energyUnit;

typedef enum
{
	kg, MeV$c2, GeV$c2
} massUnit;



#endif