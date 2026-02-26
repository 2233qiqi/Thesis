#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

RunAction :: RunAction() : G4UserRunAction()
{
    auto analysisMannager = G4AnalysisManager::Instance();
    analysisMannager->SetDefaultFileType("root");
}