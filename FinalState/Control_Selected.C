{
  //optional Set input file directory, could be done with --hsin or setenv HSIN


//Prod Data
  HSin("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/MixedParaPerp/VertexInfo/Physics_CBTaggTAPS_14962.r");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Data/DataCalibration/ChrisOutput/MixedParaPerp/");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/MixedParaPerp/Physics_CBTaggTAPS_14962.root");
  
//Empty Target  
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/EmptyTarget/MixedParaPerp/VertexCut/VertexInfo/");


  //optional set ouput directory or file.
  //Directory=>1 out file for every in file
  //file=> 1 total output file
  
//Prod Data
  HSout("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev20.0Files1PhysicsAllVertexInfoCx.root");
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Data/DataCalibration/HaspectOutput/ProdData/JUNKDev1.0Files20PhysicsAll.root");

//Empty Target
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev3.0Files12PhysicsAllVertexInfoICE.root");
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
