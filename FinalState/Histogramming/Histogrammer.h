//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov 21 15:06:21 2017 by ROOT version 6.08/06
// from TTree HSParticles/Event selection tree
// found on file: /w/work14/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/MixedParaPerp/Physics_CBTaggTAPS_14975.root
//////////////////////////////////////////////////////////

#ifndef Histogrammer_h
#define Histogrammer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include "THSOutput.h"
#include "THSWeights.h"
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include "THSParticle.h"

#include <vector>

#include "TVector3.h"



class Histogrammer : public TSelector, public THSOutput {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

  //data members for reading weights
   THSWeights* fWeights=0;
  //data members for new branches
   //you must define how they are processed for each event and set to 0 in constructor
   //e.g.   TLorentzVector  *fp1;
   // Readers to access the data (delete the ones you do not need).
   TTreeReaderArray<THSParticle> Particles = {fReader, "Particles"};
   TTreeReaderArray<THSParticle> Generated = {fReader, "Generated"};
   TTreeReaderValue<Double_t> fbeamHelicity = {fReader, "fbeamHelicity"};
   TTreeReaderValue<Double_t> ftaggedTime = {fReader, "ftaggedTime"};
   TTreeReaderValue<Double_t> feventNo = {fReader, "feventNo"};
   TTreeReaderValue<Double_t> fenergyBeam = {fReader, "fenergyBeam"};
   TTreeReaderValue<Double_t> fenergySum = {fReader, "fenergySum"};
   TTreeReaderValue<Int_t> fmultiplicity = {fReader, "fmultiplicity"};
   TTreeReaderValue<Double_t> fpidPhi = {fReader, "fpidPhi"};
   TTreeReaderValue<Int_t> fpidIndex = {fReader, "fpidIndex"};
   TTreeReaderValue<unsigned int> fUniqueID = {fReader, "fUniqueID"};
   TTreeReaderValue<unsigned int> fBits = {fReader, "fBits"};
   TTreeReaderValue<Double_t> fX = {fReader, "fX"};
   TTreeReaderValue<Double_t> fY = {fReader, "fY"};
   TTreeReaderValue<Double_t> fZ = {fReader, "fZ"};
   TTreeReaderValue<Int_t> fedgeplane = {fReader, "fedgeplane"};
   TTreeReaderValue<Double_t> flinPol = {fReader, "flinPol"};
   TTreeReaderValue<Double_t> frootinoPhi = {fReader, "frootinoPhi"};
   TTreeReaderValue<Double_t> rootinoClustE = {fReader, "rootinoClustE"};
   TTreeReaderValue<Double_t> rootinoTheta = {fReader, "rootinoTheta"};
   TTreeReaderValue<Double_t> rootinoPhi = {fReader, "rootinoPhi"};
   TTreeReaderValue<Double_t> rootinoTime = {fReader, "rootinoTime"};
   TTreeReaderValue<Double_t> rootinoClustS = {fReader, "rootinoClustS"};
   TTreeReaderValue<Double_t> rootinoClustC = {fReader, "rootinoClustC"};
   TTreeReaderValue<Double_t> rootinoVetoC = {fReader, "rootinoVetoC"};
   TTreeReaderValue<Double_t> rootinoDet = {fReader, "rootinoDet"};
   TTreeReaderValue<Double_t> rootinoVetoE = {fReader, "rootinoVetoE"};
   TTreeReaderValue<Double_t> rootinoCham1E = {fReader, "rootinoCham1E"};
   TTreeReaderValue<Double_t> rootinoCham2E = {fReader, "rootinoCham2E"};
   TTreeReaderValue<Int_t> HasTappyTaps = {fReader, "HasTappyTaps"};
   TTreeReaderValue<Int_t> HasCrisyBall = {fReader, "HasCrisyBall"};


   Histogrammer(TTree * /*tree*/ =0) { }
   virtual ~Histogrammer() {SafeDelete(fWeights); /*//SafeDelete(fp1);//If we add pointer ro classmust delete it*/  }
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
   virtual void    Terminate();
//Add THSHisto functions
   virtual void HistogramList(TString sLabel);
   virtual void FillHistograms(TString sCut);

   ClassDef(Histogrammer,0);

};

#endif

#ifdef Histogrammer_cxx
void Histogrammer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t Histogrammer::Notify()
{
   fChain=fReader.GetTree();
   THSOutput::HSNotify(fChain);
  THSOutput::InitOutTree();
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef Histogrammer_cxx
