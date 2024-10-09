#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4SystemOfUnits.hh"

// SteppingAction::SteppingAction(EventAction* eventAction)
//     : G4UserSteppingAction(), fEventAction(eventAction) {}

SteppingAction::SteppingAction() {}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    // G4String particleName = track->GetDefinition()->GetParticleName();
    // G4cout << "particle: " << particleName << G4endl;

    // Check if the particle is an optical photon (scintillation photon)
    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        // Increment photon count in EventAction
        fEventAction->AddScintillationPhoton();
    }

    // Get the energy deposited in the current step
    G4double edep = step->GetTotalEnergyDeposit();

    // Debug: Print the energy deposited in this step
    // G4cout << "Energy deposited in this step: " << edep / MeV << " MeV" << G4endl;

    // Accumulate the energy deposited
    fTotalEnergyDeposited += edep;

    // // Optionally, you can store the energy deposited in the EventAction at the end of the event
    // G4Track* track = step->GetTrack();
    // if (track->GetTrackID() == 1) { // Assuming track ID 1 corresponds to your primary particle
    //     fEventAction->AddEnergyDeposited(edep);
    // }

}

