#include "header.h"

void Draw(TTree*tree,TString variables,TString saveName,TString drawOption);

void make_plots()
{
	gROOT->SetBatch(true);
	gStyle->SetPalette(1);
	gStyle->SetOptStat(0);
	int nFiles = titles.size();
	int nTypes = VarType_RegionType.size();
	for(int j=0;j<nTypes;j++){
		cout << VarType_RegionType.at(j) << endl;
		for(int i=0;i<nFiles;i++){
			TString file_name = "./";
			file_name += VarType_RegionType.at(j);
			file_name += "/";
			file_name += titles.at(i);
			file_name += ".root";
			TTree*tree=GetTree(file_name);
			//cout << titles.at(i) << endl;
			//cout << "---------------------------" << endl;
			//cout << tree->GetEntries() << endl;
			//cout << endl;
			TString cName = "canvas";
			cName += VarType_RegionType.at(j);
			cName += "_";
			cName += titles.at(i);
			Draw(tree,"ele.energy",cName+"Energy","hist");
			Draw(tree,"ele.et",cName+"Et","hist");
			Draw(tree,"mean:ele.energy",cName+"MeanVsEnergy","colz");
			Draw(tree,"mean:ele.et",cName+"MeanVsEt","colz");
		}
	}
}

void Draw(TTree*tree,TString variables,TString cName,TString drawOption)
{
	TCanvas*canvas = new TCanvas(cName,"",0,0,1000,1000);
	canvas->SetGrid();
	tree->Draw(variables,"sc.energy>0 && mc.energy==0",drawOption);
	cName += ".png";
	TString saveName = "./plots/";
	saveName += cName;
	canvas->SaveAs(saveName);
}

TTree*  GetTree(TString file_name){
	TFile*file = new TFile(file_name);
	TTree*tree = (TTree*)file->Get(treeName);
	TTree*treeFriend = (TTree*)file->Get(friendName);
	tree->AddFriend(treeFriend);
	return tree;
}
