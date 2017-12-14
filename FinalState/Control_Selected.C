{
  //optional Set input file directory, could be done with --hsin or setenv HSIN
  HSin("/w/work14/home/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/MixedParaPerp/");
  //optional set ouput directory or file.
  //Directory=>1 out file for every in file
  //file=> 1 total output file
  HSout("/w/work14/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev14.0Files20PhysicsAll.root");
//  HSMacPath("ADDITIONALMACROPATH_WHEREPROJECTIS");
  HSfinal("THSProj_Pi0N");
  
  //Set up the input chain to be analysed,could remove HSin() if you want
  TChain* tree=new TChain("HSParticles","datachain");
  tree->Add(HSin()+"*");

  //if using proof
  //Give proof destination file (env variables can't be read directly
  if(gProof) {gProof->AddInput(new TNamed("HSOUT",HSout().Data()));tree->SetProof();}


  tree->Process("Selected.C++");
  
  //Not actually sure if this is needed or not...
  if(gProof)gProof->ClearData(TProof::kUnregistered | TProof::kForceClear);
}
