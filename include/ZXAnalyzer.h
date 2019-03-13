#ifndef ZXAnalyzer_h
#define ZXAnalyzer_h

#include "Analyzer.h"
#include "ZXTree.h"
#include "deltaR.h"
//#include "Linkdef.h"

const TString tree_type_ZXTree = "ZXTree";
const TString tree_type_LiteHZZTree = "LiteHZZTree";

class ZXAnalyzer : public Analyzer 
{
    double ele_eta_cut = 1.497;
    double mu_eta_cut = 1.2;
    TString fr_hist_mu_EB = "h1D_FRmu_EB";
    TString fr_hist_mu_EE = "h1D_FRmu_EE";
    TString fr_hist_el_EB = "h1D_FRel_EB";
    TString fr_hist_el_EE = "h1D_FRel_EE";
    private:
        TFile* elFile=0;
        TFile* muFile=0;
        TFile* outFile=0;
        TH1D* h1D_FRel_EB=0;
        TH1D*h1D_FRel_EE=0;
        TH1D*h1D_FRmu_EB=0;
        TH1D*h1D_FRmu_EE=0;
        TTree* outTree;
        TString treeName="passedEvents";
        TString inputTreeType;
    public:
        ZXAnalyzer(
                TString elFilePath_in,
                TString muFilePath_in,
                double isoCutEl_in,
                double isoCutMu_in,
                TString outputDir_in,
                TString TFileName_in="ZXTree_FRWeight.root",
                TString inputTreeType_in="ZXTree",
                TString fr_hist_mu_EB_in = "h1D_FRmu_EB",
                TString fr_hist_mu_EE_in = "h1D_FRmu_EE",
                TString fr_hist_el_EB_in = "h1D_FRel_EB",
                TString fr_hist_el_EE_in = "h1D_FRel_EE"
                );
        double isoCutEl,isoCutMu;
        TString elFilePath,muFilePath;
        bool passSelection();
        void initTree();
        void process();
        void setup();
        void end();
        double getFR(int lep_id, float lep_pt, float lep_eta, TH1D* h1D_FRel_EB,   TH1D* h1D_FRel_EE,   TH1D* h1D_FRmu_EB,   TH1D* h1D_FRmu_EE);
        void setFR(TString elFilePath, TString muFilePath);
        TString TFileName = "ZXTree_FRWeight.root";
        float FRWeightProd;
        float FRWeightSum;
        float FRWeightL3;
        float FRWeightL4;
        float FRWeightProd_UniIso;
        float FRWeightProd_AsymIso;
        int nFailedLeptonsZ2;
        bool isHZZInput;
        float drIso = 0.3;
}; 

ZXAnalyzer::ZXAnalyzer(
                TString elFilePath_in,
                TString muFilePath_in,
                double isoCutEl_in,
                double isoCutMu_in,
                TString outputDir_in,
                TString TFileName_in,
                TString inputTreeType_in,
                TString fr_hist_mu_EB_in,
                TString fr_hist_mu_EE_in,
                TString fr_hist_el_EB_in,
                TString fr_hist_el_EE_in
                ){
    elFilePath      = elFilePath_in;
    muFilePath      = muFilePath_in;
    isoCutEl        = isoCutEl_in; 
    isoCutMu        = isoCutMu_in;
    outputDir       = outputDir_in;
    TFileName       = TFileName_in;
    inputTreeType   = inputTreeType_in;
    fr_hist_mu_EB   = fr_hist_mu_EB_in;
    fr_hist_mu_EE   = fr_hist_mu_EE_in;
    fr_hist_el_EB   = fr_hist_el_EB_in;
    fr_hist_el_EE   = fr_hist_el_EE_in;
}

void ZXAnalyzer::setup(){
    setFR(elFilePath,muFilePath);
    
    outFile = new TFile(outputDir+TFileName, fOptionWrite);

    outTree = tree->CloneTree(0);
    outTree->CopyAddresses(tree);

    outTree->Branch("FRWeightProd",&FRWeightProd,"FRWeightProd/F");
    outTree->Branch("FRWeightSum",&FRWeightSum,"FRWeightSum/F");
    outTree->Branch("FRWeightL3",&FRWeightL3,"FRWeightL3/F");
    outTree->Branch("FRWeightL4",&FRWeightL4,"FRWeightL4/F");
    outTree->Branch("FRWeightProd_UniIso",&FRWeightProd_UniIso,"FRWeightProd_UniIso/F");
    outTree->Branch("FRWeightProd_AsymIso",&FRWeightProd_AsymIso,"FRWeightProd_AsymIso/F");
    outTree->Branch("nFailedLeptonsZ2",&nFailedLeptonsZ2,"nFailedLeptonsZ2/I");

}

void ZXAnalyzer::end(){
    elFile->Close();
    muFile->Close();
    outFile->cd();
    outTree->Write(treeName,TObject::kOverwrite);
    outFile->Close();
}

void ZXAnalyzer::process(){
    float weight = 1.;
    int lep_tight[4];
    float lep_iso[4];
    int idL[4];
    float pTL[4];
    float etaL[4];
    float phiL[4];
    if (lep_pt->size() >= 4){
        for(unsigned int k = 0; k <= 3; k++) {
            
            TLorentzVector lep;
            if (inputTreeType == tree_type_ZXTree) {
                lep_tight[k] = lep_tightId->at(lep_Hindex[k]);
                lep_iso[k]= lep_RelIsoNoFSR->at(lep_Hindex[k]);
                idL[k] = lep_id->at(lep_Hindex[k]);
                lep.SetPtEtaPhiM(lep_pt->at(lep_Hindex[k]),lep_eta->at(lep_Hindex[k]),lep_phi->at(lep_Hindex[k]),lep_mass->at(lep_Hindex[k]));
            } else if (inputTreeType == tree_type_LiteHZZTree) {
                lep_tight[k] = lep_tightId->at(lep_Hindex_stdvec->at(k));
                lep_iso[k]= lep_RelIsoNoFSR->at(lep_Hindex_stdvec->at(k));
                idL[k] = lep_id->at(lep_Hindex_stdvec->at(k));
                lep.SetPtEtaPhiM(lep_pt->at(lep_Hindex_stdvec->at(k)),lep_eta->at(lep_Hindex_stdvec->at(k)),lep_phi->at(lep_Hindex_stdvec->at(k)),lep_mass->at(lep_Hindex_stdvec->at(k)));
            };
            pTL[k]  = lep.Pt();
            etaL[k] = lep.Eta();
            phiL[k] = lep.Phi();
        };

        nFailedLeptonsZ2 = !(lep_tight[2] && ((abs(idL[2])==11 && lep_iso[2]<isoCutEl) || (abs(idL[2])==13 && lep_iso[2]<isoCutMu))) + !(lep_tight[3] && ((abs(idL[3])==11 && lep_iso[3]<isoCutEl) || (abs(idL[3])==13 && lep_iso[3]<isoCutMu)));
 
        if (nFailedLeptonsZ2 == 1) {
            float fr3 = getFR(idL[2], pTL[2], etaL[2], h1D_FRel_EB, h1D_FRel_EE, h1D_FRmu_EB, h1D_FRmu_EE);
            float fr4 = getFR(idL[3], pTL[3], etaL[3], h1D_FRel_EB, h1D_FRel_EE, h1D_FRmu_EB, h1D_FRmu_EE);
            float fr = (!(lep_tight[2] && ((abs(idL[2])==11 && lep_iso[2]<isoCutEl) || (abs(idL[2])==13 && lep_iso[2]<isoCutMu))))*(fr3/(1-fr3)) +
                        (!(lep_tight[3] && ((abs(idL[3])==11 && lep_iso[3]<isoCutEl) || (abs(idL[3])==13 && lep_iso[3]<isoCutMu))))*(fr4/(1-fr4));
        
            FRWeightProd=fr;
            FRWeightSum=fr;
            FRWeightL3=fr3;
            FRWeightL4=fr4;
            if (lep_iso[2] > lep_iso[3]) {
                FRWeightProd_AsymIso=fr3;
            } else {

                FRWeightProd_AsymIso=fr4;
            }
            FRWeightProd_UniIso=fr;
        } else if (nFailedLeptonsZ2 == 2) {
            float fr3 = getFR(idL[2], pTL[2], etaL[2], h1D_FRel_EB, h1D_FRel_EE, h1D_FRmu_EB, h1D_FRmu_EE);
            float fr4 = getFR(idL[3], pTL[3], etaL[3], h1D_FRel_EB, h1D_FRel_EE, h1D_FRmu_EB, h1D_FRmu_EE);
            float fr = (fr3/(1-fr3)) * (fr4/(1-fr4));
            FRWeightProd=fr;
            FRWeightSum=fr3/(1-fr3)+fr4/(1-fr4);
            FRWeightL3=fr3/(1-fr3);
            FRWeightL4=fr4/(1-fr4);
            if (lep_iso[2] > lep_iso[3]) {
                FRWeightProd_AsymIso=fr3;
            } else {

                FRWeightProd_AsymIso=fr4;
            }
            float dr2 = deltaR2(etaL[2],phiL[2],etaL[3],phiL[3]);
            FRWeightProd_UniIso = ( fr3*fr4*dr2/4./drIso/drIso + sqrt(fr3*fr4)*(1.-sqrt(dr2)/2./drIso) ) / ( (1.-fr3)*(1.-fr4)*dr2/4./drIso/drIso + sqrt((1.-fr3)*(1.-fr4))*(1.-sqrt(dr2)/2./drIso) );  

        };
        outTree->Fill();
    };
}


bool ZXAnalyzer::passSelection(){
    return true;
}

void ZXAnalyzer::initTree(){
    if (inputTreeType == tree_type_ZXTree) {
        setHZZTreeStatus(tree);
        setHZZTree(tree);
    } else if (inputTreeType == tree_type_LiteHZZTree) {
        setHZZLiteTree(tree);
    }
}

void ZXAnalyzer::setFR(TString elFilePath, TString muFilePath){
    elFile = TFile::Open(elFilePath, fOptionRead);
    muFile = TFile::Open(muFilePath,fOptionRead);

    h1D_FRel_EB = (TH1D*) elFile->Get(fr_hist_el_EB);
    h1D_FRel_EE = (TH1D*) elFile->Get(fr_hist_el_EE);
    h1D_FRmu_EB = (TH1D*) muFile->Get(fr_hist_mu_EB);
    h1D_FRmu_EE = (TH1D*) muFile->Get(fr_hist_mu_EE);
}

double ZXAnalyzer::getFR(int lep_id, float lep_pt, float lep_eta, TH1D* h1D_FRel_EB,   TH1D* h1D_FRel_EE,   TH1D* h1D_FRmu_EB,   TH1D* h1D_FRmu_EE){
    if ((abs(lep_id) == 11) && (fabs(lep_eta) < ele_eta_cut)) return h1D_FRel_EB->GetBinContent(h1D_FRel_EB->FindBin(lep_pt));
    if ((abs(lep_id) == 11) && (fabs(lep_eta) > ele_eta_cut)) return h1D_FRel_EE->GetBinContent(h1D_FRel_EE->FindBin(lep_pt));
    if ((abs(lep_id) == 13) && (fabs(lep_eta) < mu_eta_cut)) return h1D_FRmu_EB->GetBinContent(h1D_FRmu_EB->FindBin(lep_pt));
    if ((abs(lep_id) == 13) && (fabs(lep_eta) > mu_eta_cut)) return h1D_FRmu_EE->GetBinContent(h1D_FRmu_EE->FindBin(lep_pt));
    return 0;
}


#endif
