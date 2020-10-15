#!/usr/bin/env python

import subprocess
import os
try:
    from regtools import RegArgs
except ImportError:
    raise ImportError('module regtools not found, please add "python" to PYTHON27PATH or PYTHONPATH as appropriate eg\n  export PYTHON27PATH=$PYTHON27PATH:python\nand try again')
import time
import argparse
def main():  

    parser = argparse.ArgumentParser(description='runs the SC regression trainings')
    parser.add_argument('--sample',required=True,help='sample to run on')
    parser.add_argument('--input_dir','-i',default='/home/hep/wrtabb/Egamma/input_trees',help='input directory with the ntuples')
    parser.add_argument('--output_dir','-o',default="../results",help='output dir')
    args = parser.parse_args()

    #setup the selection (event number cuts come later)
    cuts_name = "stdCuts" 
    base_cuts = "(mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && {extra_cuts})"

    #prefixes all the regressions produced
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
    
    base_reg_name = "scReg_" + sample_name
    regArgs = RegArgs()
    regArgs.input_training =  str(input_sample)
    regArgs.input_testing = str(input_sample)
    regArgs.set_sc_default()
    regArgs.cfg_dir = "configs"
    regArgs.out_dir = args.output_dir
    regArgs.cuts_name = cuts_name
    regArgs.base_name = "{}_IdealIC_IdealTraining".format(base_reg_name)
    regArgs.cuts_base = base_cuts.format(extra_cuts = ideal_eventnr_cut)
    regArgs.ntrees = 1500
 
    time.sleep(20)

    if not os.path.exists(args.output_dir):
        os.makedirs(args.output_dir)

    regArgs.run_eb_and_ee()
    
    regArgs.do_eb = True
    forest_eb_file = regArgs.output_name()
    regArgs.do_eb = False
    forest_ee_file = regArgs.output_name()

if __name__ =='__main__':
    main()


