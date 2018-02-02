{
  //optional Set input file directory, could be done with --hsin or setenv HSIN
  //HSin("/w/work14/chris/Run101016/ChrisOutput/Para/LinPolTests/RootinoPhi/");
  //optional set ouput directory or file.
  //Directory=>1 out file for every in file
  //file=> 1 total output file
  //HSout("FULL_PATH_OUTPUT_FILE_DIR_OR_FILE");
 // HSMacPath("/home/chris/HAPECT6/Projects/Pi0N/");
  HSfinal("THSProj_Pi0N");
//  HSin("/w/work14/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/MixedParaPerp/Physics_CBTaggTAPS_14957.root");
  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/Flat/*");//Physics_A2Geant_DeutNoPol_9Fla.root");
//HSin("/w/work14/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/TestingJunk/Physics_*");
 // HSin("/w/work14/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/EmptyTarget/MixedParaPerp/Physics_*");
//  HSin("/w/work14/chris/LatestAnalysisRuns/Sims/SimsJan17/ChrisOutput/Deuterium/BeamAsym/Mixed/");
  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/Flat/FourthAttempt/");

  

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
