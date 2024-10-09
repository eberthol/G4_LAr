
#include "DetectorConstruction.hh"
// #include "Constants.hh"
// #include "PMTSD.hh"


#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"

// #include "G4TransportationManager.hh"
// #include "G4Mag_UsualEqRhs.hh"

// 
// #include "G4Element.hh"
// #include "G4MaterialTable.hh"

// #include "G4VSolid.hh"
// #include "G4Tubs.hh"

// #include "G4PVParameterised.hh"
// #include "G4PVReplica.hh"
// #include "G4UserLimits.hh"

// #include "G4SDManager.hh"
// #include "G4VSensitiveDetector.hh"
// #include "G4RunManager.hh"
// #include "G4GenericMessenger.hh"

// #include "G4VisAttributes.hh"
// #include "G4Colour.hh"

// #include "G4ios.hh"
#include "G4SystemOfUnits.hh"


DetectorConstruction::DetectorConstruction()
{

  ConstructMaterials();
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  // geometries --------------------------------------------------------------
  // experimental hall (world volume)
  auto worldSolid
    = new G4Box("worldBox", fxWorld*0.5, fyWorld*0.5, fzWorld*0.5);
  auto worldLogical
    = new G4LogicalVolume(worldSolid, fAir, "worldLogical");
  auto worldPhysical = new G4PVPlacement(
    nullptr, G4ThreeVector(), worldLogical, "worldPhysical", nullptr, false, 0, checkOverlaps);

  return worldPhysical;
}

void DetectorConstruction::ConstructMaterials()
{
  auto nistManager = G4NistManager::Instance();
  // to list all materials (in the interface): /material/nist/listMaterials

  // Air
  fAir = nistManager->FindOrBuildMaterial("G4_AIR");
  // Argon gas
  fGAr = nistManager->FindOrBuildMaterial("G4_Ar");
  // Argon liquid
  fLAr = nistManager->FindOrBuildMaterial("G4_lAr");
  // Vacuum doesn't exist 
  // create a gas with very low density
  // use predefined database (eg. G4_Galactic)
  fvacuum = nistManager->FindOrBuildMaterial("G4_Galactic");

  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}