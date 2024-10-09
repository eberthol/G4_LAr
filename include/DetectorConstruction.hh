#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
// #include "G4Box.hh"
// #include "G4Tubs.hh"
// #include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

#include <vector>


class G4Material;



// class G4VPhysicalVolume;
// 
// class G4VSensitiveDetector;
// class G4LogicalVolume;
// class G4GenericMessenger;
// class G4MaterialPropertiesTable;

/// Detector construction

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override = default;

    G4VPhysicalVolume* Construct() override;
    void ConstructMaterials();

  private:
    G4double fxWorld = 4. * m;
    G4double fyWorld = 3. * m;
    G4double fzWorld = 5. * m;

    G4Material* fLAr    =  nullptr;
    G4Material* fGAr    =  nullptr;
    G4Material* fAir    =  nullptr;
    G4Material* fvacuum =  nullptr;
    

};


#endif
