//
//__author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
//__copyright__ = "Copyright (c) Lingteng Kong"
//__created__ = "[03/07/2020 Fri 11:22]"
//
/// \file StackingAction.hh
/// \brief stacking action is a higher level of stepping action
//


#ifndef StackingAction_H
#define StackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

//
class StackingAction : public G4UserStackingAction
{
  public:
    StackingAction();
    virtual ~StackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    G4int fScintillationCounter;
    G4double posx;
};

#endif