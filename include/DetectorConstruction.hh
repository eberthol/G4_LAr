#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "Constants.hh"

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4MaterialPropertiesTable.hh"

#include <vector>


class G4Material;

/// Detector construction

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override = default;

    G4VPhysicalVolume* Construct() override;
    void ConstructMaterials();

  private:
    G4double fxWorld = kxWorld;
    G4double fyWorld = kyWorld;
    G4double fzWorld = kzWorld;

    G4MaterialPropertiesTable* fLArMPT =  nullptr;

    G4Material* fLAr    =  nullptr;
    G4Material* fGAr    =  nullptr;
    G4Material* fAir    =  nullptr;
    G4Material* fvacuum =  nullptr;
    

};


#endif
