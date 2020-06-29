#!/usr/bin/env python

import subprocess
import os
import regtools
from regtools import RegArgs
import argparse   

def main():
    
    parser = argparse.ArgumentParser(description='runs the SC regression trainings')
    parser.add_argument('--tag',required=True,help='year to produce for, 2016, 2017, 2018 are the options')
    parser.add_argument('--input_dir','-i',default='/home/hep/wrtabb/Egamma/input_trees/RechitThresholdRegres',help='input directory with the ntuples')
    parser.add_argument('--output_dir','-o',default="../results/PFRechit/",help='output dir')
    args = parser.parse_args()

    #step 1, run calo only regression on the ideal IC to get the mean
    #step 2, apply the mean to the real IC sample and save the result in a tree
    #step 3, retrain the resolution for the real IC on the corrected energy

    run_step1 = True
    
    base_pho_cuts = "(mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && pho.et>0 && {extra_cuts})"

    if args.tag=='base':
        # This is the baseline regression for testing different thresholds
        tag_name = "base"
        input_ideal_ic  = "{}/DoubleElectron_FlatPt-1To100_2021ScenarioFlatPU0to80RAW_106X_mcRun3_2021_realistic_v3-v2_AODSIM.root".format(args.input_dir)
        input_real_ic = "{}/DoubleElectron_FlatPt-1To100_2021ScenarioFlatPU0to80RAW_106X_mcRun3_2021_realistic_v3-v2_AODSIM.root".format(args.input_dir)
        ideal_eventnr_cut = "(evt.eventnr%5==0||evt.eventnr%5==1||evt.eventnr%5==2)"

    elif args.tag=='TL235':
        tag_name = "TL235"
        input_ideal_ic  = "{}/DoubleElectron_FlatPt-1To100_crab_DoubleEle_FlatPt-1To100_Run3_GENSIM_34sigma_TL235-8f57d3c1c8cdfa3a81c56bef63445230_USER.root".format(args.input_dir)
        input_real_ic = "{}/DoubleElectron_FlatPt-1To100_crab_DoubleEle_FlatPt-1To100_Run3_GENSIM_34sigma_TL235-8f57d3c1c8cdfa3a81c56bef63445230_USER.root".format(args.input_dir)
        ideal_eventnr_cut = "(evt.eventnr%5==0||evt.eventnr%5==1||evt.eventnr%5==2)"
    elif args.tag=='TL180':
        tag_name = "TL180"
        input_ideal_ic  = "{}/DoubleElectron_FlatPt-1To100_crab_DoubleEle_FlatPt-1To100_Run3_GENSIM_34sigma_TL180_V1-cb9ba5e110c3cfceb187c9076f92b7eb_USER.root".format(args.input_dir)
        input_real_ic = "{}/DoubleElectron_FlatPt-1To100_crab_DoubleEle_FlatPt-1To100_Run3_GENSIM_34sigma_TL180_V1-cb9ba5e110c3cfceb187c9076f92b7eb_USER.root".format(args.input_dir)
        ideal_eventnr_cut = "(evt.eventnr%5==0||evt.eventnr%5==1||evt.eventnr%5==2)"
    else:
        raise ValueError("tag {} is invalid, options are base, TL235, or TL180".format(tag))

    #step1 train the calo only regression using IDEAL intercalibration constants
    print "starting step1"
    regArgs = RegArgs()
    regArgs.input_training = str(input_ideal_ic)
    regArgs.input_testing = str(input_ideal_ic)  
    regArgs.set_phoecal_default() 
    regArgs.cuts_name = "stdCuts"
    regArgs.cuts_base = base_pho_cuts.format(extra_cuts = ideal_eventnr_cut)
    regArgs.cfg_dir = "configs"
    regArgs.out_dir = "resultsPhoV5" 
    regArgs.ntrees = 1500  
    regArgs.base_name = "regPhoEcal{tag_name}_IdealIC_IdealTraining".format(tag_name=tag_name)
    if run_step1: regArgs.run_eb_and_ee()
    
    
          
    
if __name__ =='__main__':
    main()


