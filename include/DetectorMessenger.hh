/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-21 10:57:51 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-21 22:17:41
 */

#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;

//
class DetectorMessenger: public G4UImessenger
{
  public:
  
    DetectorMessenger(DetectorConstruction* );
   ~DetectorMessenger();

    virtual    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
  
    DetectorConstruction*      fDetector;
    
    G4UIdirectory*             falphaDir;
    G4UIdirectory*             fDetDir;
    G4UIcmdWithAString*        fMaterCmd;
};

#endif
