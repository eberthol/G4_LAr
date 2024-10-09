#ifndef EventAction_h
#define EventAction_h 1

#include "RunAction.hh"

#include "G4UserEventAction.hh"
#include "globals.hh"

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
    void AddEdep(G4double edep){ fEnergyDeposited +=edep; }

private:
  G4int fScintillationPhotonCount;
  G4double fEnergyDeposited;

  
};


#endif