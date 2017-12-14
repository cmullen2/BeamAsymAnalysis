//Run with 
//root --hsfit FitHSFactorisedMmiss.C

{
  THSsPlot* RF=new THSsPlot("SF");
 // RF->SetOutDir("outCoplanProtonChannelPosPol6Files5Bins20ExcludeNoCBTAPS/");
  RF->SetOutDir("/scratch/chris/outCoplanProtonChannelPosPol20FilesCosth20Eg20MeVBinsSavedBins/");
  ///////////////////////////////Load Variables
  RF->LoadVariable("Coplanarity[-80,80]");//should be same name as variable in tree 
//  RF->LoadBinVars("Topo",1,0,1);//Not to be fitted but limits applied to dataset
//  RF->LoadBinVars("Pol",1,0,1);
//  RF->LoadBinVars("BeamEnergy",20,300,800);//Not to be fitted but limits applied to dataset (prev was 25 bins)
//  RF->LoadBinVars("Costh",20,-1,1);//Not to be fitted but limits applied to dataset (prev was 20bins)
  RF->LoadAuxVars("Phi[-180,180]");
  //  RF->LoadAuxVars("InvMass[125,145]"); //Only for Neutron Case(Not used this time)
  RF->LoadAuxVars("DetErrs[-0.25,0.25]");
  RooRealVar * var=RF->GetWorkSpace()->var("Coplanarity");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");


  //data to be fitted
//  TChain chain("HSParticles");
//  chain.Add("/w/work14/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev13.0Files20PhysicsAllV2.root");
//  RF->MakeBinnedTrees(&chain,"Data");

  //Tell this fitter to use these bins
  RF->ConfigureSavedBins("/scratch/chris/outCoplanProtonChannelPosPol20FilesCosth20Eg20MeVBinsSavedBins/"); 

 
  //RF->Factory("Gaussian::Sigi(Coplanarity, SIMm[0,-50,50], SIMw[10,0,100] )");
 RF->Factory("BifurGauss::Signal(Coplanarity,SIMm[0,-80,80], SIMwL[10,0,100], SIMwR[10,0,100]  )");
 RF->LoadSpeciesPDF("Signal");
 
 RF->Factory("Chebychev::BG(Coplanarity,{a0[-0.1,-1,1],a1[0.1,-1,1],a2[0.1,-1,1],a3[0.1,-1,1] ,a4[0.1,-1,1]      })");

 RF->LoadSpeciesPDF("BG");

  // //Load weights from Mmiss fit
  RF->LoadWeights("outGammaAveTagDiffTimeProtonChannel20FilesExcludeNoCBTAPSGaus/WeightsSimple.root","HSsWeights");
  RF->SetWeightName("Signal");

  gBenchmark->Start("M1Fit");
  RF->FitSavedBins(1); //argument = number of test fits with random initial pars
  gBenchmark->Stop("M1Fit");
  gBenchmark->Print("M1Fit");
  THSWeights* wts=new THSWeights("TotalWeights");
	wts->Merge("/scratch/chris/outCoplanProtonChannelPosPol20FilesCosth20Eg20MeVBinsSavedBins/WeightsTopo","/scratch/chris/outCoplanProtonChannelPosPol20FilesCosth20Eg20MeVBinsSavedBins/WeightsTotal.root","HSsWeights");
  //  RF->SetTree(&chain);
  RF->SetWeights(wts);


}
