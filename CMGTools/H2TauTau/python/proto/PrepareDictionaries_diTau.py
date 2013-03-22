import os
import imp
from CMGTools.H2TauTau.proto.HistogramSet import histogramSet
from CMGTools.H2TauTau.proto.H2TauTauDataMC_diTau import *
from CMGTools.RootTools.Style import formatPad,Style
from QCDEstimation_diTau import *
from SaveHistograms_diTau import *
import math

from plot_H2TauTauDataMC_diTau import run2012

def componentsWithData (selComps, weights) :

    selCompsData110 = {}
    selCompsData115 = {}
    selCompsData120 = {}
    selCompsData125 = {}
    selCompsData130 = {}
    selCompsData135 = {}
    selCompsData140 = {}
    selCompsData145 = {}

    weightsData110 = {}
    weightsData115 = {}
    weightsData120 = {}
    weightsData125 = {}
    weightsData130 = {}
    weightsData135 = {}
    weightsData140 = {}
    weightsData145 = {}

    selCompsDataMass = {110:selCompsData110,115:selCompsData115,120:selCompsData120,125:selCompsData125,130:selCompsData130,135:selCompsData135,140:selCompsData140,145:selCompsData145}
    weightsDataMass  = {110:weightsData110 ,115:weightsData115 ,120:weightsData120 ,125:weightsData125 ,130:weightsData130 ,135:weightsData135 ,140:weightsData140 ,145:weightsData145 }

    for mPoint in [110,115,120,125,130,135,140,145] :
    #for mPoint in [125] :


      if run2012:

        if 'data_Run2012A_PromptReco_v1' in selComps.keys():
          selCompsDataMass[mPoint]['data_Run2012A_PromptReco_v1']  = copy.deepcopy(selComps['data_Run2012A_PromptReco_v1'])
        if 'data_Run2012B_PromptReco_v1' in selComps.keys():
          selCompsDataMass[mPoint]['data_Run2012B_PromptReco_v1']  = copy.deepcopy(selComps['data_Run2012B_PromptReco_v1'])
        if 'data_Run2012C_PromptReco_v1' in selComps.keys():
          selCompsDataMass[mPoint]['data_Run2012C_PromptReco_v1']  = copy.deepcopy(selComps['data_Run2012C_PromptReco_v1'])
          selCompsDataMass[mPoint]['data_Run2012C_PromptReco_v2']  = copy.deepcopy(selComps['data_Run2012C_PromptReco_v2'])
        if 'data_Run2012D_PromptReco_v1' in selComps.keys():
          selCompsDataMass[mPoint]['data_Run2012D_PromptReco_v1']  = copy.deepcopy(selComps['data_Run2012D_PromptReco_v1'])

	if 'embed_Run2012A_13Jul2012_v1' in selComps.keys():
          selCompsDataMass[mPoint]['embed_Run2012A_13Jul2012_v1'] = copy.deepcopy(selComps['embed_Run2012A_13Jul2012_v1'])
	if 'embed_Run2012A_recover_06Aug2012_v1' in selComps.keys():
          selCompsDataMass[mPoint]['embed_Run2012A_recover_06Aug2012_v1'] = copy.deepcopy(selComps['embed_Run2012A_recover_06Aug2012_v1'])
	if 'embed_Run2012B_13Jul2012_v4' in selComps.keys():
          selCompsDataMass[mPoint]['embed_Run2012B_13Jul2012_v4'] = copy.deepcopy(selComps['embed_Run2012B_13Jul2012_v4'])
	if 'embed_Run2012C_24Aug2012_v1' in selComps.keys():
            selCompsDataMass[mPoint]['embed_Run2012C_24Aug2012_v1'] = copy.deepcopy(selComps['embed_Run2012C_24Aug2012_v1'])
            selCompsDataMass[mPoint]['embed_Run2012C_PromptReco_v2'] = copy.deepcopy(selComps['embed_Run2012C_PromptReco_v2'])
	if 'embed_2012D_PromptReco_v1' in selComps.keys():
            selCompsDataMass[mPoint]['embed_2012D_PromptReco_v1'] = copy.deepcopy(selComps['embed_2012D_PromptReco_v1'])

      else:
        selCompsDataMass[mPoint]['data_Run2011A_May10ReReco_v1'] = copy.deepcopy(selComps['data_Run2011A_May10ReReco_v1'])
        selCompsDataMass[mPoint]['data_Run2011A_PromptReco_v4']  = copy.deepcopy(selComps['data_Run2011A_PromptReco_v4'])
        selCompsDataMass[mPoint]['data_Run2011A_05Aug2011_v1']   = copy.deepcopy(selComps['data_Run2011A_05Aug2011_v1'])
      selCompsDataMass[mPoint]['DYJets']                       = copy.deepcopy(selComps['DYJets'])
      selCompsDataMass[mPoint]['WJets']                        = copy.deepcopy(selComps['WJets'])
      selCompsDataMass[mPoint]['WW']                           = copy.deepcopy(selComps['WW'])
      selCompsDataMass[mPoint]['WZ']                           = copy.deepcopy(selComps['WZ'])
      selCompsDataMass[mPoint]['ZZ']                           = copy.deepcopy(selComps['ZZ'])
      selCompsDataMass[mPoint]['TTJets']                       = copy.deepcopy(selComps['TTJets'])
      selCompsDataMass[mPoint]['T_tW']                         = copy.deepcopy(selComps['T_tW'])
      selCompsDataMass[mPoint]['Tbar_tW']                      = copy.deepcopy(selComps['Tbar_tW'])
      selCompsDataMass[mPoint]['HiggsGGH' +str(mPoint)]        = copy.deepcopy(selComps['HiggsGGH' +str(mPoint)])
      selCompsDataMass[mPoint]['HiggsVBF'+str(mPoint)]         = copy.deepcopy(selComps['HiggsVBF'+str(mPoint)])
      selCompsDataMass[mPoint]['HiggsVH' +str(mPoint)]         = copy.deepcopy(selComps['HiggsVH' +str(mPoint)])

      if run2012:
        if 'data_Run2012A_PromptReco_v1' in selComps.keys():
          weightsDataMass[mPoint]['data_Run2012A_PromptReco_v1'] = copy.deepcopy(weights['data_Run2012A_PromptReco_v1'])
        if 'data_Run2012B_PromptReco_v1' in selComps.keys():
          weightsDataMass[mPoint]['data_Run2012B_PromptReco_v1'] = copy.deepcopy(weights['data_Run2012B_PromptReco_v1'])
        if 'data_Run2012C_PromptReco_v1' in selComps.keys():
          weightsDataMass[mPoint]['data_Run2012C_PromptReco_v1'] = copy.deepcopy(weights['data_Run2012C_PromptReco_v1'])
          weightsDataMass[mPoint]['data_Run2012C_PromptReco_v2'] = copy.deepcopy(weights['data_Run2012C_PromptReco_v2'])
        if 'data_Run2012D_PromptReco_v1' in selComps.keys():
          weightsDataMass[mPoint]['data_Run2012D_PromptReco_v1'] = copy.deepcopy(weights['data_Run2012D_PromptReco_v1'])

	if 'embed_Run2012A_13Jul2012_v1' in selComps.keys():
          weightsDataMass[mPoint]['embed_Run2012A_13Jul2012_v1']  = copy.deepcopy(weights['embed_Run2012A_13Jul2012_v1'])
	if 'embed_Run2012A_recover_06Aug2012_v1' in selComps.keys():
          weightsDataMass[mPoint]['embed_Run2012A_recover_06Aug2012_v1'] = copy.deepcopy(weights['embed_Run2012A_recover_06Aug2012_v1'])
	if 'embed_Run2012B_13Jul2012_v4' in selComps.keys():
          weightsDataMass[mPoint]['embed_Run2012B_13Jul2012_v4']  = copy.deepcopy(weights['embed_Run2012B_13Jul2012_v4'])
	if 'embed_Run2012C_24Aug2012_v1' in selComps.keys():
          weightsDataMass[mPoint]['embed_Run2012C_24Aug2012_v1']  = copy.deepcopy(weights['embed_Run2012C_24Aug2012_v1'])
          weightsDataMass[mPoint]['embed_Run2012C_PromptReco_v2'] = copy.deepcopy(weights['embed_Run2012C_PromptReco_v2'])
	if 'embed_2012D_PromptReco_v1' in selComps.keys():
          weightsDataMass[mPoint]['embed_2012D_PromptReco_v1'] = copy.deepcopy(weights['embed_2012D_PromptReco_v1'])
      else:
        weightsDataMass[mPoint]['data_Run2011A_May10ReReco_v1']  = copy.deepcopy(weights['data_Run2011A_May10ReReco_v1'])
        weightsDataMass[mPoint]['data_Run2011A_PromptReco_v4']   = copy.deepcopy(weights['data_Run2011A_PromptReco_v4'])
        weightsDataMass[mPoint]['data_Run2011A_05Aug2011_v1']    = copy.deepcopy(weights['data_Run2011A_05Aug2011_v1'])
      weightsDataMass[mPoint]['DYJets']                        = copy.deepcopy(weights['DYJets'])
      weightsDataMass[mPoint]['WJets']                         = copy.deepcopy(weights['WJets'])
      weightsDataMass[mPoint]['WW']                            = copy.deepcopy(weights['WW'])
      weightsDataMass[mPoint]['WZ']                            = copy.deepcopy(weights['WZ'])
      weightsDataMass[mPoint]['ZZ']                            = copy.deepcopy(weights['ZZ'])
      weightsDataMass[mPoint]['TTJets']                        = copy.deepcopy(weights['TTJets'])
      weightsDataMass[mPoint]['T_tW']                          = copy.deepcopy(weights['T_tW'])
      weightsDataMass[mPoint]['Tbar_tW']                       = copy.deepcopy(weights['Tbar_tW'])
      weightsDataMass[mPoint]['HiggsGGH' +str(mPoint)]         = copy.deepcopy(weights['HiggsGGH' +str(mPoint)])
      weightsDataMass[mPoint]['HiggsVBF'+str(mPoint)]          = copy.deepcopy(weights['HiggsVBF'+str(mPoint)])
      weightsDataMass[mPoint]['HiggsVH' +str(mPoint)]          = copy.deepcopy(weights['HiggsVH' +str(mPoint)])
      
    return selCompsDataMass, weightsDataMass

def componentsWithOutData (selComps, weights) :

    selCompsMC110 = {}
    selCompsMC115 = {}
    selCompsMC120 = {}
    selCompsMC125 = {}
    selCompsMC130 = {}
    selCompsMC135 = {}
    selCompsMC140 = {}
    selCompsMC145 = {}

    weightsMC110 = {}
    weightsMC115 = {}
    weightsMC120 = {}
    weightsMC125 = {}
    weightsMC130 = {}
    weightsMC135 = {}
    weightsMC140 = {}
    weightsMC145 = {}

    selCompsMCMass = {110:selCompsData110,115:selCompsData115,120:selCompsData120,125:selCompsData125,130:selCompsData130,135:selCompsData135,140:selCompsData140,145:selCompsData145}
    weightsMCMass  = {110:weightsData110 ,115:weightsData115 ,120:weightsData120 ,125:weightsData125 ,130:weightsData130 ,135:weightsData135 ,140:weightsData140 ,145:weightsData145 }

    for mPoint in [110,115,120,125,130,135,140,145] :
    #for mPoint in [125] :
    
      selCompsMCMass[mPoint]['DYJets']               = copy.deepcopy(selComps['DYJets'])
      selCompsMCMass[mPoint]['WJets']                = copy.deepcopy(selComps['WJets'])
      selCompsMCMass[mPoint]['WW']                   = copy.deepcopy(selComps['WW'])
      selCompsMCMass[mPoint]['WZ']                   = copy.deepcopy(selComps['WZ'])
      selCompsMCMass[mPoint]['ZZ']                   = copy.deepcopy(selComps['ZZ'])
      selCompsMCMass[mPoint]['TTJets']               = copy.deepcopy(selComps['TTJets'])
      selCompsMCMass[mPoint]['HiggsGGH' +str(mPoint)] = copy.deepcopy(selComps['HiggsGGH' +str(mPoint)])
      selCompsMCMass[mPoint]['HiggsVBF'+str(mPoint)] = copy.deepcopy(selComps['HiggsVBF'+str(mPoint)])
      selCompsMCMass[mPoint]['HiggsVH' +str(mPoint)] = copy.deepcopy(selComps['HiggsVH' +str(mPoint)])

      weightsMCMass[mPoint]['DYJets']                = copy.deepcopy(weights['DYJets'])
      weightsMCMass[mPoint]['WJets']                 = copy.deepcopy(weights['WJets'])
      weightsMCMass[mPoint]['WW']                    = copy.deepcopy(weights['WW'])
      weightsMCMass[mPoint]['WZ']                    = copy.deepcopy(weights['WZ'])
      weightsMCMass[mPoint]['ZZ']                    = copy.deepcopy(weights['ZZ'])
      weightsMCMass[mPoint]['TTJets']                = copy.deepcopy(weights['TTJets'])
      weightsMCMass[mPoint]['HiggsGGH' +str(mPoint)] = copy.deepcopy(weights['HiggsGGH' +str(mPoint)])
      weightsMCMass[mPoint]['HiggsVBF'+str(mPoint)]  = copy.deepcopy(weights['HiggsVBF'+str(mPoint)])
      weightsMCMass[mPoint]['HiggsVH' +str(mPoint)]  = copy.deepcopy(weights['HiggsVH' +str(mPoint)])
      
    return selCompsMCMass, weightsMCMass

def componentsWithOutSignal (selComps, weights) :

    selCompsMCMass = {}
    weightsMCMass  = {}

    if run2012:
        if 'data_Run2012A_PromptReco_v1' in selComps.keys():
          selCompsMCMass['data_Run2012A_PromptReco_v1']  = copy.deepcopy(selComps['data_Run2012A_PromptReco_v1'])
        if 'data_Run2012B_PromptReco_v1' in selComps.keys():
          selCompsMCMass['data_Run2012B_PromptReco_v1']  = copy.deepcopy(selComps['data_Run2012B_PromptReco_v1'])
        if 'data_Run2012C_PromptReco_v1' in selComps.keys():
          selCompsMCMass['data_Run2012C_PromptReco_v1']   = copy.deepcopy(selComps['data_Run2012C_PromptReco_v1'])
          selCompsMCMass['data_Run2012C_PromptReco_v2']   = copy.deepcopy(selComps['data_Run2012C_PromptReco_v2'])
        if 'data_Run2012D_PromptReco_v1' in selComps.keys():
          selCompsMCMass['data_Run2012D_PromptReco_v1']   = copy.deepcopy(selComps['data_Run2012D_PromptReco_v1'])

	if 'embed_Run2012A_13Jul2012_v1' in selComps.keys():
          selCompsMCMass['embed_Run2012A_13Jul2012_v1']   = copy.deepcopy(selComps['embed_Run2012A_13Jul2012_v1'])
	if 'embed_Run2012A_recover_06Aug2012_v1' in selComps.keys():
          selCompsMCMass['embed_Run2012A_recover_06Aug2012_v1']   = copy.deepcopy(selComps['embed_Run2012A_recover_06Aug2012_v1'])
	if 'embed_Run2012B_13Jul2012_v4' in selComps.keys():
          selCompsMCMass['embed_Run2012B_13Jul2012_v4']   = copy.deepcopy(selComps['embed_Run2012B_13Jul2012_v4'])
	if 'embed_Run2012C_24Aug2012_v1' in selComps.keys():
            selCompsMCMass['embed_Run2012C_24Aug2012_v1']   = copy.deepcopy(selComps['embed_Run2012C_24Aug2012_v1'])
            selCompsMCMass['embed_Run2012C_PromptReco_v2']   = copy.deepcopy(selComps['embed_Run2012C_PromptReco_v2'])
	if 'embed_2012D_PromptReco_v1' in selComps.keys():
            selCompsMCMass['embed_2012D_PromptReco_v1']   = copy.deepcopy(selComps['embed_2012D_PromptReco_v1'])
    else:
        selCompsMCMass['data_Run2011A_May10ReReco_v1'] = copy.deepcopy(selComps['data_Run2011A_May10ReReco_v1'])
        selCompsMCMass['data_Run2011A_PromptReco_v4']  = copy.deepcopy(selComps['data_Run2011A_PromptReco_v4'])
        selCompsMCMass['data_Run2011A_05Aug2011_v1']   = copy.deepcopy(selComps['data_Run2011A_05Aug2011_v1'])
    selCompsMCMass['DYJets']	   = copy.deepcopy(selComps['DYJets'])
    selCompsMCMass['WJets']	   = copy.deepcopy(selComps['WJets'])
    selCompsMCMass['WW']	   = copy.deepcopy(selComps['WW'])
    selCompsMCMass['WZ']	   = copy.deepcopy(selComps['WZ'])
    selCompsMCMass['ZZ']	   = copy.deepcopy(selComps['ZZ'])
    selCompsMCMass['TTJets']	   = copy.deepcopy(selComps['TTJets'])
    selCompsMCMass['T_tW']	   = copy.deepcopy(selComps['T_tW'])
    selCompsMCMass['Tbar_tW']	   = copy.deepcopy(selComps['Tbar_tW'])

    if run2012:
        if 'data_Run2012A_PromptReco_v1' in selComps.keys():
          weightsMCMass['data_Run2012A_PromptReco_v1']   = copy.deepcopy(weights['data_Run2012A_PromptReco_v1'])
        if 'data_Run2012B_PromptReco_v1' in selComps.keys():
          weightsMCMass['data_Run2012B_PromptReco_v1']   = copy.deepcopy(weights['data_Run2012B_PromptReco_v1'])
        if 'data_Run2012C_PromptReco_v1' in selComps.keys():
          weightsMCMass['data_Run2012C_PromptReco_v1']   = copy.deepcopy(weights['data_Run2012C_PromptReco_v1'])
          weightsMCMass['data_Run2012C_PromptReco_v2']   = copy.deepcopy(weights['data_Run2012C_PromptReco_v2'])
        if 'data_Run2012D_PromptReco_v1' in selComps.keys():
          weightsMCMass['data_Run2012D_PromptReco_v1']   = copy.deepcopy(weights['data_Run2012D_PromptReco_v1'])

	if 'embed_Run2012A_13Jul2012_v1' in selComps.keys():
          weightsMCMass['embed_Run2012A_13Jul2012_v1']   = copy.deepcopy(weights['embed_Run2012A_13Jul2012_v1'])
	if 'embed_Run2012A_recover_06Aug2012_v1' in selComps.keys():
          weightsMCMass['embed_Run2012A_recover_06Aug2012_v1']   = copy.deepcopy(weights['embed_Run2012A_recover_06Aug2012_v1'])
	if 'embed_Run2012B_13Jul2012_v4' in selComps.keys():
          weightsMCMass['embed_Run2012B_13Jul2012_v4']   = copy.deepcopy(weights['embed_Run2012B_13Jul2012_v4'])
	if 'embed_Run2012C_24Aug2012_v1' in selComps.keys():
            weightsMCMass['embed_Run2012C_24Aug2012_v1']   = copy.deepcopy(weights['embed_Run2012C_24Aug2012_v1'])
            weightsMCMass['embed_Run2012C_PromptReco_v2']   = copy.deepcopy(weights['embed_Run2012C_PromptReco_v2'])
	if 'embed_2012D_PromptReco_v1' in selComps.keys():
            weightsMCMass['embed_2012D_PromptReco_v1']   = copy.deepcopy(weights['embed_2012D_PromptReco_v1'])
    else:
        weightsMCMass['data_Run2011A_May10ReReco_v1']  = copy.deepcopy(weights['data_Run2011A_May10ReReco_v1'])
        weightsMCMass['data_Run2011A_PromptReco_v4']   = copy.deepcopy(weights['data_Run2011A_PromptReco_v4'])
        weightsMCMass['data_Run2011A_05Aug2011_v1']    = copy.deepcopy(weights['data_Run2011A_05Aug2011_v1'])
    weightsMCMass['DYJets']		   = copy.deepcopy(weights['DYJets'])
    weightsMCMass['WJets']		   = copy.deepcopy(weights['WJets'])
    weightsMCMass['WW'] 		   = copy.deepcopy(weights['WW'])
    weightsMCMass['WZ'] 		   = copy.deepcopy(weights['WZ'])
    weightsMCMass['ZZ'] 		   = copy.deepcopy(weights['ZZ'])
    weightsMCMass['TTJets']		   = copy.deepcopy(weights['TTJets'])
    weightsMCMass['T_tW']		   = copy.deepcopy(weights['T_tW'])
    weightsMCMass['Tbar_tW']		   = copy.deepcopy(weights['Tbar_tW'])

    return selCompsMCMass, weightsMCMass