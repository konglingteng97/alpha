/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-15 20:27:11 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-21 00:06:18
 */

#include "StackingAction.hh"
#include "HistoManager.hh"

#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4IonTable.hh"

#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

#include "g4root.hh"
#include "G4RunManager.hh"

//stacking action is a higher level of stepping action, save track info
//a track is a particle
StackingAction::StackingAction()
  : G4UserStackingAction()
{}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  G4ParticleDefinition* particle = aTrack->GetDefinition();

  G4double Ekin = aTrack->GetKineticEnergy();  //kinetic energy
  G4double PosX = aTrack->GetPosition().x();   //x position
  G4int fCharge = particle->GetPDGCharge(); //charge of particle

  G4AnalysisManager* analysis = G4AnalysisManager::Instance();

  //scintillation photon info
  if(particle == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        analysis->FillH1(0,PosX);
        analysis->FillH1(1,Ekin);
        G4double wl = 1.24e-3/Ekin;  //wavelength, hc = 1.24e-3 nm * MeV
        analysis->FillH1(2,wl);
    }
  }

  //other particles info
  G4int ih = 0;

  if (particle == G4Gamma::Gamma()) ih = 3;
  else if (particle == G4Electron::Electron()) ih = 4;
  else if (particle == G4Alpha::Alpha()) ih = 5;
  else if (fCharge > 2.) ih = 6;
  
  if (ih) analysis->FillH1(ih, PosX);
          analysis->FillH1(ih+4, Ekin);

  return fUrgent; 
}

//info in one event
void StackingAction::NewStage()
{
}

//initialization
void StackingAction::PrepareNewEvent()
{
}