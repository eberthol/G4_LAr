#include "PhysicsList.hh"

#include "G4VModularPhysicsList.hh"

// #include "FTFP_BERT.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4NeutronTrackingCut.hh"

// #include "FTFP_BERT_HP.hh"
// #include "G4EmStandardPhysics_option4.hh"
// #include "G4OpticalPhysics.hh"


PhysicsList::PhysicsList()
{

    //--------- FTFP_BERT(_HP) default
    defaultCutValue = 0.7*CLHEP::mm;  // THIS IS VERY IMPORTANT!
    // sets the cut in G4EmModelManager::FillLambdaVector() 
    // for example: for e- in G4_Galactic Emin(MeV)= 100 Emax(MeV)= 1e+08 cut= 0.07 Type 1 nmod= 1
    // cutEnergy of the CrossSection see  source/processes/electromagnetic/utils/src/G4VEmModel.cc (L178) and also .hh

    // note that FTFP_BERT_HP includes some more cuts
    G4int ver = 0; // verbosity level
    // SetVerboseLevel(ver);

    // EM Physics
    RegisterPhysics( new G4EmStandardPhysics(ver));
    
    // Synchroton Radiation & GN Physics
    RegisterPhysics( new G4EmExtraPhysics(ver) );

    // Decays 
    RegisterPhysics( new G4DecayPhysics(ver) );
    // RegisterPhysics( new G4RadioactiveDecayPhysics(ver) ); // FTFP_BERT_HP

    // Hadron Elastic scattering
    RegisterPhysics( new G4HadronElasticPhysics(ver) );
    // RegisterPhysics( new G4HadronElasticPhysicsHP(ver) ); // FTFP_BERT_HP

    // Hadron Physics
    RegisterPhysics(  new G4HadronPhysicsFTFP_BERT(ver));
    // RegisterPhysics( new G4HadronPhysicsFTFP_BERT_HP(ver) ); // FTFP_BERT_HP

    // Stopping Physics
    RegisterPhysics( new G4StoppingPhysics(ver) );

    // Ion Physics
    RegisterPhysics( new G4IonPhysics(ver));

    // Neutron tracking cut
    RegisterPhysics( new G4NeutronTrackingCut(ver)); // not in FTFP_BERT_HP

    //--------- additions, modifications

    // RegisterPhysics( new G4OpticalPhysics );

    // fphysicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
    
    // optical photons (for example for scintillation)
    // G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();

    // // opticalPhysics->SetScintillationYieldFactor(1.);
    // // opticalPhysics->SetScintillationExcitationRatio(0.);
    // // opticalPhysics->SetTrackSecondariesFirst(kScintillation, true);

    // physicsList->RegisterPhysics(opticalPhysics);


}
