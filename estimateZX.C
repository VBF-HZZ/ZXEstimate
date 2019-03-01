#include "include/ZXTree.h"

// globals
const double CUT_M4LLOW         = 118.;
const double CUT_M4LHIGH        = 130.;
const double m4lDivide          = 150.;
double isoCutEl                 = 999999.;
//double isoCutEl               = 0.35;
double isoCutMu                 = 0.35;

const TString sPlotsStore       = "plotsZX/";
const int SORT_EVENTS           = false;
int printOutWidth               = 12;

double var_plotHigh             = 600.0;
double var_plotLow              = 50.0;
double var_nBins                = 110;
double binWidth                 = ((int) (100*(var_plotHigh - var_plotLow)/var_nBins))/100.;

TString fr_hist_mu_EB           = "h1D_FRmu_EB";
TString fr_hist_mu_EE           = "h1D_FRmu_EE";
TString fr_hist_el_EB           = "h1D_FRel_EB";
TString fr_hist_el_EE           = "h1D_FRel_EE";
TString treeName                = "passedEvents";

TString fileNameTag             = "estimatesZX";
TString fOption                 = "RECREATE";
TString lineSplit               = "================================================";

//TString slimmedZXFileName       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20181107/SkimTree_DarkPhoton_ZX_Run2017Data_m4l70/Data_Run2017_noDuplicates.root";
TString slimmedZXFileName       = "/raid/raid7/lucien/Higgs/DarkZ-NTuple/20181116/SkimTree_DarkPhoton_ZX_Run2017Data_m4l70/Data_Run2017-17Nov2017_noDuplicates.root";

// get the FR histograms and slimmed ZX tree
//TString elFilePath = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate2017.root";
//TString muFilePath = "/home/lucien/Higgs/DarkZ/CMSSW_9_4_2/src/liteUFHZZ4LAnalyzer/Data/fakeRate2017.root";
TString elFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/fakeRate2017_20190115.root";
TString muFilePath      = "/home/lucien/Higgs/DarkZ/ZXEstimate/Data/fakeRate2017_20190115.root";

double getFR(int lep_id, double lep_pt, double lep_eta, TH1D* h1D_FRel_EB,   TH1D* h1D_FRel_EE,   TH1D* h1D_FRmu_EB,   TH1D* h1D_FRmu_EE);

void getEstimateZX(TString slimmedZXFileName);
int getEstimatesFromCR(TTree* tree,
                  TH1D* h1D_FRel_EB,   TH1D* h1D_FRel_EE,   TH1D* h1D_FRmu_EB,   TH1D* h1D_FRmu_EE,
                  TH1D* &h1D_m4l_SR_2P2F, TH1D* &h1D_m4l_SR_3P1F,
                  TH1D* &h1D_m4l_SR_2P2F_4mu, TH1D* &h1D_m4l_SR_3P1F_4mu,
                  TH1D* &h1D_m4l_SR_2P2F_4e, TH1D* &h1D_m4l_SR_3P1F_4e,
                  TH1D* &h1D_m4l_SR_2P2F_2e2mu, TH1D* &h1D_m4l_SR_3P1F_2e2mu
                  );

void estimateZX(){
    cout << lineSplit << endl;
    cout << "Using input: " << endl;
    cout << slimmedZXFileName << endl;
    cout << elFilePath << endl;
    cout << muFilePath << endl;
    cout << lineSplit << endl;
    getEstimateZX(slimmedZXFileName);
}

//_______________________________________________________________________________________________________________________________________________
double getFR(int lep_id, float lep_pt, float lep_eta, TH1D* h1D_FRel_EB,   TH1D* h1D_FRel_EE,   TH1D* h1D_FRmu_EB,   TH1D* h1D_FRmu_EE){
    if ((abs(lep_id) == 11) && (fabs(lep_eta) < 1.497)) return h1D_FRel_EB->GetBinContent(h1D_FRel_EB->FindBin(lep_pt));
    if ((abs(lep_id) == 11) && (fabs(lep_eta) > 1.497)) return h1D_FRel_EE->GetBinContent(h1D_FRel_EE->FindBin(lep_pt));
    if ((abs(lep_id) == 13) && (fabs(lep_eta) < 1.2)) return h1D_FRmu_EB->GetBinContent(h1D_FRmu_EB->FindBin(lep_pt));
    if ((abs(lep_id) == 13) && (fabs(lep_eta) > 1.2)) return h1D_FRmu_EE->GetBinContent(h1D_FRmu_EE->FindBin(lep_pt));
    return 0;
}

//_______________________________________________________________________________________________________________________________________________
void getEstimateZX(TString slimmedZXFileName){

    TFile* elFile = new TFile(elFilePath,"READ");
    TH1D* h1D_FRel_EB = (TH1D*) elFile->Get(fr_hist_el_EB);
    TH1D* h1D_FRel_EE = (TH1D*) elFile->Get(fr_hist_el_EE);
    
    TFile* muFile = new TFile(muFilePath,"READ");
    TH1D* h1D_FRmu_EB = (TH1D*) muFile->Get(fr_hist_mu_EB);
    TH1D* h1D_FRmu_EE = (TH1D*) muFile->Get(fr_hist_mu_EE);

    TFile *f = TFile::Open(slimmedZXFileName);
    TTree* zxTree = (TTree*) f->Get(treeName);

    // define dummy histogram for CRs
    TH1D* h1D_dummyCR = new TH1D("dummyCR", "dummyCR", var_nBins, var_plotLow, var_plotHigh);

    // define CR histograms
    TH1D* h1D_m4l_SR_2P2F       = new TH1D("h1D_m4l_SR_2P2F","h1D_m4l_SR_2P2F",var_nBins, var_plotLow, var_plotHigh); 
    h1D_m4l_SR_2P2F->Sumw2();
    TH1D* h1D_m4l_SR_2P2F_4mu   = new TH1D("h1D_m4l_SR_2P2F_4mu","h1D_m4l_SR_2P2F_4mu",var_nBins, var_plotLow, var_plotHigh); 
    h1D_m4l_SR_2P2F_4mu->Sumw2();
    TH1D* h1D_m4l_SR_2P2F_4e    = new TH1D("h1D_m4l_SR_2P2F_4e","h1D_m4l_SR_2P2F_4e",var_nBins, var_plotLow, var_plotHigh); 
    h1D_m4l_SR_2P2F_4e->Sumw2();
    TH1D* h1D_m4l_SR_2P2F_2e2mu = new TH1D("h1D_m4l_SR_2P2F_2e2mu","h1D_m4l_SR_2P2F_2e2mu",var_nBins, var_plotLow, var_plotHigh); 
    h1D_m4l_SR_2P2F_2e2mu->Sumw2();
    TH1D* h1D_m4l_SR_3P1F       = new TH1D("h1D_m4l_SR_3P1F","h1D_m4l_SR_3P1F",var_nBins, var_plotLow, var_plotHigh); 
    h1D_m4l_SR_3P1F->Sumw2();
    TH1D* h1D_m4l_SR_3P1F_4mu   = new TH1D("h1D_m4l_SR_3P1F_4mu","h1D_m4l_SR_3P1F_4mu",var_nBins, var_plotLow, var_plotHigh); 
    h1D_m4l_SR_3P1F_4mu->Sumw2();
    TH1D* h1D_m4l_SR_3P1F_4e    = new TH1D("h1D_m4l_SR_3P1F_4e","h1D_m4l_SR_3P1F_4e",var_nBins, var_plotLow, var_plotHigh); 
    h1D_m4l_SR_3P1F_4e->Sumw2();
    TH1D* h1D_m4l_SR_3P1F_2e2mu = new TH1D("h1D_m4l_SR_3P1F_2e2mu","h1D_m4l_SR_3P1F_2e2mu",var_nBins, var_plotLow, var_plotHigh); 
    h1D_m4l_SR_3P1F_2e2mu->Sumw2();

    // get histograms from tree AnaZX/passedEvents
    getEstimatesFromCR(zxTree, h1D_FRel_EB, h1D_FRel_EE, h1D_FRmu_EB, h1D_FRmu_EE, 
            h1D_m4l_SR_2P2F, h1D_m4l_SR_3P1F, 
            h1D_m4l_SR_2P2F_4mu, h1D_m4l_SR_3P1F_4mu, 
            h1D_m4l_SR_2P2F_4e, h1D_m4l_SR_3P1F_4e, 
            h1D_m4l_SR_2P2F_2e2mu, h1D_m4l_SR_3P1F_2e2mu
            );

    // total contribution (3P1F - 2P2F)
    TH1D* h1D_m4l_SR_tot = (TH1D*) h1D_m4l_SR_3P1F->Clone("h1D_m4l_SR_tot");
    h1D_m4l_SR_tot->Add(h1D_m4l_SR_2P2F, -1);

    // store slimmed tree and histograms in .root file
    TFile* fTemplateTree = new TFile(sPlotsStore+"/"+fileNameTag+".root", fOption);
    fTemplateTree->cd();
    h1D_FRel_EB->SetName("h1D_FRel_EB"); h1D_FRel_EB->Write();
    h1D_FRel_EE->SetName("h1D_FRel_EE"); h1D_FRel_EE->Write();
    h1D_FRmu_EB->SetName("h1D_FRmu_EB"); h1D_FRmu_EB->Write();
    h1D_FRmu_EE->SetName("h1D_FRmu_EE"); h1D_FRmu_EE->Write();
    h1D_m4l_SR_2P2F->SetName("h1D_m4l_SR_2P2F"); h1D_m4l_SR_2P2F->Write();
    h1D_m4l_SR_3P1F->SetName("h1D_m4l_SR_3P1F"); h1D_m4l_SR_3P1F->Write();
    h1D_m4l_SR_tot->SetName("h1D_m4l_SR_tot"); h1D_m4l_SR_tot->Write();
    fTemplateTree->Close();
}


//_______________________________________________________________________________________________________________________________________________
int getEstimatesFromCR(TTree* tree,
              TH1D* h1D_FRel_EB,   TH1D* h1D_FRel_EE,   TH1D* h1D_FRmu_EB,   TH1D* h1D_FRmu_EE,
              TH1D* &h1D_m4l_SR_2P2F, TH1D* &h1D_m4l_SR_3P1F,
              TH1D* &h1D_m4l_SR_2P2F_4mu, TH1D* &h1D_m4l_SR_3P1F_4mu,
              TH1D* &h1D_m4l_SR_2P2F_4e, TH1D* &h1D_m4l_SR_3P1F_4e,
              TH1D* &h1D_m4l_SR_2P2F_2e2mu, TH1D* &h1D_m4l_SR_3P1F_2e2mu)
              {

    // counters
    int nEvtPassedZXCRSelection = 0;
    int nEvt2P2FLeptons = 0;
    int nEvt3P1FLeptons = 0;
    int nFailedLeptonsZ2 = 0;

    // get branches
    //setZXTree(tree);
    setHZZLiteTree(tree);

    Long64_t nentries = tree->GetEntries();
    cout << "nentries: " << nentries << endl;

    int *index = new int[nentries];
    if (SORT_EVENTS) {
        tree->Draw("Event","","goff");
        int nentries_int = static_cast<int>(nentries);
        TMath::Sort(nentries_int, tree->GetV1(), index, false);
    }
    for(int iEvt=0; iEvt < nentries; iEvt++){
        if (SORT_EVENTS) {
            tree->GetEntry(index[iEvt]);
        } else {
            tree->GetEntry(iEvt);
        }

        // weight
        float weight = 1.;

        if (passedZXCRSelection &&
                mass4l > CUT_M4LLOW &&
                mass4l < CUT_M4LHIGH 
                ) {
            nEvtPassedZXCRSelection++;
            
            int lep_tight[4];
            float lep_iso[4];
            int idL[4];
            float pTL[4];
            float etaL[4];
            float phiL[4];
            for(unsigned int k = 0; k <= 3; k++) {
                //lep_tight[k] = lep_tightId->at(lep_Hindex[k]);
                //lep_iso[k]= lep_RelIsoNoFSR->at(lep_Hindex[k]);
                //idL[k] = lep_id->at(lep_Hindex[k]);

                lep_tight[k] = lep_tightId->at(lep_Hindex_stdvec->at(k));
                lep_iso[k]= lep_RelIsoNoFSR->at(lep_Hindex_stdvec->at(k));
                idL[k] = lep_id->at(lep_Hindex_stdvec->at(k));
                TLorentzVector lep;
                lep.SetPtEtaPhiM(lep_pt->at(lep_Hindex_stdvec->at(k)),lep_eta->at(lep_Hindex_stdvec->at(k)),lep_phi->at(lep_Hindex_stdvec->at(k)),lep_mass->at(lep_Hindex_stdvec->at(k)));
                //lep.SetPtEtaPhiM(lep_pt->at(lep_Hindex[k]),lep_eta->at(lep_Hindex[k]),lep_phi->at(lep_Hindex[k]),lep_mass->at(lep_Hindex[k]));
                pTL[k]  = lep.Pt();
                etaL[k] = lep.Eta();
                phiL[k] = lep.Phi();
            }

            // count the failed leptons
            nFailedLeptonsZ2 = !(lep_tight[2] && ((abs(idL[2])==11 && lep_iso[2]<0.35) || (abs(idL[2])==13 && lep_iso[2]<0.35))) + !(lep_tight[3] && ((abs(idL[3])==11 && lep_iso[3]<0.35) || (abs(idL[3])==13 && lep_iso[3]<0.35))); 
            
            if (nFailedLeptonsZ2 == 1) {
                nEvt3P1FLeptons++;
                float fr3 = getFR(idL[2], pTL[2], etaL[2], h1D_FRel_EB, h1D_FRel_EE, h1D_FRmu_EB, h1D_FRmu_EE);
                float fr4 = getFR(idL[3], pTL[3], etaL[3], h1D_FRel_EB, h1D_FRel_EE, h1D_FRmu_EB, h1D_FRmu_EE);
                float fr = (!(lep_tight[2] && ((abs(idL[2])==11 && lep_iso[2]<0.35) || (abs(idL[2])==13 && lep_iso[2]<0.35))))*(fr3/(1-fr3)) +
                            (!(lep_tight[3] && ((abs(idL[3])==11 && lep_iso[3]<0.35) || (abs(idL[3])==13 && lep_iso[3]<0.35))))*(fr4/(1-fr4));
                h1D_m4l_SR_3P1F->Fill(mass4l, weight * fr);
                if (finalState==4 || finalState==3) {
                    h1D_m4l_SR_3P1F_2e2mu->Fill(mass4l, weight * fr);
                };
                if (finalState==1) {
                    h1D_m4l_SR_3P1F_4mu->Fill(mass4l, weight * fr);
                };
                if (finalState==2) {
                    h1D_m4l_SR_3P1F_4e->Fill(mass4l, weight * fr);
                };
            }
            if (nFailedLeptonsZ2 == 2){
                nEvt2P2FLeptons++;
                float fr3 = getFR(idL[2], pTL[2], etaL[2], h1D_FRel_EB, h1D_FRel_EE, h1D_FRmu_EB, h1D_FRmu_EE);
                float fr4 = getFR(idL[3], pTL[3], etaL[3], h1D_FRel_EB, h1D_FRel_EE, h1D_FRmu_EB, h1D_FRmu_EE);
                float fr = (fr3/(1-fr3)) * (fr4/(1-fr4));
                h1D_m4l_SR_2P2F->Fill(mass4l, weight * fr);
                if (finalState==4 || finalState==3) {
                    h1D_m4l_SR_2P2F_2e2mu->Fill(mass4l, weight * fr);
                };
                if (finalState==1) {
                    h1D_m4l_SR_2P2F_4mu->Fill(mass4l, weight * fr);
                };
                if (finalState==2) {
                    h1D_m4l_SR_2P2F_4e->Fill(mass4l, weight * fr);
                };
            }
        }
    }

    cout  << setw(printOutWidth) << "selected events in ZX CRs:      " << nEvtPassedZXCRSelection << endl;
    cout  << setw(printOutWidth) << "selected events in 2P2F region: " << nEvt2P2FLeptons << endl;
    cout  << setw(printOutWidth) << "selected events in 3P1F region: " << nEvt3P1FLeptons << endl;

    cout  << setw(printOutWidth) << "int. contributions from 2P2F region: " << h1D_m4l_SR_2P2F->Integral(0,h1D_m4l_SR_2P2F->GetNbinsX()+1) << endl;
    cout  << setw(printOutWidth) << "int. contributions from 3P1F region: " << h1D_m4l_SR_3P1F->Integral(0,h1D_m4l_SR_3P1F->GetNbinsX()+1) << endl;
    cout  << setw(printOutWidth) << "Prediction from ZX CR (total): " << h1D_m4l_SR_3P1F->Integral(0,h1D_m4l_SR_3P1F->GetNbinsX()+1) - h1D_m4l_SR_2P2F->Integral(0,h1D_m4l_SR_2P2F->GetNbinsX()+1) << endl;
    cout  << setw(printOutWidth) << "Prediction from ZX CR (4mu):   " << h1D_m4l_SR_3P1F_4mu->Integral(0,h1D_m4l_SR_3P1F_4mu->GetNbinsX()+1) - h1D_m4l_SR_2P2F_4mu->Integral(0,h1D_m4l_SR_2P2F_4mu->GetNbinsX()+1) << endl;
    cout  << setw(printOutWidth) << "Prediction from ZX CR (4e):    " << h1D_m4l_SR_3P1F_4e->Integral(0,h1D_m4l_SR_3P1F_4e->GetNbinsX()+1) - h1D_m4l_SR_2P2F_4e->Integral(0,h1D_m4l_SR_2P2F_4e->GetNbinsX()+1) << endl;
    cout  << setw(printOutWidth) << "Prediction from ZX CR (2e2mu): " << h1D_m4l_SR_3P1F_2e2mu->Integral(0,h1D_m4l_SR_3P1F_2e2mu->GetNbinsX()+1) - h1D_m4l_SR_2P2F_2e2mu->Integral(0,h1D_m4l_SR_2P2F_2e2mu->GetNbinsX()+1) << endl;
    int divideBin = h1D_m4l_SR_3P1F->GetXaxis()->FindBin(m4lDivide);
    int totBin = h1D_m4l_SR_3P1F->GetNbinsX();
    cout  << setw(printOutWidth) << "Prediction from ZX CR with m4l separation (total): " << h1D_m4l_SR_3P1F->Integral(0,divideBin) - h1D_m4l_SR_2P2F->Integral(0,divideBin) + h1D_m4l_SR_2P2F->Integral(divideBin,totBin+1) << endl;
    cout  << setw(printOutWidth) << "Prediction from ZX CR with m4l separation (4mu)  : " << h1D_m4l_SR_3P1F_4mu->Integral(0,divideBin) - h1D_m4l_SR_2P2F_4mu->Integral(0,divideBin) + h1D_m4l_SR_2P2F_4mu->Integral(divideBin,totBin+1) << endl;
    cout  << setw(printOutWidth) << "Prediction from ZX CR with m4l separation (4e)   : " << h1D_m4l_SR_3P1F_4e->Integral(0,divideBin) - h1D_m4l_SR_2P2F_4e->Integral(0,divideBin) + h1D_m4l_SR_2P2F_4e->Integral(divideBin,totBin+1) << endl;
    cout  << setw(printOutWidth) << "Prediction from ZX CR with m4l separation (2e2mu): " << h1D_m4l_SR_3P1F_2e2mu->Integral(0,divideBin) - h1D_m4l_SR_2P2F_2e2mu->Integral(0,divideBin) + h1D_m4l_SR_2P2F_2e2mu->Integral(divideBin,totBin+1) << endl;

    return 0;
}
