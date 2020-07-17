//
//__author__ = "Lingteng Kong <jn19830@bristol.ac.uk>"
//__copyright__ = "Copyright (c) Lingteng Kong"
//__created__ = "[02/07/2020 Thu 19:57]"
//
/// \file RunAction.hh
/// \brief one simulation event 
//

#ifndef RunAction_h
#define RunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

//
class G4Timer;
class HistoManager;
class G4Run;

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

  public:
    virtual void BeginOfRunAction(const G4Run* aRun);
    virtual void EndOfRunAction(const G4Run* aRun);

  private:
    G4Timer*                fTimer;
    HistoManager*           fHistoManager;    
};

#endif /*RunAction_h*/