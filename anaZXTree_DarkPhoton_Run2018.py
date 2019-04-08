import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputPath       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190402/SkimTree_DarkPhoton_Run2018Data_m4l70/Data_Run2018_noDuplicates.root"
treeName        = "passedEvents"
isoElCut        = 999999.
isoMuCut        = 0.35
outputDir       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20190402/SkimTree_DarkPhoton_ZX_Run2018Data_m4l70/"
elFilePath      = "Data/FakeRate_Vukasin_190326/FR_WZremoved_18.root"
muFilePath      = "Data/FakeRate_Vukasin_190326/FR_WZremoved_18.root"
TFileName       = "Data_Run2018_noDuplicates_FRWeightFromVukasinWZRemoved.root"

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
                #"h1D_FRmu_EB",
                #"h1D_FRmu_EE",
                #"h1D_FRel_EB",
                #"h1D_FRel_EE",
                "Data_FRmu_EB",
                "Data_FRmu_EE",
                "Data_FRel_EB",
                "Data_FRel_EE",
                )
#ana.getFile(inputPath)
#ana.getTree(treeName)
ana.loop(inputPath,treeName)
