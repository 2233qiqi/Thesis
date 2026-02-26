#include "EventAction.hh"
#include "SteppingAction.hh"
#include "G4Step.hh"

SteppingAction :: SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(), fEventAction(eventAction)
{
}