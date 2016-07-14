#ifndef CSDetectorConstruction_h
#define CSDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

/// Detector construction class to define materials and geometry.

class CSDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    CSDetectorConstruction();
    virtual ~CSDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
};

#endif

