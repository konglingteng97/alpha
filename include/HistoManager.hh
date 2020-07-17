/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-15 15:17:17 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-15 15:54:38
 */

#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

#include "g4root.hh"
//#include "g4xml.hh"

class HistoManager
{
  public:
   HistoManager();
  ~HistoManager();

  private:
    void Book();
    G4String fFileName;
};

#endif  