
std::vector<TString> inputFiles = {
 "energyHistsEleAllExt.root",
 "energyHistsEleAllStd.root",
 "energyHistsEleBadExt.root",
 "energyHistsEleBadStd.root",
 "energyHistsFakesAllExt.root",
 "energyHistsFakesAllStd.root",
 "energyHistsFakesBadExt.root",
 "energyHistsFakesBadStd.root",
 "etHistsEleAllExt.root",
 "etHistsEleAllStd.root",
 "etHistsEleBadExt.root",
 "etHistsEleBadStd.root",
 "etHistsFakesAllExt.root",
 "etHistsFakesAllStd.root",
 "etHistsFakesBadExt.root",
 "etHistsFakesBadStd.root",
 "etaHistsEleAllExt.root",
 "etaHistsEleAllStd.root",
 "etaHistsEleBadExt.root",
 "etaHistsEleBadStd.root",
 "etaHistsFakesAllExt.root",
 "etaHistsFakesAllStd.root",
 "etaHistsFakesBadExt.root",
 "etaHistsFakesBadStd.root"
};
std::vector<TString> profTitles = {
 "electrons: AllExt",
 "electrons: AllStd",
 "electrons: BadExt",
 "electrons: BadStd",
 "fakes: AllExt",
 "fakes: AllStd",
 "fakes: BadExt",
 "fakes: BadStd"
};
std::vector<Color_t> colors = {
 kRed+2,
 kMagenta+2,
 kBlue+2,
 kCyan+3,
 kGreen+2,
 kYellow+2,
 kOrange+7,
 kRed+4,
 kRed+2,
 kMagenta+2,
 kBlue+2,
 kCyan+3,
 kGreen+2,
 kYellow+2,
 kOrange+7,
 kRed+4,
 kRed+2,
 kMagenta+2,
 kBlue+2,
 kCyan+3,
 kGreen+2,
 kYellow+2,
 kOrange+7,
 kRed+4
};
std::vector<TString> profileNames = {
 "MeanVsEnergyProfile",
 "MeanVsEtProfile",
 "MeanVsEtaProfile"
};
std::vector<TFile*> GetFiles(std::vector<TString> input);
std::vector<TProfile*> GetProfiles(std::vector<TFile*> input);
std::vector<TCanvas*> GetPlots(std::vector<TProfile*> input);
void SavePlots(std::vector<TCanvas*> input);

void makePlots()
{
 std::vector<TFile*> files = GetFiles(inputFiles);
 std::vector<TProfile*> profiles = GetProfiles(files);
 std::vector<TCanvas*> canvas = GetPlots(profiles);
 SavePlots(canvas);
}

void SavePlots(std::vector<TCanvas*> input)
{
 TFile*file = new TFile("./Data/profilePlots.root","recreate");
 int nPlots = input.size();
 for(int i=0;i<nPlots;i++){
  file->cd();
  input.at(i)->Write();
  input.at(i)->SaveAs("./plots/combined"+profileNames.at(i)+".png");
  input.at(i)->SaveAs("./Data/combined"+profileNames.at(i)+".C");
 }
 file->Close();
}

std::vector<TCanvas*> GetPlots(std::vector<TProfile*> input)
{
 TLegend*legend = new TLegend(0.65,1.0,1.0,0.75);
 legend->SetTextSize(0.02);
 for(int i=0;i<8;i++){
  legend->AddEntry(input.at(i),profTitles.at(i));
 }

 std::vector<TCanvas*> can;
 int nCanvas = profileNames.size();
 int nPlots = input.size()/3;
 for(int i=0;i<nCanvas;i++){
  TString cName = "canvas";
  cName += i;
  can.push_back(new TCanvas(cName,"",0,0,1000,1000));
  can.at(i)->SetGrid();
  if(i<2)can.at(i)->SetLogx();
  can.at(i)->cd();
  int jStart = 0;
  for(int j=jStart;j<nPlots;j++){
   TString plotOption = "pe";
   if(j!=0 && j!=8 && j!=16) plotOption ="pe,same";
   input.at(j)->Draw(plotOption);
  }
  jStart = jStart+8;
  nPlots = nPlots+8;
  legend->Draw("same");
 }
 return can;
}

std::vector<TProfile*> GetProfiles(std::vector<TFile*> input)
{
 std::vector<TProfile*> prof;
 int nFiles = input.size();
 for(int i=0;i<nFiles;i++){
  if(i<8) prof.push_back((TProfile*)input.at(i)->Get(profileNames.at(0)));
  else if(i<16 && i>=8) prof.push_back((TProfile*)input.at(i)->Get(profileNames.at(1)));
  else if(i>=16) prof.push_back((TProfile*)input.at(i)->Get(profileNames.at(2)));
  prof.at(i)->SetMarkerStyle(20);
  prof.at(i)->SetMarkerColor(colors.at(i));
  prof.at(i)->SetLineColor(colors.at(i));
  prof.at(i)->SetMinimum(0.8);
  prof.at(i)->SetMaximum(2.0);
 }
 return prof;
}

std::vector<TFile*> GetFiles(std::vector<TString> input)
{
 std::vector<TFile*> files;
 int nFiles = input.size();
 TString directory = "./Data/";
 for(int i=0;i<nFiles;i++){
  files.push_back(new TFile(directory+input.at(i)));
 }
 return files;
}


