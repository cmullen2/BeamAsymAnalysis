//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Mar 18 11:57:51 2018 by ROOT version 6.08/06
// from TTree HSParticles/Event selection tree
// found on file: /w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/ChrisOutput/Perp/Physics_CBTaggTAPS_14975.root
//////////////////////////////////////////////////////////

#ifndef PimP_h
#define PimP_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "THSOutput.h"
#include "THSProj_PiMinusP.h"

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "TLorentzVector.h"
#include "TObject.h"
#include "TVector3.h"

class PimP : public TSelector, public THSOutput, public THSProj_PiMinusP {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

  //data members for new branches
   //you must define how they are processed for each event and set to 0 in constructor
   //e.g.   TLorentzVector  *fp1;
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<THSParticle*> *Particles;
   vector<THSParticle*> *Generated;
/*   Int_t           Topo;
 //TLorentzVector  *crystalPhoton;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Double_t        crystalPhotonmass;
   Double_t        crystalPhotonphi;
   Double_t        crystalPhotontheta;
   Double_t        crystalPhotonpidE;
   Double_t        crystalPhotonMWPC0E;
   Double_t        crystalPhotonMWPC1E;
 //TLorentzVector  *crystalRootino;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Double_t        crystalRootinomass;
   Double_t        crystalRootinophi;
   Double_t        crystalRootinotheta;
   Double_t        crystalRootinopidE;
   Double_t        crystalRootinoMWPC0E;
   Double_t        crystalRootinoMWPC1E;
 //TLorentzVector  *crystalRootinoIn;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Double_t        crystalRootinomassIn;
   Double_t        crystalRootinophiIn;
   Double_t        crystalRootinothetaIn;
   Double_t        crystalRootinopidEIn;
   Double_t        crystalRootinoMWPC0EIn;
   Double_t        crystalRootinoMWPC1EIn;
   Double_t        crystalCoplan;
 //TLorentzVector  *crystalRootino1;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Double_t        crystalRootinomass1;
   Double_t        crystalRootinophi1;
   Double_t        crystalRootinotheta1;
   Double_t        crystalRootinopidE1;
   Double_t        crystalRootinoMWPC0E1;
   Double_t        crystalRootinoMWPC1E1;
 //TLorentzVector  *crystalRootino2;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Double_t        crystalRootinomass2;
   Double_t        crystalRootinophi2;
   Double_t        crystalRootinotheta2;
   Double_t        crystalRootinopidE2;
   Double_t        crystalRootinoMWPC0E2;
   Double_t        crystalRootinoMWPC1E2;
 //TLorentzVector  *crystalRootino1In;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Double_t        crystalRootinomass1In;
   Double_t        crystalRootinophi1In;
   Double_t        crystalRootinotheta1In;
   Double_t        crystalRootinopidE1In;
   Double_t        crystalRootinoMWPC0E1In;
   Double_t        crystalRootinoMWPC1E1In;
 //TLorentzVector  *crystalRootino2In;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   UInt_t          fP_fUniqueID;
   UInt_t          fP_fBits;
   Double_t        fP_fX;
   Double_t        fP_fY;
   Double_t        fP_fZ;
   Double_t        fE;
   Double_t        crystalRootinomass2In;
   Double_t        crystalRootinophi2In;
   Double_t        crystalRootinotheta2In;
   Double_t        crystalRootinopidE2In;
   Double_t        crystalRootinoMWPC0E2In;
   Double_t        crystalRootinoMWPC1E2In;
   Double_t        crystalCoplan2;*/

   // List of branches
   TBranch        *b_Particles;   //!
   TBranch        *b_Generated;   //!
/*   TBranch        *b_Topo;   //!
   TBranch        *b_crystalPhoton_fUniqueID;   //!
   TBranch        *b_crystalPhoton_fBits;   //!
   TBranch        *b_crystalPhoton_fP_fUniqueID;   //!
   TBranch        *b_crystalPhoton_fP_fBits;   //!
   TBranch        *b_crystalPhoton_fP_fX;   //!
   TBranch        *b_crystalPhoton_fP_fY;   //!
   TBranch        *b_crystalPhoton_fP_fZ;   //!
   TBranch        *b_crystalPhoton_fE;   //!
   TBranch        *b_crystalPhotonmass;   //!
   TBranch        *b_crystalPhotonphi;   //!
   TBranch        *b_crystalPhotontheta;   //!
   TBranch        *b_crystalPhotonpidE;   //!
   TBranch        *b_crystalPhotonMWPC0E;   //!
   TBranch        *b_crystalPhotonMWPC1E;   //!
   TBranch        *b_crystalRootino_fUniqueID;   //!
   TBranch        *b_crystalRootino_fBits;   //!
   TBranch        *b_crystalRootino_fP_fUniqueID;   //!
   TBranch        *b_crystalRootino_fP_fBits;   //!
   TBranch        *b_crystalRootino_fP_fX;   //!
   TBranch        *b_crystalRootino_fP_fY;   //!
   TBranch        *b_crystalRootino_fP_fZ;   //!
   TBranch        *b_crystalRootino_fE;   //!
   TBranch        *b_crystalRootinomass;   //!
   TBranch        *b_crystalRootinophi;   //!
   TBranch        *b_crystalRootinotheta;   //!
   TBranch        *b_crystalRootinopidE;   //!
   TBranch        *b_crystalRootinoMWPC0E;   //!
   TBranch        *b_crystalRootinoMWPC1E;   //!
   TBranch        *b_crystalRootinoIn_fUniqueID;   //!
   TBranch        *b_crystalRootinoIn_fBits;   //!
   TBranch        *b_crystalRootinoIn_fP_fUniqueID;   //!
   TBranch        *b_crystalRootinoIn_fP_fBits;   //!
   TBranch        *b_crystalRootinoIn_fP_fX;   //!
   TBranch        *b_crystalRootinoIn_fP_fY;   //!
   TBranch        *b_crystalRootinoIn_fP_fZ;   //!
   TBranch        *b_crystalRootinoIn_fE;   //!
   TBranch        *b_crystalRootinomassIn;   //!
   TBranch        *b_crystalRootinophiIn;   //!
   TBranch        *b_crystalRootinothetaIn;   //!
   TBranch        *b_crystalRootinopidEIn;   //!
   TBranch        *b_crystalRootinoMWPC0EIn;   //!
   TBranch        *b_crystalRootinoMWPC1EIn;   //!
   TBranch        *b_crystalCoplan;   //!
   TBranch        *b_crystalRootino1_fUniqueID;   //!
   TBranch        *b_crystalRootino1_fBits;   //!
   TBranch        *b_crystalRootino1_fP_fUniqueID;   //!
   TBranch        *b_crystalRootino1_fP_fBits;   //!
   TBranch        *b_crystalRootino1_fP_fX;   //!
   TBranch        *b_crystalRootino1_fP_fY;   //!
   TBranch        *b_crystalRootino1_fP_fZ;   //!
   TBranch        *b_crystalRootino1_fE;   //!
   TBranch        *b_crystalRootinomass1;   //!
   TBranch        *b_crystalRootinophi1;   //!
   TBranch        *b_crystalRootinotheta1;   //!
   TBranch        *b_crystalRootinopidE1;   //!
   TBranch        *b_crystalRootinoMWPC0E1;   //!
   TBranch        *b_crystalRootinoMWPC1E1;   //!
   TBranch        *b_crystalRootino2_fUniqueID;   //!
   TBranch        *b_crystalRootino2_fBits;   //!
   TBranch        *b_crystalRootino2_fP_fUniqueID;   //!
   TBranch        *b_crystalRootino2_fP_fBits;   //!
   TBranch        *b_crystalRootino2_fP_fX;   //!
   TBranch        *b_crystalRootino2_fP_fY;   //!
   TBranch        *b_crystalRootino2_fP_fZ;   //!
   TBranch        *b_crystalRootino2_fE;   //!
   TBranch        *b_crystalRootinomass2;   //!
   TBranch        *b_crystalRootinophi2;   //!
   TBranch        *b_crystalRootinotheta2;   //!
   TBranch        *b_crystalRootinopidE2;   //!
   TBranch        *b_crystalRootinoMWPC0E2;   //!
   TBranch        *b_crystalRootinoMWPC1E2;   //!
   TBranch        *b_crystalRootino1In_fUniqueID;   //!
   TBranch        *b_crystalRootino1In_fBits;   //!
   TBranch        *b_crystalRootino1In_fP_fUniqueID;   //!
   TBranch        *b_crystalRootino1In_fP_fBits;   //!
   TBranch        *b_crystalRootino1In_fP_fX;   //!
   TBranch        *b_crystalRootino1In_fP_fY;   //!
   TBranch        *b_crystalRootino1In_fP_fZ;   //!
   TBranch        *b_crystalRootino1In_fE;   //!
   TBranch        *b_crystalRootinomass1In;   //!
   TBranch        *b_crystalRootinophi1In;   //!
   TBranch        *b_crystalRootinotheta1In;   //!
   TBranch        *b_crystalRootinopidE1In;   //!
   TBranch        *b_crystalRootinoMWPC0E1In;   //!
   TBranch        *b_crystalRootinoMWPC1E1In;   //!
   TBranch        *b_crystalRootino2In_fUniqueID;   //!
   TBranch        *b_crystalRootino2In_fBits;   //!
   TBranch        *b_crystalRootino2In_fP_fUniqueID;   //!
   TBranch        *b_crystalRootino2In_fP_fBits;   //!
   TBranch        *b_crystalRootino2In_fP_fX;   //!
   TBranch        *b_crystalRootino2In_fP_fY;   //!
   TBranch        *b_crystalRootino2In_fP_fZ;   //!
   TBranch        *b_crystalRootino2In_fE;   //!
   TBranch        *b_crystalRootinomass2In;   //!
   TBranch        *b_crystalRootinophi2In;   //!
   TBranch        *b_crystalRootinotheta2In;   //!
   TBranch        *b_crystalRootinopidE2In;   //!
   TBranch        *b_crystalRootinoMWPC0E2In;   //!
   TBranch        *b_crystalRootinoMWPC1E2In;   //!
   TBranch        *b_crystalCoplan2;   //! */

   PimP(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~PimP() {/*//SafeDelete(fp1);//If we add pointer ro classmust delete it*/  }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
  //Additional final state analysis function
  virtual void UserProcess();
   virtual void    Terminate();

//Add THSHisto functions
  virtual void HistogramList(TString sLabel);
  virtual void FillHistograms(TString sCut);

   ClassDef(PimP,0);
};

#endif

#ifdef PimP_cxx
void PimP::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Particles = 0;
   Generated = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Particles", &Particles, &b_Particles);
 THSFinalState::SetDetParts(Particles);
   fChain->SetBranchAddress("Generated", &Generated, &b_Generated);
 if(fChain->GetBranch("Generated"))THSFinalState::SetGenParts(Generated);
/*   fChain->SetBranchAddress("Topo", &Topo, &b_Topo);
   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_crystalPhoton_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_crystalPhoton_fBits);
   fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_crystalPhoton_fP_fUniqueID);
   fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_crystalPhoton_fP_fBits);
   fChain->SetBranchAddress("fP.fX", &fP_fX, &b_crystalPhoton_fP_fX);
   fChain->SetBranchAddress("fP.fY", &fP_fY, &b_crystalPhoton_fP_fY);
   fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_crystalPhoton_fP_fZ);
   fChain->SetBranchAddress("fE", &fE, &b_crystalPhoton_fE);
   fChain->SetBranchAddress("crystalPhotonmass", &crystalPhotonmass, &b_crystalPhotonmass);
   fChain->SetBranchAddress("crystalPhotonphi", &crystalPhotonphi, &b_crystalPhotonphi);
   fChain->SetBranchAddress("crystalPhotontheta", &crystalPhotontheta, &b_crystalPhotontheta);
   fChain->SetBranchAddress("crystalPhotonpidE", &crystalPhotonpidE, &b_crystalPhotonpidE);
   fChain->SetBranchAddress("crystalPhotonMWPC0E", &crystalPhotonMWPC0E, &b_crystalPhotonMWPC0E);
   fChain->SetBranchAddress("crystalPhotonMWPC1E", &crystalPhotonMWPC1E, &b_crystalPhotonMWPC1E);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_crystalRootino_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_crystalRootino_fBits);
//    fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_crystalRootino_fP_fUniqueID);
//    fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_crystalRootino_fP_fBits);
//    fChain->SetBranchAddress("fP.fX", &fP_fX, &b_crystalRootino_fP_fX);
//    fChain->SetBranchAddress("fP.fY", &fP_fY, &b_crystalRootino_fP_fY);
//    fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_crystalRootino_fP_fZ);
//    fChain->SetBranchAddress("fE", &fE, &b_crystalRootino_fE);
   fChain->SetBranchAddress("crystalRootinomass", &crystalRootinomass, &b_crystalRootinomass);
   fChain->SetBranchAddress("crystalRootinophi", &crystalRootinophi, &b_crystalRootinophi);
   fChain->SetBranchAddress("crystalRootinotheta", &crystalRootinotheta, &b_crystalRootinotheta);
   fChain->SetBranchAddress("crystalRootinopidE", &crystalRootinopidE, &b_crystalRootinopidE);
   fChain->SetBranchAddress("crystalRootinoMWPC0E", &crystalRootinoMWPC0E, &b_crystalRootinoMWPC0E);
   fChain->SetBranchAddress("crystalRootinoMWPC1E", &crystalRootinoMWPC1E, &b_crystalRootinoMWPC1E);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_crystalRootinoIn_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_crystalRootinoIn_fBits);
//    fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_crystalRootinoIn_fP_fUniqueID);
//    fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_crystalRootinoIn_fP_fBits);
//    fChain->SetBranchAddress("fP.fX", &fP_fX, &b_crystalRootinoIn_fP_fX);
//    fChain->SetBranchAddress("fP.fY", &fP_fY, &b_crystalRootinoIn_fP_fY);
//    fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_crystalRootinoIn_fP_fZ);
//    fChain->SetBranchAddress("fE", &fE, &b_crystalRootinoIn_fE);
   fChain->SetBranchAddress("crystalRootinomassIn", &crystalRootinomassIn, &b_crystalRootinomassIn);
   fChain->SetBranchAddress("crystalRootinophiIn", &crystalRootinophiIn, &b_crystalRootinophiIn);
   fChain->SetBranchAddress("crystalRootinothetaIn", &crystalRootinothetaIn, &b_crystalRootinothetaIn);
   fChain->SetBranchAddress("crystalRootinopidEIn", &crystalRootinopidEIn, &b_crystalRootinopidEIn);
   fChain->SetBranchAddress("crystalRootinoMWPC0EIn", &crystalRootinoMWPC0EIn, &b_crystalRootinoMWPC0EIn);
   fChain->SetBranchAddress("crystalRootinoMWPC1EIn", &crystalRootinoMWPC1EIn, &b_crystalRootinoMWPC1EIn);
   fChain->SetBranchAddress("crystalCoplan", &crystalCoplan, &b_crystalCoplan);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_crystalRootino1_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_crystalRootino1_fBits);
//    fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_crystalRootino1_fP_fUniqueID);
//    fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_crystalRootino1_fP_fBits);
//    fChain->SetBranchAddress("fP.fX", &fP_fX, &b_crystalRootino1_fP_fX);
//    fChain->SetBranchAddress("fP.fY", &fP_fY, &b_crystalRootino1_fP_fY);
//    fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_crystalRootino1_fP_fZ);
//    fChain->SetBranchAddress("fE", &fE, &b_crystalRootino1_fE);
   fChain->SetBranchAddress("crystalRootinomass1", &crystalRootinomass1, &b_crystalRootinomass1);
   fChain->SetBranchAddress("crystalRootinophi1", &crystalRootinophi1, &b_crystalRootinophi1);
   fChain->SetBranchAddress("crystalRootinotheta1", &crystalRootinotheta1, &b_crystalRootinotheta1);
   fChain->SetBranchAddress("crystalRootinopidE1", &crystalRootinopidE1, &b_crystalRootinopidE1);
   fChain->SetBranchAddress("crystalRootinoMWPC0E1", &crystalRootinoMWPC0E1, &b_crystalRootinoMWPC0E1);
   fChain->SetBranchAddress("crystalRootinoMWPC1E1", &crystalRootinoMWPC1E1, &b_crystalRootinoMWPC1E1);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_crystalRootino2_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_crystalRootino2_fBits);
//    fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_crystalRootino2_fP_fUniqueID);
//    fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_crystalRootino2_fP_fBits);
//    fChain->SetBranchAddress("fP.fX", &fP_fX, &b_crystalRootino2_fP_fX);
//    fChain->SetBranchAddress("fP.fY", &fP_fY, &b_crystalRootino2_fP_fY);
//    fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_crystalRootino2_fP_fZ);
//    fChain->SetBranchAddress("fE", &fE, &b_crystalRootino2_fE);
   fChain->SetBranchAddress("crystalRootinomass2", &crystalRootinomass2, &b_crystalRootinomass2);
   fChain->SetBranchAddress("crystalRootinophi2", &crystalRootinophi2, &b_crystalRootinophi2);
   fChain->SetBranchAddress("crystalRootinotheta2", &crystalRootinotheta2, &b_crystalRootinotheta2);
   fChain->SetBranchAddress("crystalRootinopidE2", &crystalRootinopidE2, &b_crystalRootinopidE2);
   fChain->SetBranchAddress("crystalRootinoMWPC0E2", &crystalRootinoMWPC0E2, &b_crystalRootinoMWPC0E2);
   fChain->SetBranchAddress("crystalRootinoMWPC1E2", &crystalRootinoMWPC1E2, &b_crystalRootinoMWPC1E2);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_crystalRootino1In_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_crystalRootino1In_fBits);
//    fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_crystalRootino1In_fP_fUniqueID);
//    fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_crystalRootino1In_fP_fBits);
//    fChain->SetBranchAddress("fP.fX", &fP_fX, &b_crystalRootino1In_fP_fX);
//    fChain->SetBranchAddress("fP.fY", &fP_fY, &b_crystalRootino1In_fP_fY);
//    fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_crystalRootino1In_fP_fZ);
//    fChain->SetBranchAddress("fE", &fE, &b_crystalRootino1In_fE);
   fChain->SetBranchAddress("crystalRootinomass1In", &crystalRootinomass1In, &b_crystalRootinomass1In);
   fChain->SetBranchAddress("crystalRootinophi1In", &crystalRootinophi1In, &b_crystalRootinophi1In);
   fChain->SetBranchAddress("crystalRootinotheta1In", &crystalRootinotheta1In, &b_crystalRootinotheta1In);
   fChain->SetBranchAddress("crystalRootinopidE1In", &crystalRootinopidE1In, &b_crystalRootinopidE1In);
   fChain->SetBranchAddress("crystalRootinoMWPC0E1In", &crystalRootinoMWPC0E1In, &b_crystalRootinoMWPC0E1In);
   fChain->SetBranchAddress("crystalRootinoMWPC1E1In", &crystalRootinoMWPC1E1In, &b_crystalRootinoMWPC1E1In);
//    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_crystalRootino2In_fUniqueID);
//    fChain->SetBranchAddress("fBits", &fBits, &b_crystalRootino2In_fBits);
//    fChain->SetBranchAddress("fP.fUniqueID", &fP_fUniqueID, &b_crystalRootino2In_fP_fUniqueID);
//    fChain->SetBranchAddress("fP.fBits", &fP_fBits, &b_crystalRootino2In_fP_fBits);
//    fChain->SetBranchAddress("fP.fX", &fP_fX, &b_crystalRootino2In_fP_fX);
//    fChain->SetBranchAddress("fP.fY", &fP_fY, &b_crystalRootino2In_fP_fY);
//    fChain->SetBranchAddress("fP.fZ", &fP_fZ, &b_crystalRootino2In_fP_fZ);
//    fChain->SetBranchAddress("fE", &fE, &b_crystalRootino2In_fE);
   fChain->SetBranchAddress("crystalRootinomass2In", &crystalRootinomass2In, &b_crystalRootinomass2In);
   fChain->SetBranchAddress("crystalRootinophi2In", &crystalRootinophi2In, &b_crystalRootinophi2In);
   fChain->SetBranchAddress("crystalRootinotheta2In", &crystalRootinotheta2In, &b_crystalRootinotheta2In);
   fChain->SetBranchAddress("crystalRootinopidE2In", &crystalRootinopidE2In, &b_crystalRootinopidE2In);
   fChain->SetBranchAddress("crystalRootinoMWPC0E2In", &crystalRootinoMWPC0E2In, &b_crystalRootinoMWPC0E2In);
   fChain->SetBranchAddress("crystalRootinoMWPC1E2In", &crystalRootinoMWPC1E2In, &b_crystalRootinoMWPC1E2In);
   fChain->SetBranchAddress("crystalCoplan2", &crystalCoplan2, &b_crystalCoplan2);*/
}

Bool_t PimP::Notify()
{
   THSOutput::HSNotify(fChain);
  THSOutput::InitOutTree();
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef PimP_cxx
