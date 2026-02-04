#include "DetectorConstrution.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

DetectorConstruction ::DetectorConstruction() 
{

}

DetectorConstruction::~DetectorConstruction()
{

}

G4VPhysicalVolume* DetectorConstruction ::Construct()
{
    G4bool checkoverlaps = true; 

    G4NistManager* nist = G4NistManager::Instance();
    G4Material* Worldmat = nist ->FindOrBuildMaterial("G4_AIR");
    G4Material* Bgomat = nist ->FindOrBuildMaterial("G4_BGO");

    //铜钨合金
    G4Material* WCumat = new G4Material ("WCu_mat",15*g/cm3,2);
    WCumat -> AddElement(nist ->FindOrBuildElement("G4_W",0.80),1);
    WCumat ->AddElement(nist ->FindOrBuildElement("G4_Cu",0.2),1);

    //World
    G4double World_binary = 2.*m;
    G4Box* solidWorld = new G4Box("World",World_binary/2,World_binary/2,World_binary/2);
    G4LogicalVolume* LogicalWorld = new G4LogicalVolume(solidWorld,Worldmat,"LogicalWorld");
    G4VPhysicalVolume* PhysicalWorld = new G4PVPlacement(0,G4ThreeVector(0,0,0),LogicalWorld,"PhysicalWorld",0,false,0,true);

    //BGO
    G4double Bgo_xy = 2.4*mm;
    G4double Bgo_z = 10*mm;
    G4Box* solidBgo = new G4Box("solidBgo",Bgo_xy/2,Bgo_xy/2,Bgo_z/2);
    G4LogicalVolume* LogicalBgo = new G4LogicalVolume(solidBgo,Bgomat,"LogicalBgo");
    for (G4int i = 0;i<19;i++)
    {
        for(G4int j =0;j<19;j++)
        {
            G4double x = (i-9)*Bgo_xy;
            G4double y = (j-9)*Bgo_xy;
            G4VPhysicalVolume* PhysicalBgo =  new G4PVPlacement(0,G4ThreeVector(x,y,0),LogicalBgo,"PhysicalBgo",LogicalWorld,false,0,true);
        }
    }

    //MURA
    G4double p = 19;
    








}