#include "PhysicsList.hh"

#include "G4VModularPhysicsList.hh"
#include "FTFP_BERT.hh"
// #include "FTFP_BERT_HP.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4OpticalPhysics.hh"

PhysicsList::PhysicsList()
{
    // G4VModularPhysicsList* physicsList = new FTFP_BERT;
    // physicsList->RegisterPhysics( new G4OpticalPhysics );

    // fphysicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
    
    // optical photons (for example for scintillation)
    // G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();

    // // opticalPhysics->SetScintillationYieldFactor(1.);
    // // opticalPhysics->SetScintillationExcitationRatio(0.);
    // // opticalPhysics->SetTrackSecondariesFirst(kScintillation, true);

    // physicsList->RegisterPhysics(opticalPhysics);


}
