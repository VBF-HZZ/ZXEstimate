import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190218/SkimTree_HToZdZd_ZX_Run2017Data_m4l70_noZCandRatioCut/Data_Run2017-17Nov2017_noDuplicates.root"
treeName        = "passedEvents"
#elFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/fakeRate2017_20190115.root"
#muFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/fakeRate2017_20190115.root"
elFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_2017.root" 
muFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_2017.root" 
isoElCut        = 99999.
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190218/SkimTree_HToZdZd_ZX_Run2017Data_m4l70_noZCandRatioCut/"
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
                "Data_FRel_EB",
                "Data_FRel_EE",
                "Data_FRmu_EB",
                "Data_FRmu_EE",
                )
ana.loop(inputPath,treeName)
