
#ifndef THSPROJ_PIMINUSP_h
#define THSPROJ_PIMINUSP_h

#include "THSFinalState.h"
#include "TLorentzVector.h"
#include <vector>

class THSProj_PiMinusP : public THSFinalState{

 public :
  THSProj_PiMinusP();
  ~THSProj_PiMinusP(){};

  virtual Bool_t WorkOnEvent();

  //Init functions
  void Init_Iter0();
  void Topo_0();
  void Init_Generated();
  //void Init_IterX();
  //void Topo_X();

  void Kinematics();
  protected :
  //Topology flags for this project
  Int_t fTID_0=-1;
  // Int_t fTID_=-1;
 
  //Initial state
  TLorentzVector fBeam=TLorentzVector(0,0,10.6,10.6);
  TLorentzVector fTarget=TLorentzVector(0,0,0,0.938272);
  //Final Particles
  THSParticle fPim=THSParticle("pi-");
  THSParticle fProton=THSParticle("proton");
 
  //Observables
  Double_t f_t;
  Double_t f_Q2;
  Double_t f_W;
  Double_t f_Pol;
  Double_t fCMCosTh;
  Double_t fCMPhi;

  //Discriminators
  Double_t fMissMass=0;

   public :
  virtual void FinalStateOutTree(TTree* tree);

 

};

#endif //ifdef THSProj_PiMinusP
