/**
 * \class THSProj_PiMinusP
 * 
 * Template final class .
 * 
 * Users should create their own analysis specific project classes.
 * 
 */



#include "TDatabasePDG.h"
#include "THSProj_PiMinusP.h"
#include <algorithm>


THSProj_PiMinusP::THSProj_PiMinusP(){
  //SetUseChargePID();//If want to only use charge for IDing
  //include topology for analysis and get index
  fTID_0=AddTopology("pi-:proton");
 
  //Set final state
  //Note for CheckTruth algorithm to work all particles added 
  //to fFinal should have been in Generated  (need beam, )
  fFinal.push_back(&fPim);
  fFinal.push_back(&fProton);
  fFinal.push_back(&fPhoton);//Beam
  //  fFinal.push_back(&fNeutron);//Spectator

  //Initialise particle iters
  fDetIter.resize(fNTopo);
  Init_Iter0();
}


void THSProj_PiMinusP::Init_Generated(){
   return;  //THIS LINE NEEDED FOR PROD DATA
  if(!THSFinalState::frGenParts) return;
  if(THSFinalState::frGenParts->size()!=4) {fGoodEvent=kFALSE;return;}
  //Fill our data member particles
  //User is responsible for indicing right
  //comes from order in generated file (e.g LUND)
  if(THSFinalState::fIsGenerated){
    //fElectron=*frGenParts->at(0);
    fSpec = *frGenParts->at(0);
    fPart = *frGenParts->at(1);
    // fProton = *frGenParts->at(1);
    fPimGen = *frGenParts->at(2);
    fPhotonGen = *frGenParts->at(3);

    //Is this needed?
    //   fProton = fPart;   
  }
  else{//Just assign truth values
    //fElectron.SetTruth(frGenParts->at(0));
    
    // fSpec.SetTruth(frGenParts->at(0));
    // fPart.SetTruth(frGenParts->at(1));
    fProton.SetTruth(frGenParts->at(2));  //Proton Channel only, what do I do for neutron channel?
    fPim.SetTruth(frGenParts->at(1));
    fPhoton.SetTruth(frGenParts->at(3));

    //cout <<"Truth info 0: "<< frGenParts->at(0)->PDG() <<"Truth info 1: "<< frGenParts->at(1)->PDG() << "Truth info 2: "<< frGenParts->at(2)->PDG() << "Truth info 3: "<< frGenParts->at(3)->PDG() <<  endl;
    //cout <<"Truth info 0: "<< frGenParts->at(0)->P4().E() <<"Truth info 1: "<< frGenParts->at(1)->P4().E()  <<  endl;

  }
}

//Define topology Iterator functions
void THSProj_PiMinusP::Init_Iter0(){
  //THSParticle iterator initialisation
  //For topology pi-:proton

  THSParticleIter* diter=CreateParticleIter(fTID_0,&fVecBeams,1);
  AddSelectToSelected(diter,1,1,&fPhoton);
  diter=CreateParticleIter(fTID_0,&fVecPiMs,1);
  AddSelectToSelected(diter,1,1,&fPim);
  diter=CreateParticleIter(fTID_0,&fVecProtons,1);
  AddSelectToSelected(diter,1,1,&fProton);
  


  //If create iterator must configure it
  fDetIter[fTID_0]->ConfigureIters();
}


//___________________________________________________________________________________________
//Define topology functions
void THSProj_PiMinusP::Topo_0(){
  //Reconstruct missing or combined particles

  //Dominik's Energy function (won't be as good due to charged pion energy recon)
  //  fNucleonLabEnergy = CalcQFThreeBodyRecoilPartT(fPhoton.P4.E(), fPim.P4(), fProton.P4(),massTarget,massProton,massNeutron);
  fCorrectedProtonEnergy = ProtonELossCorrection(fProton.P4p()->Theta(), fProton.P4p()->E());
  fMissNucleon = fPhoton.P4() + fFreeProton - fPim.P4();

}

void THSProj_PiMinusP::Kinematics(){
  if(!THSFinalState::fGoodEvent) return;//don't do calculations
  //Do calculations if Good Event
  if(fProton.P4p()->Phi()==0 && fProton.P4p()->Theta()==0){
    fDetErrs = -1;
  }
  else{
    fDetErrs = 0;
  }

  //  if(fNucleonLabEnergy<0){
  //    fDomFuncErrs = -1;
  //  }
  //  else{
  //    fDomFuncErrs = 0;
  //  }

  //Timing
  fTagTime = fPhoton.Time();
  fPimTime = fPim.Time();
  fProtonTime = fProton.Time();

  //Adjustment for jitter, common start and stop different in Taps vs Ball
  if( fProton.Detector()<8)  fProtonTagDiffTime = fProtonTime - fTagTime;
  if( fProton.Detector()>7)  fProtonTagDiffTime = fProtonTime - fTagTime;
  if( fPim.Detector()<8)  fPimTagDiffTime = fPimTime - fTagTime;
  if( fPim.Detector()>7)  fPimTagDiffTime = -fPimTime - fTagTime;



//Testing getting the mass of the pim set correctly
//  fPimMassB4 = fPim.M();
  fPim4VecB4 =fPim.P4();
  fPim.TakePDGMassFromE();
//  fPimMassAft = fPim.M();
  fPim4VecAft =fPim.P4();

//Decision to be made on which energy to take
  fProtonCalcEnergy = CalcQFThreeBodyRecoilPartT(fPhoton.P4.E(), fPim.P4(), fProton.P4(),massTarget,massProton,massProton); //Proton spectator for this channel
  fPimCalcEnergy = CalcQFThreeBodyRecoilPartT(fPhoton.P4.E(), fProton.P4(), fPim.P4(),massTarget,massProton,massProton); //Proton spectator for this channel


  //Apply Energy Corrections
  fNucleonRawEnergy = fProton.P4p()->E();

  fProton.P4p()->SetE(fCorrectedProtonEnergy + fProton.PDGMass() );
  if(fDetErrs==0) fProton.TakePDGMassFromE();

  //  if(std::isnan(fNucleonLabEnergy) ){
  //    fEnergyErrs = -1;
  //    fProton.P4p()->SetE(fProton.P4p()->E() + fProton->PDGMass() ); //Verify for neutron case!
  //  }
  //  else{
  //    fEnergyErrs = 0;	
  //    fProton.P4p()->SetE(fNucleonLabEnergy + fProton.PDGMass());
  //  }

  //  if(fDetErrs==0)  fProton.TakePDGMassFromE();   

  fNucleonEnergyFinal = fProton.P4p()->E();

  //Reconstruct missing or combined particles
  fPimRawEnergy = fPim.P4p()->E();
  fBeamEnergy = fPhoton.P4p()->E();
  fSpectator = fPhoton.P4() + fTarget - fProton.P4() - fPim.P4();
  fPimMassDiff = (TDatabasePDG::Instance()->GetParticle(-211)->Mass()) *1000 - fPim.P4p()->M();
  fMissP4 = fPhoton.P4() + fTarget - fProton.P4();  // now using corrected proton fPim.P4();
  fMissMass = fMissP4.M();
  fInvMass = fPim.P4p()->M();
  fSpecMass = fSpectator.M(); //Should be almost junk
  fSpecMom = fSpectator.Vect().Mag();
  fCoplanarity = ( fPim.P4().TLorentzVector::DeltaPhi( -(fProton.P4()) ) )*TMath::RadToDeg();
  fInitialN = fTarget - fSpectator;
  fConeAngle = fMissNucleon.Angle(fProton.P4().Vect());
  fConePhi = (fMissNucleon.TLorentzVector::DeltaPhi(fProton.P4() ) )*TMath::RadToDeg();



  //Tests of angular distributions
  fProtonPhi = fProton.P4().Phi();
  fProtonTheta = fProton.P4().Theta();
  fPimPhi = fPim.P4().Phi();
  fPimTheta = fPim.P4().Theta();
	  
  //Detector Tests
  fProtonDetector = fProton.Detector();
  fPimDetector = fPim.Detector();

  //Polarisation
  fTaggChannel = fPhoton.Detector();
  fPolState = fPhoton.EdgePlane();
  fPolVec = fPhoton.Vertex();
  fPol = fPolVec.X();
  fPolStateD = fPhoton.EdgePlane();
 // fPolStateD = 1; // For SIMS


  //Zero Polarisation
  if(fPol==0){
    fPolErrs = -1;
  }
  else{
    fPolErrs=0;
  }

  //Using Kinematics functions
  fKine.SetGammaTarget(fPhoton.P4(),fInitialN);
  fKine.SetMesonBaryon(fPim.P4(),fProton.P4());
  fKine.PhotoCMDecay();
  fCMPhi = (fKine.Phi())*TMath::RadToDeg();
  fCosth = fKine.CosTheta(); 
  fW = fKine.W();
  fProduc = fFreeProton + fPhoton.P4();
  fWII = fW - fProduc.M();


  if(fDetErrs==-1){     //No longer need energyerrs or dom   fDetErrs==-1 || fEnergyErrs==-1 || fDomFuncErrs==-1 ){
    fAnyErrs = -1;
  }
  else{
    fAnyErrs=0;
  }

//  cout << "Particle info Pim" <<  fPim.TruthP4().M() << "Particle info Photon" <<  fPhoton.TruthP4().M() << "Particle info Proton" <<  fProton.TruthP4().M() << endl;
// cout << "2article info Pim" <<  fPim.PDG() << "Particle info Photon" <<  fPhoton.PDG() << "Particle info Proton" <<  fProton.PDG() << endl;
// cout << "4article info Pim" <<  fPimGen.PDG() << "Particle info Photon" <<  fPhotonGen.PDG() << "Particle info Proton" <<  fPart.PDG() << "Paricle info Spectator" <<fSpec.PDG()<<  endl;
// cout << "5article info Pim" <<  fPim.ResTheta() << "Particle info Photon" <<  fPhoton.ResTheta() << "Particle info Proton" <<  fProton.ResTheta() <<  endl;
// cout << "6article info Pim" <<  fPim.ResPhi() << "Particle info Photon" <<  fPhoton.ResPhi() << "Particle info Proton" <<  fProton.ResPhi() <<  endl;


}

void THSProj_PiMinusP::FinalStateOutTree(TTree* tree){
  THSFinalState::fFinalTree=tree;
  //tree->Branch("Final",&fFinal);//If you want to save the final THSParticles
  tree->Branch("MissMass",&fMissMass,"MissMass/D");
  tree->Branch("Phi",&fCMPhi,"Phi/D");   //COM Phi angle of meson
  tree->Branch("Costh",&fCosth,"Costh/D");  //COM costheta angle of meson 
  tree->Branch("SpecMom",&fSpecMom,"SpecMom/D"); //Spectator mass
  tree->Branch("Coplanarity",&fCoplanarity,"Coplanarity/D"); //Coplanarity between pi0 and part. nucl.
  tree->Branch("BeamEnergy",&fBeamEnergy,"BeamEnergy/D");
  tree->Branch("W",&fW,"W/D");
  tree->Branch("InvMass",&fInvMass,"InvMass/D"); //Inv mass of meson
  tree->Branch("Pol",&fPol,"Pol/D"); //Polarisation mag. also has state encompassed
  tree->Branch("TaggChannel",&fTaggChannel,"TaggChannel/D"); //Tagger Channels
  tree->Branch("ConeAngle",&fConeAngle,"ConeAngle/D");
  tree->Branch("DetErrs",&fDetErrs,"DetErrs/D"); // Error indicator for NO CB or TAPS hit
  tree->Branch("PimTagDiffTime",&fPimTagDiffTime,"PimTagDiffTime/D");
  tree->Branch("AnyErrs",&fAnyErrs,"AnyErrs/D"); // Any Error given from the above three 
  tree->Branch("Correct",&fCorrect,"Correct/I");
  tree->Branch("DCorrect",&fDCorrect,"DCorrect/D"); //Does GenSim match TopoSim
  tree->Branch("SpecMass",&fSpecMass,"SpecMass/D"); //Spectator mass
  tree->Branch("WII",&fWII,"WII/D");


  tree->Branch("CorrectedProtonEnergy",&fCorrectedProtonEnergy,"CorrectedProtonEnergy/D");
  tree->Branch("TagTime",&fTagTime,"TagTime/D");
  tree->Branch("PimTime",&fPimTime,"PimTime/D");
  tree->Branch("ProtonTime",&fProtonTime,"ProtonTime/D");
  tree->Branch("ProtonTagTimeDiff",&fProtonTagDiffTime,"ProtonTagTimeDiff/D");
  tree->Branch("NucleonRawEnergy",&fNucleonRawEnergy,"NucleonRawEnergy/D");
  tree->Branch("NucleonEnergyFinal",&fNucleonEnergyFinal,"NucleonEnergyFinal/D");
  tree->Branch("PimRawEnergy",&fPimRawEnergy,"PimRawEnergy/D");
  tree->Branch("PimMassDiff",&fPimMassDiff,"PimMassDiff/D");
  tree->Branch("ConePhi",&fConePhi,"ConePhi/D");
  tree->Branch("ProtonPhi",&fProtonPhi,"ProtonPhi/D");
  tree->Branch("ProtonTheta",&fProtonTheta,"ProtonTheta/D");
  tree->Branch("PimPhi",&fPimPhi,"PimPhi/D");
  tree->Branch("PimTheta",&fPimTheta,"PimTheta/D");
  tree->Branch("ProtonDetector",&fProtonDetector,"ProtonDetector/D");
  tree->Branch("PimDetector",&fPimDetector,"PimDetector/D");

  tree->Branch("PolState",&fPolState,"PolState/I");
  tree->Branch("PolStateD",&fPolStateD,"PolStateD/D");
  tree->Branch("PolErrs",&fPolErrs,"PolErrs/D");

//Testing purposes only
//  tree->Branch("PimMassB4",&fPimMassB4,"PimMassB4/D");
//  tree->Branch("PimMassAft",&fPimMassAft,"PimMassAft/D");
  tree->Branch("Pim4VecAft",&fPim4VecAft);
  tree->Branch("Pim4VecB4",&fPim4VecB4);


}
Bool_t THSProj_PiMinusP::WorkOnEvent(){
  //Should this event be saved?
  THSFinalState::fGoodEvent=kTRUE;
  THSFinalState:: fCorrect=0; //Correct permutation? used for simulation only

  //If generated MC events
  if(THSFinalState::fIsGenerated) Init_Generated();
  else{//Look for reconstructed events
    //if reconstructed Find the detected particles in this event
    if(FindInclusiveTopology(-22)==-1) {fGoodEvent=kFALSE;return fIsPermutating0=kFALSE;}
    //    if(FindTopology()==-1) {fGoodEvent=kFALSE;return fIsPermutating0=kFALSE;}
    //Do they correspond to a defined topology?
    else if(fCurrTopo==fTID_0) Topo_0();
    // else if(fCurrTopo==fTID_) Topo_();
    else fGoodEvent=kFALSE;
    //Get truth values
    Init_Generated();
  }
  
  //Calc kinematics
  Kinematics();
  if(fPimTagDiffTime<-100 || fPimTagDiffTime>100){
    fGoodEvent=kFALSE;

  }
  //Check if assigned vectors agree with true generated
  //Simulation only
//  THSFinalState::CheckTruth();
  

//    fDCorrect = fCorrect -1; //For SIMS may be deprecated!
    fDCorrect = fCorrect; //For PROD 

  //Can do some checks if event is worth writing or not
  //if()fGoodEvent=kTRUE;
  //else() fGoodEvent =kFALSE;
  if(fIsGenerated) return kTRUE; //Generated only 1 permutation
  return kTRUE;
}
