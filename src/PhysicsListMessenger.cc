/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-21 23:40:15 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-21 23:57:21
 */

#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

//cmd for physics list
PhysicsListMessenger::PhysicsListMessenger(PhysicsList* pPhys) 
: G4UImessenger(),
  fPhysicsList(pPhys),fPhysDir(0),fVerboseCmd(0),fCerenkovCmd(0)
{
  fPhysDir = new G4UIdirectory("/alpha/phys/");
  fPhysDir->SetGuidance("PhysicsList commands");
 
  fVerboseCmd = new G4UIcmdWithAnInteger("/alpha/phys/verbose",this);
  fVerboseCmd->SetGuidance("set verbose for physics processes");
  fVerboseCmd->SetParameterName("verbose",true);
  fVerboseCmd->SetDefaultValue(1);
  fVerboseCmd->SetRange("verbose>=0");
  fVerboseCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
 
  fCerenkovCmd =
           new G4UIcmdWithAnInteger("/alpha/phys/cerenkovMaxPhotons",this);
  fCerenkovCmd->SetGuidance("set max nb of cerenkov photons per step");
  fCerenkovCmd->SetParameterName("MaxNumber",false);
  fCerenkovCmd->SetRange("MaxNumber>=0");
  fCerenkovCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

PhysicsListMessenger::~PhysicsListMessenger()
{
  delete fVerboseCmd;
  delete fCerenkovCmd;
  delete fPhysDir;
}

void PhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                               G4String newValue)
{
  if( command == fVerboseCmd )
   {fPhysicsList->SetVerbose(fVerboseCmd->GetNewIntValue(newValue));}

  if( command == fCerenkovCmd )
   {fPhysicsList->
              SetNbOfPhotonsCerenkov(fCerenkovCmd->GetNewIntValue(newValue));}
}
