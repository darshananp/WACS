#ifndef CSEventAction_h
#define CSEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class CSSteppingAction;

/// Event action class
///
/// It holds data member fEnergySum and fEnergy2Sum for accumulating 
/// the event energy deposit its square event by event.
/// These data are then used in the run action to compute the dose.
/// The accumulated energy and enrgy square sums are reset for each 
/// new run via the Reset() function from the run action.

class CSEventAction : public G4UserEventAction
{
  public:
    CSEventAction();
    virtual ~CSEventAction();
    
    // static access method
    static CSEventAction* Instance();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void Reset();

    // get methods
    G4double GetEnergySum() const { return fEnergySum; }
    G4double GetEnergy2Sum() const { return fEnergy2Sum; }
     
  private:
    static CSEventAction* fgInstance;  

    G4int     fPrintModulo;
    G4double  fEnergySum;
    G4double  fEnergy2Sum;
};

#endif

