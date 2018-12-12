import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputDir        = "/raid/raid7/lucien/Higgs/HZZ4l/NTuple/ZPlusX/ZXCR/20181129_Run2018/Z1L/"
pdNames         = ["SingleMuon","DoubleMuon","MuonEG","EGamma",]
treeName        = "Ana/passedEvents"
outputDir       = "/raid/raid7/lucien/Higgs/HZZ4l/NTuple/ZPlusX/ZXCR/20181212_Run2018_ZXCR-Z1LSkim/"
inUFTier2       = False

# ____________________________________________________________________________ ||
ROOT.gSystem.Load("include/ZXTreeSkimmer_h.so")
zxTreeSkimmer = ROOT.ZXTreeSkimmer()

makedirs(outputDir)
for pdName in pdNames:
    filePath = os.path.join(inputDir,pdName+"_Run2018.root")
    print "*"*20
    print "Processing "+filePath
    zxTreeSkimmer.makeSkim(filePath,treeName,os.path.join(outputDir,pdName+"_Run2018.root"))
