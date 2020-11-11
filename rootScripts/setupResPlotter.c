{
  //binning
  std::vector<double> resBins = {0.005, 0.0075, 0.01, 0.0125, 0.015, 0.0175, 0.02, 0.0225, 0.025, 0.0275, 0.03, 0.0325, 0.035, 0.0375, 0.04, 0.0425, 0.045, 0.0475, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1,0.12,0.2,0.4,0.5};
  std::vector<double> etaBins = {-3.0,-2.5,-2.0,-1.566,-1.4442,-1.0,-0.5,0.,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
  std::vector<double> absEtaBins = {0.,0.5,1.0,1.4442,1.566,2.0,2.5,3.0};
  std::vector<double> etBins = {0,20,40,60,80,100};
  std::vector<double> ptOneBin = {0,100};
  std::vector<double> puBins = {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70};
  
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
  std::string treeName = "egRegTree34Sigma";
  std::string treeFriendName = "egRegTree34SigmaFriend";
  
  //TL150 Mixed 
  std::string TL150MixedName_Results = "scRegTL150_Mixed_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root"; 
  std::string TL150MixedName_Input = "TL150/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL150_106X_mcRun3_TL150fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL150_Mixed = HistFuncs::makeChain(treeMixedName,inputDirectory+TL150MixedName_Input,1,1,1);
  TTree*treeTL150_MixedFriend = HistFuncs::makeChain(treeMixedFriendName,resultsDirectory+TL150MixedName_Results,1,1,1);
  treeTL150_Mixed->AddFriend(treeTL150_MixedFriend); 

  //TL150 
  std::string TL150Name_Results = "scRegTL150_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root"; 
  std::string TL150Name_Input = "TL150/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL150_106X_mcRun3_TL150fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL150 = HistFuncs::makeChain(treeName,inputDirectory+TL150Name_Input,1,1,1);
  TTree*treeTL150Friend = HistFuncs::makeChain(treeFriendName,resultsDirectory+TL150Name_Results,1,1,1);
  treeTL150->AddFriend(treeTL150Friend); 

  //TL180
  std::string TL180Name_Results = "scRegTL180_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root"; 
  std::string TL180Name_Input = "TL180/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL180_106X_mcRun3_TL180fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL180 = HistFuncs::makeChain(treeName,inputDirectory+TL180Name_Input,1,1,1);
  TTree*treeTL180Friend = HistFuncs::makeChain(treeFriendName,resultsDirectory+TL180Name_Results,1,1,1);
  treeTL180->AddFriend(treeTL180Friend); 

  //TL235
  std::string TL235Name_Results = "scRegTL235_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root"; 
  std::string TL235Name_Input = "TL235/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL235_106X_mcRun3_TL235fb_realistic_v1_ext1-v1_EGRegNtups.root"; 
  TTree*treeTL235 = HistFuncs::makeChain(treeName,inputDirectory+TL235Name_Input,1,1,1);
  TTree*treeTL235Friend = HistFuncs::makeChain(treeFriendName,resultsDirectory+TL235Name_Results,1,1,1);
  treeTL235->AddFriend(treeTL235Friend); 




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
