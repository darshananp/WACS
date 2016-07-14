#include "CSEventAction.hh"

#include "CSRunAction.hh"
#include "CSSteppingAction.hh"
  // use of stepping action to get and reset accumulated energy  

#include "G4RunManager.hh"
#include "G4Event.hh"

CSEventAction* CSEventAction::fgInstance = 0;

CSEventAction* CSEventAction::Instance()
{
// Static acces function via G4RunManager 

  return fgInstance;
}      

CSEventAction::CSEventAction(): G4UserEventAction(), fPrintModulo(100), fEnergySum(0.), fEnergy2Sum(0.)
{ 
  fgInstance = this;
}

CSEventAction::~CSEventAction()
{ 
  fgInstance = 0;
}

void CSEventAction::BeginOfEventAction(const G4Event* event)
{  
  G4int eventNb = event->GetEventID();
  if (eventNb%fPrintModulo == 0) { 
    G4cout << "\n---> Begin of event: " << eventNb << G4endl;
  }
 
  // Reset accounted energy in stepping action
  CSSteppingAction::Instance()->Reset();
}

void CSEventAction::EndOfEventAction(const G4Event* /*event*/)
{
  // accumulate statistics
  G4double energy = CSSteppingAction::Instance()->GetEnergy();
  fEnergySum  += energy;
  fEnergy2Sum += energy*energy;
}  

void CSEventAction::Reset()
{
  //reset cumulative quantities
  //
  fEnergySum = 0.;
  fEnergy2Sum = 0.;
}

