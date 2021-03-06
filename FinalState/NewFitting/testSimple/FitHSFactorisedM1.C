//Run with 
//root --hsfit FitHSFactorisedMmiss.C

{
  THSsPlot* RF=new THSsPlot("SF");
 // RF->SetOutDir("outCoplanProtonChannelPosPol6Files5Bins20ExcludeNoCBTAPS/");
  RF->SetOutDir("/scratch/chris/outCoplanFromGammaAveTagDiffProtonChannelPosPol20FilesCosth1Eg1MeVBinsExcludeNoCBTAPSBifur/");
  ///////////////////////////////Load Variables
  RF->LoadVariable("Coplanarity[-80,80]");//should be same name as variable in tree 
  RF->LoadBinVars("Topo",1,0,1);//Not to be fitted but limits applied to dataset
  RF->LoadBinVars("Pol",1,0,1);
  RF->LoadBinVars("BeamEnergy",1,300,800);//Not to be fitted but limits applied to dataset (prev was 25 bins)
  RF->LoadBinVars("Costh",1,-1,1);//Not to be fitted but limits applied to dataset (prev was 20bins)
  RF->LoadAuxVars("Phi[-180,180]");
  //  RF->LoadAuxVars("InvMass[125,145]"); //Only for Neutron Case(Not used this time)
  RF->LoadAuxVars("DetErrs[-0.25,0.25]");
  RooRealVar * var=RF->GetWorkSpace()->var("Coplanarity");
  var->setBins(100); //number of bins used in PDF histogram
  RF->SetIDBranchName("UID");

   //Split data into bins
  //MC signal
//  TChain *chainmc=new TChain("MyModel","mcsignal");
//  chainmc->Add("SigData.root");
//  RF->MakeBinnedTrees(chainmc,"Sig1");
  //MC background
//  TChain *chainmcb=new TChain("HSParticles");
//  chainmcb->Add("/w/work14/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/EmptyTargetDev5.0Files6PhysicsAll.root");
//  RF->MakeBinnedTrees(chainmcb,"BG");

  //data to be fitted
  TChain chain("HSParticles");
  chain.Add("/w/work14/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev13.0Files20PhysicsAllV2.root");
  RF->MakeBinnedTrees(&chain,"Data");

  //Tell this fitter to use these bins
  RF->ConfigureSavedBins("/scratch/chris/outCoplanFromGammaAveTagDiffProtonChannelPosPol20FilesCosth1Eg1MeVBinsExcludeNoCBTAPSBifur/"); 

 
  //RF->Factory("Gaussian::Sigi(Coplanarity, SIMm[0,-50,50], SIMw[10,0,100] )");
 RF->Factory("BifurGauss::Signal(Coplanarity,SIMm[0,-80,80], SIMwL[10,0,100], SIMwR[10,0,100]  )");
 RF->LoadSpeciesPDF("Signal");
 
  RF->Factory("Chebychev::BG(Coplanarity,{a0[-0.1,-1,1],a1[0.1,-1,1],a2[0.1,-1,1],a3[0.1,-1,1] ,a4[0.1,-1,1]      })");
// RF->Factory("RooHSEventsHistPDF::BG(Coplanarity,alphaB[0,0,5],offB[0,0,0],scaleB[1.0,0.8,1.2])");
 //RooHSEventsHistPDF* pdfb=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("BG"));

 RF->LoadSpeciesPDF("BG");
 
 

  //////////////////////////////Make signal PDF
//  RF->Factory("RooHSEventsHistPDF::Sig1(M1,alpha[0,0,20],off[0,-0,0],scale[1,1,1])");
//  RooHSEventsHistPDF* pdf=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("Sig1"));
//  RF->LoadSpeciesPDF("Sig1",1); 
  //////////////////////////////Make background PDF
//  RF->Factory("RooHSEventsHistPDF::BG1(M1,alphaB[0,0,20],offB[0,0,0],scaleB[1.0,1,1])");
//  RooHSEventsHistPDF* pdfb=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("BG1"));
//  RF->LoadSpeciesPDF("BG1",1);


  // //Load weights from Mmiss fit
  RF->LoadWeights("outGammaAveTagDiffTimeProtonChannel20FilesExcludeNoCBTAPSGaus/WeightsSimple.root","HSsWeights");
  RF->SetWeightName("Signal");

  gBenchmark->Start("M1Fit");
  //Add constraints to PDF fudge parameters
  //These are derived from the alpha off and scale parameter initial val and limits
  //i.e. intital val = gaussian mean; range = 10*sigma
  // RF->AddGausConstraint(pdf->AlphaConstraint());
  // RF->AddGausConstraint(pdf->OffConstraint());
  // RF->AddGausConstraint(pdf->ScaleConstraint());
  // RF->AddGausConstraint(pdfb->AlphaConstraint());
  // RF->AddGausConstraint(pdfb->OffConstraint());
  // RF->AddGausConstraint(pdfb->ScaleConstraint());
  RF->FitSavedBins(1); //argument = number of test fits with random initial pars
  gBenchmark->Stop("M1Fit");
  gBenchmark->Print("M1Fit");
  THSWeights* wts=new THSWeights("TotalWeights");
  wts->Merge("/scratch/chris/outCoplanFromGammaAveTagDiffProtonChannelPosPol20FilesCosth1Eg1MeVBinsExcludeNoCBTAPSBifur/WeightsTopo","/scratch/chris/outCoplanFromGammaAveTagDiffProtonChannelPosPol20FilesCosth1Eg1MeVBinsExcludeNoCBTAPSBifur/WeightsTotal.root","HSsWeights");
  //  RF->SetTree(&chain);
  RF->SetWeights(wts);
//  RF->DrawTreeVar("Mmiss",100,0,10);
//  RF->DrawTreeVar("M1",100,0,10);
//  RF->DrawTreeVar("M2",100,0,10);
//  RF->DrawTreeVar("Phi",20,-180,180);


}
