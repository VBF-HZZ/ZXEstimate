import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/HZZ4l/NTuple/ZPlusX/ZXCR/20181113/Data_Run2018_noDuplicates.root"
treeName        = "passedEvents"
elFilePath      = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate2017.root"
muFilePath      = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate2017.root"
isoElCut        = 9999999.
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/HZZ4l/NTuple/ZPlusX/ZXCR/20181114/"

# ____________________________________________________________________________ ||
ROOT.gSystem.Load("include/ZXAnalyzer_h.so")
ana = ROOT.ZXAnalyzer(
                elFilePath,
                muFilePath,
                isoElCut,
                isoMuCut,
                outputDir,
                )
#ana.getFile(inputPath)
#ana.getTree(treeName)
ana.loop(inputPath,treeName)
