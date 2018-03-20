//root --hsdata --hsfinal=THSProj_PiMinusP RunFSLund.C
//You need to replace Proj_PiMinusP with your final state class name
{
  //Create FinalState
  THSProj_PiMinusP* fs=new THSProj_PiMinusP();
  fs->SetPermutate(); //turn on permuations
  // fs->SetGenerated(); //just analyse generated branch
  //create datamanager
  THSDataManager* dm=new THSDataManager();
  //dm->SetReadGenBranch("Generated");
  dm->Init("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/ChrisOutput/Perp/Physics_CBTaggTAPS_14946.root","HSParticles");
  //connect Project to HSParticles
  fs->SetDetParts(dm->GetParticles());
  //fs->SetGenParts(dm->GetGenerated());
  Int_t counter=0;
  
  //create ouput tree
  TFile* outfile=new TFile("/w/work1/home/chris/LatestAnalysisRuns/Data/DataDec17ChargedPion/HaspectOutput/PiMinusP/Dev1.0Files1PhysicsAll.root","recreate");
  TTree* outtree=new TTree("FinalTree","output tree");
  fs->FinalStateOutTree(outtree); //connect ouput tree to project branches
  
  gBenchmark->Start("timer");
  
  while(dm->ReadEvent()){//loop over events
    fs->ProcessEvent();
  }
  gBenchmark->Stop("timer");
  gBenchmark->Print("timer");
  
  outfile->cd();
  outtree->Write();
  delete outfile;
}
