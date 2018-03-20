{
  //optional Set input file directory, could be done with --hsin or setenv HSIN
  HSin("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/ChrisOutput/Perp/");
  //optional set ouput directory or file.
  //Directory=>1 out file for every in file
  //file=> 1 total output file
  HSout("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/HaspectOutput/PiMinusP/Dev2.0Files1PhysicsAll.root");
  
  //Set up the input chain to be analysed,could remove HSin() if you want
  TChain* tree=new TChain("HSParticles","datachain");
  tree->Add(HSin()+"Physics_CBTaggTAPS_14917.root");

  //if using proof
  //Give proof destination file (env variables can't be read directly
  if(gProof) {gProof->AddInput(new TNamed("HSOUT",HSout().Data()));tree->SetProof();}


  tree->Process("PimP.C++");
  
  //Not actually sure if this is needed or not...
  if(gProof)gProof->ClearData(TProof::kUnregistered | TProof::kForceClear);
}
