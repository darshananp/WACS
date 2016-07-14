#include "CSDetectorConstruction.hh"
#include "CSSteppingAction.hh"
   // use of stepping action to set the accounting volume

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh" 
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SubtractionSolid.hh"
#include "VacDetector.hh"
#include "G4SDManager.hh"

static const G4double INCH = 2.54*cm;

CSDetectorConstruction::CSDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

CSDetectorConstruction::~CSDetectorConstruction()
{ }

G4VPhysicalVolume* CSDetectorConstruction::Construct()
{  
  G4NistManager* nist = G4NistManager::Instance();

  G4bool checkOverlaps = true; 

  G4RotationMatrix* rotD3 = new G4RotationMatrix();
  rotD3->rotateX(90.*deg);

  G4RotationMatrix* magD3 = new G4RotationMatrix();
  magD3->rotateX(-5.5*deg);

  G4RotationMatrix* tubD3 = new G4RotationMatrix();
  tubD3->rotateX(-7.8*deg);

// Colors 
  G4VisAttributes* shape1Att = new G4VisAttributes(G4Colour(1,0,0));
  G4VisAttributes* shape2Att = new G4VisAttributes(G4Colour(0,1,0));
  G4VisAttributes* shape3Att = new G4VisAttributes(G4Colour(0,0,1));
  G4VisAttributes* shape4Att = new G4VisAttributes(G4Colour(1,0,1));

// World
  G4double world_sizeXY = 8*m;
  G4double world_sizeZ  = 20*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld = new G4Box("World", world_sizeXY, world_sizeXY, world_sizeZ);       
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");                                  
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);                

// SCATTERING CHAMBER CONTAINER

  G4Material* Scat_ch_cont_mat = nist->FindOrBuildMaterial("G4_He");
  G4ThreeVector Scat_ch_cont_pos = G4ThreeVector(0*cm, 0*cm, 0*cm); 
  G4double innerRadius = 0*cm; G4double outerRadius = 20*cm; G4double hz = 10*cm;
  G4double startAngle = 0.*deg; G4double spanningAngle = 360.*deg;
  G4Tubs* Scat_ch_cont = new G4Tubs("Scat_ch_container",innerRadius,outerRadius,hz,startAngle,spanningAngle);
  G4LogicalVolume* logic_Scat_ch_cont =  new G4LogicalVolume(Scat_ch_cont,Scat_ch_cont_mat, "Shape_Scat_ch_cont"); 
  logic_Scat_ch_cont -> SetVisAttributes(shape2Att);
  new G4PVPlacement(rotD3, Scat_ch_cont_pos, logic_Scat_ch_cont, "Shape_Scat_ch_cont", logicWorld, false, 0, checkOverlaps);


//TARGET POST

  G4Material* Target_post_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4ThreeVector Target_post_pos = G4ThreeVector(0*cm,-150*cm, 0*cm);
  G4double post_innerRadius = 0*cm; G4double post_outerRadius = 20*cm; G4double post_hz = 25*cm;
  G4double post_startAngle = 0.*deg; G4double post_spanningAngle = 360.*deg;
  G4Tubs* Target_post = new G4Tubs("Target_post1",post_innerRadius,post_outerRadius,post_hz,post_startAngle,post_spanningAngle);
  G4LogicalVolume* logic_Target_post =  new G4LogicalVolume(Target_post,Target_post_mat, "Shape_Target_post"); 
  logic_Target_post-> SetVisAttributes(shape1Att);
  new G4PVPlacement(rotD3, Target_post_pos, logic_Target_post, "Shape_Target_post", logicWorld, false, 0, checkOverlaps);


// COPPER RADIATOR

  G4Material* Cu_rad_mat = nist->FindOrBuildMaterial("G4_Cu");
  G4ThreeVector Cu_rad_pos = G4ThreeVector(0*cm, 0*cm,-650*cm); 
  G4double rad_innerRadius = 0*cm; G4double rad_outerRadius = 10*cm; G4double rad_hz = 0.5*cm;
  G4double rad_startAngle = 0.*deg; G4double rad_spanningAngle = 360.*deg;
  G4Tubs* Cu_rad = new G4Tubs("Cu_rad1",rad_innerRadius,rad_outerRadius,rad_hz,rad_startAngle,rad_spanningAngle);
  G4LogicalVolume* logic_Cu_rad =  new G4LogicalVolume(Cu_rad,Cu_rad_mat, "Shape_Cu_rad"); 
  logic_Cu_rad-> SetVisAttributes(shape3Att);
  new G4PVPlacement(0, Cu_rad_pos, logic_Cu_rad, "Shape_Cu_rad", logicWorld, false, 0, checkOverlaps);


//PHOTON BEAM PIPE

  G4Material* PhotonBeamPipe_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector PhotonBeamPipe_pos = G4ThreeVector(0*cm, 0*cm,-220*cm); 
  G4double bPipe_innerRadius = 5*cm; G4double bPipe_outerRadius = 6*cm; G4double bPipe_hz = 200*cm;
  G4double bPipe_startAngle = 0.*deg; G4double bPipe_spanningAngle = 360.*deg;
  G4Tubs* PhotonBeamPipe = new G4Tubs("PhotonBeamPipe1",bPipe_innerRadius,bPipe_outerRadius,bPipe_hz,bPipe_startAngle,bPipe_spanningAngle);
  G4LogicalVolume* logic_PhotonBeamPipe =  new G4LogicalVolume(PhotonBeamPipe,PhotonBeamPipe_mat, "Shape_PhotonBeamPipe"); 
  new G4PVPlacement(0, PhotonBeamPipe_pos, logic_PhotonBeamPipe, "Shape_PhotonBeamPipe", logicWorld, false, 0, checkOverlaps);

//Magnet
  G4Material* Dipole1Container_mat = nist->FindOrBuildMaterial("G4_He");
  G4ThreeVector Dipole1Container_pos = G4ThreeVector(0*cm, -9.5*cm,-523*cm); 
  G4double dPole_px = 20*cm; G4double dPole_py = 20*cm; G4double dPole_pz = 100*cm;
  G4Box* Dipole1Container = new G4Box("Dipole1Container1", dPole_px, dPole_py, dPole_pz);
  G4LogicalVolume* logic_Dipole1Container =  new G4LogicalVolume(Dipole1Container,Dipole1Container_mat, "Shape_Dipole1Container"); 
  logic_Dipole1Container-> SetVisAttributes(shape4Att);
  new G4PVPlacement(magD3, Dipole1Container_pos, logic_Dipole1Container, "Shape_Dipole1Container", logicWorld, false, 0, checkOverlaps);


// DEFLECTED ELECTRON BEAM PIPE and LOCAL DUMP and HALL DUMP

  G4Material* Local_dumpmat = nist->FindOrBuildMaterial("G4_Cu");
  G4ThreeVector Local_dumppos = G4ThreeVector(0*cm, -130*cm,420*cm); 
  G4double L_dump_innerRadius = 0*cm; G4double L_dump_outerRadius = 40*cm; G4double L_dump_hz = 20*cm;
  G4double L_dump_startAngle = 0.*deg; G4double L_dump_spanningAngle = 360.*deg;
  G4Tubs* L_dump = new G4Tubs("L_dump1",L_dump_innerRadius,L_dump_outerRadius,L_dump_hz,L_dump_startAngle,L_dump_spanningAngle);
  G4LogicalVolume* logic_L_dump =  new G4LogicalVolume(L_dump,Local_dumpmat, "Shape_L_dump"); 
  logic_L_dump-> SetVisAttributes(shape3Att);

  VacDetector* detector = new VacDetector("/Detector");
  G4SDManager* sdman = G4SDManager::GetSDMpointer();
  sdman->AddNewDetector(detector);
  logic_L_dump->SetSensitiveDetector(detector);

  new G4PVPlacement(0, Local_dumppos, logic_L_dump, "Shape_L_dump", logicWorld, false, 0, checkOverlaps);
//------------------------------------------------------------------------------------------------------


  G4Material* elecBeamPipe_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector elecBeamPipe_pos = G4ThreeVector(0*cm, -75.0*cm,0*cm); 
  G4double elec_innerRadius = 7*cm; G4double elec_outerRadius = 8*cm; G4double elec_hz = 424*cm;
  G4double elec_startAngle = 0.*deg; G4double elec_spanningAngle = 360.*deg;
  G4Tubs* elecBeamPipe = new G4Tubs("elecBeamPipe1",elec_innerRadius,elec_outerRadius,elec_hz,elec_startAngle,elec_spanningAngle);
  G4LogicalVolume* logic_elecBeamPipe =  new G4LogicalVolume(elecBeamPipe,elecBeamPipe_mat, "Shape_elecBeamPipe"); 
  new G4PVPlacement(tubD3, elecBeamPipe_pos, logic_elecBeamPipe, "Shape_elecBeamPipe", logicWorld, false, 0, checkOverlaps);


  G4Material* Hall_dumpmat = nist->FindOrBuildMaterial("G4_Cu");
  G4ThreeVector Hall_dumppos = G4ThreeVector(0*cm, 0*cm,620*cm); 
  G4double H_dump_innerRadius = 0*cm; G4double H_dump_outerRadius = 80*cm; G4double H_dump_hz = 20*cm;
  G4double H_dump_startAngle = 0.*deg; G4double H_dump_spanningAngle = 360.*deg;
  G4Tubs* H_dump = new G4Tubs("H_dump1",H_dump_innerRadius,H_dump_outerRadius,H_dump_hz,H_dump_startAngle,H_dump_spanningAngle);
  G4LogicalVolume* logic_H_dump =  new G4LogicalVolume(H_dump,Hall_dumpmat, "Shape_H_dump"); 
  logic_H_dump-> SetVisAttributes(shape3Att);
  new G4PVPlacement(0, Hall_dumppos, logic_H_dump, "Shape_H_dump", logicWorld, false, 0, checkOverlaps);


  CSSteppingAction* steppingAction = CSSteppingAction::Instance(); 
  steppingAction->SetVolume(logic_H_dump);

  return physWorld;
}
