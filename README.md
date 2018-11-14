## Installation
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

## Produce skimmed ntuples from the central HZZ ntuples (Run 2018)
```
cd include
root -b -q build_TreeSkimmer.C
cd ..
python skimZXTree_Run2018.py
```

## Produce Z+X ntuples with additional fake rate reweighting factors from skimmed ntuples (Run 2018)
```
cd include
root -b -q build_Analyzer.C
cd ..
python anaZXTree_Run2018.py
```
