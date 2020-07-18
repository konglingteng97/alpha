/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-16 19:48:16 
 * @Last Modified by:   Lingteng Kong 
 * @Last Modified time: 2020-07-16 19:48:16 
 */

#include "SteppingAction.hh"
#include "HistoManager.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

// called after the beginning of event action
SteppingAction::SteppingAction()
: G4UserSteppingAction()
{ 
}

SteppingAction::~SteppingAction()
{ ; }

//Method called at the end of each step
void SteppingAction::UserSteppingAction(const G4Step*)
{
}