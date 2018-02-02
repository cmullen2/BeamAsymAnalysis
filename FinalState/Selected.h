//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 16 11:04:23 2017 by ROOT version 6.08/06
// from TTree HSParticles/Event selection tree
// found on file: /w/work14/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/MixedParaPerp/Physics_CBTaggTAPS_14975.root
//////////////////////////////////////////////////////////

#ifndef Selected_h
#define Selected_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "THSOutput.h"
#include "THSProj_Pi0N.h"

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "TVector3.h"
#include "TObject.h"

class Selected : public TSelector, public THSOutput, public THSProj_Pi0N {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

  //data members for new branches
   //you must define how they are processed for each event and set to 0 in constructor
   //e.g.   TLorentzVector  *fp1;
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<THSParticle*> *Particles;
   vector<THSParticle*> *Generated;
   /* Double_t        fbeamHelicity; */
   /* Double_t        ftaggedTime; */
   /* Double_t        feventNo; */
   /* Double_t        fenergyBeam; */
   /* Double_t        fenergySum; */
   /* Int_t           fmultiplicity; */
   /* Double_t        fpidPhi; */
   /* Int_t           fpidIndex; */
 //TVector3        *fchamber1Vec;
   /* UInt_t          fUniqueID; */
   /* UInt_t          fBits; */
   /* Double_t        fX; */
   /* Double_t        fY; */
   /* Double_t        fZ; */
 //TVector3        *fchamber2Vec;
 /*  UInt_t          fUniqueID;
   UInt_t          fBits;
   Double_t        fX;
   Double_t        fY;
   Double_t        fZ;*/
   /* Int_t           fedgeplane; */
   /* Double_t        flinPol; */
   /* Double_t        frootinoPhi; */
   /* Double_t        rootinoClustE; */
   /* Double_t        rootinoTheta; */
   /* Double_t        rootinoPhi; */
   /* Double_t        rootinoTime; */
   /* Double_t        rootinoClustS; */
   /* Double_t        rootinoClustC; */
   /* Double_t        rootinoVetoC; */
   /* Double_t        rootinoDet; */
   /* Double_t        rootinoVetoE; */
   /* Double_t        rootinoCham1E; */
   /* Double_t        rootinoCham2E; */
   /* Int_t           HasTappyTaps; */
   /* Int_t           HasCrisyBall; */

   // List of branches
   TBranch        *b_Particles;   //!
   TBranch        *b_Generated;   //!
   /* TBranch        *b_fbeamHelicity;   //! */
   /* TBranch        *b_ftaggedTime;   //! */
   /* TBranch        *b_feventNo;   //! */
   /* TBranch        *b_fenergyBeam;   //! */
   /* TBranch        *b_fenergySum;   //! */
   /* TBranch        *b_fmultiplicity;   //! */
   /* TBranch        *b_fpidPhi;   //! */
   /* TBranch        *b_fpidIndex;   //! */
   /* TBranch        *b_fchamber1Vec_fUniqueID;   //! */
   /* TBranch        *b_fchamber1Vec_fBits;   //! */
   /* TBranch        *b_fchamber1Vec_fX;   //! */
   /* TBranch        *b_fchamber1Vec_fY;   //! */
   /* TBranch        *b_fchamber1Vec_fZ;   //! */
   /* TBranch        *b_fchamber2Vec_fUniqueID;   //! */
   /* TBranch        *b_fchamber2Vec_fBits;   //! */
   /* TBranch        *b_fchamber2Vec_fX;   //! */
   /* TBranch        *b_fchamber2Vec_fY;   //! */
   /* TBranch        *b_fchamber2Vec_fZ;   //! */
   /* TBranch        *b_fedgeplane;   //! */
   /* TBranch        *b_flinPol;   //! */
   /* TBranch        *b_frootinoPhi;   //! */
   /* TBranch        *b_rootinoClustE;   //! */
   /* TBranch        *b_rootinoTheta;   //! */
   /* TBranch        *b_rootinoPhi;   //! */
   /* TBranch        *b_rootinoTime;   //! */
   /* TBranch        *b_rootinoClustS;   //! */
   /* TBranch        *b_rootinoClustC;   //! */
   /* TBranch        *b_rootinoVetoC;   //! */
   /* TBranch        *b_rootinoDet;   //! */
   /* TBranch        *b_rootinoVetoE;   //! */
   /* TBranch        *b_rootinoCham1E;   //! */
   /* TBranch        *b_rootinoCham2E;   //! */
   /* TBranch        *b_HasTappyTaps;   //! */
   /* TBranch        *b_HasCrisyBall;   //! */

   Selected(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selected() {/*//SafeDelete(fp1);//If we add pointer ro classmust delete it*/  }
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

   ClassDef(Selected,0);
};

#endif

#ifdef Selected_cxx
void Selected::Init(TTree *tree)
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
/*    fChain->SetBranchAddress("fbeamHelicity", &fbeamHelicity, &b_fbeamHelicity); */
/*    fChain->SetBranchAddress("ftaggedTime", &ftaggedTime, &b_ftaggedTime); */
/*    fChain->SetBranchAddress("feventNo", &feventNo, &b_feventNo); */
/*    fChain->SetBranchAddress("fenergyBeam", &fenergyBeam, &b_fenergyBeam); */
/*    fChain->SetBranchAddress("fenergySum", &fenergySum, &b_fenergySum); */
/*    fChain->SetBranchAddress("fmultiplicity", &fmultiplicity, &b_fmultiplicity); */
/*    fChain->SetBranchAddress("fpidPhi", &fpidPhi, &b_fpidPhi); */
/*    fChain->SetBranchAddress("fpidIndex", &fpidIndex, &b_fpidIndex); */
/*    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_fchamber1Vec_fUniqueID); */
/*    fChain->SetBranchAddress("fBits", &fBits, &b_fchamber1Vec_fBits); */
/*    fChain->SetBranchAddress("fX", &fX, &b_fchamber1Vec_fX); */
/*    fChain->SetBranchAddress("fY", &fY, &b_fchamber1Vec_fY); */
/*    fChain->SetBranchAddress("fZ", &fZ, &b_fchamber1Vec_fZ); */
/* //    fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_fchamber2Vec_fUniqueID); */
/* //    fChain->SetBranchAddress("fBits", &fBits, &b_fchamber2Vec_fBits); */
/* //    fChain->SetBranchAddress("fX", &fX, &b_fchamber2Vec_fX); */
/* //    fChain->SetBranchAddress("fY", &fY, &b_fchamber2Vec_fY); */
/* //    fChain->SetBranchAddress("fZ", &fZ, &b_fchamber2Vec_fZ); */
/*    fChain->SetBranchAddress("fedgeplane", &fedgeplane, &b_fedgeplane); */
/*    fChain->SetBranchAddress("flinPol", &flinPol, &b_flinPol); */
/*    fChain->SetBranchAddress("frootinoPhi", &frootinoPhi, &b_frootinoPhi); */
/*    fChain->SetBranchAddress("rootinoClustE", &rootinoClustE, &b_rootinoClustE); */
/*    fChain->SetBranchAddress("rootinoTheta", &rootinoTheta, &b_rootinoTheta); */
/*    fChain->SetBranchAddress("rootinoPhi", &rootinoPhi, &b_rootinoPhi); */
/*    fChain->SetBranchAddress("rootinoTime", &rootinoTime, &b_rootinoTime); */
/*    fChain->SetBranchAddress("rootinoClustS", &rootinoClustS, &b_rootinoClustS); */
/*    fChain->SetBranchAddress("rootinoClustC", &rootinoClustC, &b_rootinoClustC); */
/*    fChain->SetBranchAddress("rootinoVetoC", &rootinoVetoC, &b_rootinoVetoC); */
/*    fChain->SetBranchAddress("rootinoDet", &rootinoDet, &b_rootinoDet); */
/*    fChain->SetBranchAddress("rootinoVetoE", &rootinoVetoE, &b_rootinoVetoE); */
/*    fChain->SetBranchAddress("rootinoCham1E", &rootinoCham1E, &b_rootinoCham1E); */
/*    fChain->SetBranchAddress("rootinoCham2E", &rootinoCham2E, &b_rootinoCham2E); */
/*    fChain->SetBranchAddress("HasTappyTaps", &HasTappyTaps, &b_HasTappyTaps); */
/*    fChain->SetBranchAddress("HasCrisyBall", &HasCrisyBall, &b_HasCrisyBall); */
}

Bool_t Selected::Notify()
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

#endif // #ifdef Selected_cxx
