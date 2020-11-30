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
    parser.add_argument('--era',required=True,help='year to produce for, 2016, 2017, 2018 are the options')
    parser.add_argument('--input_dir','-i',default='/home/hep/wrtabb/Egamma/input_trees/ECAlPaperTrees',help='input directory with the ntuples')
    parser.add_argument('--output_dir','-o',default="/home/hep/wrtabb/Egamma/results/ECALPaper",help='output dir')
    args = parser.parse_args()

    #setup the selection (event number cuts come later)
    cuts_name = "stdCuts" 
    base_ele_cuts = "(mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && {extra_cuts})"
    
    if args.era=='2016':
        base_reg_name = "scReg2016UL"
        input_ideal_ic  = "{}/DoubleElectron_FlatPt-1To300_2016ConditionsFlatPU0to70ECALGT_105X_mcRun2_asymptotic_IdealEcalIC_newSR_v2-v2_AODSIM_EgRegTreeV5.root".format(args.input_dir)
        ideal_eventnr_cut = "evt.eventnr%5==0"
    elif args.era=='2017':
        base_reg_name = "scReg2017UL"    
        input_ideal_ic  = "{}/DoubleElectron_FlatPt-1To300_2017ConditionsFlatPU0to70ECALGT_105X_mc2017_realistic_IdealEcalIC_v5-v2_AODSIM_EgRegTreeV1_extraVars.root".format(args.input_dir)
        ideal_eventnr_cut = "evt.eventnr%2==0"
    elif args.era=='2018':
        base_reg_name = "scReg2018UL"    
        input_ideal_ic  = "{}/DoubleElectron_FlatPt-1To300_FlatPU0to70_ECAL5_106X_upgrade2018_realistic_v11_L1v1-v2_AODSIM_EgRegTree.root".format(args.input_dir)
        ideal_eventnr_cut = "evt.eventnr%5 < 3"
    else:
        raise ValueError("era {} is invalid, options are 2016/2017/2018".format(era))

    
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
 
    time.sleep(20)

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


