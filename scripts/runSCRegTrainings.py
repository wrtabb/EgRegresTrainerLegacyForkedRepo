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
    parser.add_argument('--tag',required=True,help='Threshold tag to run on. Options are TL150, TL180, or TL235')
    parser.add_argument('--input_dir','-i',default='/home/hep/wrtabb/Egamma/input_trees/ThreshForECAL',help='input directory with the ntuples')
    parser.add_argument('--output_dir','-o',default="../results/ThreshForECAL/",help='output dir')
    args = parser.parse_args()

    #setup the selection (event number cuts come later)
    cuts_name = "stdCuts" 
    base_ele_cuts = "(mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && {extra_cuts})"
    # Run regression on 3,000,000 superclusters (sample contains 5,000,000) 
    if args.tag=='TL150':
        base_reg_name = "scRegTL150"
        input_ideal_ic  = "{}/TL150/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL150_106X_mcRun3_TL150fb_realistic_v1_ext1-v1_EGRegNtups.root".format(args.input_dir)
        ideal_eventnr_cut = "evt.eventnr%5 < 3" 
    elif args.tag=='TL180':
        base_reg_name = "scRegTL180"    
        input_ideal_ic  = "{}/TL180/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL180_106X_mcRun3_TL180fb_realistic_v1_ext1-v1_EGRegNtups.root".format(args.input_dir)
        ideal_eventnr_cut = "evt.eventnr%5 < 3"
    elif args.tag=='TL235':
        base_reg_name = "scRegTL235"    
        input_ideal_ic  = "{}/TL235/DoubleElectron_FlatPt-1To100_ntuples_ECALFlatPU0to80RAWTL235_106X_mcRun3_TL235fb_realistic_v1_ext1-v1_EGRegNtups.root".format(args.input_dir)
        ideal_eventnr_cut = "evt.eventnr%5 <3"  
    else:
        raise ValueError("tag {} is invalid, options are TL150, TL180,  or TL235".format(tag))

    
    regArgs = RegArgs()
    regArgs.input_training =  str(input_ideal_ic)
    regArgs.input_testing = str(input_ideal_ic)
    regArgs.set_sc_default()
    regArgs.cfg_dir = "configs"
    regArgs.out_dir = args.output_dir
    regArgs.cuts_name = cuts_name
    regArgs.base_name = "{}_IdealIC_IdealTraining".format(base_reg_name)
    regArgs.cuts_base = base_ele_cuts.format(extra_cuts = ideal_eventnr_cut)
    regArgs.ntrees = 1500
 
    print """about to run the supercluster regression with: 
    name: {name}
    ideal ic input: {ideal_ic}
    real ic input: {real_ic}
    output dir: {out_dir}
    time.sleep(20)"""

    if not os.path.exists(args.output_dir):
        os.makedirs(args.output_dir)

    regArgs.run_eb_and_ee()
    
    regArgs.do_eb = True
    forest_eb_file = regArgs.output_name()
    regArgs.do_eb = False
    forest_ee_file = regArgs.output_name()

    regArgs.base_name = "{}_RealIC_IdealTraining".format(base_reg_name)
    input_for_res_training = str(regArgs.applied_name()) #save the output name before we change it

if __name__ =='__main__':
    main()


