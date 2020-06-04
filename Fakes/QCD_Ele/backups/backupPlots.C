
void DrawAndSave(TH2D*hist);
TH2D*defineHist(TString title);

const vector<TString> files = {
 "QCD_2016UL_1000to1400.root",
 "QCD_2016UL_1800to2400.root",
 "QCD_2016UL_470to600.root",
 "QCD_2016UL_120to170.root",
 "QCD_2016UL_2400to3200.root",
 "QCD_2016UL_50to80.root",
 "QCD_2016UL_1400to1800.root",
 "QCD_2016UL_300to470.root",
 "QCD_2016UL_600to800.root",
 "QCD_2016UL_15to30.root",
 "QCD_2016UL_30to50.root",
 "QCD_2016UL_800to1000.root",
 "QCD_2016UL_170to300.root",
 "QCD_2016UL_3200toInf.root",
 "QCD_2016UL_80to120.root"
};
const vector<TString> titles = {
 "QCD_2016UL_1000to1400",
 "QCD_2016UL_1800to2400",
 "QCD_2016UL_470to600",
 "QCD_2016UL_120to170",
 "QCD_2016UL_2400to3200",
 "QCD_2016UL_50to80",
 "QCD_2016UL_1400to1800",
 "QCD_2016UL_300to470",
 "QCD_2016UL_600to800",
 "QCD_2016UL_15to30",
 "QCD_2016UL_30to50",
 "QCD_2016UL_800to1000",
 "QCD_2016UL_170to300",
 "QCD_2016UL_3200toInf",
 "QCD_2016UL_80to120"
};


const TString treeName = "egRegTree";
const TString friendName = "egRegTreeFriend";

void backupPlots()
{
 gStyle->SetOptStat(0);
 gStyle->SetPalette(1);

 //Trees
 TChain*treeBadExt = new TChain(treeName);
 TChain*treeBadExtFriend = new TChain(friendName);
 TChain*treeBadStd = new TChain(treeName);
 TChain*treeBadStdFriend = new TChain(friendName);
 TChain*treeAllStd = new TChain(treeName);
 TChain*treeAllStdFriend = new TChain(friendName);
  
 //Chain trees together and add friends
 // BadExt = Trained on bad regions with extended variables
 // BadStd = Trained on bad regions with standard variables
 // AllStd = Trained on all regions with standard variables
 TString base; 
 for(int i=0;i<files.size();i++){
  base = "BadExt/";
  base += files.at(i);
  treeBadExt->Add(base);
  treeBadExtFriend->Add(base);
 }
 treeBadExt->AddFriend(treeBadExtFriend);
 
 for(int i=0;i<files.size();i++){
  base = "BadStd/";
  base += files.at(i);
  treeBadStd->Add(base);
  treeBadStdFriend->Add(base);
 }
 treeBadStd->AddFriend(treeBadStdFriend);

 for(int i=0;i<files.size();i++){
  base = "AllStd/";
  base += files.at(i);
  treeAllStd->Add(base);
  treeAllStdFriend->Add(base);
 }
 treeAllStd->AddFriend(treeAllStdFriend);

/*
 //Plotting pt spectrum
 TH1D*hpT = new TH1D("hpT","",500,0,100); 
 hpT->GetXaxis()->SetTitle("electron p_{T}");
 treeAllStd->Draw("ele.pt>>hpT","","hist");
 TCanvas*cpT = new TCanvas("cpT","",0,0,1000,1000);
 cpT->SetLogy();
 cpT->SetGrid();
 hpT->Draw("hist");
 cpT->SaveAs("plots/ptSpectrum0_100.png");
*/

 // Naming scheme for 2D hists:
 // TrainedRegion TrainedVariables PlottingRegion Barrel or Endcap
 // Example: AllStdAllEE = Trained in all regions and with standard variables
 // Regression applied to all variables, plotted endcap
 // Others are: AllStdBadEB, where bad means it was only for regions near gaps or dead crystals
 // in the barrel
 TH2D*hBadExtBadEE = defineHist("hBadExtBadEE");
 TH2D*hBadExtBadEB = defineHist("hBadExtBadEB");
 TH2D*hBadStdBadEE = defineHist("hBadStdBadEE");
 TH2D*hBadStdBadEB = defineHist("hBadStdBadEB");

 TH2D*hAllStdAllEE = defineHist("hAllStdAllEE");
 TH2D*hAllStdAllEB = defineHist("hAllStdAllEB");
 TH2D*hAllStdBadEE = defineHist("hAllStdBadEE");
 TH2D*hAllStdBadEB = defineHist("hAllStdBadEB");

 TString cuts = " && ele.energy>0 && sc.rawEnergy>0 && ele.pt>0";
 TString cutsBad = 
  "&&( abs(sc.etaGapCode)!=0 || abs(sc.phiGapCode)!=0 || abs(nearbyChanStatus!=0))";
 TString cutsEEBad = "abs(ele.eta)>1.566";
 cutsEEBad += cuts;
 cutsEEBad += cutsBad;
 TString cutsEBBad = "abs(ele.eta)<1.442";
 cutsEBBad += cuts;
 cutsEBBad += cutsBad;
 TString cutsEE = "abs(ele.eta)>1.566";
 cutsEE += cuts;
 TString cutsEB = "abs(ele.eta)<1.442"; 
 cutsEB += cuts;

 treeBadExt->Draw("mean:ele.energy>>hBadExtBadEE",cutsEEBad,"colz");
 treeBadExt->Draw("mean:ele.energy>>hBadExtBadEB",cutsEBBad,"colz");
 treeBadStd->Draw("mean:ele.energy>>hBadStdBadEE",cutsEEBad,"colz");
 treeBadStd->Draw("mean:ele.energy>>hBadStdBadEB",cutsEBBad,"colz");

 treeAllStd->Draw("mean:ele.energy>>hAllStdAllEE",cutsEE,"colz");
 treeAllStd->Draw("mean:ele.energy>>hAllStdAllEB",cutsEB,"colz");
 treeAllStd->Draw("mean:ele.energy>>hAllStdBadEE",cutsEEBad,"colz");
 treeAllStd->Draw("mean:ele.energy>>hAllStdBadEB",cutsEBBad,"colz");

 DrawAndSave(hBadExtBadEE);
 DrawAndSave(hBadExtBadEB);
 DrawAndSave(hBadStdBadEE);
 DrawAndSave(hBadStdBadEB);
 DrawAndSave(hAllStdAllEE);
 DrawAndSave(hAllStdAllEB);
 DrawAndSave(hAllStdBadEE);
 DrawAndSave(hAllStdBadEB);

}

TH2D*defineHist(TString title)
{
 int nBinsx = 300;
 double lowx = 0;
 double highx = 12000;
 int nBinsy = 300;
 double lowy = 0.5;
 double highy = 2.5;

 TH2D*hist = new TH2D(title,"",nBinsx,lowx,highx,nBinsy,lowy,highy);
 hist->GetYaxis()->SetTitle("correction");
 hist->GetXaxis()->SetTitle("electron energy");
 hist->SetTitle(title);
 return hist;
}

void DrawAndSave(TH2D*hist)
{
 hist->SetFillColor(kBlue+2);
 hist->SetLineColor(kBlue+2);
 TString cName = "c";
 cName += hist->GetName();
 TString saveName = "plots/profileX_";
 saveName += hist->GetName();
 saveName += ".png";
 TProfile*prof = hist->ProfileX();
 prof->GetYaxis()->SetTitle("average correction");

 TCanvas*canvas = new TCanvas(cName,"",0,0,1000,1000);

 canvas->Divide(1,2);
 canvas->cd(1);
 hist->Draw("colz");
 canvas->cd(2);
 prof->Draw("bar");
 canvas->SaveAs(saveName);
}
