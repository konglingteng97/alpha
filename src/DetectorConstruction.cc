//
//__author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
//__copyright__ = "Copyright (c) Lingteng Kong"
//__created__ = "[29/06/2020 Mon 21:19]"
//
/// \file DetectorConstruction.cc
/// \brief The geometry is a description of all the solid objects in the simulation
//         which can interact with the particles which are being simulated. Because of 
//         Geant4's roots as a simulation system for particle accelerators, 
//         this is called the Detector Construction.
//

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//Define size of world
DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{
  world_sizeX = 10.0*m;
  world_sizeY = 10.0*m;
  world_sizeZ = 10.0*m;
}

DetectorConstruction::~DetectorConstruction(){;}

//Construct world
G4VPhysicalVolume* DetectorConstruction::Construct()
{

//Define air
  G4double a, z, density;
  G4int nelements;

  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

  G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  air->AddElement(N, 70.*perCent);
  air->AddElement(O, 30.*perCent);

//air properties table
  G4double photonEnergy[] =
            { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
              2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
              2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
              2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
              2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
              3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
              3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
              3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };

  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

  G4double scintilFast[] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  assert(sizeof(scintilFast) == sizeof(photonEnergy));

  G4double scintilSlow[] =
            { 0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
              7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
              3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
              4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
              7.00, 6.00, 5.00, 4.00 };

  assert(sizeof(scintilSlow) == sizeof(photonEnergy));

  G4double refractiveIndex[] =
            { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
              1.00, 1.00, 1.00, 1.00 };

  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
  
  myMPT1->AddProperty("RINDEX", photonEnergy, refractiveIndex, nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("FASTCOMPONENT",photonEnergy, scintilFast, nEntries)
        ->SetSpline(true);
  myMPT1->AddProperty("SLOWCOMPONENT",photonEnergy, scintilSlow, nEntries)
        ->SetSpline(true);

  myMPT1->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);   
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
  myMPT1->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
  myMPT1->AddConstProperty("YIELDRATIO",0.8);   

  G4cout << "Air G4MaterialPropertiesTable" << G4endl;

  myMPT1->DumpTable();

  air->SetMaterialPropertiesTable(myMPT1);

//----------------------------------volume----------------------------------

 //In Geant4, any simulated object is defined in three steps.
 //First, a box which is basically a 3D shape, like a cube or a sphere, is created. 
  G4Box* expHall_box = new G4Box("World",world_sizeX,world_sizeX,world_sizeX);

 //Fill the world with air.
  G4LogicalVolume* expHall_log = new G4LogicalVolume(expHall_box, air, "World");

 //The logical volume is turned into a physical volume by defining its position and orientation
 //Create world mother volume
  G4VPhysicalVolume* physWorld = new G4PVPlacement(
              0, 			//no rotation
              G4ThreeVector(),	//at (0,0,0)
              expHall_log,		//its logical volume
              "World",		//its name
              0,			//its mother  volume
              false,	                //no boolean operation
              0,			//copy number
              true);			//overlaps checking


  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);

 //Finally, the detector construction class returns a pointer to the 
 //constructed geometry world volume containing the constructed geometry
  return expHall_phys;
}