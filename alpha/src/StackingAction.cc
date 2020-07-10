//
//__author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
//__copyright__ = "Copyright (c) Lingteng Kong"
//__created__ = "[03/07/2020 Fri 11:22]"
//
/// \file StackingAction.cc
/// \brief stacking action is a higher level of stepping action
//

#include "StackingAction.hh"

#include "G4VProcess.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

#include "g4root.hh"
#include "G4RunManager.hh"

//
StackingAction::StackingAction()
  : G4UserStackingAction(),
    fScintillationCounter(0),
    posx(0.)
{}

StackingAction::~StackingAction()
{}

//secondary optical photon
G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  auto analysisManager = G4AnalysisManager::Instance();
  
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        fScintillationCounter++;
        posx = aTrack->GetPosition().x();
        analysisManager->FillH1(0,posx);
    }
  }
  return fUrgent;
}

//
void StackingAction::NewStage()
{
  // G4cout << "Number of Scintillation photons produced in this event : "
  //        << fScintillationCounter << G4endl;
}

//
void StackingAction::PrepareNewEvent()
{
  fScintillationCounter = 0;
}