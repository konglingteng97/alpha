//
//__author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
//__copyright__ = "Copyright (c) Lingteng Kong"
//__created__ = "[02/07/2020 Thu 19:57]"
//
/// \file RunAction.cc
/// \brief one simulation event
//

// Make this appear first!
#include "G4Timer.hh"

#include "RunAction.hh"

#include "g4root.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//
RunAction::RunAction()
 : G4UserRunAction(),
   fTimer(0)
{
  fTimer = new G4Timer;

  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using" << analysisManager->GetType() << G4endl;

  analysisManager->CreateH1("Scintillation Photon","Scintillation Photon",10000,-100.*cm,100.*cm);
}

//
RunAction::~RunAction()
{
  delete fTimer;
}

//
void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();

  auto analysisManager = G4AnalysisManager::Instance();
  G4String fileName = "Mydata";
  analysisManager->OpenFile(fileName);
}

//
void RunAction::EndOfRunAction(const G4Run* aRun)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

  fTimer->Stop();
  //Get the ID of this run action
  G4cout << "number of event = " << aRun->GetNumberOfEvent()
         << " " << *fTimer << G4endl;
}