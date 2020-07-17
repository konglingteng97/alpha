/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-15 20:10:49 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-17 02:24:26
 */

#include "G4Timer.hh"

#include "RunAction.hh"
#include "HistoManager.hh"

#include "g4root.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


RunAction::RunAction()
 : G4UserRunAction(),
   fTimer(0),fHistoManager(0)
{
  fTimer = new G4Timer;
  fHistoManager = new HistoManager();
}

RunAction::~RunAction()
{
  delete fHistoManager;
  delete fTimer;
}

//Begin of run action
void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();

  //histograms
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  }
}

//End of run action, which is after the end of event action
void RunAction::EndOfRunAction(const G4Run* aRun)
{
 //save histograms
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 if ( analysisManager->IsActive() ) {
  analysisManager->Write();
  analysisManager->CloseFile();
  G4cout << "---Data has been saved, have a good day----" << G4endl;
 }

  fTimer->Stop();
  
  //Get the ID of this run action
  G4cout << "### Number of event = " << aRun->GetNumberOfEvent()
         << " " << *fTimer << G4endl;
}