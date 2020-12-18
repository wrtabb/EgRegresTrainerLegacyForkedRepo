{
  //binning
  std::vector<double> resBins = {0.005, 0.0075, 0.01, 0.0125, 0.015, 0.0175, 0.02, 0.0225, 0.025, 0.0275, 0.03, 0.0325, 0.035, 0.0375, 0.04, 0.0425, 0.045, 0.0475, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1,0.12,0.2,0.4,0.5};
  std::vector<double> etaBins = {-3.0,-2.5,-2.0,-1.566,-1.4442,-1.0,-0.5,0.,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
  std::vector<double> absEtaBins = {0.,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
  std::vector<double> etBinsMC = {0,20,40,60,80,100};
  std::vector<double> ptOneBin = {0,100};
  std::vector<double> ptHighBin = {80,100};
  std::vector<double> puBins = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70};
  std::vector<double> puBinsCoarse = {0,20,40,60,80};
  
  //suppressing noisy fits
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL); 
  RooMsgService::instance().setSilentMode(true);
  gErrorIgnoreLevel = kError;
 
  //Directories for making trees
  std::string resultsDirectory = "/home/hep/wrtabb/Egamma/results/ThreshForECAL/";
  std::string inputDirectory = "/home/hep/wrtabb/Egamma/input_trees/ThreshForECAL/";

  //Tree names
  std::string treeMixedName = "egRegTreeMixed";
  std::string treeMixedFriendName = "egRegTreeMixedFriend";
  std::string treeRefName = "egRegTreeRef";
  std::string treeRefFriendName = "egRegTreeRefFriend";
  std::string treeName = "egRegTree34Sigma";
  std::string treeFriendName = "egRegTree34SigmaFriend";
  
  //TL150_Thr150_RegTL150TL150
  std::string TL150_Thr150_RegTL150TL150_Results = "scRegTL150_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root"; 
  std::string TL150_Thr150_RegTL150TL150_Input = "TL150/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL150_106X_mcRun3_TL150fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL150_Thr150_RegTL150TL150 = HistFuncs::makeChain(treeName,inputDirectory+TL150_Thr150_RegTL150TL150_Input,1,1,1);
  TTree*treeTL150_Thr150_RegTL150TL150Friend = HistFuncs::makeChain(treeFriendName,resultsDirectory+TL150_Thr150_RegTL150TL150_Results,1,1,1);
  treeTL150_Thr150_RegTL150TL150->AddFriend(treeTL150_Thr150_RegTL150TL150Friend); 

  //TL150_ThrMixed_RegTL150Mixed 
  std::string TL150_ThrMixed_RegTL150Mixed_Results = "scRegTL150_Mixed_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root"; 
  std::string TL150_ThrMixed_RegTL150Mixed_Input = "TL150/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL150_106X_mcRun3_TL150fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL150_ThrMixed_RegTL150Mixed = HistFuncs::makeChain(treeMixedName,inputDirectory+TL150_ThrMixed_RegTL150Mixed_Input,1,1,1);
  TTree*treeTL150_ThrMixed_RegTL150MixedFriend = HistFuncs::makeChain(treeMixedFriendName,resultsDirectory+TL150_ThrMixed_RegTL150Mixed_Results,1,1,1);
  treeTL150_ThrMixed_RegTL150Mixed->AddFriend(treeTL150_ThrMixed_RegTL150MixedFriend); 

  //TL180_ThrTL180_Regr_TL180TL180
  std::string TL180_ThrTL180_RegTL180TL180_Results = "scRegTL180_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root"; 
  std::string TL180_ThrTL180_RegTL180TL180_Input = "TL180/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL180_106X_mcRun3_TL180fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL180_ThrTL180_RegTL180TL180 = HistFuncs::makeChain(treeName,inputDirectory+TL180_ThrTL180_RegTL180TL180_Input,1,1,1);
  TTree*treeTL180_ThrTL180_RegTL180TL180Friend = HistFuncs::makeChain(treeFriendName,resultsDirectory+TL180_ThrTL180_RegTL180TL180_Results,1,1,1);
  treeTL180_ThrTL180_RegTL180TL180->AddFriend(treeTL180_ThrTL180_RegTL180TL180Friend); 

  //TL180_ThrMixed_Regr_TL150Mixed
  std::string TL180_ThrMixed_RegTL150Mixed_Results = "scReg_TL180_ThrMixed_RegTL150ThrMixed.root"; 
  std::string TL180_ThrMixed_RegTL150Mixed_Input = "TL180/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL180_106X_mcRun3_TL180fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL180_ThrMixed_RegTL150Mixed = HistFuncs::makeChain(treeMixedName,inputDirectory+TL180_ThrMixed_RegTL150Mixed_Input,1,1,1);
  TTree*treeTL180_ThrMixed_RegTL150MixedFriend = HistFuncs::makeChain(treeMixedFriendName,resultsDirectory+TL180_ThrMixed_RegTL150Mixed_Results,1,1,1);
  treeTL180_ThrMixed_RegTL150Mixed->AddFriend(treeTL180_ThrMixed_RegTL150MixedFriend); 
  
  //TL150_ThrTL180_RegTL180TL180
  std::string TL150_ThrTL180_RegTL180TL180_Results = "scReg_TL150_ThrTL180_RegTL180TL180.root"; 
  std::string TL150_ThrTL180_RegTL180TL180_Input = "TL150/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL150_106X_mcRun3_TL150fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL150_ThrTL180_RegTL180TL180 = HistFuncs::makeChain(treeRefName,inputDirectory+TL150_ThrTL180_RegTL180TL180_Input,1,1,1);
  TTree*treeTL150_ThrTL180_RegTL180TL180Friend = HistFuncs::makeChain(treeRefFriendName,resultsDirectory+TL150_ThrTL180_RegTL180TL180_Results,1,1,1);
  treeTL150_ThrTL180_RegTL180TL180->AddFriend(treeTL150_ThrTL180_RegTL180TL180Friend); 

  //TL235_ThrTL180_RegTL180TL180
  std::string TL235_ThrTL180_RegTL180TL180_Results = "scReg_TL235_ThrTL180_RegTL180TL180.root"; 
  std::string TL235_ThrTL180_RegTL180TL180_Input = "TL235/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL235_106X_mcRun3_TL235fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL235_ThrTL180_RegTL180TL180 = HistFuncs::makeChain(treeRefName,inputDirectory+TL235_ThrTL180_RegTL180TL180_Input,1,1,1);
  TTree*treeTL235_ThrTL180_RegTL180TL180Friend = HistFuncs::makeChain(treeRefFriendName,resultsDirectory+TL235_ThrTL180_RegTL180TL180_Results,1,1,1);
  treeTL235_ThrTL180_RegTL180TL180->AddFriend(treeTL235_ThrTL180_RegTL180TL180Friend); 

  //TL235_ThrTL235_RegTL235TL235
  std::string TL235_ThrTL235_RegTL235TL235_Results = "scRegTL235_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root"; 
  std::string TL235_ThrTL235_RegTL235TL235_Input = "TL235/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL235_106X_mcRun3_TL235fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL235_ThrTL235_RegTL235TL235 = HistFuncs::makeChain(treeName,inputDirectory+TL235_ThrTL235_RegTL235TL235_Input,1,1,1);
  TTree*treeTL235_ThrTL235_RegTL235TL235Friend = HistFuncs::makeChain(treeFriendName,resultsDirectory+TL235_ThrTL235_RegTL235TL235_Results,1,1,1);
  treeTL235_ThrTL235_RegTL235TL235->AddFriend(treeTL235_ThrTL235_RegTL235TL235Friend); 




   /*************************************
   #now as an example do the following, 
   #note the second tree argument is for when I was comparing to a different sample, 
   #ie 102X 2018, now we just set it to null

   ResPlotter resPlotter
   resPlotter.makeHists({regTreeEleReal2018V52018Reg,nullptr},"Real IC, 1.566< |#eta|<2.5","mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3","mc.pt","sc.seedEta",etBins,etaBins)
   resPlotter.printFits({3,5,6},"plots/regresFitsThreeComp")

   #or compare two variables 
   resPlotter.printFits({3,6},"plots/regresFitsTwoComp")
  
   ************************************/
}
