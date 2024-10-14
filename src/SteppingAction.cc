#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "G4Neutron.hh"
// #include "G4AnalysisManager.hh"

SteppingAction::SteppingAction(EventAction* eventAction) 
{
    fEventAction = eventAction;
    ftotalDistance = 0.0;
}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    const G4StepPoint* preStepPoint = step->GetPreStepPoint();
    const G4StepPoint* postStepPoint = step->GetPostStepPoint();

    

    // G4cout << "UserSteppingAction: step " << track->GetCurrentStepNumber() << ": " << G4endl
    //            << track->GetDefinition()->GetParticleName() << " Interaction in  "
    //            << track->GetVolume()->GetName() << G4endl
    //            << "            TrackID : " << track->GetTrackID() << G4endl
    //            << "            Energy of the track : " << track->GetKineticEnergy() / MeV << " MeV, " << G4endl
    //            << "            Energy deposited: " << step->GetTotalEnergyDeposit() / MeV << " MeV" << G4endl;


    if (track->GetDefinition() == G4Neutron::Neutron()) 
    {
        G4ThreeVector currentPosition = track->GetPosition();
        G4ThreeVector previousPosition = track->GetStep()->GetPreStepPoint()->GetPosition();
        G4double distance = (currentPosition - previousPosition).mag();
        ftotalDistance += distance;
        fEventAction->AddFlightDistance(distance);

        // G4cout << "UserSteppingAction: step " << track->GetCurrentStepNumber() << ": " << G4endl
        //        << "Neutron flight distance "  << ftotalDistance / cm << " cm" << G4endl 
        //        << "Process "  << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << G4endl;

        //     G4cout << "preStepPoint->GetPhysicalVolume() " << preStepPoint->GetPhysicalVolume()->GetName() <<  G4endl;

        if (preStepPoint->GetPhysicalVolume()->GetName() == "LArSpherePhysical" && 
            postStepPoint->GetPhysicalVolume()->GetName() != "LArSpherePhysical") {
            // Get the 4-momentum at the exit point
            G4ThreeVector momentum = track->GetMomentum(); 
            G4double energy = track->GetTotalEnergy();

            fEventAction->getExitFourMomentum(energy, momentum); 
            
            // Output the 4-momentum
            G4cout << "Particle exited the target volume with 4-momentum: "
                   << momentum << " and energy: " << energy / MeV << " MeV" << G4endl;
        }

    }


    // Check if the particle is an optical photon (scintillation photon)
    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) 
    {
        // Increment photon count in EventAction
        fEventAction->AddScintillationPhoton();
    }

    // Get the energy deposited in the current step
    G4double edep = step->GetTotalEnergyDeposit();

    // Get the energy deposited in the current step by the primary particle
    if (track->GetTrackID() == 1){
        G4double edepPrimary = step->GetTotalEnergyDeposit();
        fEventAction->AddEdepPrimary(edepPrimary);
    }

    // Accumulate the energy deposited
    fEventAction->AddEdep(edep);

    // // Optionally, you can store the energy deposited in the EventAction at the end of the event
    // G4Track* track = step->GetTrack();
    // if (track->GetTrackID() == 1) { // Assuming track ID 1 corresponds to your primary particle
    //     fEventAction->AddEnergyDeposited(edep);
    // }

}

