{

 //Create THSRooFit manager 
  THSRooFit* RF=new THSRooFit("AFit");
  RF->SetOutDir("out/"); //give output directory
 
  RF->LoadVariable("Z[-1,1]");//theta
  RF->LoadVariable("Phi[0,-3.14159,3.14159]");//phi
  Int_t LMAX=4;
  RooArgSet pars=RooHSSphHarMoments::CreateMoments(LMAX);
  RF->GetWorkSpace()->import(pars);
  RF->GetWorkSpace()->defineSet("Moments",pars);

  RooHSSphHarMoments* pdf=new RooHSSphHarMoments("YLM","YLM",*(RF->GetWorkSpace()->var("Z")) ,*(RF->GetWorkSpace()->var("Phi")),LMAX,*RF->GetWorkSpace()->set("Moments"));
  TChain chain("decayAngles");
  chain.Add("events.root");
  
  pdf->SetEvTree(&chain);
  pdf->SetUseWeightsGen(kFALSE);
  RF->GetWorkSpace()->import(*pdf);
  RF->LoadSpeciesPDF("YLM");
  RF->TotalPDF();
  RF->GetWorkSpace()->var("MomY_4_2")->setVal(3.3731/10);
  RF->GetWorkSpace()->var("MomY_4_1")->setVal(4.77/20);
  RooDataSet *ds1=RF->GetModel()->generate(RF->GetVariables(),1000);
  RF->LoadDataSet(ds1);
  ds1->createHistogram(*(RF->GetWorkSpace()->var("Z")) ,*(RF->GetWorkSpace()->var("Phi")),50,50)->Draw("col1");
  new TCanvas();
  ((TH2F*)RF->GetModel()->createHistogram("Z,Phi",50,50))->Draw("col1");
  RF->FitAndStudy(1);

  new TCanvas();
  ((TH2F*)RF->GetModel()->createHistogram("Z,Phi",50,50))->Draw("col1");

}
