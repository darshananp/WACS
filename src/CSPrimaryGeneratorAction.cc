#include "CSPrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"


CSPrimaryGeneratorAction* CSPrimaryGeneratorAction::fgInstance = 0;
const CSPrimaryGeneratorAction* CSPrimaryGeneratorAction::Instance()
{
// Static acces function via G4RunManager 

  return fgInstance;
}      
CSPrimaryGeneratorAction::CSPrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName="e-");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(8.8*GeV);
  
  fgInstance = this;
}

CSPrimaryGeneratorAction::~CSPrimaryGeneratorAction()
{
  delete fParticleGun;
  fgInstance = 0;
}

void CSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  //

  G4double x0 = 0*cm;
  G4double y0 = 0*cm;
  G4double z0 = -1000*cm;
  
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

