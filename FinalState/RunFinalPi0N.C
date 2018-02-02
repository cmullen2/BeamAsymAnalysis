//root --hsdata --hsproj=THSProj_pKK RunProjectPerm.C
{
  //Create Project
 
  THSProj_Pi0N* ggg=new THSProj_Pi0N(); //Breaks here as expected
  ggg->SetPermutate(); //turn on permuations
//  ggg->SetGenerated(); //just analyse generated branch
  //create datamanager
  THSDataManager* dm=new THSDataManager();
  //dm->SetReadGenBranch("Generated");
  
//Production
//  dm->Init("/w/work14/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/Para/","HSParticles");
  dm->Init("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/Para/Physics_CBTaggTAPS_14919.root","HSParticles");
//  Simulation 
// dm->Init("/w/work14/chris/LatestAnalysisRuns/Sims/SimsJan17/ChrisOutput/Deuterium/BeamAsym/PosPolarisation/Physics_A2OutPosPol.root","HSParticles");
//Empty
//  dm->Init("/w/work14/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/EmptyTarget/Para/Physics_CBTaggTAPS_15811.root","HSParticles");

//  dm->Init("/w/work14/chris/Run101016/ChrisOutput/Para/LinPolTests/Physics_CBTaggTAPS_14919.root","HSParticles");
 // dm->Init("/w/work14/chris/ForBonn/Neutron/ChrisGoatOut/Perp/TestHaspect/Physics_CBTaggTAPS_15156.root","Particles");
  //connect Project to HSParticles
  ggg->SetDetParts(dm->GetParticles());
//  ggg->SetGenParts(dm->GetGenerated());
  Int_t counter=0;

   //create ouput tree
  TFile* outfile=new TFile("/scratch/chris/OutputNewTimingDetDependence.root","recreate");
  TTree* outtree=new TTree("FinalTree","output tree");
  ggg->FinalStateOutTree(outtree); //connect output tree to project branches

  gBenchmark->Start("timer");
   
  while(dm->ReadEvent()){//loop over events
    ggg->ProcessEvent();
  }
  gBenchmark->Stop("timer");
  gBenchmark->Print("timer");

  outfile->cd();
  outtree->Write();
  delete outfile;
}
