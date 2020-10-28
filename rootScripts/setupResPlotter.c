{
  //binning
  std::vector<double> resBins = {0.005, 0.0075, 0.01, 0.0125, 0.015, 0.0175, 0.02, 0.0225, 0.025, 0.0275, 0.03, 0.0325, 0.035, 0.0375, 0.04, 0.0425, 0.045, 0.0475, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.09, 0.1,0.12,0.2,0.4,0.5};
  std::vector<double> etaBins = {0.,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.4442,1.566,1.7,1.8,1.9,2.,2.25,2.5,2.75,3.0};
  std::vector<double> etBins = {10,20,30,40,50,60,70,80,90,100};
  std::vector<double> absEtaBins2p5 = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.4442,1.566,1.7,1.8,1.9,2.0,2.25,2.5};

  
  //suppressing noisy fits
  RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL); 
  RooMsgService::instance().setSilentMode(true);
  gErrorIgnoreLevel = kError;
 
  //Directories for making trees
  std::string resultsDirectory = "/home/hep/wrtabb/Egamma/results/ThreshForECAL";
  std::string inputDirectory = "/home/hep/wrtabb/Egamma/input_trees/ThreshForECAL";

  //root file names 
  std::string TL150MixedName_Results = "scRegTL150_Mixed_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root"; 
  std::string TL150MixedName_Input = "DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL150_106X_mcRun3_TL150fb_realistic_v1_ext1-v1_EGRegNtups.root"; 

 TTree*treeTL150_Mixed = HistFuncs::makeChain("egRegTree150Mixed",inputDirectory+TL150MixedName_Input,1,1,1);
 TTree*treeTL150_MixedFriend = HistFuncs::makeChain("egRegTree150MixedFriend",resultsEle+TL150MixedName_Results,1,1,1);
 treeTL150_Mixed->AddFriend(treeTL150_MixedFriend); 



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
