
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
  TLorentzVector fBeam;
  TLorentzVector fTarget=TLorentzVector(0,0,0,1875.612);
  TLorentzVector fInitialN;
  THSParticle fPhoton = THSParticle(-22);
  //Final Particles
  THSParticle fPim=THSParticle("pi-"); //use PDG code?
  THSParticle fProton=THSParticle("proton");
  THSParticle fNeutron = THSParticle("neutron");
  //fGenerated Particles
  THSParticle fSpec;
  THSParticle fPart;
 
  //Observables
  Double_t f_t;
  Double_t f_Q2;
  Double_t f_W;
  Double_t f_Pol;
  Double_t fCMCosTh;
  Double_t fCMPhi;

  //Discriminators
  //Double_t fMissMass=0;
  Double_t fNucleonLabEnergy=-1;
  Double_t fCorrectedProtonEnergy;
  Double_t massTarget=1875.612;
  Double_t massProton=938.272; 
  Double_t massNeutron=939.575;
  Double_t fDetErrs;
  Double_t fDomFuncErrs;
  Double_t fTagTime;
  Double_t fPimTime;
  Double_t fProtonTime;
  Double_t fProtonTagDiffTime;
  Double_t fPimTagDiffTime;
  Double_t fNucleonRawEnergy;
  Double_t fEnergyErrs;
  Double_t fNucleonEnergyFinal;
  Double_t fPimRawEnergy;
  Double_t fBeamEnergy;
  Double_t fPimMassDiff;
  Double_t fMissMass;
  Double_t fInvMass;
  Double_t fSpecMass;
  Double_t fSpecMom;
  Double_t fCoplanarity;
  Double_t fConeAngle;
  Double_t fConePhi;
  Double_t fProtonPhi;
  Double_t fProtonTheta;
  Double_t fPimPhi;
  Double_t fPimTheta;
  Double_t fProtonDetector;
  Double_t fPimDetector;
  Double_t fTaggChannel;
  Int_t fPolState;
  Double_t fPol;
  Double_t fPolStateD;
  Double_t fPolErrs;
  Double_t fW;
  Double_t fCosth;
  Double_t fWII;
  Double_t fAnyErrs;
  Double_t fDCorrect;
  TLorentzVector fMissNucleon;
  TLorentzVector fFreeProton=TLorentzVector(0,0,0,938.272);
  TLorentzVector fSpectator;
  TLorentzVector fMissP4;
  TLorentzVector fProduc;
  TVector3 fPolVec; 

   public :
  virtual void FinalStateOutTree(TTree* tree);

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

#endif //ifdef THSProj_PiMinusP
