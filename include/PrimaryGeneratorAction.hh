
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

#include <CLHEP/Units/SystemOfUnits.h>

class G4ParticleGun;
// class G4GenericMessenger;
// class G4Event;
// class G4ParticleDefinition;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction() override;

    void GeneratePrimaries(G4Event*) override;

  private:
    G4ParticleGun* fParticleGun;
    
};

#endif
