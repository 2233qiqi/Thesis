#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"    
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4Exception.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    fGPS = new G4GeneralParticleSource();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    fGPS->GeneratePrimaryVertex(anEvent);
}