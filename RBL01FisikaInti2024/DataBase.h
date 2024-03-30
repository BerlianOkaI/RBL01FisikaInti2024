#ifndef	DATABASE_H
#define DATABASE_H

#include "Type_Unit.h"
#include <math.h>
#include <cstdlib>

const NUM c				= 299792458.0;
const NUM hbar			= 1.05457182 * pow(10.0, -34.0);
const NUM J2MeV			= 6.242 * pow(10.0, 12.0);
const NUM kg2MeV$c2		= 5.6 * pow(10.0, 29.0);
const NUM elecMass		= 0.51099895;						// In MeV$c2

typedef enum
{
	Up, Down,
	Top, Bottom,
	Charm, Strange,
	// Antiquark
	AUp, ADown,
	ATop, ABottom,
	ACharm, AStrange, 
	null
} quarkType;

typedef enum
{
	// Leptons
	Electron,	nuElectron,
	Positron,	AnuElectron,
	Muon,		nuMuon,
	PMuon,		AnuMuon,
	Tau,		nuTau,
	PTau,		AnuTau,
	// Hadrons (?)
	PPion,		ZPion,		NPion,
	PKaon,		NKaon,
	Proton,		Neutron,
	ZLambda,	cLambda,	bLambda,
	PSigma,		ZSigma,		NSigma,
	bPSigma,	bNSigma,
	ZXi,		NXi,
	cPXi,		cZXi,		bNXi,
	NOmega,		cZOmega
} particleClass;
typedef struct tagConserveNum
{
	INT charge;
	INT	LNumElectron;
	INT	LNumMuon;
	INT	LNumTauon;
	NUM	BaryonNum;
	INT	StrangeNum;
} ConserveNum;

typedef struct tagReactParticle
{
	/*
	// Number of Leptons in reaction (initial or final)
	INT Electron, nuElectron, Positron, AnuElectron;
	INT Muon, nuMuon, PMuon, AnuMuon;
	INT Tau, nuTau, PTau, AnuTau;
	// Number of Hadrons
	INT PPion, ZPion, NPion;
	INT PKaon, NKaon;
	INT Proton, Neutron;
	INT ZLambda, cLambda, bLambda;
	INT PSigma, ZSigma, NSigma;
	INT bPSigma, bNSigma;
	INT ZXi, NXi;
	INT cPXi, cZXi, bNXi;
	INT NOmega, cZOmega;
	*/
	NUM EnergySystem;
	NUM massSystem;
	INT ParticleCombination[34];

	ConserveNum NumComb;
} ReactParticle;

class Particle
{
public:
	Particle(
		particleClass	particle,
		INT				charge,
		INT				LNumElectron,
		INT				LNumMuon,
		INT				LNumTauon,
		NUM				BaryonNum,
		INT				StrangeNum,
		NUM				mass,
		const char*		tagName);

	particleClass particleType;
	INT	charge;
	INT	LNumElectron;
	INT	LNumMuon;
	INT	LNumTauon;
	NUM	BaryonNum;
	INT	StrangeNum;
	NUM mass;

	const char* tag;
};

class ParticleDatabase
{
public:
	// Leptons and Antileptons
	static Particle Electron_part;
	static Particle nuElectron_part;
	static Particle Positron_part;
	static Particle AnuElectron_part;

	static Particle Muon_part;
	static Particle nuMuon_part;
	static Particle PMuon_part;
	static Particle AnuMuon_part;

	static Particle Tau_part;
	static Particle nuTau_part;
	static Particle PTau_part;
	static Particle AnuTau_part;

	// Hadrons
	static Particle PPion_part;
	static Particle ZPion_part;
	static Particle NPion_part;

	static Particle PKaon_part;
	static Particle NKaon_part;

	static Particle Proton_part;
	static Particle Neutron_part;

	static Particle ZLambda_part;
	static Particle cLambda_part;
	static Particle bLambda_part;

	static Particle PSigma_part;
	static Particle ZSigma_part;
	static Particle NSigma_part;
	static Particle bPSigma_part;
	static Particle bNSigma_part;

	static Particle ZXi_part;
	static Particle NXi_part;
	static Particle cPXi_part;
	static Particle cZXi_part;
	static Particle bNXi_part;

	static Particle NOmega_part;
	static Particle cZOmega_part;
	static PPAR pDBP[34];

	static void initializeDatabase(void);
};

extern ParticleDatabase dbParticles;

void ReactParticleInit(ReactParticle* target);
void ConserveNumCalculate(ReactParticle* pRP);

BOOL incrementArray(INT* array, INT size, INT max_value);

SIMRESULT CompareReactParticles(
	ReactParticle* initial,
	ReactParticle* final
);
SIMRESULT FindReactionProduct(
	ReactParticle* input,
	ReactParticle* output
);

#endif