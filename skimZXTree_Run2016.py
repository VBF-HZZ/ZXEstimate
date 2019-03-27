import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputDirData            = '/cms/data/store/user/t2/users/klo/Higgs/HZZ4l/NTuple/Run2/Data_80X_2lskim_M17_Feb02/'
bkgTreeDirT2_Feb21      = "/cms/data/store/user/t2/users/klo/Higgs/HZZ4l/NTuple/Run2/MC80X_M17_2l_Feb21/"
bkgTreeDirT2_Aug10      = "/cms/data/store/user/t2/users/klo/Higgs/HZZ4l/NTuple/Run2/MC80X_M17_2lskim_Aug10/"
inputTreeName           = "Ana/passedEvents"
outputDir               = "/raid/raid7/lucien/Higgs/HZZ4l/NTuple/ZPlusX/ZXCR/20190315_Run2016_ZXCR-Z1LSkim/"
inUFTier2               = True

fileNames = [
    inputDirData+"DoubleEG.root",
    inputDirData+"DoubleMuon.root",
    inputDirData+"MuonEG.root",
    inputDirData+"SingleElectron.root",
    inputDirData+"SingleMuon.root",
    bkgTreeDirT2_Feb21+"DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root",
    bkgTreeDirT2_Feb21+"TTJets_Dilept_TuneCUETP8M2T4_13TeV-amcatnloFXFX-pythia8.root",
    bkgTreeDirT2_Feb21+"WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root",
    bkgTreeDirT2_Aug10+"DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8.root",
    ]

# ____________________________________________________________________________ ||
ROOT.gSystem.Load("include/ZXTreeSkimmer_h.so")
zxTreeSkimmer = ROOT.ZXTreeSkimmer()

makedirs(outputDir)
for filePath in fileNames:
    fileInfo = FileInfo(filePath,inUFTier2)
    print "*"*20
    print "Processing "+filePath
    zxTreeSkimmer.makeSkim(fileInfo.file_path(),inputTreeName,os.path.join(outputDir,os.path.basename(filePath)))
