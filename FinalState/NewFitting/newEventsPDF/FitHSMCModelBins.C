{


  THSsPlot* RF=new THSsPlot("SF");
  RF->SetOutDir("outBins/"); //dir to save all the split trees and results
  ///////////////////////////////Load Variables
  RF->LoadVariable("Mmiss[0,9.5]");//should be same name as variable in tree 
  RF->LoadBinVars("Eg",3,3,3.3);//a vairiable to split data in i,e, 3 bins between 3 and 3.3 
  RF->SetIDBranchName("fgID");  //branch containing unique id value for each event
  RooRealVar * var=RF->GetWorkSpace()->var("Mmiss");
  var->setBins(100);  //number of bins used in PDF histogram 

  //Split data into bins
  //MC signal
  TChain *chainmc=new TChain("MyModel","mcsignal");
  chainmc->Add("SigData.root");
  RF->MakeBinnedTrees(chainmc,"Sig");
  //MC background
  TChain *chainmcb=new TChain("MyModel","mcsignal");
  chainmcb->Add("BGData.root");
  RF->MakeBinnedTrees(chainmcb,"BG");
  //data to be fitted
  TChain chain("MyModel");
  chain.Add("Data.root");
  RF->MakeBinnedTrees(&chain,"Data");
  RF->ConfigureSavedBins("outBins/"); 

  //////////////////////////////Make signal PDF
  RF->Factory("RooHSEventsHistPDF::Sig(Mmiss,alpha[0,0,2],off[0,-2,2],scale[1,0.8,1.2])");
  RooHSEventsHistPDF* pdf=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("Sig"));
  RF->LoadSpeciesPDF("Sig",1);
  //////////////////////////////Make background PDF
  RF->Factory("RooHSEventsHistPDF::BG(Mmiss,alphaB[0,0,5],offB[0,0,0],scaleB[1,0.9,1.2])");
  RooHSEventsHistPDF* pdfb=dynamic_cast<RooHSEventsHistPDF*>(RF->GetWorkSpace()->pdf("BG"));
  RF->LoadSpeciesPDF("BG",1);

  gBenchmark->Start("Binned");
  //Add constraints to PDF fudge parameters
  //These are derived from the alpha off and scale parameter initial val and limits
  //i.e. intital val = gaussian mean; range = 10*sigma 
  RF->AddGausConstraint(pdf->AlphaConstraint());
  RF->AddGausConstraint(pdf->OffConstraint());
  RF->AddGausConstraint(pdf->ScaleConstraint());
  RF->AddGausConstraint(pdfb->AlphaConstraint());
  RF->AddGausConstraint(pdfb->OffConstraint());
  RF->AddGausConstraint(pdfb->ScaleConstraint());
  RF->FitSavedBins(1);//argument = number of test fits with random initial pars
  gBenchmark->Stop("Binned");
  gBenchmark->Print("Binned");
  
}
