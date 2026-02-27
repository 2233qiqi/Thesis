#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

RunAction :: RunAction() : G4UserRunAction()
{
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetVerboseLevel(1);
    analysisManager->SetDefaultFileType("root");
}

RunAction :: ~RunAction()
{
    delete G4AnalysisManager :: Instance();
}
    
void RunAction::BeginOfRunAction(const G4Run* anRun)
{
    auto analysisManager = G4AnalysisManager :: Instance();

    analysisManager->OpenFile("CodedAperture.root");
    analysisManager->CreateNtuple("Hits", "Crystal Edep Data");
    analysisManager->CreateNtupleIColumn("CrystalID"); 
    analysisManager->CreateNtupleDColumn("Edep");      
    analysisManager->FinishNtuple();
}

void RunAction :: EndOfRunAction(const G4Run* anRun)
{
    auto analysisManager = G4AnalysisManager :: Instance();

    analysisManager->Write();
    analysisManager->CloseFile();
}