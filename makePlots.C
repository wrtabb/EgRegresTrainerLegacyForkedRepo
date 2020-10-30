
void plot(bool etaPlot, bool puPlot, bool ePlot, bool dcbFit);

void makePlots()
{
 //-----parameters-----//
 //Which plots to plot
 bool etaPlot = true;
 bool puPlot = true;
 bool ePlot = true;
 //Double crystal ball fit option (default is Cruijff)
 bool dcbFit = true;

 gSystem->Exec("gmake RegressionTrainerExe -j 8");
 gSystem->Exec("gmake RegressionApplierExe -j 8");

 gROOT->ProcessLine("gROOT->SetBatch(true)");
 gROOT->ProcessLine(".x rootScripts/setupResPlotter.c");

 plot(etaPlot,puPlot,ePlot,dcbFit);
}

void plot(bool etaPlot, bool puPlot, bool ePlot,bool dcbFit)
{
 gROOT->ProcessLine("ResPlotter res");
 if(dcbFit) gROOT->ProcessLine("res.setFitType(ResFitter::FitType::DCB)");
 //Eta
 if(etaPlot){
/*
  //TL150 Mixed
  gROOT->ProcessLine("res.makeHists({treeTL150_Mixed,nullptr,nullptr,nullptr},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"sc.seedEta\",etBins,etaBins)");
  gROOT->ProcessLine("res.printFits({1,2},\"../plots/ThreshForECAL/TL150Mixed/Eta_\")");

  //TL150
  gROOT->ProcessLine("res.makeHists({treeTL150,nullptr,nullptr,nullptr},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"sc.seedEta\",etBins,etaBins)");
  gROOT->ProcessLine("res.printFits({1,2},\"../plots/ThreshForECAL/TL150/Eta_\")");

  //TL180
  gROOT->ProcessLine("res.makeHists({treeTL180,nullptr,nullptr,nullptr},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"sc.seedEta\",etBins,etaBins)");
  gROOT->ProcessLine("res.printFits({1,2},\"../plots/ThreshForECAL/TL180/Eta_\")");

  //TL235
  gROOT->ProcessLine("res.makeHists({treeTL235,nullptr,nullptr,nullptr},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"sc.seedEta\",etBins,etaBins)");
  gROOT->ProcessLine("res.printFits({1,2},\"../plots/ThreshForECAL/TL235/Eta_\")");
*/
  //All Four
  gROOT->ProcessLine("res.makeHists({treeTL150_Mixed,treeTL150,treeTL180,treeTL235},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && eventnr%5>=3\",\"mc.pt\",\"sc.seedEta\",etBins,etaBins)");
  gROOT->ProcessLine("res.printFits({2,5,8,11},\"../plots/ThreshForECAL/AllFour/Eta_\")");

 }
/*
 //Pileup
 if(puPlot){
  gROOT->ProcessLine("res.makeHists({treeEleStep3,treeEleStep4},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",ptOneBin,puBins)");
  gROOT->ProcessLine("res.printFits({1,2,3},\"../plots/2016UL/PU_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeEleStep3,treeEleStep4},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",ptOneBin,puBins)");
  gROOT->ProcessLine("res.printFits({1,2,3},\"../plots/2016UL/PU_EE_\")");
 }

 //Et
 if(ePlot){
  gROOT->ProcessLine("res.makeHists({treeEleStep3,treeEleStep4},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBins)");
  gROOT->ProcessLine("res.printFits({1,2,3},\"../plots/2016UL/Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeEleStep3,treeEleStep4},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && sc.rawEnergy>0 && ssFrac.sigmaIEtaIEta>0 && mc.dR<0.1 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBins)");
  gROOT->ProcessLine("res.printFits({1,2,3},\"../plots/2016UL/Et_EE_\")");
 }
*/
}
