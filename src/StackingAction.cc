/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-15 20:27:11 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-24 00:03:29
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

#include "G4PhysicalConstants.hh"

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

  G4double Ekin           = aTrack->GetKineticEnergy();                 //kinetic energy
  G4int fCharge           = particle->GetPDGCharge();                   //charge of particle
  G4int pid               = aTrack->GetDynamicParticle()->GetPDGcode(); //particle ID
  G4ThreeVector vertex    = aTrack->GetPosition();                      //position
  G4ThreeVector direction = aTrack->GetMomentumDirection();             //momentum direction
  G4double weight         = aTrack->GetWeight();

  G4double x = vertex.x(), y = vertex.y(), z = vertex.z();
  G4double theta = direction.theta(), phi = direction.phi();
  if (phi < 0.) phi += twopi; 

  G4AnalysisManager* analysis = G4AnalysisManager::Instance();

  //scintillation photon info
  if(particle == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        //distribution and spectra
        analysis->FillH1(0,x);
        analysis->FillH1(1,Ekin);
        G4double wl = 1.24e-3/Ekin;  //wavelength, hc = 1.24e-3 nm * MeV
        analysis->FillH1(2,wl);

        //2D distribution
        analysis->FillH2(0,x,y);
    }
  }

  //other particles info
  G4int ih = 0;

  if (particle == G4Gamma::Gamma()) ih = 3;
  else if (particle == G4Electron::Electron()) ih = 4;
  else if (particle == G4Alpha::Alpha()) ih = 5;
  else if (fCharge > 2.) ih = 6;
  
  if (ih) analysis->FillH1(ih, x);
          analysis->FillH1(ih+4, Ekin);

  //fill ntuple
  analysis->FillNtupleIColumn(0,pid);
  analysis->FillNtupleDColumn(1,Ekin);
  analysis->FillNtupleDColumn(2,x);
  analysis->FillNtupleDColumn(3,y);
  analysis->FillNtupleDColumn(4,z);
  analysis->FillNtupleDColumn(5,theta);
  analysis->FillNtupleDColumn(6,phi);
  analysis->FillNtupleDColumn(7,weight);
  analysis->AddNtupleRow();  

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