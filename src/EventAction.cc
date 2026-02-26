#include "EventAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

EvenAction :: EvenAction() : G4UserEventAction()
{

}

EvenAction :: ~EvenAction()
{

}

void EvenAction ::BeginOfEventAction(const G4Event* anEvent)
{
    fCrystalEdep.clear();
}

void EvenAction :: EndOfEventAction(const G4Event* anEvent)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager :: Instance();

    for (auto const&crystal : fCrystalEdep)
    {
        if (edep>0)
        {
            
        }
    }
}