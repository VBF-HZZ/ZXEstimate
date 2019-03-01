#include "include/ZXTree.h"
#include "include/UFUtils.h"

TString slimmedZXFileName=t2_prefix+"/store/user/t2/users/klo/Higgs/DarkZ/NTuples/Z1LSkim/Run2016/Data_Run2016_noDuplicates.root";
//TString file_path="/store/user/t2/users/klo/Higgs/DarkZ/NTuples/Z1LSkim/Run2016/Data_Run2016_noDuplicates.root";
//TString slimmedZXFileName="/raid/raid7/lucien/Higgs/DarkZ-NTuple/20180820/SkimTree_DarkPhoton_ZX_Run2016Data_v1/Data_Run2016_noDuplicates.root";
//TString slimmedZXFileName="/raid/raid7/lucien/Higgs/DarkZ-NTuple/20180823/SkimTree_Data80X_HIG-16-041-ZXCRSelectionWithFlag_v3_liteHZZAna/Data_Run2016_noDuplicates_1.root";
//TString slimmedZXFileName="/raid/raid5/predragm/Run2/HZZ4l/SubmitArea_13TeV/rootfiles_MC80X_2lskim_M17_Feb21/Data_ZX_Run2017-03Feb2017_slimmedZX.root";
//TString slimmedZXFileName="root://cmsio5.rc.ufl.edu//store/user/t2/users/dsperka/Run2/HZZ4l/SubmitArea_13TeV/rootfiles_Data80X_2lskim_M17_Feb21/SingleDoubleMuon_Run2016-03Feb2017.root";
//TString slimmedZXFileName="root://cmsio5.rc.ufl.edu//store/user/t2/users/dsperka/Run2/HZZ4l/SubmitArea_13TeV/rootfiles_Data80X_2lskim_M17_Feb21/SingleDoubleMuon_Run2016-03Feb2017.root";
//TString file_path="/store/user/t2/users/klo/Higgs/DarkZ/NTuples/ZPlusX_Early2017_v1/skimZ1L_Data_Run2017-17Nov2017_noDuplicates.root";
//TString slimmedZXFileName=t2_prefix+file_path;

//TString outputPath = "Data/fakeRate2017_20190115.root";
TString outputPath = "Data/fakeRate2016_20190115.root";

//double isoCutEl     = 999999.;
double isoCutEl     = 0.35;
double isoCutMu     = 0.35;
double metCut       = 25.; 
double massZ1Cut    = 4.;
double massZ1Diff   = 7.;
double muEtaCut     = 1.2;
double elEtaCut     = 1.497;
TString treeName    = "passedEvents";
//TString treeName    = "selectedEvents";
//TString treeName    = "Ana/passedEvents";
double var_plotHigh = 80.0, var_plotLow = 0.0; int var_nBins = 8;
double binWidth     = ((int) (100*(var_plotHigh - var_plotLow)/var_nBins))/100.;
TString fOption     = "RECREATE";

void getEstimateFR( TTree* tree, 
                    TH1D* &h1D_FRel_EB,   TH1D* &h1D_FRel_EE,   TH1D* &h1D_FRmu_EB,   TH1D* &h1D_FRmu_EE,
                    TH1D* &h1D_FRel_EB_d, TH1D* &h1D_FRel_EE_d, TH1D* &h1D_FRmu_EB_d, TH1D* &h1D_FRmu_EE_d
                    );

void estimateFR(){
    
    TFile *f = TFile::Open(slimmedZXFileName);
    TTree* zxTree = (TTree*) f->Get(treeName);
    
    // define dummy histogram for FRs
    TH1D* h1D_dummy = new TH1D("dummy", "dummy", var_nBins, var_plotLow, var_plotHigh);

    // define FR numerator histograms
    TH1D* h1D_FRel_EB   = new TH1D("h1D_FRel_EB","h1D_FRel_EB",var_nBins, var_plotLow, var_plotHigh); h1D_FRel_EB->Sumw2();
    TH1D* h1D_FRel_EE   = new TH1D("h1D_FRel_EE","h1D_FRel_EE",var_nBins, var_plotLow, var_plotHigh); h1D_FRel_EE->Sumw2();
    TH1D* h1D_FRmu_EB   = new TH1D("h1D_FRmu_EB","h1D_FRmu_EB",var_nBins, var_plotLow, var_plotHigh); h1D_FRmu_EB->Sumw2();
    TH1D* h1D_FRmu_EE   = new TH1D("h1D_FRmu_EE","h1D_FRmu_EE",var_nBins, var_plotLow, var_plotHigh); h1D_FRmu_EE->Sumw2();

    // define FR denominator histograms
    TH1D* h1D_FRel_EB_d   = new TH1D("h1D_FRel_EB_d","h1D_FRel_EB_d",var_nBins, var_plotLow, var_plotHigh); h1D_FRel_EB_d->Sumw2();
    TH1D* h1D_FRel_EE_d   = new TH1D("h1D_FRel_EE_d","h1D_FRel_EE_d",var_nBins, var_plotLow, var_plotHigh); h1D_FRel_EE_d->Sumw2();
    TH1D* h1D_FRmu_EB_d   = new TH1D("h1D_FRmu_EB_d","h1D_FRmu_EB_d",var_nBins, var_plotLow, var_plotHigh); h1D_FRmu_EB_d->Sumw2();
    TH1D* h1D_FRmu_EE_d   = new TH1D("h1D_FRmu_EE_d","h1D_FRmu_EE_d",var_nBins, var_plotLow, var_plotHigh); h1D_FRmu_EE_d->Sumw2();

    getEstimateFR(zxTree,
              h1D_FRel_EB,   h1D_FRel_EE,   h1D_FRmu_EB,   h1D_FRmu_EE,
              h1D_FRel_EB_d, h1D_FRel_EE_d, h1D_FRmu_EB_d, h1D_FRmu_EE_d
              );
   
    // divide hists to get the fake rates
    h1D_FRel_EB->Divide(h1D_FRel_EB_d);
    h1D_FRel_EE->Divide(h1D_FRel_EE_d);
    h1D_FRmu_EB->Divide(h1D_FRmu_EB_d);
    h1D_FRmu_EE->Divide(h1D_FRmu_EE_d);

    TFile* fTemplateTree = new TFile(outputPath, fOption);
    fTemplateTree->cd();
    
    h1D_FRel_EB->SetName("h1D_FRel_EB"); h1D_FRel_EB->Write();
    h1D_FRel_EE->SetName("h1D_FRel_EE"); h1D_FRel_EE->Write();
    h1D_FRmu_EB->SetName("h1D_FRmu_EB"); h1D_FRmu_EB->Write();
    h1D_FRmu_EE->SetName("h1D_FRmu_EE"); h1D_FRmu_EE->Write();
    
    fTemplateTree->Close();

}

//_______________________________________________________________________________________________________________________________________________
void getEstimateFR( TTree* tree, 
                    TH1D* &h1D_FRel_EB,   TH1D* &h1D_FRel_EE,   TH1D* &h1D_FRmu_EB,   TH1D* &h1D_FRmu_EE,
                    TH1D* &h1D_FRel_EB_d, TH1D* &h1D_FRel_EE_d, TH1D* &h1D_FRmu_EB_d, TH1D* &h1D_FRmu_EE_d
                    ){

    // counters
    int nEvtPassedZXCRSelection = 0;
    int nEvt2P2FLeptons = 0;
    int nEvt3P1FLeptons = 0;
    int nFailedLeptonsZ2 = 0;

    setFRTree(tree);

    Long64_t nentries = tree->GetEntries();
    cout << "nentries: " << nentries << endl;
    
    int nEvtPassedZ1LSelection = 0;

    for(int iEvt=0; iEvt < nentries; iEvt++){
        tree->GetEntry(iEvt);

        if(iEvt%100000==0) cout<<"Event "<<iEvt<<"/"<<tree->GetEntries()<<endl;
        
        float weight = 1.;

        if (!passedZ1LSelection) continue;

        TLorentzVector lepTmp0, lepTmp1, lepTmp2;
        lepTmp0.SetPtEtaPhiM(lepFSR_pt->at(0),lepFSR_eta->at(0),lepFSR_phi->at(0),lepFSR_mass->at(0));
        lepTmp1.SetPtEtaPhiM(lepFSR_pt->at(1),lepFSR_eta->at(1),lepFSR_phi->at(1),lepFSR_mass->at(1));
        lepTmp2.SetPtEtaPhiM(lepFSR_pt->at(2),lepFSR_eta->at(2),lepFSR_phi->at(2),lepFSR_mass->at(2));
        int idTmp0=lep_id->at(0); int idTmp1=lep_id->at(1); int idTmp2=lep_id->at(2);
        double massZ1_01=0; double massZ1_12=0; double massZ1_02=0;
        if (lep_tightId->at(0) && ((lep_RelIsoNoFSR->at(0)<isoCutEl && abs(lep_id->at(0))==11) || (lep_RelIsoNoFSR->at(0)<isoCutMu && abs(lep_id->at(0))==13)) && lep_tightId->at(1) && ((lep_RelIsoNoFSR->at(1)<isoCutEl && abs(lep_id->at(1))==11) || (lep_RelIsoNoFSR->at(1)<isoCutMu && abs(lep_id->at(1))==13)) && (idTmp0+idTmp1)==0)
            massZ1_01=(lepTmp0+lepTmp1).M();
        if (lep_tightId->at(0) && ((lep_RelIsoNoFSR->at(0)<isoCutEl && abs(lep_id->at(0))==11) || (lep_RelIsoNoFSR->at(0)<isoCutMu && abs(lep_id->at(0))==13)) && lep_tightId->at(2) && ((lep_RelIsoNoFSR->at(2)<isoCutEl && abs(lep_id->at(2))==11) || (lep_RelIsoNoFSR->at(2)<isoCutMu && abs(lep_id->at(2))==13)) && (idTmp0+idTmp2)==0)
            massZ1_02=(lepTmp0+lepTmp2).M();
        if (lep_tightId->at(1) && ((lep_RelIsoNoFSR->at(1)<isoCutEl && abs(lep_id->at(1))==11) || (lep_RelIsoNoFSR->at(1)<isoCutMu && abs(lep_id->at(1))==13)) && lep_tightId->at(2) && ((lep_RelIsoNoFSR->at(2)<isoCutEl && abs(lep_id->at(2))==11) || (lep_RelIsoNoFSR->at(2)<isoCutMu && abs(lep_id->at(2))==13)) && (idTmp1+idTmp2)==0)
            massZ1_12=(lepTmp1+lepTmp2).M();

        if ((abs(pdg_massZ1-massZ1_01) < TMath::Min(abs(pdg_massZ1-massZ1_02), abs(pdg_massZ1-massZ1_12)))){
            lep_Hindex[2] = 2;
            massZ1 = massZ1_01;
        }else if ((abs(pdg_massZ1-massZ1_02) < abs(pdg_massZ1-massZ1_12))){
            lep_Hindex[2] = 1;
            massZ1 = massZ1_02;
        }else{
            lep_Hindex[2] = 0;
            massZ1 = massZ1_12;
        }

        if (!(massZ1 > massZ1Cut)) continue;
        if (!(met < metCut)) continue;
        if (!(abs(massZ1-pdg_massZ1) < massZ1Diff)) continue;

        nEvtPassedZ1LSelection++;

        int lep_tight = lep_tightId->at(lep_Hindex[2]);
        float lep_iso = lep_RelIsoNoFSR->at(lep_Hindex[2]);
        int idL3 = lep_id->at(lep_Hindex[2]);
//        TLorentzVector *lep = (TLorentzVector*) lep_p4->At(lep_Hindex[2]);
        TLorentzVector lep;
        lep.SetPtEtaPhiM(lep_pt->at(lep_Hindex[2]),lep_eta->at(lep_Hindex[2]),lep_phi->at(lep_Hindex[2]),lep_mass->at(lep_Hindex[2]));
        float pTL3  = lep.Pt();
        float etaL3 = lep.Eta();

        // fill 1D hists
        if ((abs(idL3) == 11) && (fabs(etaL3) < elEtaCut)) {
            h1D_FRel_EB_d->Fill(pTL3, weight);
            if (lep_tight && (lep_iso<isoCutEl)) {
                h1D_FRel_EB->Fill(pTL3, weight);
            }
        }
        if ((abs(idL3) == 11) && (fabs(etaL3) > elEtaCut)) {
            h1D_FRel_EE_d->Fill(pTL3, weight);
            if (lep_tight && (lep_iso<isoCutEl)) {
                h1D_FRel_EE->Fill(pTL3, weight);
            }
        }
        if ((abs(idL3) == 13) && (fabs(etaL3) < muEtaCut)) {
            h1D_FRmu_EB_d->Fill(pTL3, weight);
            if (lep_tight && (lep_iso<isoCutMu)) {
                h1D_FRmu_EB->Fill(pTL3, weight);
            }
        }
        if ((abs(idL3) == 13) && (fabs(etaL3) > muEtaCut)) {
            h1D_FRmu_EE_d->Fill(pTL3, weight);
            if (lep_tight && (lep_iso<isoCutMu)) {
                h1D_FRmu_EE->Fill(pTL3, weight);
            }
        }
    }
}
