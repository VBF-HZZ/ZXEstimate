import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190121/SkimTree_WrongFC_Run2016Data_v1/Data_Run2017-17Nov2017-v1_noDuplicates.root"
treeName        = "passedEvents"
elFilePath      = "Data/fakeRate2017_20190115.root"
muFilePath      = "Data/fakeRate2017_20190115.root"
isoElCut        = 9999999.
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190121/SkimTree_WrongFC_Run2017Data_v1/"
TFileName       = "Data_Run2017-17Nov2017-v1_noDuplicates_FRWeight.root"

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
