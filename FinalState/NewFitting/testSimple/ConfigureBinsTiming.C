//root  --hsfit ConfigureBins.C
{


  THSRooFit* RF=new THSRooFit("SF");
  RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/BinsEmptyTargetBins1File");
  //RF->SetOutDir("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/FittingOverFlow/ProtonTiming20Bins20Files");
  ///////////////////////////////Load Variables
  RF->LoadVariable("GammaAveTagDiffTime[-80,20]");//should be same name as variable in tree 
  RF->LoadBinVars("Topo",1,0,1);//Not to be fitted but limits applied to dataset
  RF->LoadBinVars("BeamEnergy",20,300,800);//Not to be fitted but limits applied to dataset (prev was 25 bins)
  RF->LoadBinVars("DetErrs",1,-0.25,0.25);
//  RF->LoadAuxVars("InvMass[125,145]");
  RF->LoadAuxVars("Costh[-1,1]");//Not to be fitted but limits applied to dataset (prev was 20bins)
  RF->LoadAuxVars("Pol[-1,1]");
  RF->LoadAuxVars("Phi[-180,180]");
  //  RF->LoadAuxVars("InvMass[125,145]"); //Only for Neutron Case(Not used this time)

  RF->SetIDBranchName("UID");

  TChain chain("HSParticles");
  chain.Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/EmptyTarget/Dev1.0Files1PhysicsAll.root");
  //chain.Add("/w/work1/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev15.0Files1PhysicsAll.root");
  RF->MakeBinnedTrees(&chain,"Data");

}
