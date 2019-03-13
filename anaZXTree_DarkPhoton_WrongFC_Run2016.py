import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190307/SkimTree_DarkPhoton_WrongFC_Run2016Data_m4l70/Data_Run2016-03Feb2017_2l_noDuplicates.root"
treeName        = "passedEvents"
elFilePath      = "/raid/raid7/lucien/AnalysisCode/Higgs/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_el_2016.root"
muFilePath      = "/raid/raid7/lucien/AnalysisCode/Higgs/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_mu_2016.root"
isoElCut        = 0.35
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190307/SkimTree_DarkPhoton_WrongFC_Run2016Data_m4l70/"
TFileName       = "Data_Run2016-03Feb2017_2l_noDuplicates_FRWeightFromVukasin.root"

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
                "h1D_FRmu_EB",
                "h1D_FRmu_EE",
                "h1D_FRel_EB",
                "h1D_FRel_EE",
                )
ana.loop(inputPath,treeName)
