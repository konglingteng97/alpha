
// __author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
// __copyright__ = "Copyright (c) Lingteng Kong"
// __created__ = "[06/07/2020 Mon 16:34]"

// / \file ActionInitialization.cc
// / \brief initialization of action


#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "StackingAction.hh"

//
ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization()
{}

//
void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction());
}

//PrimaryGenerator, runaction, stepping action, stacking action
void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction());
  SetUserAction(new RunAction());
  SetUserAction(new SteppingAction());
  SetUserAction(new EventAction());
  SetUserAction(new StackingAction());
}
