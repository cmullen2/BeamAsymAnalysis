//Run with 
//root --hsfit FitHSSimpleBins2.C
{
  THSsPlot* RF=new THSsPlot("binFit");
  RF->SetOutDir("outBins2/");
 ///////////////////////////////Load Variables
  RF->LoadVariable("Mmiss[0,10]");//should be same name as variable in tree
  RF->LoadBinVars("Eg",1,3,4);//should be same name as variable in tree 
  RF->LoadBinVars("M1",4,0,10);//should be same name as variable in tree 
   ///////////////////////////Load Data
  TChain chain("MyModel");
  chain.Add("Data.root");
  RF->SetIDBranchName("fgID");
  RF->MakeBinnedTrees(&chain,"Data");
  // RF->ConfigureSavedBins(RF->GetOutDir());
  
  /////////////////////////////Make Model Signal
  RF->Factory("Gaussian::Signal( Mmiss, SIMm[6,4,7], SIMw[0.2,0.0001,3] )");
  RF->LoadSpeciesPDF("Signal");

  ////////////////////////////////Additional background
  RF->Factory("Chebychev::BG(Mmiss,{a0[0.1,-0.4,0.4],a1[-0.1,-0.3,0.3]})");
  RF->LoadSpeciesPDF("BG");

  gBenchmark->Start("Binned");
  RF->RunWeights(2);//argument gives number of parameter fits to perform
  RF->DrawTreeVar("M1",100,0,10);
  RF->DrawTreeVar("M2",100,0,10);
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");

  //chain deleted so recreate for extra plots  
  TChain chain2("MyModel");
  chain2.AddFile("Data.root");

  //save the weights in one combined file
  //Note already saved in individual bins 
  RF->GetWeights()->Save();


}
