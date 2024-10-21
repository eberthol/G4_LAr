#ifndef Constants_h
#define Constants_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"

//--- room dimensions
constexpr G4double kxWorld = 5.* m;
constexpr G4double kyWorld = 5.* m;
constexpr G4double kzWorld = 5.* m;

//--- argon sphere
constexpr G4double kouterRadius = 50.*cm;      // Outer radius

//--- particle gun
constexpr G4double kEnergy       = 10.0 * MeV;
// position
constexpr G4double kGunPositionX = 0.0;
constexpr G4double kGunPositionY = 0.0;
constexpr G4double kGunPositionZ = -kzWorld/2 ;
// direction
constexpr G4double kDirectionX = 0.0;
constexpr G4double kDirectionY = 0.0;
constexpr G4double kDirectionZ = 1.0;

//--- Material properties
constexpr G4double kFastTimeConstant = 6.0*ns;    // Fast scintillation decay time
constexpr G4double kSlowTimeConstant = 1500.0*ns; // Slow scintillation decay time
constexpr G4double kYieldRatio = 0.8; // 80% fast component, 20% slow component
constexpr G4double kScintYield = 10./MeV; // dummy 

const std::vector<G4double> kPhotonEnergy = {9.69*eV, 9.69*eV}; // dummy   128nm -> 9.69eV
const std::vector<G4double> kLArRefractionIndex = {1.49, 1.49}; // dummy 
const std::vector<G4double> kLArAbsorptionLength = {200.*cm, 200.*cm}; // dummy
const std::vector<G4double> kScintComponent1 = {1.0, 1.0}; // Fast component (normalized to 1)
const std::vector<G4double> kScintComponent2 = {0.3, 0.3}; // Slow component (normalized to 0.3)






#endif
