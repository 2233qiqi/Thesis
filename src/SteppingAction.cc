#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4Step.hh"

SteppingAction :: SteppingAction(EvenAction* eventAction): G4UserSteppingAction(), fEventAction(eventAction)
{

}

SteppingAction::~SteppingAction()
{

}

void SteppingAction :: UserSteppingAction(const G4Step* step)
{
     G4VPhysicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
    if (!volume) return;
    if (volume->GetName() == "PhysicalBgo") 
    {
         G4double edep = step->GetTotalEnergyDeposit();

        if (edep > 0.)
        {
            G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
            fEventAction->AddEnergy(copyNo, edep);
        }
    }
}