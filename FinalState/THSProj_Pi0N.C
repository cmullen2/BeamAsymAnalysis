/**
 * \class THSProj_Pi0N
 * 
 * Template final class .
 * 
 * Users should create their own analysis specific project classes.
 * 
 */



#include "TDatabasePDG.h"
#include "THSProj_Pi0N.h"
#include <algorithm>


THSProj_Pi0N::THSProj_Pi0N(){
  //SetUseChargePID();//If want to only use charge for IDing
  //include topology for analysis and get index
  fTID_0=AddTopology("proton:gamma:gamma");
  fTID_1=AddTopology("gamma:gamma:gamma");
 
  //Set final state
  fFinal.push_back(&fPhoton);
  fFinal.push_back(&fProton);

//  fFinal.push_back(&fNeutron);  //Is this needed for the fGen stuff for the truth values to expect a correct final state and produce correct correlations
  //fFinal.push_back(&fPion);
  fFinal.push_back(&fGamma1);
  fFinal.push_back(&fGamma2);

  //Initialise particle iters
  fDetIter.resize(fNTopo);
  Init_Iter0();
  Init_Iter1();
}


void THSProj_Pi0N::Init_Generated(){
  return; //THIS LINE IS NEEDED FOR NON SIMULATION DATA
  if(!THSFinalState::frGenParts) return;
  if(THSFinalState::frGenParts->size()!=5) {fGoodEvent=kFALSE;return;}
  //Fill our data member particles
  //User is responsible for indicing right
  //comes from order in generated file (e.g LUND)
  if(THSFinalState::fIsGenerated){
    //fElectron=*frGenParts->at(0);

    //two ball photons, spectator and participant, will only be parti. proton for one file, photon is tag. Ordering is crucial see input file for it. Order so far is Spec(neut), Part(prot),gamma,gamma,beam

    fSpec=*frGenParts->at(0);
    fPart=*frGenParts->at(1);
    fGamma1=*frGenParts->at(2);
    fGamma2=*frGenParts->at(3);
    fPhoton=*frGenParts->at(4);


    // fInitialN=fTarget-fSpec.P4(); Don't want to form a different one from the prod data, this will be done with truth. Just use the other 4 particles to do it.
    //fPion.Add(&fGamma1,&fGamma2,111);
    fPion.SetP4(fGamma1.P4() + fGamma2.P4()); 
    fPion.SetTime((fGamma1.Time() + fGamma2.Time())/2);
    fNucleon= &fPart;




  }
  else{//Just assign truth values
    //fElectron.SetTruth(frGenParts->at(0));

    //Sets the truth values using the p4 of the particle etc.
    fSpec.SetTruth(frGenParts->at(0));
    fPart.SetTruth(frGenParts->at(1));
    fProton.SetTruth(frGenParts->at(1));  //Proton Channel only, what do I do for neutron channel?
//    fNeutron.SetTruth(frGenParts->at(1)); //Neutron Channel?
    fGamma1.SetTruth(frGenParts->at(2));
    fGamma2.SetTruth(frGenParts->at(3));
    fPhoton.SetTruth(frGenParts->at(4));




  }
}

//Define topology Iterator functions
void THSProj_Pi0N::Init_Iter0(){
  //THSParticle iterator initialisation
  THSParticleIter* diter=CreateParticleIter(fTID_0,&fVecBeams,1);
  AddSelectToSelected(diter,1,1,&fPhoton);
  diter=CreateParticleIter(fTID_0,&fVecGams,2);
  //  AddSelectToSelected(diter,2,1,&fGamma1,&fGamma2);
  AddSelectToSelected(diter,1,2,&fGamma1,&fGamma2);
  diter=CreateParticleIter(fTID_0,&fVecProtons,1);
  AddSelectToSelected(diter,1,1,&fProton);

  //If create iterator must configure it
  fDetIter[fTID_0]->ConfigureIters();
}
void THSProj_Pi0N::Init_Iter1(){
  //THSParticle iterator initialisation
  THSParticleIter* diter=CreateParticleIter(fTID_1,&fVecBeams,1);
  AddSelectToSelected(diter,1,1,&fPhoton);
  diter=CreateParticleIter(fTID_1,&fVecGams,3);
  //  THSParticleIter* pi0diter=AddSelectToSelected(diter,2,1,&fGamma1,&fGamma2);
  THSParticleIter* pi0diter=AddSelectToSelected(diter,1,2,&fGamma1,&fGamma2);
  AddSelectToRemainder(pi0diter,1,1,&fNeutron);

  //If create iterator must configure it
  fDetIter[fTID_1]->ConfigureIters();
}
// void THSProj_Pi0N::Init_IterX(){
//  THSParticleIter* diter=CreateParticleIter(fTID_X,&fVecY,NPARTICLES);
//  ...
//  fDetIter[fTID_0]->ConfigureIters();
// }
//Or if iterator the same as a previous one
// void THSProj_Pi0N::Init_IterY(){
//   fDetIter[fTID_1]=fDetIter[fTID_0];
// }
//Define topology functions


//______________________________________________________________________________
void THSProj_Pi0N::Topo_0(){

  //fPhoton is Tagged photon, fProton is proton and fGamma1,2 is the two photons of pi0.
  //pdgcode is 111, pi+ is 211, pi-????? This sets p4, pdg, time measmass(i.e. deposited energy) and the mass to the pdg mass(.M() is now pdg mass) Also sets the vertex based on some closest approach function  and if truth available  will do the same for truth.

  fTopologies=1; //Proton Channel
  // fPion.Add(&fGamma1,&fGamma2,111);
  fPion.SetP4(fGamma1.P4() + fGamma2.P4());
  fPion.SetTime((fGamma1.Time() + fGamma2.Time() )/2 );

  InitialNucleon.SetPxPyPzE(fProton.P4p()->Px(),fProton.P4p()->Py(),fProton.P4p()->Pz(),fProton.P4p()->E());

  // Mikhails energy correction function
  fCorrectedProtonLabEnergyb4 = ProtonELossCorrection(fProton.P4p()->Theta(), fProton.P4p()->E());
  //  fProton.P4p()->SetE(fCorrectedProtonLabEnergyb4);

  AftMikNucleon.SetPxPyPzE(fProton.P4p()->Px(),fProton.P4p()->Py(),fProton.P4p()->Pz(),fProton.P4p()->E());


  fMissNucleon=fPhoton.P4() + fFreeProton - fPion.P4();

  //Dominik's function
  fNucleonLabEnergy = CalcQFThreeBodyRecoilPartT(fPhoton.P4().E(), fPion.P4(), fProton.P4(), massTarget, massProton,massNeutron);
 
  //Set up a generic nucleon variable to be used in kinematics
  fNucleon = &fProton;

}

//______________________________________________________________________________
void THSProj_Pi0N::Topo_1(){
  
  fTopologies=-1; //Neutron Channel
  // fPion.Add(&fGamma1,&fGamma2,111);
  fPion.SetP4(fGamma1.P4() + fGamma2.P4());
  fPion.SetTime((fGamma1.Time() + fGamma2.Time() )/2 );

  //A dummy representative of Mikhail's energy correction.(kinetic energy of the neutron)
  fCorrectedProtonLabEnergyb4 =fNeutron.P4p()->E(); //If used to setE then have this as neutron.GetE etc.
  

  fMissNucleon=fPhoton.P4() + fFreeNeutron - fPion.P4();


  //Dominik's function
  fNucleonLabEnergy = CalcQFThreeBodyRecoilPartT(fPhoton.P4().E(), fPion.P4(), fNeutron.P4(), massTarget, massNeutron,massProton);
 
  //Set up a generic nucleon variable to be used in kinematics
  fNeutron.SetPDGcode(2112);
  fNucleon = &fNeutron;
}

//______________________________________________________________________________
void THSProj_Pi0N::Kinematics(){
  if(!THSFinalState::fGoodEvent) return;//don't do calculations
  //Do calculations if Good Event

  //  Test for ball or taps hit Make this a detector based selection
  if(fNucleon->P4p()->Phi()==0 && fNucleon->P4p()->Theta()==0){
    fDetErrs= -1;
  }
  else{
    fDetErrs=0;
  }
  

  if(fNucleonLabEnergy<0){
    fDomFuncErrs=-1;
  }
  else{
    fDomFuncErrs=0;
  }


  // Timing
  fTagTime=fPhoton.Time();
  fGammaOneTime=fGamma1.Time();
  fGammaTwoTime=fGamma2.Time();
  fNucleonTime=fNucleon->Time();
  fNucleonTagDiffTime = fNucleonTime - fTagTime;

  //Adjustment for jitter, common start/stop
  if(  fGamma1.Detector()<8 && fGamma2.Detector()<8)fGammaAveTagDiffTime= fPion.Time() - fTagTime;
  if(  fGamma1.Detector()>7 && fGamma2.Detector()>7)fGammaAveTagDiffTime= -fPion.Time() - fTagTime;
  if(  fGamma1.Detector()>7 && fGamma2.Detector()<8)fGammaAveTagDiffTime= -fGamma1.Time() - fTagTime;
  if(  fGamma1.Detector()<8 && fGamma2.Detector()>7)fGammaAveTagDiffTime= -fGamma2.Time() - fTagTime;

  //Needs adjustment for jitter, common start/stop
  //  if(  fGamma1.Detector()>7 || fGamma2.Detector()>7){ //if one in TAPs
  //    if(fGamma1.Detector()<8){//if Gam1 in CB
  //      fGammaAveTagDiffTime= fGamma1.Time() - fTagTime;
  //    } 
  //    else if(fGamma2.Detector()<8){ //if Gam2 in CB
  //      fGammaAveTagDiffTime= fGamma2.Time() - fTagTime;
  //    }
  //    else{ //if both in TAPS
  //      fGammaAveTagDiffTime=  fGammaAveTagDiffTime- fOffset;
  //    }
  // }




  //Applying an Energy correction, either Doms or Mikhails.

  fNucleonLabEnergyb4 = fNucleon->P4p()->E();

  if(std::isnan(fNucleonLabEnergy) ){
    fEnergyErrs =  -1;
    fNucleon->P4p()->SetE(fNucleon->P4p()->E()+fNucleon->PDGMass());  //Not sure if 1000 needed see if still in GeV.
    //  if(fNucleon->P4p()->E()<0) cout <<" Negatives  " << fNucleon->P4p()->E()   << endl;
  }
  else{
    fEnergyErrs = 0;
    fNucleon->P4p()->SetE(fNucleonLabEnergy + fNucleon->PDGMass() ); //issue with phi due to this.
    //  fNucleon->P4p()->SetE(fNucleonLabEnergy); 
    // if(fNucleon->P4p()->E()<0) cout <<" Negatives  " << fNucleon->P4p()->E()   << "Lab E " << fNucleonLabEnergy << " PDG MASS " << fNucleon->PDGMass() <<" Topo  " << fTopologies  <<endl;
  }

  //if(fNucleon->P4p()->E()<0) cout <<" Negatives  " << fNucleon->P4p()->E()   << endl;

  TLorentzVector AftDomNucleon;
  AftDomNucleon.SetPxPyPzE(fProton.P4p()->Px(),fProton.P4p()->Py(),fProton.P4p()->Pz(),fProton.P4p()->E());


  TLorentzVector AftPDGNucleon;
  AftPDGNucleon.SetPxPyPzE(fProton.P4p()->Px(),fProton.P4p()->Py(),fProton.P4p()->Pz(),fProton.P4p()->E());

  if(fDetErrs==0) fNucleon->TakePDGMassFromE(); //Hits with no cb or taps will cause vector stretch error if not dealt with by fDetErrs

  //  fNucleon->TakePDGMassFromE(); //Tvector3 vector can't be stretched error here on this line. sqrt(E^2 - M^2) so E=M or E<M? Due to not adding PDG mass on ,Removed for testing purposes for a minute. NEUTRON CASE
  fNucleonLabEnergyAft = fNucleon->P4p()->E();



  //Reconstruct missing or combined particles
  fPionLabEnergy=fPion.P4p()->E();
  fBeamEnergy=fPhoton.P4p()->E();
  fSpectator=fPhoton.P4() +  fTarget - fNucleon->P4() -fPion.P4(); //Is this correct????
  fM2gamma= (TDatabasePDG::Instance()->GetParticle(111)->Mass())*1000  - fPion.P4p()->M(); //in MeV now //MassDiff(); //Need to convert to MeV the pdg mass
  fMissP4=fPhoton.P4() + fTarget - fPion.P4();
  fMissMass=fMissP4.M();
  fMissPionP4 = fPhoton.P4() +fTarget -fNucleon->P4();
  fMissMassPion = fMissPionP4.M();
  fInvMass=fPion.P4p()->M();   //MeasMass();

  fSpecMass=fSpectator.M();


  fSpecMom=fSpectator.Vect().Mag();
  fCoplanarity=( fPion.P4().TLorentzVector::DeltaPhi(  -(fNucleon->P4()) )  )*TMath::RadToDeg();
  fInitialN=fTarget- fSpectator;
  fConeAngle=fMissNucleon.Angle(fNucleon->P4().Vect());
  fConePhi=(fMissNucleon.TLorentzVector::DeltaPhi(fNucleon->P4()) )*TMath::RadToDeg();


  //Tests of angular distribution

  fNucleonPhi=fNucleon->P4().Phi() ; 
  fNucleonTheta=fNucleon->P4().Theta();
  fPi0Phi=fPion.P4().Phi();
  fPi0Theta=fPion.P4().Theta();


  fDetectorGamma1 = fGamma1.Detector();
  fDetectorGamma2 = fGamma2.Detector();
  fGamma1Phi = fGamma1.P4().Phi();
  fGamma2Phi = fGamma2.P4().Phi();
  fGamma1Theta = fGamma1.P4().Theta();
  fGamma2Theta = fGamma2.P4().Theta();



  //Polarisation
  fTaggChannel = fPhoton.Detector();
  fPolState=fPhoton.EdgePlane();
  fPolVec=fPhoton.Vertex();
  fPol=fPolVec.X();   //Edge plane =1,-1,0  describes Para,Perp or Moeller( not necess in that order)
 

//  if (fPolState==1)fPol=fPolVec.X();
//  if (fPolState==-1)fPol=fPolVec.Y();




//cout << fPolState << "Pol State and vector X and Y "<< fPolVec.X() <<"   " << fPolVec.Y() <<" fPol  "<< fPol <<endl;
//if(fPolState==-1)fPol=fPol*-1;  //A correction to previoulsy incorrect Goat code!! 
//cout << fPolState << "Pol State and vector X and Y "<< fPolVec.X() <<"   " << fPolVec.Y() <<"  fPol " << fPol <<endl;


//Double for Fitting in Roofit as a binvar
fPolStateD = fPhoton.EdgePlane();// FOR PROD DATA
//fPolStateD = -1; // For  Sim Data so that have both polarisation for binning for fitting  (Need to rerun for +1) DO the same for polstate
//fPolState = -1; //SIMS


  //Zero Polarisation 
  if (fPol==0){
	fPolErrs=-1; 
}
else{
	fPolErrs=0;

}



  //Detectors used for each particle
  fDetector = fNucleon->Detector();


  fPionP4 = fPion.P4();
  fPhotonP4 = fPhoton.P4();


  //  fKine.SetGammaTarget((&fPhoton)->P4(),fInitialN);
  fKine.SetGammaTarget(fPhoton.P4(),fInitialN);
  fKine.SetMesonBaryon(fPion.P4(),fNucleon->P4());
  fKine.PhotoCMDecay();
  fCMPhi=(fKine.Phi())*TMath::RadToDeg() ;
  fCosth=fKine.CosTheta(); 
  fW = fKine.W();//Commented out only as a test so far

  fOpeningAngle2 =( TMath::ACos(fCosth) -    (fNucleon->P4().Theta() )  ) ;



//Attempting to get W correct

  fProduc=fFreeProton + fPhoton.P4() ;
  fWII =fW - fProduc.M() ;
  
//PseudoVertex information
  fPseudoVertexZ = fNucleon->PseudoVertex().Z();
  fPseudoVertexX = fNucleon->PseudoVertex().X();
  fPseudoVertexY = fNucleon->PseudoVertex().Y();
 


/*
//MWPC hits and Cx analysis first attempt
  fChamber1Vec.SetXYZ(fNucleon->MWPC0Hits.X(),fNucleon->MWPC0Hits.Y(),fNucleon->MWPC0Hits.Z()); //Vector of tvector3's so need to loop something here
  fChamber2Vec.SetXYZ(fNucleon->MWPC1Hits.X(),fNucleon->MWPC1Hits.Y(),fNucleon->MWPC1Hits.Z());

  if( fChamber1Vec.X()==0 && fChamber2Vec.X()==0 && fChamber1Vec.Y()==0 && fChamber2Vec.Y()==0 && fChamber1Vec.Z==0 && fChamber2Vec.Z==0){
    fChamberErrs=-1;

  }

  else{
  fChamberErrs=0;

  }

//No rotation of MWPC0 yet needs to be determined by the phi of mwpcs from earlier in analysis.
//Add these to and errs to output then add function to .h

  fNucleonVec1 =  fChamber1Vec - fTargetVec ;
  fNucleonVec2 =  fChamber2Vec - fChamber1Vec;
 
  fNucleonScatAngleb4Trans = (fNucleonVec1.Angle(fNucleonVec2))*TMath::RadToDeg();
  fScatVec = ScatteredVector(fNucleonVec1,fNucleonVec2);
  fNucleonScatPhi = fScatVec.Phi()*TMath::RadToDeg();
  fNucleonScatTheta = fScatVec.Theta()*TMath::RadToDeg() ;

*/




  if(std::isnan(fCoplanarity)){
  //  cout << fCoplanarity << " coplan " <<fCMPhi <<" phi " << " Costh " <<  fCosth << endl;// " UID " << UID <<endl;
    fCoplanarity=0;
  }


  if(std::isnan(fCMPhi)){
    //cout << fCoplanarity << " coplan " <<fCMPhi <<" phi " << " Costh " <<  fCosth <<" DetErrs " <<fDetErrs << " EnergyErrs " <<fEnergyErrs<< " Cone Angle " << fConeAngle <<"  "  << endl;// " UID " << UID <<endl;
    
  }
  if(TMath::IsNaN(fCMPhi)){
    //cout << "Inside the TMath version " << endl;
    //cout << "Beam Energy " <<fBeamEnergy << " Detector of Nucleon " << fDetector   <<" nucleon lab energy before "<< fNucleonLabEnergyb4 <<" after " << fNucleonLabEnergyAft  << endl;
  }

  if(fDetErrs==-1 || fEnergyErrs==-1 || fDomFuncErrs==-1  ){
    fAnyErrs=-1;
  }
  else{
    fAnyErrs=0;
  }


}

void THSProj_Pi0N::FinalStateOutTree(TTree* tree){


  /*  if(std::isnan(fCoplanarity)){
      cout << fCoplanarity << " coplan " <<fCMPhi <<" phi " << " Costh " <<  fCosth << endl;// " UID " << UID <<endl;
      fCoplanarity=0;
      }


      if(std::isnan(fCMPhi)){
      cout << fCoplanarity << " coplan " <<fCMPhi <<" phi " << " Costh " <<  fCosth <<" DetErrs " <<fDetErrs << " EnergyErrs " <<fEnergyErrs<< " Cone Angle " << fConeAngle <<"  "  << endl;// " UID " << UID <<endl;
    
      }
      if(TMath::IsNaN(fCMPhi)){
      cout << "Inside the TMath version " << endl;

      }*/


  THSFinalState::fFinalTree=tree;
  //tree->Branch("Final",&fFinal);

  //Needed For Fitting
  tree->Branch("Topo",&fTopologies,"Topo/D");//Two topologies proton particapant and neutron part,pi0 
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
  tree->Branch("EnergyErrs",&fEnergyErrs,"EnergyErrs/D");  // Error indicator for Dom's func.
  tree->Branch("DetErrs",&fDetErrs,"DetErrs/D"); // Error indicator for NO CB or TAPS hit
  tree->Branch("GammaAveTagDiffTime",&fGammaAveTagDiffTime,"GammaAveTagDiffTime/D"); 
  tree->Branch("DomFuncErrs",&fDomFuncErrs,"DomFuncErrs/D"); // Negative Energy from Doms Function indicator 
  tree->Branch("AnyErrs",&fAnyErrs,"AnyErrs/D"); // Any Error given from the above three 
  tree->Branch("MissMass",&fMissMass,"MissMass/D"); //Missing Mass of Participant
  tree->Branch("Correct",&fCorrect,"Correct/I"); 
  tree->Branch("DCorrect",&fDCorrect,"DCorrect/D"); //Does GenSim match TopoSim
  tree->Branch("SpecMass",&fSpecMass,"SpecMass/D"); //Spectator mass
  tree->Branch("WII",&fWII,"WII/D"); 
  tree->Branch("PseudoVertexZ",&fPseudoVertexZ,"PseudoVertexZ/D"); 
  tree->Branch("PseudoVertexX",&fPseudoVertexX,"PseudoVertexX/D"); 
  tree->Branch("PseudoVertexY",&fPseudoVertexY,"PseudoVertexY/D"); 

/*  //C_x Stuff
  tree->Branch("ChamberErrs",&fChamberErrs,"ChamberErrs/D"); 
  tree->Branch("NucleonScatAngleb4Trans",&fNucleonScatAngleb4Trans,"NucleonScatAngleb4Trans/D"); 
  tree->Branch("NucleonScatPhi",&fNucleonScatPhi,"NucleonScatPhi/D"); 
  tree->Branch("NucleonScatTheta",&fNucleonScatTheta,"NucleonScatTheta/D"); 
*/

  //Not Needed for Fitting yet
  //  tree->Branch("M2gamma",&fM2gamma,"M2gamma/D");  
  //  tree->Branch("MissNucleon",&fMissNucleon,"MissNucleon/D"); //Spectator mass
//  tree->Branch("Detector",&fDetector,"Detector/D"); //Detector hit by participant, NaI etc. see Goat for code conv. 
  //  tree->Branch("TagTime",&fTagTime,"TagTime/D"); //Tagger Time //Test Case
    tree->Branch("PolState",&fPolState,"PolState/I"); //PolState +-1 or 0 ,Perp Para moeller
    tree->Branch("PolStateD",&fPolStateD,"PolStateD/D"); //PolState +-1 or 0 ,Perp Para moeller
    tree->Branch("PolErrs",&fPolErrs,"PolErrs/D"); // Any Error given from the above three 
  //  tree->Branch("NucleonLabEnergy",&fNucleonLabEnergy,"NucleonLabEnergy/D"); //E from Dom's func.
  //  tree->Branch("NucleonLabEnergyb4",&fNucleonLabEnergyb4,"NucleonLabEnergyb4/D"); //E from before Dom's func.
  //  tree->Branch("NucleonLabEnergyAft",&fNucleonLabEnergyAft,"NucleonLabEnergyAft/D"); //E from after Dom's func.
  //  tree->Branch("CorrectedProtonLabEnergyb4",&fCorrectedProtonLabEnergyb4,"CorrectedProtonLabEnergyb4/D");
  //  tree->Branch("PionLabEnergy",&fPionLabEnergy,"PionLabEnergy/D"); //E from Dom's func.
  //  tree->Branch("NucleonPhi",&fNucleonPhi,"NucleonPhi/D");
  //  tree->Branch("NucleonTheta",&fNucleonTheta,"NucleonTheta/D");
  //  tree->Branch("Pi0Phi",&fPi0Phi,"Pi0Phi/D");
  //  tree->Branch("Pi0Theta",&fPi0Theta,"Pi0Theta/D");
  //  tree->Branch("OpeningAngle2",&fOpeningAngle2,"OpeningAngle2/D");
  //  tree->Branch("ConePhi",&fConePhi,"ConePhi/D");
  //  tree->Branch("GammaOneTime",&fGammaOneTime,"GammaOneTime/D"); 
  //  tree->Branch("GammaTwoTime",&fGammaTwoTime,"GammaTwoTime/D"); 
  //  tree->Branch("NucleonTime",&fNucleonTime,"NucleonTime/D"); 
  //  tree->Branch("NucleonTagDiffTime",&fNucleonTagDiffTime,"NucleonTagDiffTime/D"); 
//  tree->Branch("Gamma1Detector",&fDetectorGamma1,"Gamma1Detector/D"); 
//  tree->Branch("Gamma2Detector",&fDetectorGamma2,"Gamma2Detector/D"); 
  //  tree->Branch("Gamma1Phi",&fGamma1Phi,"Gamma1Phi/D"); 
  //  tree->Branch("Gamma2Phi",&fGamma2Phi,"Gamma2Phi/D"); 
  //  tree->Branch("Gamma1Theta",&fGamma1Theta,"Gamma1Theta/D"); 
  //  tree->Branch("Gamma2Theta",&fGamma2Theta,"Gamma2Theta/D"); 


//  tree->Branch("InitialN",&fInitialN); 
//  tree->Branch("Photon",&fPhotonP4); 
//  tree->Branch("Pion",&fPionP4); 
//  tree->Branch("Nucleon",&fNucleon); 
//  tree->Branch("Produc",&fProduc); 

}
Bool_t THSProj_Pi0N::WorkOnEvent(){
  //Should this event be saved?
  THSFinalState::fGoodEvent=kTRUE;
  THSFinalState:: fCorrect=0; //Correct permutation? used for simulation only
  //If generated MC events
  if(THSFinalState::fIsGenerated) Init_Generated();
  else{//Look for reconstructed events
    //if reconstructed Find the detected particles in this event
    //    if(FindInclusiveTopology()==-1) {fGoodEvent=kFALSE;return fIsPermutating0=kFALSE;}
    //if(FindTopology()==-1) {fGoodEvent=kFALSE;return fIsPermutating0=kFALSE;}
    if(FindInclusiveTopology(-22)==-1){fGoodEvent=kFALSE;return fIsPermutating0=kFALSE;} 

    //Do they correspond to a defined topology?
    else if(fCurrTopo==fTID_0) Topo_0();
    else if(fCurrTopo==fTID_1) Topo_1();
    // else if(fCurrTopo==fTID_) Topo_();
    else fGoodEvent=kFALSE;
    //Get truth values
    Init_Generated();
  }

  //cout<<"MAsses"<<fPhoton.TruthP4().M()<<"  " << fProton.TruthP4().M()<< "  " <<fPhoton.TruthP4().Rho() << " " <<fProton.TruthP4().Rho() <<" " <<fPhoton.ResRho()<<"  "<< fProton.ResRho()<< "Proton Rho Res "  <<endl;

  //Calc kinematics
  Kinematics();
if(fGammaAveTagDiffTime<-100 || fGammaAveTagDiffTime>100){
fGoodEvent=kFALSE;

}
//if(fPseudoVertexZ<0 || fPseudoVertexZ>80){
//fGoodEvent=kFALSE;

//}
  
  //Check if assigned vectors agree with true generated
  //Simulation only
//  THSFinalState::CheckTruth();
  //SIMS NEXT TWO LINES NEEDED BUT CRASH DATA FILES
  fGamma1.SetTruth(frGenParts->at(3));
  fGamma2.SetTruth(frGenParts->at(2));  

//  THSFinalState::CheckTruth();


  //For Sims Temporary fix!
//  fDCorrect=fCorrect -1;
  //For Prod, Emp (Fix this at some stage! Needed so that they give the same value for cuts during fitting)
  fDCorrect=fCorrect;

  //Can do some checks if event is worth writing or not
  //if()fGoodEvent=kTRUE;
  //else() fGoodEvent =kFALSE;
  if(fIsGenerated) return kTRUE; //Generated only 1 permutation
  return kTRUE;

  //THSFinalState::PermutateParticles();
  //if(IsPermutating()) return kTRUE;
  //else return kFALSE;
}
