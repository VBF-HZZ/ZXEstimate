import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190408/SkimTree_DarkPhoton_Run2018Data_m4l70/Data_Run2018_UFHZZNTuple_noDuplicates.root"
treeName        = "passedEvents"
elFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_2018.root" 
muFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_2018.root" 
isoElCut        = 9999999.
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190408/SkimTree_DarkPhoton_Run2018Data_m4l70/"
TFileName       = "Data_Run2018_UFHZZNTuple_noDuplicates_FRWeight.root"

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
