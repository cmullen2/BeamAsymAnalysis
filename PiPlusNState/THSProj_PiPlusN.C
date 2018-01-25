/**
 * \class THSProj_PiPlusN
 * 
 * Template final class .
 * 
 * Users should create their own analysis specific project classes.
 * 
 */



#include "TDatabasePDG.h"
#include "THSProj_PiPlusN.h"
#include <algorithm>


THSProj_PiPlusN::THSProj_PiPlusN(){
  //SetUseChargePID();//If want to only use charge for IDing
  //include topology for analysis and get index
  fTID_0=AddTopology("pi+:neutron");
 
  //Set final state
  //Note for CheckTruth algorithm to work all particles added 
  //to fFinal should have been in Generated 
  fFinal.push_back(&fNeutron);
  fFinal.push_back(&fPip);
  fFinal.push_back(&fPhoton);

  //Initialise particle iters
  fDetIter.resize(fNTopo);
  Init_Iter0();
}


void THSProj_PiPlusN::Init_Generated(){
  if(!THSFinalState::frGenParts) return;
  if(THSFinalState::frGenParts->size()!=REPLACE_WITH_N_GENERATED_PARTICLES) {fGoodEvent=kFALSE;return;}
  //Fill our data member particles
  //User is responsible for indicing right
  //comes from order in generated file (e.g LUND)
  if(THSFinalState::fIsGenerated){
    //fElectron=*frGenParts->at(0);
  }
  else{//Just assign truth values
    //fElectron.SetTruth(frGenParts->at(0));
  }
}

//Define topology Iterator functions
void THSProj_PiPlusN::Init_Iter0(){
  //THSParticle iterator initialisation
  //For topology pi+:neutron

  THSParticleIter* diter=CreateParticleIter(fTID_0,&fVecBeams,1);
  AddSelectToSelected(diter,1,1,&fPhoton);
  diter=CreateParticleIter(fTID_0,&fVecPiPs,1);
  //  AddSelectToSelected(diter,2,1,&fGamma1,&fGamma2);
  AddSelectToSelected(diter,1,1,&fPip);
  diter=CreateParticleIter(fTID_0,&fVecNeutrons,1);
  AddSelectToSelected(diter,1,1,&fNeutron);



//If create iterator must configure it
  fDetIter[fTID_0]->ConfigureIters();
}


// void THSProj_PiPlusN::Init_IterX(){
//  THSParticleIter* diter=CreateParticleIter(fTID_X,&fVecY,NPARTICLES);
//  ...
//  fDetIter[fTID_0]->ConfigureIters();
// }
//Or if iterator the same as a previous one
// void THSProj_PiPlusN::Init_IterY(){
//   fDetIter[fTID_1]=fDetIter[fTID_0];
// }



//__________________________________________________________________________________________
//Define topology functions
void THSProj_PiPlusN::Topo_0(){
  //Reconstruct missing or combined particles

}
// void THSProj_PiPlusN::Topo_X(){
// }

void THSProj_PiPlusN::Kinematics(){
  if(!THSFinalState::fGoodEvent) return;//don't do calculations
  //Do calculations if Good Event

}

void THSProj_PiPlusN::FinalStateOutTree(TTree* tree){
  THSFinalState::fFinalTree=tree;
  //tree->Branch("Final",&fFinal);//If you want to save the final THSParticles
  tree->Branch("MissMass",&fMissMass,"MissMass/D");

}
Bool_t THSProj_PiPlusN::WorkOnEvent(){
  //Should this event be saved?
  THSFinalState::fGoodEvent=kTRUE;
  THSFinalState:: fCorrect=0; //Correct permutation? used for simulation only

  //If generated MC events
  if(THSFinalState::fIsGenerated) Init_Generated();
  else{//Look for reconstructed events
    //if reconstructed Find the detected particles in this event
    //    if(FindInclusiveTopology()==-1) {fGoodEvent=kFALSE;return fIsPermutating0=kFALSE;}
    if(FindTopology()==-1) {fGoodEvent=kFALSE;return fIsPermutating0=kFALSE;}
    //Do they correspond to a defined topology?
    else if(fCurrTopo==fTID_0) Topo_0();
    // else if(fCurrTopo==fTID_) Topo_();
    else fGoodEvent=kFALSE;
    //Get truth values
    Init_Generated();
  }
  
  //Calc kinematics
  Kinematics();
  
  //Check if assigned vectors agree with true generated
  //Simulation only
  THSFinalState::CheckTruth();
  
  //Can do some checks if event is worth writing or not
  //if()fGoodEvent=kTRUE;
  //else() fGoodEvent =kFALSE;
  if(fIsGenerated) return kTRUE; //Generated only 1 permutation
  return kTRUE;
}