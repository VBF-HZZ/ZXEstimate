#ifndef TreeSkimmer_h
#define TreeSkimmer_h

//#include "Linkdef.h"
#include "Library.h"

//TString fOptionWrite = "RECREATE";
//TString fOptionRead = "READ";

class TreeSkimmer : public TObject {
        TTree* inTree;
        TTree* outTree;
    public:
        TreeSkimmer();
        ~TreeSkimmer();
        ClassDef(TreeSkimmer,1);
        void makeSkim(TString inputPath, TString inputTreeName, TString outputPath);
        virtual bool passSelection();
        virtual void setTreeStatus(TTree* tree);
        virtual void setTree(TTree* tree);
};

ClassImp(TreeSkimmer) 

TreeSkimmer::TreeSkimmer(){

};

TreeSkimmer::~TreeSkimmer(){

};

bool TreeSkimmer::passSelection(){
    return true;
};

void TreeSkimmer::setTreeStatus(TTree* tree){

}

void TreeSkimmer::setTree(TTree* tree){

}

void TreeSkimmer::makeSkim(TString inputPath, TString inputTreeName, TString outputPath){
    TFile* outFile = new TFile(outputPath, fOptionWrite);

    //TFile *inFile = new TFile(inputPath, fOptionRead);
    TFile *inFile = TFile::Open(inputPath, fOptionRead);
    inTree = (TTree*) inFile->Get(inputTreeName); 
    setTreeStatus(inTree);

    outTree = inTree->CloneTree(0);
    outTree->CopyAddresses(inTree);

    // get branches
    setTree(inTree);
    
    Long64_t nentries = inTree->GetEntries();

    for(int iEvt=0; iEvt < nentries; iEvt++){
        inTree->GetEntry(iEvt);

        if(iEvt%100000==0) cout<<"Event "<<iEvt<<"/"<<inTree->GetEntries()<<endl;

        if (!passSelection()) continue;

        outTree->Fill();

    }

    outFile->cd();
    outTree->Write();
    outFile->Close();
}

#endif
