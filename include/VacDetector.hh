// header file for SensitiveDetector

#ifndef VacDetector_h
#define VacDetector_h 1

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;


class VacDetector:public G4VSensitiveDetector
{
public:

  VacDetector(G4String SDname);

  ~VacDetector();

public:

  G4bool ProcessHits(G4Step* step,G4TouchableHistory* hist);

  void EndOfEvent(G4HCofThisEvent* HCE);
  
  void setOutputFileName(G4String outfile){fHe4OutputFileName = outfile;}
  
private:
  
  G4String fHe4OutputFileName;



};

#endif
