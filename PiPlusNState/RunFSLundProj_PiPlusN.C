//root --hsdata --hsfinal=THSProj_PiPlusN RunFSLund.C
//You need to replace Proj_PiPlusN with your final state class name
{
  //Create FinalState
  THSProj_PiPlusN* fs=new THSProj_PiPlusN();
  //  fs->SetPermutate(); //turn on permuations
  fs->SetGenerated(); //just analyse generated branch
  //create datamanager
  THSLundReader* dm=new THSLundReader();
  dm->SetWriteGenBranch("Generated");
  dm->Init("/lund/file/name.lund","HSParticles");
  //connect Project to HSParticles
  // pKK->SetDetParts(dm->GetParticles());
  fs->SetGenParts(dm->GetGenerated());
  Int_t counter=0;
  
  //create ouput tree
  TFile* outfile=new TFile("gentest.root","recreate");
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
