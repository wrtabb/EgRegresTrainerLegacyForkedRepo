

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
enum VarType{
 EXT,
 STD
};
enum RegionType{
 ALL,
 BAD,
 GOOD
};
const TString treeName = "egRegTree";
const TString friendName = "egRegTreeFriend";

//Functions
TH2D*defineHist(TString title);
TCanvas*defineCanvas(TString title);
TProfile*defineProfile(TH2D*hist);
TChain*LoadTrees(VarType varType,RegionType regionType);
void PtAndEtaPlots(TTree*tree,bool savePlots);
void MeanPlot(TChain*tree,TString title,RegionType region,bool savePlots);
