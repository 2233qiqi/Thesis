#include "EventAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

EventAction :: EventAction() : G4UserEventAction()
{

}

EventAction :: ~EventAction()
{

}

void EventAction ::BeginOfEventAction(const G4Event* anEvent)
{
    fCrystalEdep.clear();
}

void EventAction :: EndOfEventAction(const G4Event* anEvent)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager :: Instance();

    for (auto const&[id,edep] : fCrystalEdep)
    {
        if (edep>0.)
        {
            analysisManager->FillNtupleIColumn(0, id);   
            analysisManager->FillNtupleDColumn(1, edep); 
            analysisManager->AddNtupleRow();
        }
    }
}