
void plot(bool etPlot,bool etaPlot,bool dcbFit);

void resECALvsTrkPlot()
{
 //Double crystal ball fit option (default is Cruijff)
 bool dcbFit = true;
 bool plotEt = true;
 bool plotEta = true;

 gSystem->Exec("gmake RegressionTrainerExe -j 8");
 gSystem->Exec("gmake RegressionApplierExe -j 8");

 gROOT->ProcessLine("gROOT->SetBatch(true)");
 gROOT->ProcessLine(".x rootScripts/setupResPlotter2018UL.c");

 plot(plotEt,plotEta,dcbFit);
}

void plot(bool etPlot,bool etaPlot,bool dcbFit)
{
 gROOT->ProcessLine("ResPlotter res");
 if(dcbFit) gROOT->ProcessLine("res.setFitType(ResFitter::FitType::DCB)");

 if(etPlot){
  gROOT->ProcessLine("res.makeHists({treeEleStep3,treeEleStep4},\"Barrel\",\"abs(sc.seedEta)<1.442 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBins)");
  gROOT->ProcessLine("res.printFits({2,4,5},\"../plots/resECALvsTrk_2018UL_v2/Et_EB_\")");

  gROOT->ProcessLine("res.makeHists({treeEleStep3,treeEleStep4},\"Endcap\",\"abs(sc.seedEta)>1.566 && mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"mc.pt\",ptOneBin,etBins)");
  gROOT->ProcessLine("res.printFits({2,4,5},\"../plots/resECALvsTrk_2018UL_v2/Et_EE_\")");
 }//end etPlot

 if(etaPlot){
  gROOT->ProcessLine("res.makeHists({treeEleStep3,treeEleStep4},\"\",\"mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && eventnr%5>=3\",\"mc.pt\",\"abs(sc.seedEta)\",etBins32AndUp,absEtaBins)");
  gROOT->ProcessLine("res.printFits({2,4,5},\"../plots/resECALvsTrk_2018UL_v2/Eta_\")");
 }//end etaPlot


}
