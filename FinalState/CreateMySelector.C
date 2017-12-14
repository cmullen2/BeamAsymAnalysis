{
  THSSkeleton* ske=new THSSkeleton();
  //Give your project a name
 // ske->SetHisto();
  ske->SetNewTree();
//  ske->SetAppendTree();
//  ske->SetWeights();
  HSfinal("THSProj_Pi0N");
//  ske->SetProject(HSproj(),kTRUE); 
  ske->SetFinalState(HSfinal(),kTRUE); 
 // ske->CreateSelector("Selected","/w/work14/chris/ForBonn/Neutron/ChrisGoatOut/Perp/TestHaspect/Physics_CBTaggTAPS_15156.root","Particles");
//  ske->CreateSelector("Selected","/w/work14/chris/Run101016/ChrisOutput/Para/LinPolTests/RootinoPhi/Physics_CBTaggTAPS_14919.root","HSParticles");
  ske->CreateSelector("Selected","/w/work14/chris/LatestAnalysisRuns/Data/DataJul17/ChrisOutput/MixedParaPerp/Physics_CBTaggTAPS_14975.root","HSParticles");
 //creating the project class with perms
  //Set the detected particle combinations you will analyse
//  sk->SetProjectTopo("pi+:pi-,pi+:pi-:pi0,proton:pi+:pi-:pi0");
 // ske->SetProjectTopo("photon:photon:photon,proton:photon:photon");
  //Set the actual final state particles of the reaction
  //These will just be used as the data member names
 // sk->SetProjectFinal("Electron:e-,Proton:proton,Pip:pi+,Pim:pi-");
//  ske->SetProjectFinal("Photon:photon");
  //Make some code
//  ske->CreateMyProject(); 
}
