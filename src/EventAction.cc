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
  fTotalEnergyDeposited = 0;
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
    << " monentum " << primary->GetMomentum() << G4endl;

  // Output the total number of scintillation photons at the end of each event
    G4cout << "Total scintillation photons in this event: " 
           << fScintillationPhotonCount << G4endl;
    G4cout << "Total Energy Deposited: " << fTotalEnergyDeposited / MeV << " MeV" << G4endl;

  int numVertices = event->GetNumberOfPrimaryVertex();
  for (int i = 0; i < numVertices; ++i) {
      G4PrimaryVertex* vertex = event->GetPrimaryVertex(i);
      // Loop over primary particles in this vertex
      for (int j = 0; j < vertex->GetNumberOfParticle(); ++j) {
          G4PrimaryParticle* particle = vertex->GetPrimary(j);
        //   partCount += vertex->GetNumberOfParticle();
          G4cout << "Particles in the event: " << particle->GetPDGcode() << G4endl;
        //   if (particle->GetPDGcode() == 22) { // PDG code for photons (gammas)
        //       gammaCount++;
        //   }
        //   if (particle->GetPDGcode() == -22) { // PDG code for optical photons
        //       photonCount++;
        //   }
      }
  }





// //   Get analysis manager
//     auto analysisManager = G4AnalysisManager::Instance();
//     analysisManager->FillNtupleIColumn(0, 0, event->GetEventID());
//     analysisManager->FillNtupleIColumn(0, 1, primary->GetPDGcode());
//     analysisManager->FillNtupleDColumn(0, 2, primary->GetG4code()->GetPDGMass());
//     analysisManager->FillNtupleIColumn(0, 3, primary->GetCharge()); 
//     analysisManager->FillNtupleDColumn(0, 4, primary->GetTotalMomentum());
//     analysisManager->FillNtupleDColumn(0, 5, primary->GetMomentum().x());
//     analysisManager->FillNtupleDColumn(0, 6, primary->GetMomentum().y());
//     analysisManager->FillNtupleDColumn(0, 7, primary->GetMomentum().z());
//     analysisManager->FillNtupleDColumn(0, 8, primary->GetKineticEnergy());
//     analysisManager->FillNtupleIColumn(0, 9, numVertices); // number of primary vertices
//     analysisManager->FillNtupleIColumn(0, 10, partCount); // number of particles
//     analysisManager->FillNtupleIColumn(0, 11, gammaCount); // number of gammas
//     analysisManager->FillNtupleIColumn(0, 12, photonCount); // number of (optical) photons
//     analysisManager->AddNtupleRow(0);


}

void EventAction::AddScintillationPhoton() {
    fScintillationPhotonCount++;
}
