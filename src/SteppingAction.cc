#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "G4Neutron.hh"
#include "G4PhysicalConstants.hh"  // For physical constants like h_Planck, c_light
#include "G4AnalysisManager.hh"

// //Redirect cout to /dev/null, i.e. don't print out stuff in the terminal
// #include <iostream>
// #include <fstream>
// std::ofstream null_stream("/dev/null");
// std::streambuf* old_cout_buffer = std::cout.rdbuf(null_stream.rdbuf());

SteppingAction::SteppingAction(EventAction* eventAction) 
{
    fEventAction = eventAction;
    ftotalDistance = 0.0;
    // fprocessCount = 0;
}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    const G4StepPoint* preStepPoint = step->GetPreStepPoint();
    const G4StepPoint* postStepPoint = step->GetPostStepPoint();

    PrintInfo(step); // ignores the optical photons

    // Get the energy deposited in the current step
    G4double edep = step->GetTotalEnergyDeposit();
    fEventAction->AddEdep(edep);

    // what to do with the primary particle
    if (track->GetTrackID() == 1)
    {
        // Get the energy deposited in the current step by the primary particle
        G4double edepPrimary = step->GetTotalEnergyDeposit();
        fEventAction->AddEdepPrimary(edepPrimary);

        G4ThreeVector currentPosition = track->GetPosition();
        G4ThreeVector previousPosition = track->GetStep()->GetPreStepPoint()->GetPosition();
        G4double distance = (currentPosition - previousPosition).mag();
        ftotalDistance += distance;
        fEventAction->AddFlightDistance(distance);

        G4cout << track->GetDefinition()->GetParticleName() << " flight distance "  << ftotalDistance / cm << " cm" << G4endl; 


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

    // what to do with optical photons
    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) 
    {
        // Increment photon count in EventAction
        fEventAction->AddScintillationPhoton();

        // get the wavelength
        G4double photonEnergy = track->GetKineticEnergy();  // in MeV
        G4double wavelength = (h_Planck * c_light) / photonEnergy;  // Wavelength in mm

        // Fill the histogram with the wavelength
        auto analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillH1(0, wavelength); // Fill histogram with the wavelength (unit is set in the .mac file)
        // analysisManager->FillH1(1, photonEnergy / eV);


        // G4double Ephoton = track->GetTotalEnergy();  // in MeV
        // G4double Pphoton = track->GetMomentum().mag();  // in MeV
        // analysisManager->FillH1(2, Ephoton / eV);
        // analysisManager->FillH1(3, Pphoton / eV);

        // G4double vertexTime = track->GetGlobalTime();
        // analysisManager->FillH1(4, vertexTime / ns);

        G4cout << "Optical photon wavelength: " << wavelength / nm << " nm" << G4endl;

    }

    // what to do with gammas
    if (track->GetDefinition() == G4Gamma::Definition()) 
    {
        // Increment photon count in EventAction
        fEventAction->AddScintillationPhoton();

        // get the wavelength
        G4double photonEnergy = track->GetKineticEnergy();  // in MeV
        G4double wavelength = (h_Planck * c_light) / photonEnergy;  // Wavelength in mm

        // // Fill the histogram with the wavelength
        // auto analysisManager = G4AnalysisManager::Instance();
        // analysisManager->FillH1(5, wavelength / nm); // Fill histogram with the wavelength
        // analysisManager->FillH1(6, photonEnergy / MeV);


        // G4double Ephoton = track->GetTotalEnergy();  // in MeV
        // G4double Pphoton = track->GetMomentum().mag();  // in MeV
        // analysisManager->FillH1(7, Ephoton / MeV);
        // analysisManager->FillH1(8, Pphoton / MeV);

        // G4double vertexTime = track->GetGlobalTime();
        // analysisManager->FillH1(9, vertexTime / ns);

    }


    // Get the secondary particles created in this step
    const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();
    if (secondaries->size() > 0) 
    {
        G4cout << "Secondary particles produced in this step: " << secondaries->size() << G4endl;
        if (secondaries->size() <= 10)
        {
            // Loop over all secondary particles
            for (size_t i = 0; i < secondaries->size(); ++i) 
            {
                const G4Track* secondaryTrack = (*secondaries)[i];

                // Get secondary particle name
                G4String particleName = secondaryTrack->GetDefinition()->GetParticleName();

                // Get the vertex of the secondary particle
                // G4ThreeVector secondaryVertex = secondaryTrack->GetVertexPosition(); // not always initialized correctly for secondary particles
                G4ThreeVector secondaryCreationPosition = secondaryTrack->GetPosition();
                fEventAction->AddSecondaryVertex();
                G4double vertexTime = secondaryTrack->GetGlobalTime();
                
                // Get the process that created the secondary particle
                const G4VProcess* process = secondaryTrack->GetCreatorProcess(); // process that created the particle
                G4String processName = (process) ? process->GetProcessName() : "unknown";

                // // Print the information
                G4cout << " Secondary particle: " << particleName << G4endl;
                G4cout << "   Created by process: " << processName << G4endl;
                G4cout << "   Vertex position: " << secondaryCreationPosition << G4endl;
                G4cout << "   Energy: " << secondaryTrack->GetTotalEnergy() << G4endl;
                G4cout << "   3-momentum: " << secondaryTrack->GetMomentum() << G4endl;
                G4cout << "   Global time of creation: " << vertexTime / ns << " ns" << G4endl;
            }
        } 

    }

}

void SteppingAction::PrintInfo(const G4Step* step)
{
    G4Track* track = step->GetTrack();
    if (track->GetDefinition() != G4OpticalPhoton::OpticalPhotonDefinition()) 
    {
        G4cout << G4endl
            << "UserSteppingAction: step " << track->GetCurrentStepNumber() << ": " << G4endl
            << "          Track" << track->GetTrackID() << ": "
            << track->GetDefinition()->GetParticleName() << " interaction in "
            << track->GetVolume()->GetName()
            << ", process that created the step: "  << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()
            << ", ParentID : " << track->GetParentID() << G4endl
            << "          Kinetic energy of the track : " << track->GetKineticEnergy() / MeV << " MeV, "
            << "          Energy deposited: " << step->GetTotalEnergyDeposit() / MeV << " MeV" << G4endl
            << "          Energy: " << track->GetTotalEnergy() / MeV << " MeV" << G4endl
            << "          Momentum: " << track->GetMomentum() / MeV << " MeV" << G4endl;


    }

}

