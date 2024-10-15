#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "EventAction.hh"
#include "globals.hh" // This includes Geant4 type definitions like G4int, G4double, etc.
// #include "G4Track.hh"


class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction(EventAction* eventAction); //EventAction* eventAction
    virtual ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*) override;

    void PrintInfo(const G4Step* step); // to print out stuff 

private:
    EventAction* fEventAction;
    G4double fTotalEnergyDeposited; // Accumulated energy deposited in the event
    G4double ftotalDistance;
};

#endif
