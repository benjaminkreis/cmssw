import FWCore.ParameterSet.Config as cms

import os 
rootfile_dir = os.environ['CMSSW_BASE'] + '/src/CMGTools/Common/data'
centraldir = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/PileUp'

vertexWeightEPSJul8 = cms.EDProducer(
    "VertexWeightProducer",
    verbose = cms.untracked.bool( False ),
    src = cms.InputTag('addPileupInfo'),
    inputHistMC = cms.string( rootfile_dir + '/Pileup_Summer11MC.root'),
    inputHistData = cms.string( centraldir + '/Pileup_2011_EPS_8_jul.root'),
    )
