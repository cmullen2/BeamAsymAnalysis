{
  //optional Set input file directory, could be done with --hsin or setenv HSIN
  HSin("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/ChrisOutput/MixedParaPerp/");
 // HSin("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/ChrisOutput/EmptyTarget/MixedParaPerp/");
  //optional set ouput directory or file.
  //Directory=>1 out file for every in file
  //file=> 1 total output file
  HSout("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/HaspectOutput/PiMinusP/ProdData/Dev3.0Files1PhysicsAllTesting.root");
 // HSout("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/HaspectOutput/PiMinusP/EmptyTarget/Dev3.0Files1PhysicsAll.root");
  
  //Final State class
  HSfinal("THSProj_PiMinusP");


  //Set up the input chain to be analysed,could remove HSin() if you want
  TChain* tree=new TChain("HSParticles","datachain");
  tree->Add(HSin()+"Physics_CBTaggTAPS_14919.*");

  //if using proof
  //Give proof destination file (env variables can't be read directly
  if(gProof) {gProof->AddInput(new TNamed("HSOUT",HSout().Data()));tree->SetProof();}


  tree->Process("PimP.C++");
  
  //Not actually sure if this is needed or not...
  if(gProof)gProof->ClearData(TProof::kUnregistered | TProof::kForceClear);
}
