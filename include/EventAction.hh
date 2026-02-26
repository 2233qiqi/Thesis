#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include <vector>

class EvenAction : public G4UserEventAction
{
    public: 
    EvenAction();
    virtual ~EvenAction();

    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void EndOfEventAction(const G4Event* anEvent);
    void AddEnergy(G4int crystalID,G4double edep)
    {
        fCrystalEdep[crystalID] += edep;
    }


    private:
    std::map<G4int, G4double> fCrystalEdep;


};




#endif