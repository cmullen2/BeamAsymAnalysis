//Run with 
//root --hsfit FitHSFactorisedMmiss.C

{
  THSsPlot* RF=new THSsPlot("SF");
  RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/EmptyTargetFitNeutronTiming20Bins12Files/");
  //RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/FitNeutronTiming20Bins20Files/");
  ///////////////////////////////Load Variables
  RF->LoadVariable("GammaAveTagDiffTime[-80,20]");//should be same name as variable in tree 
  RF->LoadAuxVars("Phi[-180,180]");
  RF->LoadAuxVars("InvMass[125,145]"); //Only for Neutron Case(Not used this time)
  RF->LoadAuxVars("Costh[-1,1]");//Not to be fitted but limits applied to dataset (prev was 20bins)
  RF->LoadAuxVars("Pol[-1,1]");
//  RF->LoadAuxVars("DetErrs[-0.25,0.25]");
  RooRealVar * var=RF->GetWorkSpace()->var("GammaAveTagDiffTime");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");


  //Tell this fitter to use these bins
  RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/EmptyTargetNeutronTiming20Bins12Files/"); 
  //RF->ConfigureSavedBins("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/NeutronTiming20Bins20Files/"); 

  RF->Factory("Gaussian::Signal( GammaAveTagDiffTime, SIMm[-60,-80,-20], SIMw[10,0,100] )");
//  RF->Factory("BifurGauss::Signal(GammaOneTagDiffTime,SIMm[-60,-80,-20], SIMwL[10,0,100], SIMwR[10,0,100]  )");
  RF->LoadSpeciesPDF("Signal");


  ////////////////////////////////Additional background
  RF->Factory("Chebychev::BG(GammaAveTagDiffTime,{a0[-0.1,-1,1]})");   //,a1[0.1,-1,1],a2[0.1,-1,1],a3[0.1,-1,1] ,a4[0.1,-1,1]      })");
  RF->LoadSpeciesPDF("BG");


  gBenchmark->Start("M1Fit");
  RF->FitSavedBins(1); //argument = number of test fits with random initial pars
  gBenchmark->Stop("M1Fit");
  gBenchmark->Print("M1Fit");


}
