//
//__author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
//__copyright__ = "Copyright (c) Lingteng Kong"
//__created__ = "[02/07/2020 Thu 13:28]"
//
/// \file PrimaryGeneratorAction.hh
/// \brief create particle source class and overrides the abstract method
//

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
    virtual ~PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         

    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
            
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
};

#endif