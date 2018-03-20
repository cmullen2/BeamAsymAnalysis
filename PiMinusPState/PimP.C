#define PimP_cxx
// The class definition in PimP.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("PimP.C")
// root> T->Process("PimP.C","some options")
// root> T->Process("PimP.C+")
//

#include "PimP.h"
#include <TH2.h>
#include <TStyle.h>


void PimP::Begin(TTree * tree)
{
   THSOutput::HSBegin(fInput,fOutput);
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   fBins=new THSBins("HSBins");
   fBins->AddAxis("Eg",24,200,800);
   fBins->AddAxis("Costh",20,-1,1);
   if(!fInput) fInput=new TList();
   fInput->Add(fBins);


}

void PimP::SlaveBegin(TTree * tree)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   THSOutput::HSSlaveBegin(fInput,fOutput);
   SetPermutate();//will permutate like particles
  //Initialise the ouput tree
   //Only done once. THSOutput::FinishOutput Resets the tree before new files
   //If you want to save additional branches to a new file, do it here
   //If you are creating a HSParticle tree via fStrParticles then do not create a new tree here, just add the extra branches
   fOutTree=new TTree("HSParticles","A tree containing reconstructed particles"); 
   THSProj_PiMinusP::FinalStateOutTree(fOutTree);
  //e.g. Make some objects to make branch with, these should be declared in the .h file 
  //e.g. fp1=new TLorentzVector();
  //e.g.  fOutTree->Branch("p1",&fp1,buff,split);
  THSHisto::InitialiseHisto(fInput);
  THSHisto::LoadHistograms();

}
void PimP::UserProcess(){
   
  if(fBins) fCurrBin=fBins->FindBin(fBeamEnergy,fCosth);

  THSOutput::HSProcessFill();
}

Bool_t PimP::Process(Long64_t entry)
{
   GetEntry(entry);
   THSOutput::HSProcessStart(entry);
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either PimP::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   
  
  //You must define the UserProcess function if you want to do additional
  //analyssis to making the FinalState tree, e.g. histogramming
  THSFinalState::ProcessEvent();


   return kTRUE;
}

void PimP::SlaveTerminate()
{
   THSOutput::HSSlaveTerminate();
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void PimP::Terminate()
{
   THSOutput::HSTerminate();
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}

void PimP::HistogramList(TString sLabel){
   TDirectory::AddDirectory(kFALSE);
   fOutput->Add(MapHist(new TH1F("MissMass","M_{miss}",100,0,4000)));
   TDirectory::AddDirectory(kTRUE);

}

void PimP::FillHistograms(TString sCut){
   if(fBins&&fCurrBin==-1) return;
   fCurrCut=sCut;

   FindHist("MissMass")->Fill(fMissMass);
   
}









