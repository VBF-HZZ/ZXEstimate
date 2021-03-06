import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20181116/SkimTree_DarkPhoton_ZX_Run2016Data_m4l70/Data_Run2016-03Feb2017_noDuplicates.root"
treeName        = "passedEvents"
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20181116/SkimTree_DarkPhoton_ZX_Run2016Data_m4l70/"
isoElCut        = 0.35
isoMuCut        = 0.35

# ============================================================================ ||
# FRWeight
#elFilePath      = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate.root"
#muFilePath      = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate.root"
#TFileName       = "Data_Run2016-03Feb2017_noDuplicates_FRWeight.root"

# ============================================================================ ||
# FRWeight from Vukasin
elFilePath      = "/raid/raid7/lucien/AnalysisCode/Higgs/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_el_2016.root"
muFilePath      = "/raid/raid7/lucien/AnalysisCode/Higgs/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_mu_2016.root"
TFileName       = "Data_Run2016-03Feb2017_noDuplicates_FRWeightFromVukasin.root"

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
#ana.getFile(inputPath)
#ana.getTree(treeName)
ana.loop(inputPath,treeName)
