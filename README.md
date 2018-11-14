# ZXEstimate

##Installation
```
git clone git@github.com:VBF-HZZ/ZXEstimate.git
```

## Before running any code
```
source setup.sh
```

## Produce fake rate
```
root -b -q estimateFR.C
```

## Produce Z+X ntuples for Run 2018
```
cd include
root -b -q build_Analyzer.C
cd ..
python anaZXTree_Run2018.py
```
