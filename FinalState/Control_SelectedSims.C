{
  //optional Set input file directory, could be done with --hsin or setenv HSIN
  //HSin("/w/work14/chris/Run101016/ChrisOutput/Para/LinPolTests/RootinoPhi/");
  //optional set ouput directory or file.
  //Directory=>1 out file for every in file
  //file=> 1 total output file
  //HSout("FULL_PATH_OUTPUT_FILE_DIR_OR_FILE");
 // HSMacPath("/home/chris/HAPECT6/Projects/Pi0N/");
  HSfinal("THSProj_Pi0N");

 // HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/Flat/Physics_A2Geant_DeutNoPol*");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/NPi0/Physics_A2Geant_DeutNoPol*");
 // HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/NPi0/Physics_A2Geant_DeutNoPol_0*");

//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/PPi0/VertexInfo/Physics_A2Geant_DeutNoPol*");
 

//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPi0/VertexAttempt/");



//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/PPi0Pi0/Physics_A2Geant_DeutNoPol*");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/PPi0Pim/Physics_A2Geant_DeutNoPol*");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/PPipPim/Physics_A2Geant_DeutNoPol*");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/PPipPimNoHadron/Physics_A2Geant_DeutNoPol*");
  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/PCompton/Physics_A2Geant_DeutNoPol*");


//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/NPi0Pi0/Physics_A2Geant_DeutNoPol*");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/NPipPi0/Physics_A2Geant_DeutNoPol*");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/NPipPim/Physics_A2Geant_DeutNoPol*");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/NPipPimNoHadron/Physics_A2Geant_DeutNoPol*");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/NCompton/Physics_A2Geant_DeutNoPol*");


//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/PEta/Physics_A2Geant_DeutNoPol*");
//  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/NEta/Physics_A2Geant_DeutNoPol*");

  

//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPi0Pi0/");
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPi0Pim/");
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPipPim/");
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPipPimNoHadron/");
  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PCompton/");


//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NPi0Pi0/");
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NPipPi0/");
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NPipPim/");
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NPipPimNoHadron/");
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NCompton/");


//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PEta/");
//  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/NEta/");






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
