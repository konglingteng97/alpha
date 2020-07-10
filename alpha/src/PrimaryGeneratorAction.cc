//
//__author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
//__copyright__ = "Copyright (c) Lingteng Kong"
//__created__ = "[02/07/2020 Thu 13:27]"
//
/// \file PrimaryGeneratorAction.cc
/// \brief define and generate alpha source at the beginning of the simulation
//

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//The easiest way to generate primary particles in Geant4 is to use the helper class G4ParticleGun.
//This methord will be called at the beginning of the simulation of the Geant4 kernel to generate a particle
PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

//initialization: set energy, position, momentum direction to 0 for decay process
  fParticleGun->SetParticleEnergy(0*eV);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,0.));          
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//set particle definition
//Primary generator will be called at every event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
//geantino is a virtual particle used for simulation and which does not interact with materials.
  if (fParticleGun->GetParticleDefinition() == G4Geantino::Geantino()) {  
//Am-241 alpha source
    G4int Z = 95, A = 241;
    G4double ionCharge   = 0.*eplus;
    G4double excitEnergy = 0.*keV;
    
    G4ParticleDefinition* ion
       = G4IonTable::GetIonTable()->GetIon(Z,A,excitEnergy);

//tell the gun to emit ion
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(ionCharge);
  }    

//Generate the primary particle in every event
  fParticleGun->GeneratePrimaryVertex(anEvent);
}