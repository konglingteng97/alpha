//
//__author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
//__copyright__ = "Copyright (c) Lingteng Kong"
//__created__ = "[29/06/2020 Mon 21:23]"
//
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class of alpha detection
//

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4LogicalVolume;
class G4Material;
class DetectorMessenger;

//The experiment geometry is provided as a class which inherits from the abstract class G4VUserDetectorConstruction. 
//It must overload the method G4VPhysicalVolume* Construct() which returns a pointer to the experiment geometry.
class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual 
    G4VPhysicalVolume* Construct();
    void SetMaterial (const G4String&);

    const
    G4VPhysicalVolume* GetWorld() const     {return fBox;};
    const G4Material*  GetMaterial() const  {return fMaterial;};
    
    void  PrintParameters() const;

  private:
    G4double world_sizeX;
    G4double world_sizeY;
    G4double world_sizeZ;

    G4VPhysicalVolume*    fBox;
    G4Material*           fMaterial; 
    DetectorMessenger*    fDetectorMessenger;

  private:
    
    void               DefineMaterials();
};

#endif /*DetectorConstruction_h*/
