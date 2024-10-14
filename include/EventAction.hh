#ifndef EventAction_h
#define EventAction_h 1

#include "RunAction.hh"

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"

#include <vector>
#include <array>

/// Event action

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;

    void AddScintillationPhoton();
    void AddFlightDistance(G4double distance);
    void AddEdep(G4double edep){ fEnergyDeposited +=edep; }
    void AddEdepPrimary(G4double edep){ fEnergyDepositedPrimary +=edep; }

    void getExitFourMomentum(G4double E, G4ThreeVector p);

private:
  G4int fScintillationPhotonCount;
  G4double fEnergyDeposited;
  G4double fEnergyDepositedPrimary;
  G4double fFlightDist;
  G4double fExitEnergy;
  G4ThreeVector fExitMomentum;

  
};


#endif