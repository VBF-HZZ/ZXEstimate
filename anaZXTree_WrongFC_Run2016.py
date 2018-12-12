import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/HZZ4l/NTuple/ZPlusX/WrongFC/20181209/SkimTree_WrongFC_Run2016Data_v1/Data_Run2016-03Feb2017_4l_noDuplicates.root"
treeName        = "passedEvents"
elFilePath      = "Data/FakeRate/Run2016/fakeRate.root"
muFilePath      = "Data/FakeRate/Run2016/fakeRate.root"
isoElCut        = 0.35
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/HZZ4l/NTuple/ZPlusX/WrongFC/20181209/SkimTree_WrongFC_Run2016Data_v1/"
TFileName       = "Data_Run2016-03Feb2017_4l_noDuplicates_FRWeight.root"

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
