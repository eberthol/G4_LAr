#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"


class G4Run;
class DetectorConstruction;
class EventAction;
class HistoManager;

/// Run action class

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    ~RunAction() override;

    void BeginOfRunAction(const G4Run*) override;
    void   EndOfRunAction(const G4Run*) override;

  private:
    HistoManager*           fHistoManager = nullptr;
 
};


#endif