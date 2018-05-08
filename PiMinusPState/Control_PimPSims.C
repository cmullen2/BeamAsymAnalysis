{

  HSin("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/ChrisOutput/Deuterium/PPiM/");
  HSout("/w/work1/home/chris/LatestAnalysisRuns/Sims/SimsOct17/HaspectOutput/Deuterium/PPiM/FirstAttempt/");
  HSfinal("THSProj_PiMinusP");
  TChain* tree=new TChain("HSParticles","datachain");
  tree->Add(HSin()+"Physics*");
  if(gProof) {gProof->AddInput(new TNamed("HSOUT",HSout().Data()));tree->SetProof();}
  tree->Process("PimP.C++");
  if(gProof)gProof->ClearData(TProof::kUnregistered | TProof::kForceClear);

}
