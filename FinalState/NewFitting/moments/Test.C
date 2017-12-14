{

 //Create THSRooFit manager 
  THSRooFit* RF=new THSRooFit("AFit");
  RF->SetOutDir("outRes10/"); //give output directory
 
  RF->LoadVariable("Z[-1,1]");//theta
  RF->LoadVariable("Phi[0,-3.14159,3.14159]");//phi
  Int_t LMAX=4;
  RooArgSet pars=RooHSSphHarMoments::CreateMoments(LMAX);
  RF->GetWorkSpace()->import(pars);
  RF->GetWorkSpace()->defineSet("Moments",pars);

  RooHSSphHarMoments* pdf=new RooHSSphHarMoments("YLM","YLM",*(RF->GetWorkSpace()->var("Z")) ,*(RF->GetWorkSpace()->var("Phi")),LMAX,*RF->GetWorkSpace()->set("Moments"));
  RF->GetWorkSpace()->import(*pdf);

  RF->LoadSpeciesPDF("YLM");
  RF->TotalPDF();
  // RF->GetWorkSpace()->var("MomY_1_1")->setVal(0.5);
  //RF->GetWorkSpace()->var("MomY_2_1")->setVal(-0.1);
  RF->GetWorkSpace()->var("MomY_4_2")->setVal(3.3731/10);
  RF->GetWorkSpace()->var("MomY_4_1")->setVal(4.77/20);
  //RF->GetWorkSpace()->var("MomY_4_4")->setVal(-0.7);
  RooDataSet *ds1=RF->GetModel()->generate(RooArgSet(*(RF->GetWorkSpace()->var("Z")) ,*(RF->GetWorkSpace()->var("Phi"))),100000);
  //  pdf->fitTo(*ds1,RooFit::Extended());
  //  RF->LoadDataSet(ds1);
  ds1->createHistogram(*(RF->GetWorkSpace()->var("Z")) ,*(RF->GetWorkSpace()->var("Phi")),50,50)->Draw("col1");
  new TCanvas();
  ((TH2F*)RF->GetModel()->createHistogram("Z,Phi",50,50))->Draw("col1");
  // RooFormulaVar penalty("penalty","100*((1-MomY_1_0-MomY_1_1-MomY_2_0-MomY_2_1-MomY_1_1)<0)",*RF->GetWorkSpace()->set("Moments")) ;
  // RooAbsReal* igx = RF->GetModel()->createIntegral() ;
  // RooAbsReal* nll = RF->GetModel()->createNLL(*ds1,RF->GetFitOptions()) ;
  // RooAddition nllp("nllp","nllp",RooArgSet(*nll,penalty)) ;
  // RooMinuit m(nllp) ;
  // m.migrad() ;
  // m.hesse() ;
  //  RF->FitAndStudy(1);
  
  // RooPlot *frame=RF->GetWorkSpace()->var("Z")->frame();
  // pdf->plotOn(frame);
  // frame->Draw();

  
}
