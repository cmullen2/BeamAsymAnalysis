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
  //Also need the spectator too here(beam, spec, participant, meson)
  fFinal.push_back(&fNeutron);
  fFinal.push_back(&fPip);
  fFinal.push_back(&fPhoton);
  fFinal.push_back(&fProton);//spectator

  //Initialise particle iters
  fDetIter.resize(fNTopo);
  Init_Iter0();
}


void THSProj_PiPlusN::Init_Generated(){
  if(!THSFinalState::frGenParts) return;
  if(THSFinalState::frGenParts->size()!=4) {fGoodEvent=kFALSE;return;}
  //Fill our data member particles
  //User is responsible for indicing right
  //comes from order in generated file (e.g LUND)
  if(THSFinalState::fIsGenerated){
    //fElectron=*frGenParts->at(0);
    fSpec = *frGenParts->at(0);
    fPart = *frGenParts->at(1);
    fPip = *frGenParts->(2);
    fPhoton = *frGenParts(3);

        //Is this needed?
    fNeutron = fPart;
         
    
    

  }
  else{//Just assign truth values
    //fElectron.SetTruth(frGenParts->at(0));
    
    fSpec.SetTruth(frGenParts->at(0));
    fPart.SetTruth(frGenParts->at(1));
    fNeutron.SetTruth(frGenParts->at(1));  
    fPip.SetTruth(frGenParts->at(2));
    fPhoton.SetTruth(frGenParts->at(3));

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

//__________________________________________________________________________________________
//Define topology functions
void THSProj_PiPlusN::Topo_0(){
  //Reconstruct missing or combined particles
  
//Plan to use simulation to correct for pion energy and take this as 'perfect' then use doms function on the neutron. Create all the missing stuff using the pion as good.

  //Dominik's Energy function(Dependent on the pion 4-vec and neutron angles
  fNucleonLabEnergy = CalcQFThreeBodyRecoilPartT(fPhoton.P4.E(), fPip.P4(), fNeutron.P4(), massTarget, massNeutron, massProton);
  fMissNucleon = fPhoton.P4() + fFreeNeutron - fPip.P4();
}

void THSProj_PiPlusN::Kinematics(){
  if(!THSFinalState::fGoodEvent) return;//don't do calculations
  //Do calculations if Good Event

 if(fNeutron.P4p()->Phi()==0 && fNeutron.P4p()->Theta()==0){
    fDetErrs = -1;
  }
  else{
    fDetErrs = 0;
  }


  if(fNucleonLabEnergy<0){
    fDomFuncErrs = -1;
  }
  else{
    fDomFuncErrs = 0;
  }

	//Timing
  fTagTime = fPhoton.Time();
  fPipTime = fPip.Time();
  fNeutronTime = fNeutron.Time();

        //Adjustment for jitter, common start and stop different in Taps vs Ball
  if( fNeutron.Detector()<8)  fNeutronTagDiffTime = fProtonTime - fTagTime;
  if( fNeutron.Detector()>7)  fNeutronTagDiffTime = fNeutronTime - fTagTime;
  if( fPip.Detector()<8)  fPipTagDiffTime = fPipTime - fTagTime;
  if( fPip.Detector()>7)  fPipTagDiffTime = -fPipTime - fTagTime;


	//Apply any Energy Corrections
  fNucleonRawEnergy = fNeutron.P4p()->E();

  if(std::isnan(fNucleonLabEnergy) ){
    fEnergyErrs = -1;
    fNeutron.P4p()->SetE(fNeutron.P4p()->E() + fNeutron->PDGMass() ); //Verify for neutron case!
  }
  else{
    fEnergyErrs = 0;
    fNeutron.P4p()->SetE(fNucleonLabEnergy + fNeutron.PDGMass());
  }

  if(fDetErrs==0)  fNeutron.TakePDGMassFromE();

  fNucleonEnergyFinal = fNeutron.P4p()->E();



        //Reconstruct missing or combined particles
  fPipRawEnergy = fPip.P4p()->E();
  fBeamEnergy = fPhoton.P4p()->E();
  fSpectator = fPhoton.P4() + fTarget - fNeutron.P4() - fPip.P4();
  fPipMassDiff = (TDatabasePDG::Instance()->GetParticle(211)->Mass()) *1000 - fPip.P4p()->M();
  fMissP4 = fPhoton.P4() + fTarget - fPip.P4();
  fMissMass = fMissP4.M();
  fInvMass = fPip.P4p()->M();
  fSpecMass = fSpectator.M(); //Should be almost junk
  fSpecMom = fSpectator.Vect().Mag();
  fCoplanarity = ( fPip.P4().TLorentzVector::DeltaPhi( -(fNeutron.P4()) ) )*TMath::RadToDeg();
  fInitialN = fTarget - fSpectator;
  fConeAngle = fMissNucleon.Angle(fNeutron.P4().Vect());
  fConePhi = (fMissNucleon.TLorentzVector::DeltaPhi(fNeutron.P4() ) )*TMath::RadToDeg();



        //Tests of angular distributions
  fNeutronPhi = fNeutron.P4().Phi();
  fNeutronTheta = fNeutron.P4().Theta();
  fPipPhi = fPip.P4().Phi();
  fPipTheta = fPip.P4().Theta();

        //Detector Tests
  fNeutronDetector = fNeutron.Detector();
  fPipDetector = fPip.Detector();

        //Polarisation
  fTaggChannel = fPhoton.Detector();
  fPolState = fPhoton.EdgePlane();
  fPolVec = fPhoton.Vertex();
  fPol = fPolVec.X();
  fPolStateD = fPhoton.EdgePlane();
//  fPolStateD = -1; // For SIMS

        //Zero Polarisation
  if(fPol==0){
    fPolErrs = -1;
  }
  else{
    fPolErrs=0;
  }

        //Using Kinematics functions
  fKine.SetGammaTarget(fPhoton.P4(),fInitialN);
  fKine.SetMesonBaryon(fPip.P4(),fNeutron.P4());
  fKine.PhotoCMDecay();
  fCMPhi = (fKine.Phi())*TMath::RadToDeg();
  fCosth = fKine.CosTheta();
  fW = fKine.W();
  fProduc = fFreeNeutron + fPhoton.P4();
  fWII = fW - fProduc.M();


  if(fDetErrs==-1 || fEnergyErrs==-1 || fDomFuncErrs==-1 ){
    fAnyErrs = -1;
  }
  else{
    fAnyErrs=0;
  }

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
    if(FindInclusiveTopology(-22)==-1) {fGoodEvent=kFALSE;return fIsPermutating0=kFALSE;}
    //if(FindTopology()==-1) {fGoodEvent=kFALSE;return fIsPermutating0=kFALSE;}
    //Do they correspond to a defined topology?
    else if(fCurrTopo==fTID_0) Topo_0();
    // else if(fCurrTopo==fTID_) Topo_();
    else fGoodEvent=kFALSE;
    //Get truth values
    Init_Generated();
  }
  
  //Calc kinematics
  Kinematics();

  if(fPipTagDiffTime<-100 || fPipTagDiffTime>100){
    fGoodEvent=kFALSE;

  }
  



  //Check if assigned vectors agree with true generated
  //Simulation only
  THSFinalState::CheckTruth();
  
//  fDCorrect = fCorrect -1; //For SIMS may be deprecated!
    fDCorrect = fCorrect; //For PROD 
    



  //Can do some checks if event is worth writing or not
  //if()fGoodEvent=kTRUE;
  //else() fGoodEvent =kFALSE;
  if(fIsGenerated) return kTRUE; //Generated only 1 permutation
  return kTRUE;
}
