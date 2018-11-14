import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

inputDir = "/cms/data/store/user/klo/HZZ4l/ZXData_Early2018/"
outputDir = "/cms/data/store/user/t2/users/klo/Higgs/DarkZ/NTuples/Data_Run2018/ZXData_Oct18_v1/"

# ____________________________________________________________________________ ||
inputDir        = "/cms/data/store/user/t2/users/klo/Higgs/DarkZ/NTuples/Data_Run2018/ZXData_Oct18_v1/"
pdNames         = ["SingleMuon","DoubleMuon","MuonEG","EGamma",]
treeName        = "Ana/passedEvents"
outputDir       = "/raid/raid7/lucien/Higgs/HZZ4l/NTuple/ZPlusX/ZXCR/20181113/"
inUFTier2       = True

# ____________________________________________________________________________ ||
ROOT.gSystem.Load("ZXTreeSkimmer_h.so")
zxTreeSkimmer = ROOT.ZXTreeSkimmer()

makedirs(outputDir)
for pdName in pdNames:
    fileNames = listdir_uberftp(os.path.join(inputDir,pdName))
    for fName in fileNames:
        filePath = os.path.join(inputDir,pdName,fName)
        fileInfo = FileInfo(filePath,inUFTier2)
        print "*"*20
        print "Processing "+filePath
        zxTreeSkimmer.makeSkim(fileInfo.file_path(),treeName,os.path.join(outputDir,fName))
