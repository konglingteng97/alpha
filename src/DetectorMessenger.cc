/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-21 10:59:22 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-21 23:02:07
 */

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

//add UI command for detector construction
DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:G4UImessenger(),fDetector(Det),falphaDir(0),fDetDir(0),fMaterCmd(0)
{ 
  falphaDir = new G4UIdirectory("/alpha/");
  falphaDir->SetGuidance("commands specific to this simulation");
  
  fDetDir = new G4UIdirectory("/alpha/det/");
  fDetDir->SetGuidance("detector construction commands");
        
  fMaterCmd = new G4UIcmdWithAString("/alpha/det/setMat",this);
  fMaterCmd->SetGuidance("Select material of the box.");
  fMaterCmd->SetParameterName("choice",false);
  fMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DetectorMessenger::~DetectorMessenger()
{
  delete fMaterCmd;
  delete fDetDir;
  delete falphaDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == fMaterCmd )
   { fDetector->SetMaterial(newValue);}
}
