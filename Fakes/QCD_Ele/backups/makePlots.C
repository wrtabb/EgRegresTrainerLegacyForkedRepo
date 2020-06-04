#include "header.h"

void makePlots()
{
 gStyle->SetOptStat(0);
 gStyle->SetPalette(1);
 gROOT->SetBatch(true);
 TChain*treeBadExt;
 TChain*treeBadStd;
 TChain*treeAllExt;
 TChain*treeAllStd;

 treeBadExt = LoadTrees(EXT,BAD);
 treeBadStd = LoadTrees(STD,BAD);
 treeAllExt = LoadTrees(EXT,ALL);
 treeAllStd = LoadTrees(STD,ALL);
 
 //PtAndEtaPlots(treeBadStd,true);

 // Naming scheme for 2D hists:
 // TrainedRegion TrainedVariables PlottingRegion Barrel or Endcap
 // Example: AllStdAllEE = Trained in all regions and with standard variables, plotted all
 // in endcap
 // Others are: AllStdBadEB, where bad means it was only for regions near gaps or dead crystals
 // in the barrel
 
 MeanPlot(treeBadExt,"hBadExtBad",BAD,true);
 MeanPlot(treeBadStd,"hBadExtStd",ALL,true);
 MeanPlot(treeAllExt,"hAllExtBad",BAD,true);
 MeanPlot(treeAllStd,"hAllExtStd",ALL,true);

 TH2D*hBadExtBadEE = defineHist("hBadExtBadEE");
 TH2D*hBadExtBadEB = defineHist("hBadExtBadEB");
 TH2D*hBadStdBadEE = defineHist("hBadStdBadEE");
 TH2D*hBadStdBadEB = defineHist("hBadStdBadEB");

 TH2D*hAllExtBadEE = defineHist("hAllExtBadEE");
 TH2D*hAllExtBadEB = defineHist("hAllExtBadEB");
 TH2D*hAllStdBadEE = defineHist("hAllStdBadEE");
 TH2D*hAllStdBadEB = defineHist("hAllStdBadEB");

 TString cuts = "&& ele.energy>0 && sc.rawEnergy>0 && ele.et>0";
 TString cutsBad = 
  "&&( abs(sc.etaGapCode)!=0 || abs(sc.phiGapCode)!=0 || abs(nearbyChanStatus!=0))";
 TString cutsEEBad = "abs(ele.eta)>1.566";
 cutsEEBad += cuts;
 cutsEEBad += cutsBad;
 TString cutsEBBad = "abs(ele.eta)<1.442";
 cutsEBBad += cuts;
 cutsEBBad += cutsBad;

 treeBadExt->Draw("mean:ele.energy>>hBadExtBadEE",cutsEEBad,"colz");
 TProfile*profBadExtBadEE = defineProfile(hBadExtBadEE);
 treeBadExt->Draw("mean:ele.energy>>hBadExtBadEB",cutsEBBad,"colz");
 TProfile*profBadExtBadEB = defineProfile(hBadExtBadEB);
 treeBadStd->Draw("mean:ele.energy>>hBadStdBadEE",cutsEEBad,"colz");
 TProfile*profBadStdBadEE = defineProfile(hBadStdBadEE);
 treeBadStd->Draw("mean:ele.energy>>hBadStdBadEB",cutsEBBad,"colz");
 TProfile*profBadStdBadEB = defineProfile(hBadStdBadEB);

 treeAllExt->Draw("mean:ele.energy>>hAllExtBadEE",cutsEEBad,"colz");
 TProfile*profAllExtBadEE = defineProfile(hAllExtBadEE);
 treeAllExt->Draw("mean:ele.energy>>hAllExtBadEB",cutsEBBad,"colz");
 TProfile*profAllExtBadEB = defineProfile(hAllExtBadEB);
 treeAllStd->Draw("mean:ele.energy>>hAllStdBadEE",cutsEEBad,"colz");
 TProfile*profAllStdBadEE = defineProfile(hAllStdBadEE);
 treeAllStd->Draw("mean:ele.energy>>hAllStdBadEB",cutsEBBad,"colz");
 TProfile*profAllStdBadEB = defineProfile(hAllStdBadEB);

 TCanvas*cBadStdBadEE = defineCanvas("cBadStdBadEE");
 hBadStdBadEE->Draw("colz");
 TCanvas*cBadStdBadEB = defineCanvas("cBadStdBadEB");
 hBadStdBadEB->Draw("colz");
 TCanvas*cBadExtBadEE = defineCanvas("cBadExtBadEE");
 hBadExtBadEE->Draw("colz");
 TCanvas*cBadExtBadEB = defineCanvas("cBadExtBadEB");
 hBadExtBadEB->Draw("colz");
 
 TCanvas*cAllStdBadEE = defineCanvas("cAllStdBadEE");
 hAllStdBadEE->Draw("colz");
 TCanvas*cAllStdBadEB = defineCanvas("cAllStdBadEB");
 hAllStdBadEB->Draw("colz");
 TCanvas*cAllExtBadEE = defineCanvas("cAllExtBadEE");
 hAllExtBadEE->Draw("colz");
 TCanvas*cAllExtBadEB = defineCanvas("cAllExtBadEB");
 hAllExtBadEB->Draw("colz");

 TCanvas*cProfBadExtBadEE = defineCanvas("cProfBadExtBadEE");
 profBadExtBadEE->Draw("pe");
 TCanvas*cProfBadExtBadEB = defineCanvas("cProfBadExtBadEB");
 profBadExtBadEB->Draw("pe");
 TCanvas*cProfBadStdBadEE = defineCanvas("cProfBadStdBadEE");
 profBadStdBadEE->Draw("pe");
 TCanvas*cProfBadStdBadEB = defineCanvas("cProfBadStdBadEB");
 profBadStdBadEB->Draw("pe");

 TCanvas*cProfAllExtBadEE = defineCanvas("cProfAllExtBadEE");
 profAllExtBadEE->Draw("pe");
 TCanvas*cProfAllExtBadEB = defineCanvas("cProfAllExtBadEB");
 profAllExtBadEB->Draw("pe");
 TCanvas*cProfAllStdBadEE = defineCanvas("cProfAllStdBadEE");
 profAllStdBadEE->Draw("pe");
 TCanvas*cProfAllStdBadEB = defineCanvas("cProfAllStdBadEB");
 profAllStdBadEB->Draw("pe");
}

void MeanPlot(TChain*tree,TString title,RegionType region,bool savePlots)
{
 TString hNameEE = title+"EE";
 TString hNameEB = title+"EB";
 TH2D*histEE = defineHist(hNameEE);
 TH2D*histEB = defineHist(hNameEB);

 TString baseCuts = "&& ele.energy>0 && sc.rawEnergy>0 && ele.et>0";
 TString cutsBad = 
  "&&( abs(sc.etaGapCode)!=0 || abs(sc.phiGapCode)!=0 || abs(nearbyChanStatus!=0))";
 TString cutsEE = "abs(ele.eta)>1.566";
 cutsEE += baseCuts;
 TString cutsEB = "abs(ele.eta)<1.442";
 cutsEB += baseCuts;

 if(region==BAD){
  cutsEE += cutsBad;
  cutsEB += cutsBad;
 }

 tree->Draw("mean:ele.energy>>histEE",cutsEE,"colz");
 TProfile*profEE = defineProfile(histEE);
 tree->Draw("mean:ele.energy>>histEB",cutsEB,"colz");
 TProfile*profEB = defineProfile(histEB);

 TCanvas*canvasEE = defineCanvas("canvasEE");
 histEE->Draw("colz");
 TCanvas*canvasEB = defineCanvas("canvasEB");
 histEB->Draw("colz");
 
 TString saveNameEE = "plots/";
 saveNameEE += title;
 saveNameEE += "EE.png";
 TString saveNameEB = "plots/";
 saveNameEB += title;
 saveNameEB += "EB.png";
 if(savePlots){
  canvasEE->SaveAs(saveNameEE);
  canvasEB->SaveAs(saveNameEB);
 }
}

TChain*LoadTrees(VarType varType,RegionType regionType)
{
 TString base; 
 TChain*tree = new TChain(treeName);
 TChain*treeFriend = new TChain(friendName);
 if(regionType==BAD){
  if(varType==STD){
   for(int i=0;i<files.size();i++){
    base = "BadStd/";
    base += files.at(i);
    tree->Add(base);
    treeFriend->Add(base);
   } 
   tree->AddFriend(treeFriend);
  }
  else if(varType==EXT){
   for(int i=0;i<files.size();i++){
    base = "BadExt/";
    base += files.at(i);
    tree->Add(base);
    treeFriend->Add(base);
   }
   tree->AddFriend(treeFriend);
  }
 }//end regiontype==BAD

 if(regionType==ALL){
  if(varType==STD){
   for(int i=0;i<files.size();i++){
    base = "AllStd/";
    base += files.at(i);
    tree->Add(base);
    treeFriend->Add(base);
   } 
   tree->AddFriend(treeFriend);
  }
  else if(varType==EXT){
   for(int i=0;i<files.size();i++){
    base = "AllExt/";
    base += files.at(i);
    tree->Add(base);
    treeFriend->Add(base);
   }
   tree->AddFriend(treeFriend);
  }
 }//end regiontype==BAD
 return tree;
}

void PtAndEtaPlots(TTree*tree,bool savePlots)
{
 TH1D*hEta = new TH1D("hEta","",100,-2.4,2.4);
 TH1D*hpT = new TH1D("hpT","",500,0,10000); 

 hEta->GetXaxis()->SetTitle("electron #eta");
 hpT->GetXaxis()->SetTitle("electron p_{T}");
 tree->Draw("ele.pt>>hpT","","hist");
 tree->Draw("ele.eta>>hEta","","hist");

 TCanvas*cpT = new TCanvas("cpT","",0,0,1000,1000);
 cpT->SetLogy();
 cpT->SetGrid();
 hpT->Draw("hist");

 TCanvas*cEta = new TCanvas("cEta","",0,0,1000,1000);
 cEta->SetLogy();
 cEta->SetGrid();
 hEta->Draw("hist");
 
 if(savePlots){
  cEta->SaveAs("plots/etaSpectrum.png");
  cpT->SaveAs("plots/ptSpectrum0_10000.png");
 }
}

TCanvas*defineCanvas(TString title)
{
 TCanvas*canvas = new TCanvas(title,"",0,0,1000,1000);
 canvas->SetGrid();
 canvas->SetLogz();
 return canvas;
}

TProfile*defineProfile(TH2D*hist)
{
 TProfile*prof = hist->ProfileX();
 prof->SetMarkerStyle(20);
 prof->GetYaxis()->SetTitle("<correction>");
 return prof;
}

TH2D*defineHist(TString title)
{
 int nBinsx = 300;
 double lowx = 0;
 double highx = 16000;
 int nBinsy = 300;
 double lowy = 0.5;
 double highy = 2.5;

 TH2D*hist = new TH2D(title,"",nBinsx,lowx,highx,nBinsy,lowy,highy);
 hist->GetYaxis()->SetTitle("correction");
 hist->GetXaxis()->SetTitle("electron energy");
 hist->SetTitle(title);
 return hist;
}
