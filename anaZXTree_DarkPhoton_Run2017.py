import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20181116/SkimTree_DarkPhoton_ZX_Run2017Data_m4l70/Data_Run2017-17Nov2017_noDuplicates.root"
treeName        = "passedEvents"
isoElCut        = 999999.
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20181116/SkimTree_DarkPhoton_ZX_Run2017Data_m4l70/"

# ============================================================================ ||
# FRWeight
#elFilePath      = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate2017.root"
#muFilePath      = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate2017.root"
#TFileName       = "Data_Run2017-17Nov2017_noDuplicates_FRWeight.root"

# ============================================================================ ||
# FRWeight
#elFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/fakeRate2017_20190115.root"
#muFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/fakeRate2017_20190115.root"
#TFileName       = "Data_Run2017-17Nov2017_noDuplicates_FRWeightv2.root"

# ============================================================================ ||
# FRWeight from Vukasin
elFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_2017.root"
muFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/FakeRate_Vukasin_190301/fakeRates_2017.root"
TFileName       = "Data_Run2017-17Nov2017_noDuplicates_FRWeightFromVukasin.root"

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
#ana.getFile(inputPath)
#ana.getTree(treeName)
ana.loop(inputPath,treeName)
