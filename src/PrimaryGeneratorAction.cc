#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
// #include "G4IonTable.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    // Create a particle gun to generate neutrons
    fParticleGun = new G4ParticleGun(1);  // One particle at a time

    // Set the neutron properties
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* neutron = particleTable->FindParticle("neutron");
    fParticleGun->SetParticleDefinition(neutron);
    fParticleGun->SetParticleEnergy(2.45 * MeV);  // Set the energy of the neutron
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.)); // Set initial position
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    // Generate the primary particle
    fParticleGun->GeneratePrimaryVertex(event);
}