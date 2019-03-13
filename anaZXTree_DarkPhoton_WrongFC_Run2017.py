import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190307/SkimTree_DarkPhoton_WrongFC_Run2017Data_m4l70/Data_Run2017-17Nov2017_noDuplicates.root"
treeName        = "passedEvents"
elFilePath      = "Data/FakeRate_Vukasin_190212/Hist_Data_ptl3_Data.root"
muFilePath      = "Data/FakeRate_Vukasin_190212/Hist_Data_ptl3_Data.root"
isoElCut        = 9999999.
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190307/SkimTree_DarkPhoton_WrongFC_Run2017Data_m4l70/"
TFileName       = "Data_Run2017-17Nov2017-v1_noDuplicates_FRWeightFromVukasin.root"

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
                "Data_FRmu_EB",
                "Data_FRmu_EE",
                "Data_FRel_EB",
                "Data_FRel_EE",
                )
ana.loop(inputPath,treeName)
