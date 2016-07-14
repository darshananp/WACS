#include "G4Step.hh"
#include "G4SystemOfUnits.hh"
#include "VacDetector.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include "G4TouchableHistory.hh"
#include "G4VPhysicalVolume.hh"

#include<fstream>
#include<iostream>

#include "G4RunManager.hh"

using namespace std;

//extern G4int pid;

VacDetector::VacDetector(G4String name): G4VSensitiveDetector(name)
{
  

}

G4bool VacDetector::ProcessHits(G4Step *step, G4TouchableHistory *hist)
{

  static int num = 0; //number of hits
  G4ThreeVector vertexPos; 
  G4ThreeVector hitPos;
  const G4LogicalVolume* logic; 
  G4String vertexName;
  G4int PDG;
  G4ThreeVector worldPos;
  G4TouchableHandle touchable;
  G4ThreeVector localPos;
  G4double Mom;
  G4double E;
  G4double eDep_total;
  G4double eDep_nonIonize;
  G4double eDep_Ionize;
  G4ThreeVector momdir;
  G4double theta;
  G4double phi;
  G4int eid;
  G4int trackID;
  G4bool atBoundary;
  G4double stepLength;
  G4int cpNo;
  G4ThreeVector centerPos;
  G4double TrackLength;
  


  G4TouchableHistory* theTouchable = (G4TouchableHistory*)(step->GetPreStepPoint()->GetTouchable());
  G4VPhysicalVolume* physVol = theTouchable->GetVolume();

  //Hit Position
  worldPos = step->GetTrack()->GetVertexPosition();
  touchable = step->GetPreStepPoint()->GetTouchableHandle();
  //localPos = touchable->GetHistory()->GetTransform(1).TransformPoint(worldPos);
  
  //Event number
  eid = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();

  //Momentum
  Mom = step->GetPreStepPoint()->GetMomentum().mag();
  if (Mom==0.) return false;

  //Energy
  E = step->GetPreStepPoint()->GetKineticEnergy();

  //Particle momentum direction
  momdir = step->GetPreStepPoint()->GetMomentumDirection();

  //calculating theta and phi

  theta = fabs((acos(momdir.z())));
  phi = atan2(momdir.y(),momdir.x());

  //Step length
  stepLength = step->GetStepLength();
      
  //Particle ID
  PDG = step->GetTrack()->GetDefinition()->GetPDGEncoding();
  

  //Saving in a text file
      
      std::ostringstream convert;
 //     convert << pid;
      std::string pid_string = convert.str();
      
      std::ofstream file;
      //file.open(("/scratch/mmk6qa/DINREG/VacDetector_" + pid_string + ".txt").c_str(), std::ios::app);
      file.open(("VacDetector_" + pid_string + ".txt").c_str(), std::ios::app);
      
      
      file<< std::setw(5) << eid <<" "
	  << std::setw(5) << E/MeV <<" "
	  << std::setw(5) << stepLength/cm <<" "
	  << std::setw(10) << theta/deg <<" "
	  << std::setw(10) << phi/deg <<" "
	  << std::setw(10) << PDG << std::endl;
      
      file.close();
  
  return true;
}



void VacDetector::EndOfEvent(G4HCofThisEvent*)
{
  
}



VacDetector::~VacDetector()
{
}
