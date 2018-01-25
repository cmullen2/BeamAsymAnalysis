{
  THSSkeleton* sk=new THSSkeleton();
  //Give your project a name
  sk->SetFinalState("Proj_PiPlusN",kTRUE);  //creating the project class with perms
  //Set the detected particle combinations you will analyse
//  sk->SetProjectTopo("pi+:pi-,pi+:pi-:pi0,proton:pi+:pi-:pi0");
  sk->SetFinalStateTopo("pi+:neutron");
  //Set the actual final state particles of the reaction
  //These will just be used as the data member names
 // sk->SetProjectFinal("Electron:e-,Proton:proton,Pip:pi+,Pim:pi-");
  sk->SetFinalStateParts("Neutron:neutron,Pip:pi+");
  //Make some code
  sk->CreateMyFinalState(); 
}
