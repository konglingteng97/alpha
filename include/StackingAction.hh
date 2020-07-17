/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-16 19:05:37 
 * @Last Modified by:   Lingteng Kong 
 * @Last Modified time: 2020-07-16 19:05:37 
 */


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
};

#endif