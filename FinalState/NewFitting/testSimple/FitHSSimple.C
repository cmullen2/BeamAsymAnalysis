//Run with 
//root --hsfit FitHSSimple.C
{

  THSsPlot* RF=new THSsPlot("Simple");
  RF->SetOutDir("outGammaAveTagDiffTimeNeutronChannel20FilesExcludeNoCBTAPSGaus/");
  RF->SetBinnedFit(); //For parameter fits do binned chi2
  ///////////////////////////////Load Variables
  RF->LoadVariable("GammaAveTagDiffTime[-80,-20]");//should be same name as variable in tree  
  RF->LoadAuxVars("BeamEnergy[300,800]");
  RF->LoadAuxVars("Costh[-1,1]");
  RF->LoadAuxVars("Topo[-1,0]");
  RF->LoadAuxVars("Coplanarity[-180,180]");//should be same name as variable in tree 
  RF->LoadAuxVars("DetErrs[-0.25,0.25]");

  /////////////////////////////Make Model Signal
  RF->Factory("Gaussian::Signal( GammaAveTagDiffTime, SIMm[-60,-80,-20], SIMw[10,0,100] )");
//  RF->Factory("BifurGauss::Signal(GammaOneTagDiffTime,SIMm[-60,-80,-20], SIMwL[10,0,100], SIMwR[10,0,100]  )");
  RF->LoadSpeciesPDF("Signal");


  ////////////////////////////////Additional background
  RF->Factory("Chebychev::BG(GammaAveTagDiffTime,{a0[-0.1,-1,1]})");   //,a1[0.1,-1,1],a2[0.1,-1,1],a3[0.1,-1,1] ,a4[0.1,-1,1]      })");
  RF->LoadSpeciesPDF("BG");

   ///////////////////////////Load Data
  TChain chain("HSParticles");
  chain.AddFile("/w/work14/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev13.0Files20PhysicsAllV2.root");
  RF->SetIDBranchName("UID");//This is not needed if all events from tree go into dataset, i.e. the variable ranges do not cut any events. It is safer to have it...
  //import to RooFit
  RF->LoadDataSet(&chain);
  gBenchmark->Start("Binned");
  RF->FitAndStudy(20); //argument gives number of parameter fits to perform
  //Do some other stuff before saving weights
//  RF->DrawTreeVar("Phi",100,-180,180);
//  RF->DrawTreeVar("InvMass",100,0,1000);
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");
  RF->GetWeights()->Save();

}
