/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-17 02:40:49 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-19 14:37:19
 */

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
 //number of photons generated is proportional to the energy lost during the step
  G4double photonEnergy[] =
              { 3.168*eV, 3.258*eV, 3.301*eV, 3.466*eV,
                3.505*eV, 3.678*eV, 3.925*eV, 3.954*eV };

  const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

  //Fast intensity
  G4double scintilFast[] =
            { 0.28, 0.27, 0.18, 0.67, 
              0.21, 1., 0.39, 0.11 };

  assert(sizeof(scintilFast) == sizeof(photonEnergy));

  // //Slow intensity
  // G4double scintilSlow[] =
  //           { 0.28, 0.27, 0.18, 0.67, 
  //             0.21, 1.00, 0.39, 0.11 };

  // assert(sizeof(scintilSlow) == sizeof(photonEnergy));


  G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();
  
  myMPT1->AddProperty("FASTCOMPONENT",photonEnergy, scintilFast, nEntries)
        ->SetSpline(true);
  // myMPT1->AddProperty("SLOWCOMPONENT",photonEnergy, scintilSlow, nEntries)
  //       ->SetSpline(true);

  //gaussian distribution? scintillation photon produced per absorbed energy 
  myMPT1->AddConstProperty("SCINTILLATIONYIELD",20./MeV);
  //broadens the statistical distribution of generated photons
  //widen given by resolutionscale*sqrt(meannumberofphotons)
  myMPT1->AddConstProperty("RESOLUTIONSCALE",1.); // >1 broaden the fluctuation 
  //Decay time constant
  myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);  

  // G4cout << "Air G4MaterialPropertiesTable" << G4endl;
  // myMPT1->DumpTable();

  air->SetMaterialPropertiesTable(myMPT1);

//----------------------------------volume----------------------------------

 //In Geant4, any simulated object is defined in three steps.
 //First, a box which is basically a 3D shape, like a cube or a sphere, is created. 
  G4Box* solidWorld = new G4Box("World",world_sizeX,world_sizeX,world_sizeX);

 //Fill the world with air.
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, air, "World");

 //The logical volume is turned into a physical volume by defining its position and orientation
 //Create world mother volume
  G4VPhysicalVolume* physWorld = new G4PVPlacement(
              0, 			//no rotation
              G4ThreeVector(),	//at (0,0,0)
              logicWorld,		//its logical volume
              "World",		//its name
              0,			//its mother  volume
              false,	                //no boolean operation
              0,			//copy number
              true);			//overlaps checking

 //Finally, the detector construction class returns a pointer to the 
 //constructed geometry world volume containing the constructed geometry
  return physWorld;
}