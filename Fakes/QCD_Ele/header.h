
vector<TString> filesQCD = {
 "QCD_2016UL_15to30",
 "QCD_2016UL_30to50",
 "QCD_2016UL_50to80",
 "QCD_2016UL_80to120",
 //"QCD_2016UL_120to170",
 //"QCD_2016UL_170to300",
 //"QCD_2016UL_300to470",
 //"QCD_2016UL_470to600",
 //"QCD_2016UL_600to800",
 "QCD_2016UL_800to1000",
 "QCD_2016UL_1000to1400",
 "QCD_2016UL_1400to1800",
 "QCD_2016UL_1800to2400",
 "QCD_2016UL_2400to3200",
 "QCD_2016UL_3200toInf"
};
//vector<TString> filesELE = {
// "DoubleElectron_FlatPt-1To300_2016ConditionsFlatPU0to70RAW_105X_realistic_v2-v2"
//};
vector<TString> filesELEIdeal = {
 "DoubleElectron_FlatPt-1To300_2016ConditionsFlatPU0to70ECALGT_105X_realistic_IdealEcalIC_v2-v2"
};
vector<TString> filesELEReal = {
 "DoubleElectron_FlatPt-1To300_2016ConditionsFlatPU0to70RAW_105X_realistic_v2-v2"
};
TString fileELEFriend = "../../../results/";
vector<TString> VarType_RegionType = {
	"AllStd",
	"AllExt",
	"BadStd",
	"BadExt"
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
TString treeName = "egRegTree";
TString friendName = "egRegTreeFriend";
const double etaGapHigh = 1.566;
const double etaGapLow = 1.4442;
//Functions
TTree*GetTree(TString file_name);
