
#ifndef THSPROJ_PI0N_h
#define THSPROJ_PI0N_h

#include "THSFinalState.h"
#include "TLorentzVector.h"
#include <vector>

class THSProj_Pi0N : public THSFinalState{

 public :
  THSProj_Pi0N();
  ~THSProj_Pi0N(){};

  virtual Bool_t WorkOnEvent();

  //Init functions
  void Init_Iter0();
  void Init_Iter1();
  void Topo_0();
  void Topo_1();
  void Init_Generated();
  //void Init_IterX();
  //void Topo_X();

  void Kinematics();
  protected :
  //Topology flags for this project
  Int_t fTID_0=-1;
  Int_t fTID_1=-1;
  // Int_t fTID_=-1;
 
  //Initial state
  //TLorentzVector fBeam=TLorentzVector(0,0,10.6,10.6);
  TLorentzVector fBeam;//=THSParticle(22);
  TLorentzVector fTarget=TLorentzVector(0,0,0,1875.612);
  TLorentzVector fInitialN;
  //Final Particles
  THSParticle fPhoton=THSParticle(-22);
//  THSParticle fProton=THSParticle("proton");
  THSParticle fProton=THSParticle(2212);
  THSParticle fNeutron=THSParticle("neutron");  //Needed as neutron since Particles branch has no neutrons only photons but other channel has charge so prot is identified.
  THSParticle fPion=THSParticle("pi0");
  THSParticle fGamma1=THSParticle("gamma");
  THSParticle fGamma2=THSParticle("gamma");
//fGenerated Particles
  THSParticle fSpec; //=THSParticle(2122); //Neutron spectator
  THSParticle fPart; //=THSParticle(2212); //Proton participant


 
  //For Kinematics
  THSParticle *fNucleon=nullptr;

  //Observables
  Double_t f_t;
  Double_t f_Q2;
  Double_t f_W;
  Double_t f_Pol;
  Double_t fCMCosTh;
  Double_t fCMPhi;

  //Discriminators
  Double_t fMissMass=0;
  Double_t fMissMassPion=0; 
  Double_t fM2gamma=0;
  Double_t fInvMass=0;
  Double_t fSpecMass=0;
  Double_t fSpecMom=0;
  Double_t fTopologies=0;
  Double_t fCoplanarity=0;
  Double_t fConePhi=0;
  Double_t fConeAngle=0;
  Double_t fCosth=0;
  Double_t fW =0;
  Double_t fBeamEnergy=0;
  Double_t fTagTime=0;
  Double_t fPol=0;
  Double_t fPolStateD=0;
  Int_t fPolState=0;
  TVector3 fPolVec;
  Double_t fTaggChannel=0;
  Double_t fOpeningAngle;
  Double_t fOpeningPhi;
  Double_t fNucleonPhi;
  Double_t fNucleonTheta;
  Double_t fPi0Phi;
  Double_t fPi0Theta;
  Double_t fNucleonLabEnergy;
  Double_t fNucleonLabEnergyb4;
  Double_t fNucleonLabEnergyAft;
  Double_t fCorrectedProtonLabEnergyb4=0;
  Double_t fPionLabEnergy;
  Double_t fOpeningAngle2;
  Double_t fOpeningAngle3;
  Double_t fOpeningAngle4;
  Double_t fCMNucPhi;
  Double_t fCMNucCosTh;
  Double_t fEnergyErrs; 
  Double_t fDetErrs;
  Double_t fDomFuncErrs;
  Double_t fPolErrs;
  Double_t fAnyErrs;
  Double_t fGammaOneTime=0;
  Double_t fGammaTwoTime=0;
  Double_t fGammaDiffTime=0;
  Double_t fNucleonTime=0;
  Double_t fNucleonTagDiffTime=0;
  Double_t fGammaOneTagDiffTime=0;
  Double_t fGammaTwoTagDiffTime=0;
  Double_t fGammaAveTagDiffTime=0;
  Double_t fDetector=-1;
  Double_t fDCorrect;
  Double_t fWII;
  Double_t fPseudoVertexZ;
  Double_t fPseudoVertexX;
  Double_t fPseudoVertexY;

//For C_x and MWPC
  TVector3 fTargetVec;
  TVector3 fChamber1Vec;
  TVector3 fChamber2Vec;
  TVector3 fNucleonVec1;
  TVector3 fNucleonVec2;

  Double_t fNucleonScatAngleb4Trans;
  TVector3 fScatVec;
  Double_t fNucleonScatPhi;
  Double_t fNucleonScatTheta;
  Double_t fChamberErrs;


//Kinematics Issue so separate for each channel.
//  Double_t fCMPhiTopoNeut;
//  Double_t fCosthTopoNeut=0;
//  Double_t fWTopoNeut =0;
//  Double_t fOpeningAngle2TopoNeut;

//  Double_t fCMPhiTopoProt;
//  Double_t fCosthTopoProt=0;
//  Double_t fWTopoProt =0;
//  Double_t fOpeningAngle2TopoProt;


  //Additional 4-Vectors
  TLorentzVector fSpectator;
  TLorentzVector fMissP4;
  TLorentzVector fMissPionP4;
  TLorentzVector fNuclvec;
  TLorentzVector fPionvec;
  TLorentzVector fMissNucleon;
  TLorentzVector fFreeProton=TLorentzVector(0,0,0,938.272);
  TLorentzVector fFreeNeutron=TLorentzVector(0,0,0,939.565);

  //For QFEnergy function
  Double_t massProton=938.272;
  Double_t massNeutron=939.565;
  Double_t massTarget = 1875.612;  //LD2


   //Timing TAPS adjustment if both photons in TAPS
   Double_t fOffset=55;


//Junk
TLorentzVector InitialNucleon;
TLorentzVector AftMikNucleon;
  Double_t fDetectorGamma1;
  Double_t fDetectorGamma2; 
  Double_t fGamma1Phi;
  Double_t fGamma2Phi;
  Double_t fGamma1Theta; 
  Double_t fGamma2Theta;

//TO be Deleted
 TLorentzVector fPionP4;
 TLorentzVector fPhotonP4;
 TLorentzVector fProduc; 

   public :
  virtual void FinalStateOutTree(TTree* tree);

  //______________________________________________________________________________


TVector3 ScatteredVector(TVector3 v_inc,TVector3 v_sc){
  TVector3 XLAB(1,0,0);
  TVector3 YLAB(0,1,0);
  TVector3 ZLAB(0,0,1);

  //Define primed frame
  TVector3 Zprime=v_inc.Unit();//Nucleon momentum direction
  TVector3 Yprime=ZLAB.Cross(-v_inc);//BeamXpi momentum or protonXbeam
  Yprime=Yprime.Unit();
  TVector3 Xprime=Yprime.Cross(Zprime);
  Xprime=Xprime.Unit();

   //Make rotation matrix
  Double_t Drot[3][3];
  Drot[0][0]=XLAB.Dot(Xprime);Drot[1][0]=YLAB.Dot(Xprime);Drot[2][0]=ZLAB.Dot(Xprime);
  Drot[0][1]=XLAB.Dot(Yprime);Drot[1][1]=YLAB.Dot(Yprime);Drot[2][1]=ZLAB.Dot(Yprime);
  Drot[0][2]=XLAB.Dot(Zprime);Drot[1][2]=YLAB.Dot(Zprime);Drot[2][2]=ZLAB.Dot(Zprime);
  //Calculate new coordinates
  TVector3 v_scat; 
  v_scat.SetX(Drot[0][0]*v_sc.X()+Drot[1][0]*v_sc.Y()+Drot[2][0]*v_sc.Z());
  v_scat.SetY(Drot[0][1]*v_sc.X()+Drot[1][1]*v_sc.Y()+Drot[2][1]*v_sc.Z());
  v_scat.SetZ(Drot[0][2]*v_sc.X()+Drot[1][2]*v_sc.Y()+Drot[2][2]*v_sc.Z());
  return v_scat;

}



  //______________________________________________________________________________
  Double_t ProtonELossCorrection(Double_t ProtTheta, Double_t NaIDeposit)
  {
    //Mikhails proton energy correction for the polarimeter Mainz beamtime of Aug 16
    // Returns kinetic energy of proton from the deposit in the sodium iodide and proton theta angle(in radians?)  (test case of theta=90deg or pi/2 rads gives no change in Ekin)

    Double_t E_kin=NaIDeposit+(201.915-57.9314*sin(ProtTheta))*(exp((-0.000800067-0.00451967*sin(ProtTheta))*NaIDeposit))+(-82.3023+23.2409*sin(ProtTheta));

    return (E_kin);

  }


  //______________________________________________________________________________
  Double_t CalcQFThreeBodyRecoilPartT(Double_t beamE, TLorentzVector p4Meson, TLorentzVector p4Part,
				      Double_t mTarg, Double_t mPart, Double_t mSpec)
  {
    // Calculate the kinetic energy of the recoil participant with mass 'mPart'
    // in meson photoproduction off a target with mass 'mTarg' with beam energy
    // 'beamE' in a quasi-free three-body-decay:
    //
    // gamma + Target(Participant + Spectator) -> Participant + Spectator + Meson
    //
    // Use the reconstructed theta and phi angles in the 4-vector of the
    // participant 'p4Part' and the fully reconstructed 4-vector
    // of the meson 'p4Meson' to calculate the kinetic energy of the recoil
    // participant. The spectator mass is 'mSpec'.

    // set input kinematics variables
    Double_t mesonPx = p4Meson.Px();
    Double_t mesonPy = p4Meson.Py();
    Double_t mesonPz = p4Meson.Pz();
    Double_t mesonE  = p4Meson.E();

    Double_t partTheta = p4Part.Theta();
    Double_t partPhi   = p4Part.Phi();

    // calculate terms
    Double_t a = mesonE - beamE - mTarg;
    Double_t b = (mesonE + mPart - beamE - mTarg) * (mesonE + mPart - beamE - mTarg)
      - mSpec * mSpec
      - mesonPx * mesonPx
      - mesonPy * mesonPy
      - mesonPz * mesonPz
      - beamE * beamE
      + 2 * beamE * mesonPz;
    Double_t c =   mesonPx * TMath::Sin(partTheta) * TMath::Cos(partPhi)
      + mesonPy * TMath::Sin(partTheta) * TMath::Sin(partPhi)
      + (mesonPz - beamE ) * TMath::Cos(partTheta);

    Double_t quadEquA = a*a - c*c;
    Double_t quadEquB = a*b - 2*c*c*mPart;
    Double_t quadEquC = b*b / 4;

    return (-quadEquB + TMath::Sqrt(quadEquB*quadEquB - 4*quadEquA*quadEquC)) / (2*quadEquA);
  }





};

#endif //ifdef THSProj_Pi0N
