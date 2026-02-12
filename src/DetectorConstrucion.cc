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

    //MURA准直器
    G4int p = 19;
    G4double mask_xy = 2.4*mm;
    G4double mask_z = 8.0*mm;
    G4double MDD = 59*mm;

    //MURA图案
    G4int MURA19[19];
    MURA19[0]=0;
    for (G4int i = 1;i<p;i++)
    {
        bool result = false;
        for (G4int j =1 ;j<p;j++)
        {
            if ((j*j)% p ==i)
            {
                result =  true;
                break;
            }
        }
        MURA19[i]= result ? 1:0;
    }

    //准直器单元
    G4Box* solidMaskUnit = new G4Box("solidMaskUnit",mask_xy/2,mask_xy/2,mask_z/2);
    G4LogicalVolume* LogicalMaskUnit = new G4LogicalVolume(solidMaskUnit,WCumat,"LogicalMaskUnit");
    G4double mask_z = (Bgo_z/2)+MDD+(mask_z/2);
    for (G4int i =0;i<37;i++)
    {
        for (G4int j = 0;j<37;j++)
        {
            G4int mask_i = i%p;
            G4int mask_j = j%p;

            G4int val;
            if (mask_i==0)
            {
                val = MURA19[mask_i];
            }
            else
            {
                val = MURA19[(mask_i*mask_j)%p];
            }

            if (val==0)
            {
                G4double x = (i-18)*mask_xy;
                G4double y = (j-18)*mask_xy;
                G4VPhysicalVolume* PhysicalMaskUnit = new G4PVPlacement(0,G4ThreeVector(x,y,mask_z),LogicalMaskUnit,"PhysicalMaskUnit",LogicalWorld,false,0,true);
            }
         
        }
        
    }
    
    //可视化属性
    LogicalBgo->SetVisAttributes(new G4VisAttributes(G4Color(1.0,0.0,0.0,1.0)) );
    LogicalMaskUnit->SetVisAttributes(new G4VisAttributes(G4Color(0.0,1.0,0.5,1.0)));

    return PhysicalWorld;

}