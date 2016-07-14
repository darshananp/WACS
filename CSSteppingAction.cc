#include "CSSteppingAction.hh"

#include "CSDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"


CSSteppingAction* CSSteppingAction::fgInstance = 0;

CSSteppingAction* CSSteppingAction::Instance()
{
// Static acces function via G4RunManager 

  return fgInstance;
}      

CSSteppingAction::CSSteppingAction()
: G4UserSteppingAction(),
  fVolume(0),
  fEnergy(0.)
{ 
  fgInstance = this;
}

CSSteppingAction::~CSSteppingAction()
{ 
  fgInstance = 0;
}

void CSSteppingAction::UserSteppingAction(const G4Step* step)
{
  // get volume of the current step
  G4LogicalVolume* volume 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  if (volume != fVolume ) return;

  // collect energy and track length step by step
  G4double edep = step->GetTotalEnergyDeposit();
  fEnergy += edep;
}

void CSSteppingAction::Reset()
{
  fEnergy = 0.;
}
