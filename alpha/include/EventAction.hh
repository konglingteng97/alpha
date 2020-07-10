//
//__author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
//__copyright__ = "Copyright (c) Lingteng Kong"
//__created__ = "[08/07/2020 Wed 22:37]"
//
/// \file EventAction.hh
/// \brief after run action
//

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

//
class EventAction : public G4UserEventAction
{
  public:
    EventAction();
   ~EventAction();

  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);
};

#endif