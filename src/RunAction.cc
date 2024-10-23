
#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction()
{
  fHistoManager = new HistoManager();
  /*
        Here we define our nTuples
  */
//   auto analysisManager = G4AnalysisManager::Instance();
//   analysisManager->SetDefaultFileType("root");
// //   analysisManager->SetVerboseLevel(1); //0?

//   // truth nTuple
//   analysisManager->CreateNtuple("truth", "truth");
//   analysisManager->CreateNtupleIColumn("event"); 
//   // gen Particle
//   analysisManager->CreateNtupleIColumn("gen_PDGcode"); 
//   analysisManager->CreateNtupleDColumn("gen_PDGmass"); 
//   analysisManager->CreateNtupleIColumn("gen_charge");  
//   analysisManager->CreateNtupleDColumn("gen_p");
//   analysisManager->CreateNtupleDColumn("gen_px");
//   analysisManager->CreateNtupleDColumn("gen_py");
//   analysisManager->CreateNtupleDColumn("gen_pz");
//   analysisManager->CreateNtupleDColumn("gen_Ekin"); // kinetic energy
//   // particle counters
//   analysisManager->CreateNtupleIColumn("nParticles"); // number of photons generated in an event
//   analysisManager->CreateNtupleIColumn("nPrimary"); // number of primary vertices generated in an event
//   analysisManager->CreateNtupleIColumn("nGammas"); // number of gammas generated in an event
//   analysisManager->CreateNtupleIColumn("nOptPhotons"); // number of photons generated in an event
//   analysisManager->CreateNtupleIColumn("nScintPhotons"); // number of scintillation photons generated in an event
//   // more variabbles
//   analysisManager->CreateNtupleDColumn("Edep"); // Energy deposited [MeV]
//   analysisManager->CreateNtupleDColumn("FlightDistance"); // Distance travelled by the neutron
//   // 4-momentum of the neutron when exiting the LAr sphere
//   analysisManager->CreateNtupleDColumn("neutronExit_px"); 
//   analysisManager->CreateNtupleDColumn("neutronExit_py"); 
//   analysisManager->CreateNtupleDColumn("neutronExit_pz"); 
//   analysisManager->CreateNtupleDColumn("neutronExit_theta"); 
//   analysisManager->CreateNtupleDColumn("neutronExit_phi"); 
//   analysisManager->CreateNtupleDColumn("neutronExit_E"); 

//   analysisManager->CreateNtupleDColumn("EdepPrimary"); // Energy deposited by the primary particle [MeV]


//   analysisManager->FinishNtuple(0); 

//   /*
//         Here we define our histograms
//   */
//  // Create a histogram for wavelengths
//   analysisManager->CreateH1("Wavelength",   "Optical Photons; Wavelength (nm); Counts", 100, 120, 140);
//   analysisManager->CreateH1("Ekin",         "Optical Photons; Kinetic Energy (eV); Counts", 100, 0, 20);
//   analysisManager->CreateH1("Energy",       "Optical Photons; Energy (eV); Counts", 100, 0, 20);
//   analysisManager->CreateH1("Momentum",     "Optical Photons; Momentum (eV); Counts", 100, 0, 20);
//   analysisManager->CreateH1("CreationTime", "Optical Photons; Global Time of Creation (ns); Counts", 100, 30, 150);

//   analysisManager->CreateH1("WavelengthGammas",   "Gammas; Wavelength (nm); Counts", 100, 0, 20);
//   analysisManager->CreateH1("EkinGammas",         "Gammas; Kinetic Energy (MeV); Counts", 100, 0, 20);
//   analysisManager->CreateH1("EnergyGammas",       "Gammas; Energy (MeV); Counts", 100, 0, 10);
//   analysisManager->CreateH1("MomentumGammas",     "Gammas; Momentum (MeV); Counts", 100, 0, 10);
//   analysisManager->CreateH1("CreationTimeGammas", "Gammas; Global Time of Creation (ns); Counts", 100, 30, 150);





}

RunAction::~RunAction()
{
 delete fHistoManager;
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
  // Get analysis manager
  // auto analysisManager = G4AnalysisManager::Instance();

  // G4int runID = run->GetRunID();
  // std::stringstream strRunID;
  // strRunID << runID;
  // analysisManager->OpenFile("output_r" + strRunID.str() + ".root");


  //histograms
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  }  

}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{

  // auto analysisManager = G4AnalysisManager::Instance();
  // analysisManager->Write();
  // analysisManager->CloseFile();


  //save histograms      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();  
  if ( analysisManager->IsActive() ) {
    analysisManager->Write();
    analysisManager->CloseFile();
  }
  

}

