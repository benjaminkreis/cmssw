import sys,os

# REMOVE DATASET NAMES CONTAINING:

remove = ["http","prime","Grav","SUSY","QstarTo","RSGluonTo","WRTo","TstarTstar","Unpart","LQTo","Radion","BstarTo",
          "HToZZ","HToWW","HToG","HToT","/ADD","GJet","GluGluToZZ","TTbarDM","HToInvisible","WToENu_M","WToMuNu_M","WToTauNu_M",
          "ttHJetToGG","ttHJetToNonbb","ttHJetToTT","Muminus_Pt","/Muplus","Photon","SinglePion","ZZTo4L","DoubleElectron",
          "SingleEta","tGamma","JPsiToMuMu","JpsiToMuMu","mtop1"]

# FILELIST OF AVAILABLE DATASETS ON DAS AS VALID

# das_valid = [line.rstrip('\n').rstrip('\r') for line in open('all_datasets_MCRUN2_25ns.txt')]
das_valid = os.popen('python ./das_client.py --limit=0 --query="dataset=/*/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v*/MINIAODSIM"').read().split('\n')
das_valid = filter(None, das_valid)

# FILELIST OF AVAILABLE DATASETS ON DAS AS PRODUCTION

das_production = os.popen('python ./das_client.py --limit=0 --query="dataset dataset=/*/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v*/MINIAODSIM status=PRODUCTION"').read().split('\n')
das_production = filter(None, das_production)

# FILTER DATASETS WITH REMOVE LIST
for i in remove:
  das_valid = [ x for x in das_valid if i not in x ]
  das_production = [ x for x in das_production if i not in x ]

# CHECK EXISTING LIST OF DATASETS TO BE PROCESSED

vhbb_all = open('datasets_MCRUN2_25ns.txt').read()

print '\nDATASETS AVAILABLE ON DAS AS VALID AND NOT (YET) INCLUDED IN THE HBB LIST\n'
for line in das_valid:
  if line not in vhbb_all:
    print line
    
print '\nDATASETS AVAILABLE ON DAS AS PRODUCTION AND NOT (YET) INCLUDED IN THE HBB LIST\n'
for line in das_production:
  if line not in vhbb_all:
    print line
    