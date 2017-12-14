//root  --hsfit ConfigureBins.C
{


  THSRooFit* RF=new THSRooFit("SF");
  RF->SetOutDir("/scratch/chris/outCoplanNeutronChannelPosPol20FilesCosth20Eg20MeVBinsSavedBins/");
  ///////////////////////////////Load Variables
  RF->LoadVariable("Coplanarity[-80,80]");//should be same name as variable in tree 
  RF->LoadBinVars("Topo",1,-1,0);//Not to be fitted but limits applied to dataset
  RF->LoadBinVars("Pol",1,0,1);
  RF->LoadBinVars("BeamEnergy",20,300,800);//Not to be fitted but limits applied to dataset (prev was 25 bins)
  RF->LoadBinVars("Costh",20,-1,1);//Not to be fitted but limits applied to dataset (prev was 20bins)
  RF->LoadAuxVars("Phi[-180,180]");
  //  RF->LoadAuxVars("InvMass[125,145]"); //Only for Neutron Case(Not used this time)
  RF->LoadAuxVars("DetErrs[-0.25,0.25]");
  RF->SetIDBranchName("UID");

  TChain chain("HSParticles");
  chain.Add("/w/work14/home/chris/LatestAnalysisRuns/Data/DataJul17/HaspectOutput/TestMulti/Dev13.0Files20PhysicsAllV2.root");
  RF->MakeBinnedTrees(&chain,"Data");

}
