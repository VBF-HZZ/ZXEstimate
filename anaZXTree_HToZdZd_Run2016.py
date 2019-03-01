import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190218/SkimTree_HToZdZd_ZX_Run2016Data_m4l70_noZCandRatioCut/Data_Run2016-2l_noDuplicates.root"
treeName        = "passedEvents"
elFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/fakeRate2016_20190115.root"
muFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/fakeRate2016_20190115.root"
isoElCut        = 0.35
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190218/SkimTree_HToZdZd_ZX_Run2016Data_m4l70_noZCandRatioCut/"
TFileName       = "Data_Run2016-2l_noDuplicates_FRWeight.root"

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
ana.loop(inputPath,treeName)
