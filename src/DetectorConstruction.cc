
#include "DetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Sphere.hh"
#include "G4SystemOfUnits.hh"
#include "G4MaterialPropertiesTable.hh"


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
    = new G4LogicalVolume(worldSolid, fvacuum, "worldLogical");
  auto worldPhysical = new G4PVPlacement(
    nullptr, G4ThreeVector(), worldLogical, "worldPhysical", nullptr, false, 0, checkOverlaps);

  // Define a solid sphere filled with LAr with a radius of 11 cm
  G4double innerRadius = 0.*cm;       // Inner radius (0 for a solid sphere)
  // G4double outerRadius = 11.*cm;      // Outer radius
  G4double outerRadius = 50.*cm;      // Outer radius
  G4double startPhi = 0.*deg;         // Start angle in phi
  G4double deltaPhi = 360.*deg;       // Full coverage in phi
  G4double startTheta = 0.*deg;       // Start angle in theta
  G4double deltaTheta = 180.*deg;     // Full coverage in theta (for a complete sphere)
  G4Sphere* LArSphereSolid = new G4Sphere("LArSphere", innerRadius, outerRadius, 
                                         startPhi, deltaPhi, 
                                         startTheta, deltaTheta);

    // Logical volume: The material and shape of the volume
    G4LogicalVolume* LArSphereLogical = new G4LogicalVolume(LArSphereSolid, fLAr, "LArSphereLogical");

    // Placement of the sphere in the world (at the origin in this case)
    G4VPhysicalVolume* LArSpherePhysical = new G4PVPlacement(0,                    // No rotation
                                                      G4ThreeVector(0,0,0), // At (0, 0, 0)
                                                      LArSphereLogical,          // Logical volume
                                                      "LArSpherePhysical",         // Name
                                                      worldLogical,           // Mother volume (assume it's already defined)
                                                      false,                // No boolean operation
                                                      0,                    // Copy number
                                                      true);                // Check for overlaps

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

  const G4int nEntries = 2;
  G4double PhotonEnergy[nEntries] = {1.0*eV, 7.0*eV}; // dummy values
  G4double LArRefractionIndex[nEntries] = {1.25, 1.25}; // dummy values
  G4double LArAbsorptionLength[nEntries] = {50*cm, 50*cm}; // dummy values
  G4double ScintEnergy[nEntries] = {3.26*eV, 3.44*eV}; // dummy values
  G4double ScintFast[nEntries] = {1.0, 1.0}; // dummy values


  fLArMPT = new G4MaterialPropertiesTable();
  fLArMPT->AddProperty("RINDEX", PhotonEnergy, LArRefractionIndex, nEntries);
  fLArMPT->AddProperty("ABSLENGTH", PhotonEnergy, LArAbsorptionLength, nEntries);

  // fLArMPT->AddProperty("FASTCOMPONENT", ScintEnergy, LArAbsorptionLength, nEntries);

  fLArMPT->AddConstProperty("SCINTILLATIONYIELD", 10. / MeV); // dummy value
  // fLArMPT->AddConstProperty("SCINTILLATIONYIELD", 100. / keV); // dummy value
  fLArMPT->AddConstProperty("RESOLUTIONSCALE", 1.0);  // Scaling factor for fluctuations
  // fLArMPT->AddConstProperty("FASTTIMECONSTANT", 20.*ns);  // dummy value
  // fLArMPT->AddConstProperty("YIELDRATIO", 1.);  // dummy value

  fLAr->SetMaterialPropertiesTable(fLArMPT);


  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}