import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20181116/SkimTree_DarkPhoton_ZX_Run2017Data_m4l70/Data_Run2017-17Nov2017_noDuplicates.root"
treeName        = "passedEvents"
elFilePath      = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate2017.root"
muFilePath      = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate2017.root"
isoElCut        = 999999.
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20181116/SkimTree_DarkPhoton_ZX_Run2016Data_m4l70/"
TFileName       = "Data_Run2017-17Nov2017_noDuplicates_FRWeight.root"

# ____________________________________________________________________________ ||
ROOT.gSystem.Load("include/ZXAnalyzer_h.so")
ana = ROOT.ZXAnalyzer(
                elFilePath,
                muFilePath,
                isoElCut,
                isoMuCut,
                outputDir,
                TFileName,
                "LiteHZZTree",
                )
#ana.getFile(inputPath)
#ana.getTree(treeName)
ana.loop(inputPath,treeName)
