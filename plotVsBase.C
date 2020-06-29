
void plotEleECAL(bool etaPlot, bool puPlot, bool ePlot, bool dcbFit);
void plotEleEP(bool etaPlot, bool puPlot, bool ePlot, bool dcbFit);
void plotSC(bool etaPlot, bool puPlot, bool ePlot, bool dcbFit);
void plotPho(bool etaPlot,bool puPlot,bool ePlot,bool dcbFit);

void plotVsBase()
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
 gROOT->ProcessLine(".x rootScripts/setupBaseComparison.c");

 //plotEleECAL(etaPlot,puPlot,ePlot,dcbFit);
 //plotEleEP(etaPlot,puPlot,ePlot,dcbFit);
 //plotSC(etaPlot,puPlot,ePlot,dcbFit);
 plotPho(etaPlot,puPlot,ePlot,dcbFit);
}

void plotEleECAL(bool etaPlot, bool puPlot, bool ePlot,bool dcbFit)
{
 gROOT->ProcessLine("ResPlotter res1");
 if(dcbFit) gROOT->ProcessLine("res1.setFitType(ResFitter::FitType::DCB)");
 //Eta
 if(etaPlot){
  gROOT->ProcessLine("res1.makeHists({treeBaseStep3Ele,treeTL180Step3Ele,treeTL235Step3Ele},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBins,absEtaBins3)");
  gROOT->ProcessLine("res1.printFits({0,1,2},\"../plots/PFRechit/ECAL_Eta_\")");
 }

 //Pileup
 if(puPlot){
  gROOT->ProcessLine("res1.makeHists({treeBaseStep3Ele,treeTL180Step3Ele,treeTL235Step3Ele},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",etOneBin,puBins)");
  gROOT->ProcessLine("res1.printFits({0,1,2},\"../plots/PFRechit/ECAL_PU_EB_\")");

  gROOT->ProcessLine("res1.makeHists({treeBaseStep3Ele,treeTL180Step3Ele,treeTL235Step3Ele},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",etOneBin,puBins)");
  gROOT->ProcessLine("res1.printFits({0,1,2},\"../plots/PFRechit/ECAL_PU_EE_\")");
 }

 //Et
 if(ePlot){
  gROOT->ProcessLine("res1.makeHists({treeBaseStep3Ele,treeTL180Step3Ele,treeTL235Step3Ele},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",etOneBin,etBins)");
  gROOT->ProcessLine("res1.printFits({0,1,2},\"../plots/PFRechit/ECAL_Et_EB_\")");

  gROOT->ProcessLine("res1.makeHists({treeBaseStep3Ele,treeTL180Step3Ele,treeTL235Step3Ele},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",etOneBin,etBins)");
  gROOT->ProcessLine("res1.printFits({0,1,2},\"../plots/PFRechit/ECAL_Et_EE_\")");
 }
}

void plotEleEP(bool etaPlot, bool puPlot, bool ePlot,bool dcbFit)
{
 gROOT->ProcessLine("ResPlotter res2");
 if(dcbFit) gROOT->ProcessLine("res2.setFitType(ResFitter::FitType::DCB)");
 //Eta
 if(etaPlot){
  gROOT->ProcessLine("res2.makeHists({treeBaseStep4Ele,treeTL180Step4Ele,treeTL235Step4Ele},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBins,absEtaBins3)");
  gROOT->ProcessLine("res2.printFits({0,1,2},\"../plots/PFRechit/EP_Eta_\")");
 }

 //Pileup
 if(puPlot){
  gROOT->ProcessLine("res2.makeHists({treeBaseStep4Ele,treeTL180Step4Ele,treeTL235Step4Ele},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",etOneBin,puBins)");
  gROOT->ProcessLine("res2.printFits({0,1,2},\"../plots/PFRechit/EP_PU_EB_\")");

  gROOT->ProcessLine("res2.makeHists({treeBaseStep4Ele,treeTL180Step4Ele,treeTL235Step4Ele},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",etOneBin,puBins)");
  gROOT->ProcessLine("res2.printFits({0,1,2},\"../plots/PFRechit/EP_PU_EE_\")");
 }

 //Et
 if(ePlot){
  gROOT->ProcessLine("res2.makeHists({treeBaseStep4Ele,treeTL180Step4Ele,treeTL235Step4Ele},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",etOneBin,etBins)");
  gROOT->ProcessLine("res2.printFits({0,1,2},\"../plots/PFRechit/EP_Et_EB_\")");

  gROOT->ProcessLine("res2.makeHists({treeBaseStep4Ele,treeTL180Step4Ele,treeTL235Step4Ele},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",etOneBin,etBins)");
  gROOT->ProcessLine("res2.printFits({0,1,2},\"../plots/PFRechit/EP_Et_EE_\")");
 }
}

void plotSC(bool etaPlot, bool puPlot, bool ePlot,bool dcbFit)
{
 gROOT->ProcessLine("ResPlotter res3");
 if(dcbFit) gROOT->ProcessLine("res3.setFitType(ResFitter::FitType::DCB)");
 //Eta
 if(etaPlot){
  gROOT->ProcessLine("res3.makeHists({treeBaseStep3SC,treeTL180Step3SC,treeTL235Step3SC},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBins,absEtaBins3)");
  gROOT->ProcessLine("res3.printFits({0,1,2},\"../plots/PFRechit/SC_Eta_\")");
 }

 //Pileup
 if(puPlot){
  gROOT->ProcessLine("res3.makeHists({treeBaseStep3SC,treeTL180Step3SC,treeTL235Step3SC},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",etOneBin,puBins)");
  gROOT->ProcessLine("res3.printFits({0,1,2},\"../plots/PFRechit/SC_PU_EB_\")");

  gROOT->ProcessLine("res3.makeHists({treeBaseStep3SC,treeTL180Step3SC,treeTL235Step3SC},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",etOneBin,puBins)");
  gROOT->ProcessLine("res3.printFits({0,1,2},\"../plots/PFRechit/SC_PU_EE_\")");
 }

 //Et
 if(ePlot){
  gROOT->ProcessLine("res3.makeHists({treeBaseStep3SC,treeTL180Step3SC,treeTL235Step3SC},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",etOneBin,etBins)");
  gROOT->ProcessLine("res3.printFits({0,1,2},\"../plots/PFRechit/SC_Et_EB_\")");

  gROOT->ProcessLine("res3.makeHists({treeBaseStep3SC,treeTL180Step3SC,treeTL235Step3SC},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",etOneBin,etBins)");
  gROOT->ProcessLine("res3.printFits({0,1,2},\"../plots/PFRechit/SC_Et_EE_\")");
 }
}

void plotPho(bool etaPlot, bool puPlot, bool ePlot,bool dcbFit)
{
 gROOT->ProcessLine("ResPlotter res4");
 if(dcbFit) gROOT->ProcessLine("res4.setFitType(ResFitter::FitType::DCB)");
 //Eta
 if(etaPlot){
  gROOT->ProcessLine("res4.makeHists({treeBasePho,treeTL180Pho,treeTL235Pho},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBins,absEtaBins3)");
  gROOT->ProcessLine("res4.printFits({0,1,2},\"../plots/PFRechit/unNormPHO_Eta_\")");
 }

 //Pileup
 if(puPlot){
  gROOT->ProcessLine("res4.makeHists({treeBasePho,treeTL180Pho,treeTL235Pho},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",etOneBin,puBins)");
  gROOT->ProcessLine("res4.printFits({0,1,2},\"../plots/PFRechit/unNormPHO_PU_EB_\")");

  gROOT->ProcessLine("res4.makeHists({treeBasePho,treeTL180Pho,treeTL235Pho},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"nrVert\",etOneBin,puBins)");
  gROOT->ProcessLine("res4.printFits({0,1,2},\"../plots/PFRechit/unNormPHO_PU_EE_\")");
 }

 //Et
 if(ePlot){
  gROOT->ProcessLine("res4.makeHists({treeBasePho,treeTL180Pho,treeTL235Pho},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",etOneBin,etBins)");
  gROOT->ProcessLine("res4.printFits({0,1,2},\"../plots/PFRechit/unNormPHO_Et_EB_\")");

  gROOT->ProcessLine("res4.makeHists({treeBasePho,treeTL180Pho,treeTL235Pho},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",etOneBin,etBins)");
  gROOT->ProcessLine("res4.printFits({0,1,2},\"../plots/PFRechit/unNormPHO_Et_EE_\")");
 }
}
