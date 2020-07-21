/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-21 23:39:58 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-21 23:48:31
 */

#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class PhysicsList;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

class PhysicsListMessenger: public G4UImessenger
{
  public:
    PhysicsListMessenger(PhysicsList* );
    virtual ~PhysicsListMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:
    PhysicsList*  fPhysicsList;
 
    G4UIdirectory*        fPhysDir;
    G4UIcmdWithAnInteger* fVerboseCmd;
    G4UIcmdWithAnInteger* fCerenkovCmd;
};

#endif
