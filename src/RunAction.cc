
#include "RunAction.hh"
// #include "EventAction.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction()
{
  /*
        Here we define our nTuples
  */
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");
//   analysisManager->SetVerboseLevel(1); //0?

  // truth nTuple
  analysisManager->CreateNtuple("truth", "truth");
  analysisManager->CreateNtupleIColumn("event"); 
  // gen Particle
  analysisManager->CreateNtupleIColumn("gen_PDGcode"); 
  analysisManager->CreateNtupleDColumn("gen_PDGmass"); 
  analysisManager->CreateNtupleIColumn("gen_charge");  
  analysisManager->CreateNtupleDColumn("gen_p");
  analysisManager->CreateNtupleDColumn("gen_px");
  analysisManager->CreateNtupleDColumn("gen_py");
  analysisManager->CreateNtupleDColumn("gen_pz");
  analysisManager->CreateNtupleDColumn("gen_Ekin"); // kinetic energy
  // particle counters
  analysisManager->CreateNtupleIColumn("nParticles"); // number of photons generated in an event
  analysisManager->CreateNtupleIColumn("nPrimary"); // number of primary vertices generated in an event
  analysisManager->CreateNtupleIColumn("nGammas"); // number of gammas generated in an event
  analysisManager->CreateNtupleIColumn("nOptPhotons"); // number of photons generated in an event
  analysisManager->CreateNtupleIColumn("nScintPhotons"); // number of scintillation photons generated in an event
  // more variabbles
  analysisManager->CreateNtupleDColumn("Edep"); // Energy deposited [MeV]
  analysisManager->CreateNtupleDColumn("FlightDistance"); // Distance travelled by the neutron
  // 4-momentum of the neutron when exiting the LAr sphere
  analysisManager->CreateNtupleDColumn("neutronExit_px"); 
  analysisManager->CreateNtupleDColumn("neutronExit_py"); 
  analysisManager->CreateNtupleDColumn("neutronExit_pz"); 
  analysisManager->CreateNtupleDColumn("neutronExit_E"); 

  analysisManager->CreateNtupleDColumn("EdepPrimary"); // Energy deposited by the primary particle [MeV]


  analysisManager->FinishNtuple(0); 

  /*
        Here we define our histograms
  */
 // Create a histogram for wavelengths
  analysisManager->CreateH1("Wavelength", "Wavelength of Optical Photons; Wavelength (nm); Counts", 100, 100, 200);

}



void RunAction::BeginOfRunAction(const G4Run* run)
{
  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  G4int runID = run->GetRunID();
  std::stringstream strRunID;
  strRunID << runID;
  analysisManager->OpenFile("output_r" + strRunID.str() + ".root");

}


void RunAction::EndOfRunAction(const G4Run* /*run*/)
{


  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
  

}

