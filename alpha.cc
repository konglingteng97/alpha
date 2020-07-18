/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-16 23:42:15 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-17 00:00:22
 */

#include "G4Types.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  //choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  
  // Get instance of runmanager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
  runManager->SetNumberOfThreads(std::min(4,G4Threading::G4GetNumberOfCores()));
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // the user initialization classes must be passed to runManager
  // Detector construction
  runManager->SetUserInitialization(new DetectorConstruction());

  // Physics list
  // the physics list must always be registered before the primary generator action can be 
  // instantiated since otherwise the relevant particle definitions may not be available.
  runManager->SetUserInitialization(new PhysicsList);

  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization());

  //initialize G4 kernel
  runManager->Initialize();

  // Initialize visualization
  G4VisManager* visManager = nullptr;

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
}