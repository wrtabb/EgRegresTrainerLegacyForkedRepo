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
    parser.add_argument('--tag',required=True,help='year to produce for, 2016, 2017, 2018 are the options')
    parser.add_argument('--input_dir','-i',default='/home/hep/wrtabb/Egamma/input_trees/RechitThresholdRegres',help='input directory with the ntuples')
    parser.add_argument('--output_dir','-o',default="../results/PFRechit/",help='output dir')
    args = parser.parse_args()

    #step 1, run calo only regression on the ideal IC to get the mean
    #step 2, apply the mean to the real IC sample and save the result in a tree
    #step 3, retrain the resolution for the real IC on the corrected energy
    run_step1 = True
    run_step2 = True
    run_step3 = True

    #setup the selection (event number cuts come later)
    cuts_name = "stdCuts" 
    base_ele_cuts = "(mc.energy>0 && ssFrac.sigmaIEtaIEta>0 && ssFrac.sigmaIPhiIPhi>0 && {extra_cuts})"
    
    #prefixes all the regressions produced
    if args.tag=='base':
        tag_name = "base"
        input_ideal_ic  = "{}/DoubleElectron_FlatPt-1To100_2021ScenarioFlatPU0to80RAW_106X_mcRun3_2021_realistic_v3-v2_AODSIM.root".format(args.input_dir)
        input_real_ic = "{}/DoubleElectron_FlatPt-1To100_2021ScenarioFlatPU0to80RAW_106X_mcRun3_2021_realistic_v3-v2_AODSIM.root".format(args.input_dir)    
        ideal_eventnr_cut = "evt.eventnr%5==0"
        real_eventnr_cut = "evt.eventnr%5==1" 
    elif args.tag=='TL235':
        tag_name = "TL235"    
        input_ideal_ic  = "{}/DoubleElectron_FlatPt-1To100_crab_DoubleEle_FlatPt-1To100_Run3_GENSIM_34sigma_TL235-8f57d3c1c8cdfa3a81c56bef63445230_USER.root".format(args.input_dir)
        input_real_ic = "{}/DoubleElectron_FlatPt-1To100_crab_DoubleEle_FlatPt-1To100_Run3_GENSIM_34sigma_TL235-8f57d3c1c8cdfa3a81c56bef63445230_USER.root".format(args.input_dir)   
        ideal_eventnr_cut = "evt.eventnr%5==0"
        real_eventnr_cut = "evt.eventnr%5==0" 
    elif args.tag=='TL180':
        tag_name = "TL180"    
        input_ideal_ic  = "{}/DoubleElectron_FlatPt-1To100_crab_DoubleEle_FlatPt-1To100_Run3_GENSIM_34sigma_TL180_V1-cb9ba5e110c3cfceb187c9076f92b7eb_USER.root".format(args.input_dir)
        input_real_ic = "{}/DoubleElectron_FlatPt-1To100_crab_DoubleEle_FlatPt-1To100_Run3_GENSIM_34sigma_TL180_V1-cb9ba5e110c3cfceb187c9076f92b7eb_USER.root".format(args.input_dir)    
        ideal_eventnr_cut = "evt.eventnr%5==0"
        real_eventnr_cut = "evt.eventnr%5==1" 
    else:
        raise ValueError("tag {} is invalid, options are base, TL235, or TL180".format(tag))

    
    regArgs = RegArgs()
    regArgs.input_training =  str(input_ideal_ic)
    regArgs.input_testing = str(input_ideal_ic)
    regArgs.set_sc_default()
    regArgs.cfg_dir = "configs"
    regArgs.out_dir = args.output_dir+tag_name
    regArgs.cuts_name = cuts_name
    regArgs.base_name = "{}_IdealIC_IdealTraining".format(tag_name)
    regArgs.cuts_base = base_ele_cuts.format(extra_cuts = ideal_eventnr_cut)
    regArgs.ntrees = 1500
 
    print """about to run the supercluster regression with: 
    name: {name}
    ideal ic input: {ideal_ic}
    real ic input: {real_ic}
    output dir: {out_dir}
steps to be run:
    step 1: ideal training for mean       = {step1}
    step 2: apply ideal training to real  = {step2}
    step 3: real training for sigma       = {step3}""".format(name=tag_name,ideal_ic=input_ideal_ic,real_ic=input_real_ic,out_dir=args.output_dir,step1=run_step1,step2=run_step2,step3=run_step3)
    time.sleep(20)

    if not os.path.exists(args.output_dir):
        os.makedirs(args.output_dir)

    if run_step1: regArgs.run_eb_and_ee()
    
    regArgs.do_eb = True
    forest_eb_file = regArgs.output_name()
    regArgs.do_eb = False
    forest_ee_file = regArgs.output_name()

    regArgs.base_name = "{}_RealIC_IdealTraining".format(tag_name)
    input_for_res_training = str(regArgs.applied_name()) #save the output name before we change it
    input_for_input_for_res_training = str(input_real_ic)
    
    if run_step2: subprocess.Popen(["bin/slc7_amd64_gcc700/RegressionApplierExe",input_for_input_for_res_training,input_for_res_training,"--gbrForestFileEE",forest_ee_file,"--gbrForestFileEB",forest_eb_file,"--nrThreads","4","--treeName",regArgs.tree_name,"--writeFullTree","1","--regOutTag","Ideal"]).communicate()

    regArgs.base_name = "{}_RealIC_RealTraining".format(tag_name)
    regArgs.input_training = input_for_res_training
    regArgs.input_testing = input_for_res_training
    regArgs.target = "mc.energy/(sc.rawEnergy*regIdealMean)"
    regArgs.fix_mean = True
    regArgs.cuts_base = base_ele_cuts.format(extra_cuts = real_eventnr_cut)
    if run_step3: regArgs.run_eb_and_ee()

if __name__ =='__main__':
    main()


