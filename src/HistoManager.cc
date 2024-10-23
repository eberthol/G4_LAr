#include "HistoManager.hh"
#include "G4UnitsTable.hh"

HistoManager::HistoManager()
{
  Book();
}

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetDefaultFileType("root");
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);   //enable inactivation of histograms
  
  // Define histograms start values
  const G4int kMaxHisto = 1;
//   const G4String id[] = { "0", "1", "2", "3" , "4", "5", "6"};
  const G4String id[] = { "WavelengthOptical"};
  const G4String title[] = 
                {  "Optical Photons; Wavelength (nm); Counts",             //0
                    // "Optical Photons; Wavelength (nm); Counts",           //1
                //   "scattered primary particle: costheta distribution",  //2
                //   "charged secondaries: energy spectrum",               //3
                //   "charged secondaries: costheta distribution",         //4
                //   "neutral secondaries: energy spectrum",               //5
                //   "neutral secondaries: costheta distribution"          //6
                 };  

                //  analysisManager->CreateH1("Wavelength",   "Optical Photons; Wavelength (nm); Counts", 100, 120, 140);

  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHisto; k++) {
    G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih, false);
  }
}