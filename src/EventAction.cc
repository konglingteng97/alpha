/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-15 20:23:36 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-15 20:25:49
 */


#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include <iomanip>


EventAction::EventAction()
:G4UserEventAction()
{
  // Set default print level 
  G4RunManager::GetRunManager()->SetPrintProgress(10000);
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
}

void EventAction::EndOfEventAction(const G4Event*)
{
}
