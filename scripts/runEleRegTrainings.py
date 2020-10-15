#!/usr/bin/env python

import subprocess
import os
import regtools
from regtools import RegArgs
import argparse

def main():
    parser = argparse.ArgumentParser(description='runs the SC regression trainings')
    parser.add_argument('--sample',required=True,help='sample to run on')
    parser.add_argument('--input_dir','-i',default='/home/hep/wrtabb/Egamma/input_trees',help='input directory with the ntuples')
    parser.add_argument('--output_dir','-o',default="results",help='output dir')
    args = parser.parse_args()
    
    base_ele_cuts = "(mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && ele.et>0 && {extra_cuts})"

    if args.sample=='2016UL':
        sample_name = args.sample
        input_sample  = "{}/2016UL/DoubleElectron_FlatPt-1To300_2016ConditionsFlatPU0to70ECALGT_105X_realistic_IdealEcalIC_v2-v2.root".format(args.input_dir)
        ideal_eventnr_cut = "evt.eventnr%2==0"

    elif args.sample=='ECALTest':
        sample_name = args.sample
        input_sample  = "{}/ECALTest/DoubleElectron_FlatPt-1To300_FlatPU0to70_106X_upgrade2018_realistic_v11_Ecal3-v4_AODSIM_EgRegTree.root".format(args.input_dir)
        ideal_eventnr_cut = "evt.eventnr%2==0"  #2million electrons
    else:
        raise ValueError("sample {} is invalid, options are 2016UL or ECALTest".format(sample))

    #step1 train the calo only regression using IDEAL intercalibration constants
    print "starting step1"
    regArgs = RegArgs()
    regArgs.input_training = str(input_sample)
    regArgs.input_testing = str(input_sample)  
    regArgs.set_ecal_default()
    regArgs.cuts_base = base_ele_cuts.format(extra_cuts = ideal_eventnr_cut)
    regArgs.cuts_name = "stdCuts"
    regArgs.cfg_dir = "configs"
    regArgs.out_dir = "../results/ECALTest/"+sample_name 
    regArgs.ntrees = 1500  
    regArgs.base_name = "regEleEcal{sample_name}_IdealIC_IdealTraining".format(sample_name=sample_name)
    regArgs.run_eb_and_ee()
    
    
        
    
if __name__ =='__main__':
    main()


