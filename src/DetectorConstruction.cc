/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-17 02:40:49 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-21 23:10:27
 */

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//Define world
DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
 fBox(nullptr),fMaterial(nullptr)
{
  world_sizeX = 10.0*m;
  world_sizeY = 10.0*m;
  world_sizeZ = 10.0*m;

  DefineMaterials();
  SetMaterial("Air");  
  fDetectorMessenger = new DetectorMessenger(this);
  PrintParameters();
}

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

//Define material
void DetectorConstruction::DefineMaterials()
{
 //Define elements
  G4double a, z;
  G4int nelements;

  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  G4Element* H  = new G4Element("Hydrogen" ,"H" , z= 1., a=   1.01*g/mole);

  //Define material
  //0 degree and 1 atm
  G4double density;
  G4int ncomponents, natoms;
  G4double fractionmass;  

  G4Material* Air = new G4Material("Air", density=1.290*mg/cm3, nelements=2);
  Air->AddElement(N, fractionmass=70.*perCent);
  Air->AddElement(O, fractionmass=30.*perCent);

  G4Material* N2 = 
  new G4Material("Nitrogen", density= 1.251*mg/cm3, ncomponents=1);
  N2->AddElement(N, fractionmass=1.);

  G4Material* H2O = 
  new G4Material("Water", density= 1.000*g/cm3, ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  ///H2O->SetChemicalFormula("H_2O");
  H2O->GetIonisation()->SetMeanExcitationEnergy(78.0*eV);
        
  G4Material* steam = 
  new G4Material("WaterSteam", density= 1.0*mg/cm3, ncomponents=1);
  steam->AddMaterial(H2O, fractionmass=1.);
  steam->GetIonisation()->SetMeanExcitationEnergy(71.6*eV); 

  G4Material* argonGas =   
  new G4Material("ArgonGas", z=18, a=39.948*g/mole, density= 1.782*mg/cm3,
                 kStateGas, 273.15*kelvin, 1*atmosphere);

 //Matrial properties for scintillation process

 //Air
 //number of photons generated is proportional to the energy lost during the step
  G4double AirPhotonEnergy[] =
              { 3.168*eV, 3.258*eV, 3.301*eV, 3.466*eV,
                3.505*eV, 3.678*eV, 3.925*eV, 3.954*eV };

  const G4int nEntries_Air = sizeof(AirPhotonEnergy)/sizeof(G4double);

  G4double AirScintilFast[] =    //Fast intensity
              { 0.28, 0.27, 0.18, 0.67, 
                0.21, 1., 0.39, 0.11 };

  assert(sizeof(AirScintilFast) == sizeof(AirPhotonEnergy));

  G4MaterialPropertiesTable* AirMPT = new G4MaterialPropertiesTable();
  
  AirMPT->AddProperty("FASTCOMPONENT",AirPhotonEnergy, AirScintilFast, nEntries_Air)
        ->SetSpline(true);
  //gaussian distribution? scintillation photon produced per absorbed energy 
  AirMPT->AddConstProperty("SCINTILLATIONYIELD",20./MeV);
  //broadens the statistical distribution of generated photons
  //widen given by resolutionscale*sqrt(meannumberofphotons)
  AirMPT->AddConstProperty("RESOLUTIONSCALE",1.); // >1 broaden the fluctuation 
  //Decay time constant
  AirMPT->AddConstProperty("FASTTIMECONSTANT", 1.*ns);  

  Air->SetMaterialPropertiesTable(AirMPT);

  //Nitrogen
  //data from 'Spectral measurement of alpha-induced radioluminescence in various gases'
  //to be completed
  G4double N2PhotonEnergy[] =
              { 3.168*eV, 3.258*eV, 3.301*eV, 3.466*eV,
                3.505*eV, 3.678*eV, 3.925*eV, 3.954*eV,
                4.593*eV, 5.00*eV};

  const G4int nEntries_N2 = sizeof(N2PhotonEnergy)/sizeof(G4double);

  G4double N2ScintilFast[] =    
              { 0.28, 0.27, 0.18, 0.67, 
                0.21, 1.,   0.39, 0.11,
                1.2,  1.42 };

  assert(sizeof(N2ScintilFast) == sizeof(N2PhotonEnergy));

  G4MaterialPropertiesTable* N2MPT = new G4MaterialPropertiesTable();
  
  N2MPT->AddProperty("FASTCOMPONENT",N2PhotonEnergy, N2ScintilFast, nEntries_N2)
        ->SetSpline(true);
  N2MPT->AddConstProperty("SCINTILLATIONYIELD",200./MeV); //ten times more than air
  N2MPT->AddConstProperty("RESOLUTIONSCALE",1.); 
  N2MPT->AddConstProperty("FASTTIMECONSTANT", 1.*ns);  

  N2->SetMaterialPropertiesTable(N2MPT);

 //argonGas (to be completed...)
  G4double ArPhotonEnergy[] =
              { 4.862*eV, 3.974*eV, 1.771*eV, 1.632*eV,
                1.512*eV };

  const G4int nEntries_Ar = sizeof(ArPhotonEnergy)/sizeof(G4double);

  G4double ArScintilFast[] =   
              { 0.2, 1., 0.45, 0.3,
                0.25 };

  assert(sizeof(ArScintilFast) == sizeof(ArPhotonEnergy));

  G4MaterialPropertiesTable* ArMPT = new G4MaterialPropertiesTable();
  
  ArMPT->AddProperty("FASTCOMPONENT",ArPhotonEnergy, ArScintilFast, nEntries_Ar)
        ->SetSpline(true);
  ArMPT->AddConstProperty("SCINTILLATIONYIELD",100./MeV);
  ArMPT->AddConstProperty("RESOLUTIONSCALE",1.);  
  ArMPT->AddConstProperty("FASTTIMECONSTANT", 1.*ns);  

  argonGas->SetMaterialPropertiesTable(ArMPT);
}

//----------------------------------volume----------------------------------
G4VPhysicalVolume* DetectorConstruction::Construct()
{
  if(fBox) { return fBox; }

 //In Geant4, any simulated object is defined in three steps.
 //First, a box which is basically a 3D shape, like a cube or a sphere, is created. 
  G4Box* solidWorld = new G4Box("World",world_sizeX,world_sizeX,world_sizeX);

 //Fill the world with gas.
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, fMaterial, fMaterial->GetName());

 //The logical volume is turned into a physical volume by defining its position and orientation
 //Create world mother volume
  fBox = new G4PVPlacement( 0, 			//no rotation
                            G4ThreeVector(),	//at (0,0,0)
                            logicWorld,		//its logical volume
                            fMaterial->GetName(),		//its name
                            0,			//its mother  volume
                            false,	                //no boolean operation
                            0,			//copy number
                            true);			//overlaps checking

 //Finally, the detector construction class returns a pointer to the 
 //constructed geometry world volume containing the constructed geometry
  return fBox;
}

void DetectorConstruction::PrintParameters() const
{
  G4cout << "scintillation material is " << fMaterial->GetName() << G4endl;
}

#include "G4RunManager.hh"

void DetectorConstruction::SetMaterial(const G4String& materialChoice)
{
  // search the material by its name, or build it from nist data base
  G4Material* pttoMaterial = 
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);

  if (pttoMaterial) {
    fMaterial = pttoMaterial;
    if(fBox) { fBox->GetLogicalVolume()->SetMaterial(fMaterial); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetMaterial : "
           << materialChoice << " not found" << G4endl;  
  }  
}
