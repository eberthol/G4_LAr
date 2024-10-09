#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4SystemOfUnits.hh"

#include "G4Neutron.hh"

SteppingAction::SteppingAction(EventAction* eventAction) 
{
    fEventAction = eventAction;
}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();

    G4cout << "UserSteppingAction: step " << track->GetCurrentStepNumber() << ": " << G4endl
               << track->GetDefinition()->GetParticleName() << " Interaction in  "
               << track->GetVolume()->GetName() << G4endl
               << "            TrackID : " << track->GetTrackID() << G4endl
               << "            Energy of the track : " << track->GetKineticEnergy() / MeV << " MeV, " << G4endl
               << "            Energy deposited: " << step->GetTotalEnergyDeposit() / MeV << " MeV" << G4endl;


    // Check if the particle is an optical photon (scintillation photon)
    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
        // Increment photon count in EventAction
        fEventAction->AddScintillationPhoton();
    }

    // Get the energy deposited in the current step
    G4double edep = step->GetTotalEnergyDeposit();

    // Accumulate the energy deposited
    fEventAction->AddEdep(edep);

    // // Optionally, you can store the energy deposited in the EventAction at the end of the event
    // G4Track* track = step->GetTrack();
    // if (track->GetTrackID() == 1) { // Assuming track ID 1 corresponds to your primary particle
    //     fEventAction->AddEnergyDeposited(edep);
    // }

}

