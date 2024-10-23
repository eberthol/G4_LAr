#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"
#include "G4AnalysisManager.hh"

class HistoManager
{
  public:
   HistoManager();
  ~HistoManager() = default;

  private:
    void Book();
    G4String fFileName = "Histograms";
};

#endif