
#include "header.h"
std::vector<TString> region = {
 "AllStd",
 "AllExt",
 "BadStd",
 "BadExt"
};
enum Variable{
 ENERGY,
 ET,
 ETA
};
enum LepType{
 ELE,
 FAKES
};
struct EleStruct {
 float et,energy,energyErr,ecalEnergy,ecalEnergyErr,eta,phi,trkEtaMode,trkPhiMode,trkPMode,
 trkPModeErr,fbrem,corrMean,corrSigma,hademTow,hademCone,trkPInn,trkPtInn,trkPVtx,trkPOut,
 trkChi2,trkNDof,ecalDrivenSeed,nrSatCrys,scRawEnergy,scRawESEnergy;
};
struct MCStruct {
  float energy,pt,eta,phi,pdgId,status,dR;
 };
void MakePlots(Variable var,TString savePrefix,int nBinsX,double lowBinX,double highBinX,int nBinxY,double lowBinY,double highBinY,TString fileLocation,LepType lepType);
double energybins[] = {
 10,
 12.58925412,
 15.84893192,
 19.95262315,
 25.11886432,
 31.6227766,
 39.81071706,
 50.11872336,
 63.09573445,
 79.43282347,
 100,
 125.8925412,
 158.4893192,
 199.5262315,
 251.1886432,
 316.227766,
 398.1071706,
 501.1872336,
 630.9573445,
 794.3282347,
 1000,
 1258.925412,
 1584.893192,
 1995.262315,
 2511.886432,
 3162.27766,
 3981.071706,
 5011.872336,
 6309.573445,
 7943.282347,
 10000,
 12589.25412,
 15848.93192
};
int nEnergyBins = 32;
std::vector<Color_t> hColor = {
 kRed,
 kMagenta,
 kBlue,
 kCyan,
 kYellow,
 kRed+2,
 kMagenta+2,
 kCyan+3,
 kOrange+2,
 kGreen+2
};

void savePlots()
{
 gROOT->SetBatch(true);
 gStyle->SetPalette(1);
 gStyle->SetOptStat(0);
 
 TH1::SetDefaultSumw2();
 TTimeStamp ts_start;
 cout << "[Start Time(local time): " << ts_start.AsString("l") << "]" << endl;
 TStopwatch totaltime;
 totaltime.Start();

 bool realIC = false;
 for(int i=0;i<region.size();i++){
  MakePlots(ETA,"etaHists",100,-2.5,2.5,100,0,2.2,region.at(i),ELE,realIC);
  MakePlots(ENERGY,"energyHists",100,0,12000,100,0,2.2,region.at(i),ELE,realIC);
  MakePlots(ET,"etHists",100,0,12000,100,0,2.2,region.at(i),ELE,realIC);
  MakePlots(ETA,"etaHists",100,-2.5,2.5,100,0,2.2,region.at(i),FAKES,realIC);
  MakePlots(ENERGY,"energyHists",100,0,12000,100,0,2.2,region.at(i),FAKES,realIC);
  MakePlots(ET,"etHists",100,0,12000,100,0,2.2,region.at(i),FAKES,realIC);
 }

 totaltime.Stop();
 Double_t TotalCPURunTime = totaltime.CpuTime();
 Double_t TotalRunTime = totaltime.RealTime();
 TTimeStamp ts_end;
 cout << endl;
 cout << "**************************************************************************" << endl;
 cout << "Total CPU RunTime: " << TotalCPURunTime/60 << " minutes" << endl;
 cout << "Total Real RunTime: " << TotalRunTime/60 << " minutes" << endl;
 cout << "[End Time(local time): " << ts_end.AsString("l") << "]" << endl;
 cout << "**************************************************************************" << endl;
 cout << endl;
}

void MakePlots(Variable var,TString savePrefix,int nBinsX,double lowBinX,double highBinX,int nBinxY,double lowBinY,double highBinY,TString fileLocation,LepType lepType,bool realIC)
{
 float mean;
 float fill;
 int nChains;
 vector<TString> titles;
 if(lepType==FAKES){
  titles = filesQCD;
 }
 else if(lepType==ELE){
  if(realIC) titles = filesELEReal; 
  else titles = filesELEIdeal;
 }
 nChains = titles.size();
 EleStruct eleObject;
 MCStruct mcObject;
 TTree*chain[nChains];
 TTree*chainFriend[nChains];
 TBranch*b_ele;
 TBranch*b_mean;

 TString saveName;
 TString namePrefix = "h";
 if(var==ENERGY)   namePrefix = "Energy";
 else if(var==ET)  namePrefix = "Et";
 else if(var==ETA) namePrefix = "Eta";

 TString histCombinedName = namePrefix+"All";
 TString hist2DName = "MeanVs"+namePrefix;

 TH1D*hist[nChains];
 TH1D*histCombined;
 TH2D*hist2D;

 if(var==ENERGY || var==ET){
  histCombined = new TH1D(histCombinedName,"",nEnergyBins,energybins);
  hist2D = new TH2D(hist2DName,"",nEnergyBins,energybins,nBinxY,lowBinY,highBinY);
 }
 else{
  histCombined = new TH1D(histCombinedName,"",nBinsX,lowBinX,highBinX);
  hist2D = new TH2D(hist2DName,"",nBinsX,lowBinX,highBinX,nBinxY,lowBinY,highBinY);
 } 

 histCombined->SetMinimum(0.1);
 histCombined->SetMaximum(1e7);
 histCombined->GetXaxis()->SetTitle(namePrefix);
 hist2D->GetXaxis()->SetTitle(namePrefix);
 hist2D->GetYaxis()->SetTitle("correction");

 for(int i=0;i<nChains;i++){
  TString histName = namePrefix;
  histName += titles.at(i);

  if(var==ENERGY || var==ET) hist[i] = new TH1D(histName,"",nEnergyBins,energybins);
  else hist[i] = new TH1D(histName,"",nBinsX,lowBinX,highBinX);
  hist[i]->SetMarkerStyle(20);
  hist[i]->SetMarkerColor(hColor.at(i));
  hist[i]->SetLineColor(hColor.at(i));
  TString fileLoad;
  if(lepType==FAKES) fileLoad = "./"+fileLocation+"/";
  else if(lepType==ELE) fileLoad = "/home/hep/wrtabb/Egamma/input_trees/2016UL/";
  fileLoad += titles.at(i);
  fileLoad += ".root"; 
  cout << "Opening file: " << fileLoad << endl;
  TFile*file = new TFile(fileLoad);
  TFile*fileFriend;
  TString fileFriendName = fileELEFriend+fileLocation+"/regEleEcal2016UL_IdealIC_IdealTraining_stdVar_stdCuts_ntrees1500_applied.root";
  if(lepType==FAKES) fileFriend = file;
  else if(lepType==ELE) fileFriend = new TFile(fileFriendName);
  chain[i] = (TTree*)file->Get(treeName);
  chainFriend[i] = (TTree*)fileFriend->Get(friendName);
  chain[i]->AddFriend(chainFriend[i]);
  chain[i]->SetBranchAddress("ele",&eleObject,&b_ele); 
  chain[i]->SetBranchAddress("mean",&mean,&b_mean);

  Long64_t nEntries;
  if(lepType==ELE) nEntries = chain[i]->GetEntries();
  else if(lepType==FAKES) nEntries = 2e6;
  cout << "Number of entries in " << titles.at(i) << ": "  << nEntries << endl;
  for(Long64_t j=0;j<nEntries;j++){
   chain[i]->GetEntry(j);
   if(eleObject.energy == 0) continue;
   if(eleObject.et == 0) continue;

   if(var==ENERGY)   fill = eleObject.energy;
   else if(var==ET)  fill = eleObject.et;
   else if(var==ETA) fill = eleObject.eta; 
   hist[i]->Fill(fill);
   histCombined->Fill(fill);
   hist2D->Fill(fill,mean);
  }
  if(hist[i]->Integral() == 0){
   cout << "ERROR: Nothing placed in histogram!!!" << endl;
   break;
  }
 } 
 
 TProfile*hProfile = hist2D->ProfileX("MeanVs"+namePrefix+"Profile");
 hProfile->GetYaxis()->SetTitle("average correction");
 TLegend*legend = new TLegend(0.65,1.0,1.0,0.75);
 legend->SetTextSize(0.02);
 legend->AddEntry(histCombined,"Combination");
 
 TString cName = "canvas";
 TCanvas*canvas = new TCanvas(cName,"",0,0,1000,1000);
 canvas->SetGrid();
 canvas->SetLogy();
 if(var==ENERGY || var==ET) canvas->SetLogx();
 histCombined->Draw("hist");
 for(int i=0;i<nChains;i++){
  legend->AddEntry(hist[i],titles.at(i));
  hist[i]->Draw("pe,same");
 }
 legend->Draw("same");
 saveName = "./plots/";
 saveName += namePrefix;
 saveName += "Spectrum_";
 saveName += fileLocation;
 if(lepType==ELE) saveName += "Ele";
 else if(lepType==FAKES) saveName += "Fakes";
 saveName += ".png";
 canvas->SaveAs(saveName);

 cName += "Prof";
 TCanvas*canvas3 = new TCanvas(cName,"",0,0,1000,1000);
 if(var==ENERGY || var==ET) canvas3->SetLogx();
 canvas3->SetLogz();
 canvas3->SetGrid();
 hProfile->SetMarkerStyle(20);
 hProfile->Draw("pe");
 saveName = "./plots/";
 saveName += "MeanVs";
 saveName += namePrefix;
 saveName += "_";
 saveName += fileLocation;
 if(lepType==ELE) saveName += "Ele";
 else if(lepType==FAKES) saveName += "Fakes";
 saveName += "Profile";
 saveName += ".png";
 canvas3->SaveAs(saveName);

 cName += "2D";
 TCanvas*canvas2 = new TCanvas(cName,"",0,0,1000,1000);
 if(var==ENERGY || var==ET) canvas2->SetLogx();
 canvas2->SetLogz();
 canvas2->SetGrid();
 hist2D->Draw("colz");
 saveName = "./plots/";
 saveName += "MeanVs";
 saveName += namePrefix;
 saveName += "_";
 saveName += fileLocation;
 if(lepType==ELE) saveName += "Ele";
 else if(lepType==FAKES) saveName += "Fakes";
 saveName += ".png";
 canvas2->SaveAs(saveName);

 saveName = "./Data/"+savePrefix;
 if(lepType==ELE) saveName += "Ele";
 else if(lepType==FAKES) saveName += "Fakes";
 saveName += fileLocation;
 saveName += ".root";
 TFile*saveFile = new TFile(saveName,"recreate");
 histCombined->Write();
 hist2D->Write();
 hProfile->Write();
 for(int i=0;i<nChains;i++){
  hist[i]->Write();
 }
 saveFile->Close();
}

TH1D*GetHistCombined(Variable var,TString namePrefix,TString histName)
{
 TH1D*hist;
 if(var==ENERGY || var==ET){
  hist = new TH1D(histName,"",nEnergyBins,energybins);
 }
 else{
  hist = new TH1D(histName,"",nBinsX,lowBinX,highBinX);
 }
 histCombined->SetMinimum(0.1);
 histCombined->SetMaximum(1e7);
 histCombined->GetXaxis()->SetTitle(namePrefix);

 return hist;
}
