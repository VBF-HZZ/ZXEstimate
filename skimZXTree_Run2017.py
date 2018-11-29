import ROOT,os,argparse,glob
from PyUtils.UFTier2 import listdir_uberftp,t2_prefix,FileInfo
from PyUtils.Shell import makedirs 

# ____________________________________________________________________________ ||
inputDir        = "/cms/data/store/user/t2/users/klo/Higgs/DarkZ/NTuples/ZPlusX_Early2017_v1/"
treeName        = "Ana/passedEvents"
outputDir       = "/raid/raid7/lucien/Higgs/HZZ4l/NTuple/ZPlusX/ZXCR/20181129/"
inUFTier2       = True
fileNames       = [
                    "TTJets.root",    
                    "DYJetsToLL_M50.root",  
                    "DYJetsToLL_M10To50.root",  
                    "WZTo3LNu.root",  
                    "Data_Run2017-17Nov2017.root",      
        ]

# ____________________________________________________________________________ ||
ROOT.gSystem.Load("include/ZXTreeSkimmer_h.so")
zxTreeSkimmer = ROOT.ZXTreeSkimmer()

makedirs(outputDir)
for fName in fileNames:
    filePath = os.path.join(inputDir,fName)
    fileInfo = FileInfo(filePath,inUFTier2)
    print "*"*20
    print "Processing "+filePath
    zxTreeSkimmer.makeSkim(fileInfo.file_path(),treeName,os.path.join(outputDir,fName))
