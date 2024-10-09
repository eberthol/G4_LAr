#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
// #include "PhysicsList.hh"

#include "G4UIExecutive.hh"
#include "G4SteppingVerbose.hh"
#include "G4RunManagerFactory.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"

#include "FTFP_BERT.hh"
#include "G4EmStandardPhysics_option4.hh"
// #include "G4StepLimiterPhysics.hh"
// #include "G4OpticalParameters.hh"
// #include "G4OpticalPhysics.hh"


int main(int argc,char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = nullptr;
  if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }

  // Use G4SteppingVerboseWithUnits
  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);

  // Construct the default run manager
  //
  auto runManager =
    G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  // Mandatory user initialization classes
  runManager->SetUserInitialization(new DetectorConstruction);

  // runManager->SetUserInitialization(new PhysicsList);

  auto physicsList = new FTFP_BERT;
  // auto physicsList = new QGSP_BERT;
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  runManager->SetUserInitialization(physicsList);



  // User action initialization
  runManager->SetUserInitialization(new ActionInitialization());

  // Visualization manager construction
  auto visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // auto visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  auto UImanager = G4UImanager::GetUIpointer();

  if ( !ui ) {
    // execute an argument macro file if exist
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    UImanager->ApplyCommand("/control/execute init_vis.mac");
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


