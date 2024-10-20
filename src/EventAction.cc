#include "EventAction.hh"
#include "SteppingAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
// #include "G4EventManager.hh"
// #include "G4HCofThisEvent.hh"
// #include "G4VHitsCollection.hh"
// #include "G4SDManager.hh"
// #include "G4ios.hh"
// #include "G4PrimaryParticle.hh"
// #include "G4PrimaryVertex.hh"
// #include "G4UserEventAction.hh"

using std::array;
using std::vector;

EventAction::EventAction()
{
//   G4RunManager::GetRunManager()->SetPrintProgress(1);
}

void EventAction::BeginOfEventAction(const G4Event*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  fScintillationPhotonCount = 0;  // Reset photon count at start of each event
  fEnergyDeposited = 0; 
  fEnergyDepositedPrimary = 0;
  fFlightDist = 0;  // neutron flight distance
  fSecondaryVertexCount = 0; 
}

void EventAction::EndOfEventAction(const G4Event* event)
{
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( printModulo == 0 || event->GetEventID() % printModulo != 0) return;

  auto primary = event->GetPrimaryVertex(0)->GetPrimary(0);
  G4cout
    << G4endl
    << ">>> Event " << event->GetEventID() << " >>> Simulation truth : "
    << primary->GetG4code()->GetParticleName()
    << " momentum " << primary->GetMomentum() << G4endl;

  // Output: total number of scintillation photons at the end of each event
    G4cout << "EventAction: Total scintillation photons in this event: " << fScintillationPhotonCount << G4endl;
    G4cout << "EventAction: Total Energy Deposited in the event: " << fEnergyDeposited / MeV << " MeV" << G4endl;
    G4cout << "EventAction: Total Energy Deposited by the primary particle: " << fEnergyDepositedPrimary / MeV << " MeV" << G4endl;
    G4cout << "Number of secondary vertices: " << fSecondaryVertexCount << G4endl;
    

  // Count daughter particles in the event
  // reset count for each event
  G4int partCount = 0; 
  G4int gammaCount = 0; 
  G4int photonCount = 0; 
  int numVertices = event->GetNumberOfPrimaryVertex();
  for (int i = 0; i < numVertices; ++i) {
      G4PrimaryVertex* vertex = event->GetPrimaryVertex(i);
      // Loop over primary particles in this vertex
      for (int j = 0; j < vertex->GetNumberOfParticle(); ++j) {
          G4PrimaryParticle* particle = vertex->GetPrimary(j);
          partCount += vertex->GetNumberOfParticle();
          // G4cout << "EventAction: Particles in the event: " << particle->GetPDGcode() << G4endl;
          if (particle->GetPDGcode() == 22) { // PDG code for photons (gammas)
              gammaCount++;
          }
          if (particle->GetPDGcode() == -22) { // PDG code for optical photons
              photonCount++;
          }
      }
  }


//   Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleIColumn(0, 0, event->GetEventID());
    analysisManager->FillNtupleIColumn(0, 1, primary->GetPDGcode());
    analysisManager->FillNtupleDColumn(0, 2, primary->GetG4code()->GetPDGMass());
    analysisManager->FillNtupleIColumn(0, 3, primary->GetCharge()); 
    analysisManager->FillNtupleDColumn(0, 4, primary->GetTotalMomentum());
    analysisManager->FillNtupleDColumn(0, 5, primary->GetMomentum().x());
    analysisManager->FillNtupleDColumn(0, 6, primary->GetMomentum().y());
    analysisManager->FillNtupleDColumn(0, 7, primary->GetMomentum().z());
    analysisManager->FillNtupleDColumn(0, 8, primary->GetKineticEnergy());
    analysisManager->FillNtupleIColumn(0, 9, numVertices); // number of primary vertices
    analysisManager->FillNtupleIColumn(0, 10, partCount); // number of particles
    analysisManager->FillNtupleIColumn(0, 11, gammaCount); // number of gammas
    analysisManager->FillNtupleIColumn(0, 12, photonCount); // number of (optical) photons
    analysisManager->FillNtupleIColumn(0, 13, fScintillationPhotonCount); // number of (scintillation) photons
    analysisManager->FillNtupleDColumn(0, 14, fEnergyDeposited); // Edep
    analysisManager->FillNtupleDColumn(0, 15, fFlightDist);
    // exiting neutron 4-momentum
    analysisManager->FillNtupleDColumn(0, 16, fExitMomentum.x() / MeV); // px
    analysisManager->FillNtupleDColumn(0, 17, fExitMomentum.y() / MeV); // py
    analysisManager->FillNtupleDColumn(0, 18, fExitMomentum.z() / MeV); // pz
    analysisManager->FillNtupleDColumn(0, 19, fExitEnergy / MeV);       // energy

    analysisManager->FillNtupleDColumn(0, 20, fEnergyDepositedPrimary); // Edep primary particle

    analysisManager->AddNtupleRow(0);

  
    // TH1D* hWavelength = new TH1D("hWavelength", "Wavelength of Optical Photons; Wavelength (nm); Counts", 100, 100, 200); // 100 bins from 100 nm to 200 nm
    // const std::vector<G4double>& wavelengths = fSteppingAction->GetWavelengths();
    // // Fill the histogram
    //   for (G4double wavelength : wavelengths) {
    //       hWavelength->Fill(wavelength);
    //   }

    //   // Draw the histogram (you may want to save it or analyze further)
    //   TCanvas* c = new TCanvas("c", "Wavelength Histogram", 800, 600);
    //   hWavelength->Draw();
    //   c->SaveAs("wavelength_histogram.png"); // Save the histogram as an image

}

void EventAction::AddScintillationPhoton() 
{
    fScintillationPhotonCount++;
}

void EventAction::AddSecondaryVertex() 
{
    fSecondaryVertexCount++;
}

void EventAction::AddFlightDistance(G4double distance)
{
    fFlightDist += distance;
}

void EventAction::getExitFourMomentum(G4double E, G4ThreeVector p)
{
  fExitEnergy   = E;
  fExitMomentum = p;
}
