//Run with 
//root --hsfit FitHSSimpleBins.C
{
  THSsPlot* RF=new THSsPlot("binFit");
  RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/outGammaAveTagDiffTimeNeutronChannel1FilesEg20BinsExcludeNoCBTAPSGaus/");
 ///////////////////////////////Load Variables
  RF->LoadVariable("GammaAveTagDiffTime[-80,-20]");//should be same name as variable in tree  
  RF->LoadBinVars("BeamEnergy",20,300,800);
  RF->LoadAuxVars("Costh[-1,1]");
  RF->LoadAuxVars("Topo[-1,0]");
  RF->LoadAuxVars("Coplanarity[-180,180]");//should be same name as variable in tree 
  RF->LoadAuxVars("DetErrs[-0.25,0.25]");

 RF->Factory("Gaussian::Signal( GammaAveTagDiffTime, SIMm[-60,-80,-20], SIMw[10,0,100] )");
//  RF->Factory("BifurGauss::Signal(GammaOneTagDiffTime,SIMm[-60,-80,-20], SIMwL[10,0,100], SIMwR[10,0,100]  )");
  RF->LoadSpeciesPDF("Signal");

  ////////////////////////////////Additional background
  RF->Factory("Chebychev::BG(GammaAveTagDiffTime,{a0[-0.1,-1,1]})");   //,a1[0.1,-1,1],a2[0.1,-1,1],a3[0.1,-1,1] ,a4[0.1,-1,1]      })");
  RF->LoadSpeciesPDF("BG");  


   ///////////////////////////Load Data
  TChain chain("HSParticles");
  chain.AddFile("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev15.0Files1PhysicsAll.root");
  RF->SetIDBranchName("UID");
  //import to RooFit
  RF->LoadDataSet(&chain);
  gBenchmark->Start("Binned");
  RF->FitAndStudy(2);//argument gives number of parameter fits to perform

  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  

  //save the weights in one combined file
  //Note already saved in individual bins 
  RF->GetWeights()->Save();


}
