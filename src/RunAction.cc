
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
//   auto analysisManager = G4AnalysisManager::Instance();
//   analysisManager->SetDefaultFileType("root");
//   analysisManager->SetVerboseLevel(1); //0?

//   // truth nTuple
//   analysisManager->CreateNtuple("truth", "truth");
//   analysisManager->CreateNtupleIColumn("event"); 
//   analysisManager->CreateNtupleIColumn("gen_PDGcode"); 
//   analysisManager->CreateNtupleDColumn("gen_PDGmass"); 
//   analysisManager->CreateNtupleIColumn("gen_charge");  
//   analysisManager->CreateNtupleDColumn("gen_p");
//   analysisManager->CreateNtupleDColumn("gen_px");
//   analysisManager->CreateNtupleDColumn("gen_py");
//   analysisManager->CreateNtupleDColumn("gen_pz");
//   analysisManager->CreateNtupleDColumn("gen_Ekin"); // kinetic energy

}



void RunAction::BeginOfRunAction(const G4Run* run)
{
  // Get analysis manager
//   auto analysisManager = G4AnalysisManager::Instance();

//   G4int runID = run->GetRunID();
//   std::stringstream strRunID;
//   strRunID << runID;
//   analysisManager->OpenFile("output_r" + strRunID.str() + ".root");

}


void RunAction::EndOfRunAction(const G4Run* /*run*/)
{


//   auto analysisManager = G4AnalysisManager::Instance();
//   analysisManager->Write();
//   analysisManager->CloseFile();

}

