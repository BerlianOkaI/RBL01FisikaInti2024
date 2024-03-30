#include "DataBase.h"
#include <iostream>

using namespace std;

#define PDB		ParticleDatabase

PPAR PDB::pDBP[34];

Particle::Particle(
	particleClass	particle,
	INT				charge,
	INT				LNumElectron,
	INT				LNumMuon,
	INT				LNumTauon,
	NUM				BaryonNum,
	INT				StrangeNum,
	NUM				mass,
	const char*		tagName
)
{
	this->particleType	= particle;
	this->charge		= charge;
	this->LNumElectron	= LNumElectron;
	this->LNumMuon		= LNumMuon;
	this->LNumTauon		= LNumTauon;
	this->BaryonNum		= BaryonNum;
	this->StrangeNum	= StrangeNum;
	this->mass			= mass;

	this->tag = tagName;
}

void ParticleDatabase::initializeDatabase(void)
{
	// Leptons
	PDB::pDBP[Electron] = &PDB::Electron_part;
	PDB::pDBP[nuElectron] = &PDB::nuElectron_part;
	PDB::pDBP[Positron] = &PDB::Positron_part;
	PDB::pDBP[AnuElectron] = &PDB::AnuElectron_part;

	PDB::pDBP[Muon] = &PDB::Muon_part;
	PDB::pDBP[nuMuon] = &PDB::nuMuon_part;
	PDB::pDBP[PMuon] = &PDB::PMuon_part;
	PDB::pDBP[AnuMuon] = &PDB::AnuMuon_part;

	PDB::pDBP[Tau] = &PDB::Tau_part;
	PDB::pDBP[nuTau] = &PDB::nuTau_part;
	PDB::pDBP[PTau] = &PDB::PTau_part;
	PDB::pDBP[AnuTau] = &PDB::AnuTau_part;

	// Hadrons
	PDB::pDBP[PPion] = &PDB::PPion_part;
	PDB::pDBP[ZPion] = &PDB::ZPion_part;
	PDB::pDBP[NPion] = &PDB::NPion_part;

	PDB::pDBP[PKaon] = &PDB::PKaon_part;
	PDB::pDBP[NKaon] = &PDB::NKaon_part;

	PDB::pDBP[Proton] = &PDB::Proton_part;
	PDB::pDBP[Neutron] = &PDB::Neutron_part;

	PDB::pDBP[ZLambda] = &PDB::ZLambda_part;
	PDB::pDBP[cLambda] = &PDB::cLambda_part;
	PDB::pDBP[bLambda] = &PDB::bLambda_part;

	PDB::pDBP[PSigma] = &PDB::PSigma_part;
	PDB::pDBP[ZSigma] = &PDB::ZSigma_part;
	PDB::pDBP[NSigma] = &PDB::NSigma_part;
	PDB::pDBP[bPSigma] = &PDB::bPSigma_part;
	PDB::pDBP[bNSigma] = &PDB::bNSigma_part;

	PDB::pDBP[ZXi] = &PDB::ZXi_part;
	PDB::pDBP[NXi] = &PDB::NXi_part;
	PDB::pDBP[cPXi] = &PDB::cPXi_part;
	PDB::pDBP[cZXi] = &PDB::cZXi_part;
	PDB::pDBP[bNXi] = &PDB::bNXi_part;

	PDB::pDBP[NOmega] = &PDB::NOmega_part;
	PDB::pDBP[cZOmega] = &PDB::cZOmega_part;
}

void ReactParticleInit(ReactParticle* target)
{
	for (int iter = 0; iter < 34; iter++)
	{
		target->ParticleCombination[iter] = 0;
	}
}
void ConserveNumCalculate(ReactParticle* pRP)
{
	pRP->NumComb.charge = 0;
	pRP->NumComb.LNumElectron = 0;
	pRP->NumComb.LNumMuon = 0;
	pRP->NumComb.LNumTauon = 0;
	pRP->NumComb.BaryonNum = 0;
	pRP->NumComb.StrangeNum = 0;
	pRP->massSystem = 0;

	for (int iter = 0; iter < 34; iter++)
	{
		pRP->NumComb.charge			+= pRP->ParticleCombination[iter] * PDB::pDBP[iter]->charge;
		pRP->NumComb.LNumElectron	+= pRP->ParticleCombination[iter] * PDB::pDBP[iter]->LNumElectron;
		pRP->NumComb.LNumMuon		+= pRP->ParticleCombination[iter] * PDB::pDBP[iter]->LNumMuon;
		pRP->NumComb.LNumTauon		+= pRP->ParticleCombination[iter] * PDB::pDBP[iter]->LNumTauon;
		pRP->NumComb.BaryonNum		+= pRP->ParticleCombination[iter] * PDB::pDBP[iter]->BaryonNum;
		pRP->NumComb.StrangeNum		+= pRP->ParticleCombination[iter] * PDB::pDBP[iter]->StrangeNum;

		pRP->massSystem += pRP->ParticleCombination[iter] * PDB::pDBP[iter]->mass;
	}
}

SIMRESULT CompareReactParticles(
	ReactParticle* initial,
	ReactParticle* final
)
{
	ConserveNumCalculate(initial);
	ConserveNumCalculate(final);
	
	if (initial->NumComb.charge != final->NumComb.charge) {
		return 0;
	}
	if (initial->NumComb.LNumElectron != final->NumComb.LNumElectron) {
		return 0;
	}
	if (initial->NumComb.LNumMuon != final->NumComb.LNumMuon) {
		return 0;
	}
	if (initial->NumComb.LNumTauon != final->NumComb.LNumTauon) {
		return 0;
	}
	if (initial->NumComb.BaryonNum != final->NumComb.BaryonNum) {
		return 0;
	}
	if (initial->NumComb.StrangeNum != final->NumComb.StrangeNum) {
		return 0;
	}
	if (initial->massSystem < final->massSystem)
	{
		return 0;
	}
	return 1;
}

BOOL incrementArray(INT* array, INT size, INT max_value)
{
	BOOL loop_status, pointer;
	pointer = 0;
	loop_status = 1;
	while (loop_status && pointer < size)
	{
		array[pointer] += 1;
		if (array[pointer] > max_value)
		{
			array[pointer] = 0;
			pointer++;
		}
		else {
			loop_status = 0;
		}
	}
	if (pointer >= size) {
		// Array overflown
		return 1;
	}
	else {
		return 0;
	}
}

SIMRESULT FindReactionProduct(
	ReactParticle* input,
	ReactParticle* output
)
{
	SIMRESULT result = 0;
	// Initiating output
	ReactParticleInit(output);
	// Calculating conservenum of input
	ConserveNumCalculate(input);
	BOOL loops = 1;

	while (loops)
	{
		if (incrementArray(output->ParticleCombination, 34, 1)) {
			loops = 0;
		}
		ConserveNumCalculate(output);
		if (CompareReactParticles(input, output))
		{
			// Match occur!
			cout << "Found Reaction Result!" << endl;
			for (int iter2 = 0; iter2 < 34; iter2++)
			{
				if (output->ParticleCombination[iter2])
				{
					cout << PDB::pDBP[iter2]->tag << "\t: " << output->ParticleCombination[iter2];
					cout << endl;
				}
			}
			cout << endl;
			result += 1;
		}
	}
	return result;
}


// Database
Particle ParticleDatabase::Electron_part(
	Electron,
	-1,
	1, 0, 0,
	0, 0,
	elecMass,
	"Electron"
);

Particle ParticleDatabase::nuElectron_part(
	nuElectron,
	0,
	1, 0, 0,
	0, 0,
	2 * pow(10.0, -6.0),
	"nuElectron"
);

Particle ParticleDatabase::Positron_part(
	Positron,
	1,
	-1, 0, 0,
	0, 0,
	elecMass,
	"Positron"
);

Particle ParticleDatabase::AnuElectron_part(
	AnuElectron,
	0,
	-1, 0, 0,
	0, 0,
	2 * pow(10.0, -6.0),
	"AnuElectron"
);

Particle ParticleDatabase::Muon_part(
	Muon,
	-1,
	0, 1, 0,
	0, 0,
	105.7,
	"Muon"
);

Particle ParticleDatabase::nuMuon_part(
	nuMuon,
	0,
	0, 1, 0,
	0, 0,
	0.19,
	"nuMuon"
);

Particle ParticleDatabase::PMuon_part(
	PMuon,
	1,
	0, -1, 0,
	0, 0,
	105.7,
	"PMuon"
);

Particle ParticleDatabase::AnuMuon_part(
	AnuMuon,
	0,
	0, -1, 0,
	0, 0,
	0.19,
	"AnuMuon"
);

Particle ParticleDatabase::Tau_part(
	Tau,
	-1,
	0, 0, 1,
	0, 0,
	1776.9,
	"Tau"
);

Particle ParticleDatabase::nuTau_part(
	nuTau,
	0,
	0, 0, 1,
	0, 0,
	18.2,
	"nuTau"
);

Particle ParticleDatabase::PTau_part(
	PTau,
	1,
	0, 0, -1,
	0, 0,
	1776.9,
	"PTau"
);

Particle ParticleDatabase::AnuTau_part(
	AnuTau,
	0,
	0, 0, -1,
	0, 0,
	18.2,
	"AnuTau"
);

// Hadrons
Particle ParticleDatabase::PPion_part(
	PPion,
	1,
	0, 0, 0,
	0, 0,
	139.58,
	"PPion"
);

Particle ParticleDatabase::ZPion_part(
	ZPion,
	0,
	0, 0, 0,
	0, 0,
	135.0,
	"ZPion"
);

Particle ParticleDatabase::NPion_part(
	NPion,
	-1,
	0, 0, 0,
	0, 0,
	139.58,
	"NPion"
);

Particle ParticleDatabase::PKaon_part(
	PKaon,
	1,
	0, 0, 0,
	0, 1,
	493.7,
	"PKaon"
);

Particle ParticleDatabase::NKaon_part(
	NKaon,
	-1,
	0, 0, 0,
	0, -1,
	493.7,
	"NKaon"
);

Particle ParticleDatabase::Proton_part(
	Proton,
	1,
	0, 0, 0,
	1, 0,
	938.3,
	"Proton"
);

Particle ParticleDatabase::Neutron_part(
	Neutron,
	0,
	0, 0, 0,
	1, 0,
	939.6,
	"Neutron"
);

Particle ParticleDatabase::ZLambda_part(
	ZLambda,
	0,
	0, 0, 0,
	1, -1,
	1115.7,
	"ZLambda"
);

Particle ParticleDatabase::cLambda_part(
	cLambda,
	1,
	0, 0, 0,
	1, 0,
	2285.0,
	"cLambda"
);

Particle ParticleDatabase::bLambda_part(
	bLambda,
	0,
	0, 0, 0,
	1, 0,
	5624.0,
	"bLambda"
);

Particle ParticleDatabase::PSigma_part(
	PSigma,
	1,
	0, 0, 0,
	1, -1,
	1189.4,
	"PSigma"
);

Particle ParticleDatabase::ZSigma_part(
	ZSigma,
	0,
	0, 0, 0,
	1, -1,
	1192.5,
	"ZSigma"
);

Particle ParticleDatabase::NSigma_part(
	NSigma,
	-1,
	0, 0, 0,
	1, -1,
	1197.4,
	"NSigma"
);

Particle ParticleDatabase::bPSigma_part(
	bPSigma,
	1,
	0, 0, 0,
	1, 0,
	5.81,
	"bPSigma"
);

Particle ParticleDatabase::bNSigma_part(
	bNSigma,
	-1,
	0, 0, 0,
	1, 0,
	5.81,
	"bNSigma"
);

Particle ParticleDatabase::ZXi_part(
	ZXi,
	0,
	0, 0, 0,
	1, -2,
	1315.0,
	"ZXi"
);

Particle ParticleDatabase::NXi_part(
	NXi,
	-1,
	0, 0, 0,
	1, -2,
	1321.0,
	"NXi"
);

Particle ParticleDatabase::cPXi_part(
	cPXi,
	1,
	0, 0, 0,
	1, -1,
	2466.0,
	"cPXi"
);

Particle ParticleDatabase::cZXi_part(
	cZXi,
	0,
	0, 0, 0,
	1, -1,
	2472.0,
	"cZXi"
);

Particle ParticleDatabase::bNXi_part(
	bNXi,
	-1,
	0, 0, 0,
	1, -1,
	5792.3,
	"bNXi"
);

Particle ParticleDatabase::NOmega_part(
	NOmega,
	-1,
	0, 0, 0,
	1, -3,
	1672.0,
	"NOmega"
);

Particle ParticleDatabase::cZOmega_part(
	cZOmega,
	0,
	0, 0, 0,
	1, -2,
	2698.0,
	"cZOmega"
);
