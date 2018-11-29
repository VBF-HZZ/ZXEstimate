#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdio.h>

// ROOT includes
#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TChain.h>
#include <TLatex.h>
#include <TMath.h>
#include "TRandom.h"
#include <TFeldmanCousins.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <THStack.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TEfficiency.h>
#include <TLine.h>
#include <TPolyLine.h>
#include <TLegend.h>
#include <TLorentzVector.h>
#include "Math/VectorUtil.h"
#include "TClonesArray.h"

using namespace std;

void setFRTree( TTree* tree );
void setZXTree( TTree* tree );
void setHZZTreeStatus( TTree* tree );
void setHZZTree( TTree* tree );

const double pdg_massZ1 = 91.1876;

bool passedFullSelection, passedZ4lSelection;
bool passedZ1LSelection;
bool passedZXCRSelection, passedZ4lZXCRSelection;
bool passSmartCut;
int nZXCRFailedLeptons;
int nFailedLeptonsZ2;
int finalState;
//
bool passed_4l_reco,passed_properLep_ID,passed_LepTightID_Z1,passed_Lep_Leading_subleading;
bool passed_Lep_overlaping, passed_QCD_cut, passed_smartcut, passed_LepIso_Z2, passed_LepTightID_Z2;
bool passed_mZ1_mZ2,passed_Lep_OSSF; 
bool passed_LepIso_Z1;
int Event_NLeptons;
//
bool passTrig;
float pTL1, etaL1;
float pTL2, etaL2;
float pTL3, etaL3;
float pTL4, etaL4;
float phiL1, deltaphiL13;
float phiL2, deltaphiL14;
float phiL3, deltaphiL23;
float phiL4, deltaphiL24;
float deltaphiZZ;
int idL1, idL2, idL3, idL4;

float mass4l, mass4lErr;
float mass3l;
float mass4lREFIT, mass4lErrREFIT;
float massZ1REFIT, massZ2REFIT;
float mass4mu, mass4e, mass2e2mu;
float pT4l;
float massZ1, massZ1_Z1L, massZ2;
int njets_pt30_eta4p7;
int njets_pt30_eta2p5;
float pTj1, etaj1;
float pTj2, etaj2;
float qgj1, qgj2;
float pTj1_2p5, pTj2_2p5;

float D_bkg_kin;
float D_bkg;
float Dgg10_VAMCFM;
float D_g4;
float D_g1g4;
float D_VBF;
float D_VBF1j;
float D_HadWH;
float D_HadZH;
float D_VBF_QG;
float D_VBF1j_QG;
float D_HadWH_QG;
float D_HadZH_QG;

int EventCat;
int nisoleptons, nbjets_pt30_eta4p7;
float met,met_phi;

// input tree variables
std::string *triggersPassed;
ULong64_t Run, LumiSect, Event;
bool passedTrig;
bool passedFiducialSelection;
float dataMCWeight, genWeight, pileupWeight, crossSection, sumweight ;
float k_qqZZ_qcd_M,k_qqZZ_ewk,k_ggZZ;
float sumW;
int nVtx, nInt; //nPV
float me_qqZZ_MCFM;
float eventWeight;

int lep_Hindex[4];

std::vector<float>* lep_mass = 0;
std::vector<float> *lep_pt = 0; 
std::vector<float> *lep_eta = 0; 
std::vector<float> *lep_phi = 0;
std::vector<float>* lepFSR_mass = 0;
std::vector<float> *lepFSR_pt = 0; 
std::vector<float> *lepFSR_eta = 0; 
std::vector<float> *lepFSR_phi = 0;
std::vector<int> *lep_Hindex_stdvec = 0;

std::vector<int> *lep_tightId = 0;
std::vector<int> *lep_ecalDriven = 0;
std::vector<int> *lep_id = 0;
std::vector<int> *lep_Sip = 0;
std::vector<float> *lep_dxy = 0;
std::vector<float> *lep_dz = 0;
std::vector<float> *lep_RelIso = 0;
std::vector<float> *lep_RelIsoNoFSR = 0;
std::vector<float> *lep_pterr = 0;
std::vector<float> *lep_dataMC = 0;
std::vector<int> *lep_matchedR03_PdgId = 0;
std::vector<int> *lep_matchedR03_MomId = 0;
std::vector<int> *lep_matchedR03_MomMomId = 0;

std::vector<float> *jet_mass = 0;
std::vector<float> *jet_pt = 0; 
std::vector<float> *jet_eta = 0; 
std::vector<float> *jet_phi = 0;
std::vector<int> *jet_iscleanH4l = 0; 
std::vector<float> *jet_QGTagger = 0; 
std::vector<float> *jet_csvv2 = 0;

std::vector<int> *fsrPhotons_lepindex = 0;
std::vector<float> *fsrPhotons_pt = 0; 
std::vector<float> *fsrPhotons_eta = 0; 
std::vector<float> *fsrPhotons_phi = 0;
std::vector<float> *fsrPhotons_pterr = 0;

TBranch *b_lep_pt = 0;
TBranch *b_lep_eta = 0;
TBranch *b_lep_phi = 0;
TBranch *b_lep_mass = 0;
TBranch *b_lepFSR_pt = 0;
TBranch *b_lepFSR_eta = 0;
TBranch *b_lepFSR_phi = 0;
TBranch *b_lepFSR_mass = 0;
TBranch *b_lep_id = 0;
TBranch *b_lep_tightId = 0;
TBranch *b_lep_RelIso = 0;
TBranch *b_lep_RelIsoNoFSR = 0;
TBranch *b_lep_matchedR03_PdgId = 0;
TBranch *b_lep_matchedR03_MomId = 0;
TBranch *b_lep_matchedR03_MomMomId = 0;

void setFRTree( TTree* tree
                ){
    // get branches
    tree->SetBranchAddress("Run",&Run);
    tree->SetBranchAddress("LumiSect",&LumiSect);
    tree->SetBranchAddress("Event",&Event);
    tree->SetBranchAddress("crossSection",&crossSection);
    tree->SetBranchAddress("eventWeight",&eventWeight);
    tree->SetBranchAddress("dataMCWeight",&dataMCWeight);
    tree->SetBranchAddress("passedFullSelection",&passedFullSelection);
    tree->SetBranchAddress("passedZ1LSelection",&passedZ1LSelection);
    tree->SetBranchAddress("passedZXCRSelection",&passedZXCRSelection);
    tree->SetBranchAddress("passedZ4lSelection",&passedZ4lSelection);
    tree->SetBranchAddress("nVtx",&nVtx);
    tree->SetBranchAddress("finalState",&finalState);
    tree->SetBranchAddress("mass4l",&mass4l);
    tree->SetBranchAddress("massZ1",&massZ1);
    tree->SetBranchAddress("massZ2",&massZ2);
    tree->SetBranchAddress("met",&met);
    tree->SetBranchAddress("lep_Hindex",&lep_Hindex);
    tree->SetBranchAddress("lep_pt",&lep_pt,&b_lep_pt);
    tree->SetBranchAddress("lep_eta",&lep_eta,&b_lep_eta);
    tree->SetBranchAddress("lep_phi",&lep_phi,&b_lep_phi);
    tree->SetBranchAddress("lep_mass",&lep_mass,&b_lep_mass);
    tree->SetBranchAddress("lep_id",&lep_id,&b_lep_id);
    tree->SetBranchAddress("lep_tightId",&lep_tightId,&b_lep_tightId);
    tree->SetBranchAddress("lep_RelIsoNoFSR",&lep_RelIsoNoFSR,&b_lep_RelIsoNoFSR);
    tree->SetBranchAddress("lepFSR_pt",&lepFSR_pt,&b_lepFSR_pt);
    tree->SetBranchAddress("lepFSR_eta",&lepFSR_eta,&b_lepFSR_eta);
    tree->SetBranchAddress("lepFSR_phi",&lepFSR_phi,&b_lepFSR_phi);
    tree->SetBranchAddress("lepFSR_mass",&lepFSR_mass,&b_lepFSR_mass);
}

void setZXTree( TTree* tree
                ){
    tree->SetBranchAddress("Run",&Run);
    tree->SetBranchAddress("LumiSect",&LumiSect);
    tree->SetBranchAddress("Event",&Event);
    tree->SetBranchAddress("crossSection",&crossSection);
    tree->SetBranchAddress("eventWeight",&eventWeight);
    tree->SetBranchAddress("dataMCWeight",&dataMCWeight);
    tree->SetBranchAddress("passedFullSelection",&passedFullSelection);
    tree->SetBranchAddress("passedZ1LSelection",&passedZ1LSelection);
    tree->SetBranchAddress("passedZXCRSelection",&passedZXCRSelection);
    tree->SetBranchAddress("passedZ4lSelection",&passedZ4lSelection);
    tree->SetBranchAddress("nVtx",&nVtx);
    tree->SetBranchAddress("finalState",&finalState);
    tree->SetBranchAddress("mass4l",&mass4l);
    tree->SetBranchAddress("massZ1",&massZ1);
    tree->SetBranchAddress("massZ2",&massZ2);
    tree->SetBranchAddress("lep_Hindex",&lep_Hindex);
    tree->SetBranchAddress("lep_pt",&lep_pt,&b_lep_pt);
    tree->SetBranchAddress("lep_eta",&lep_eta,&b_lep_eta);
    tree->SetBranchAddress("lep_phi",&lep_phi,&b_lep_phi);
    tree->SetBranchAddress("lep_mass",&lep_mass,&b_lep_mass);
    tree->SetBranchAddress("lep_id",&lep_id,&b_lep_id);
    tree->SetBranchAddress("lep_tightId",&lep_tightId,&b_lep_tightId);
    tree->SetBranchAddress("lep_RelIsoNoFSR",&lep_RelIsoNoFSR,&b_lep_RelIsoNoFSR);
}

void setHZZTree( TTree* tree 
                ){ 
    tree->SetBranchAddress("Run",&Run); 
    tree->SetBranchAddress("LumiSect",&LumiSect); 
    tree->SetBranchAddress("Event",&Event); 
    tree->SetBranchAddress("crossSection",&crossSection); 
    tree->SetBranchAddress("eventWeight",&eventWeight); 
    tree->SetBranchAddress("dataMCWeight",&dataMCWeight);
    tree->SetBranchAddress("passedFullSelection",&passedFullSelection);
    tree->SetBranchAddress("passedZ1LSelection",&passedZ1LSelection);
    tree->SetBranchAddress("passedZXCRSelection",&passedZXCRSelection);
    tree->SetBranchAddress("passedZ4lSelection",&passedZ4lSelection);
    tree->SetBranchAddress("nVtx",&nVtx);
    tree->SetBranchAddress("finalState",&finalState);
    tree->SetBranchAddress("mass4l",&mass4l);
    tree->SetBranchAddress("mass4lErr",&mass4lErr);
    tree->SetBranchAddress("mass4lREFIT",&mass4lREFIT);
    tree->SetBranchAddress("mass4lErrREFIT",&mass4lErrREFIT);
    tree->SetBranchAddress("mass3l",&mass3l);
    tree->SetBranchAddress("massZ1",&massZ1);
    tree->SetBranchAddress("massZ2",&massZ2);
    tree->SetBranchAddress("met",&met);
    tree->SetBranchAddress("met_phi",&met_phi);
    tree->SetBranchAddress("D_bkg",&D_bkg);
    tree->SetBranchAddress("D_bkg_kin",&D_bkg_kin);
    tree->SetBranchAddress("lep_Hindex",&lep_Hindex);
    tree->SetBranchAddress("lep_pt",&lep_pt,&b_lep_pt);
    tree->SetBranchAddress("lep_eta",&lep_eta,&b_lep_eta);
    tree->SetBranchAddress("lep_phi",&lep_phi,&b_lep_phi);
    tree->SetBranchAddress("lep_mass",&lep_mass,&b_lep_mass);
    tree->SetBranchAddress("lep_id",&lep_id,&b_lep_id);
    tree->SetBranchAddress("lep_tightId",&lep_tightId,&b_lep_tightId);
    tree->SetBranchAddress("lep_RelIso",&lep_RelIso,&b_lep_RelIso);
    tree->SetBranchAddress("lep_RelIsoNoFSR",&lep_RelIsoNoFSR,&b_lep_RelIsoNoFSR);
    tree->SetBranchAddress("lepFSR_pt",&lepFSR_pt,&b_lepFSR_pt);
    tree->SetBranchAddress("lepFSR_eta",&lepFSR_eta,&b_lepFSR_eta);
    tree->SetBranchAddress("lepFSR_phi",&lepFSR_phi,&b_lepFSR_phi);
    tree->SetBranchAddress("lepFSR_mass",&lepFSR_mass,&b_lepFSR_mass);
    tree->SetBranchAddress("lep_matchedR03_PdgId",&lep_matchedR03_PdgId,&b_lep_matchedR03_PdgId);
    tree->SetBranchAddress("lep_matchedR03_MomId",&lep_matchedR03_MomId,&b_lep_matchedR03_MomId);
    tree->SetBranchAddress("lep_matchedR03_MomMomId",&lep_matchedR03_MomMomId,&b_lep_matchedR03_MomMomId);
}

void setHZZTreeStatus(TTree* tree){
    tree->SetBranchStatus("*",0);

    tree->SetBranchStatus("Run",1);
    tree->SetBranchStatus("LumiSect",1);
    tree->SetBranchStatus("Event",1);
    tree->SetBranchStatus("eventWeight",1);
    tree->SetBranchStatus("nVtx",1);
    tree->SetBranchStatus("crossSection",1);
    tree->SetBranchStatus("lep_id",1);
    tree->SetBranchStatus("lep_tightId",1);
    tree->SetBranchStatus("lep_pt",1);
    tree->SetBranchStatus("lep_eta",1);
    tree->SetBranchStatus("lep_phi",1);
    tree->SetBranchStatus("lep_mass",1);
    tree->SetBranchStatus("lep_RelIso",1);
    tree->SetBranchStatus("lep_RelIsoNoFSR",1);
    tree->SetBranchStatus("lepFSR_pt",1);
    tree->SetBranchStatus("lepFSR_eta",1);
    tree->SetBranchStatus("lepFSR_phi",1);
    tree->SetBranchStatus("lepFSR_mass",1);
    tree->SetBranchStatus("lep_Hindex",1);
    tree->SetBranchStatus("lep_matchedR03_PdgId",1);
    tree->SetBranchStatus("lep_matchedR03_MomId",1);
    tree->SetBranchStatus("lep_matchedR03_MomMomId",1);
    tree->SetBranchStatus("passedZ4lSelection",1);
    tree->SetBranchStatus("passedZ1LSelection",1);
    tree->SetBranchStatus("passedFullSelection",1);
    tree->SetBranchStatus("passedZXCRSelection",1);
    tree->SetBranchStatus("finalState",1);
    tree->SetBranchStatus("dataMCWeight",1);
    tree->SetBranchStatus("mass4l",1);
    tree->SetBranchStatus("mass4lErr",1);
    tree->SetBranchStatus("mass4lREFIT",1);
    tree->SetBranchStatus("mass4lErrREFIT",1);
    tree->SetBranchStatus("mass3l",1);
    tree->SetBranchStatus("massZ1",1);
    tree->SetBranchStatus("massZ2",1);
    tree->SetBranchStatus("met",1);
    tree->SetBranchStatus("met_phi",1);
    tree->SetBranchStatus("D_bkg",1);
    tree->SetBranchStatus("D_bkg_kin",1);
}


void setHZZLiteTree(TTree* tree){

   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("Run",1);
   tree->SetBranchStatus("LumiSect",1);
   tree->SetBranchStatus("Event",1);
   tree->SetBranchStatus("nVtx",1);
   tree->SetBranchStatus("passedTrig",1);
   tree->SetBranchStatus("passedFullSelection",1);
   tree->SetBranchStatus("passedZ4lSelection",1);
   tree->SetBranchStatus("passedZXCRSelection",1);
   tree->SetBranchStatus("passSmartCut",1);
   tree->SetBranchStatus("nZXCRFailedLeptons",1);
   tree->SetBranchStatus("finalState",1);
   tree->SetBranchStatus("dataMCWeight",1);
   tree->SetBranchStatus("pileupWeight",1);
   tree->SetBranchStatus("genWeight",1);
   tree->SetBranchStatus("sumWeight",1);
   tree->SetBranchStatus("crossSection",1);
   tree->SetBranchStatus("k_qqZZ_qcd_M",1);
   tree->SetBranchStatus("k_qqZZ_ewk",1);
   tree->SetBranchStatus("k_ggZZ",1);
   tree->SetBranchStatus("lep_id",1);
   tree->SetBranchStatus("lep_pt",1);
   tree->SetBranchStatus("lep_eta",1);
   tree->SetBranchStatus("lep_phi",1);
   tree->SetBranchStatus("lep_mass",1);
   tree->SetBranchStatus("lep_tightId",1);
   tree->SetBranchStatus("lep_RelIso",1);
   tree->SetBranchStatus("lep_RelIsoNoFSR",1);
   tree->SetBranchStatus("lep_Hindex",1);
   tree->SetBranchStatus("pTL1",1);
   tree->SetBranchStatus("pTL2",1);
   tree->SetBranchStatus("pTL3",1);
   tree->SetBranchStatus("pTL4",1);
   tree->SetBranchStatus("idL1",1);
   tree->SetBranchStatus("idL2",1);
   tree->SetBranchStatus("idL3",1);
   tree->SetBranchStatus("idL4",1);
   tree->SetBranchStatus("etaL1",1);
   tree->SetBranchStatus("etaL2",1);
   tree->SetBranchStatus("etaL3",1);
   tree->SetBranchStatus("etaL4",1);
   tree->SetBranchStatus("phiL1",1);
   tree->SetBranchStatus("phiL2",1);
   tree->SetBranchStatus("phiL3",1);
   tree->SetBranchStatus("phiL4",1);
   tree->SetBranchStatus("deltaphiL13",1);
   tree->SetBranchStatus("deltaphiL14",1);
   tree->SetBranchStatus("deltaphiL23",1);
   tree->SetBranchStatus("deltaphiL24",1);
   tree->SetBranchStatus("deltaphiZZ",1);
   tree->SetBranchStatus("mass4l",1);
   tree->SetBranchStatus("mass4mu",1);
   tree->SetBranchStatus("mass4e",1);
   tree->SetBranchStatus("mass2e2mu",1);
   tree->SetBranchStatus("pT4l",1);
   tree->SetBranchStatus("massZ1",1);
   tree->SetBranchStatus("massZ2",1);
   tree->SetBranchStatus("njets_pt30_eta4p7",1);
   tree->SetBranchStatus("njets_pt30_eta2p5",1);
   tree->SetBranchStatus("met",1);
   tree->SetBranchStatus("pTj1",1);
   tree->SetBranchStatus("etaj1",1);
   tree->SetBranchStatus("qgj1",1);
   tree->SetBranchStatus("pTj2",1);
   tree->SetBranchStatus("etaj2",1);
   tree->SetBranchStatus("qgj2",1);
   tree->SetBranchStatus("pt_leadingjet_pt30_eta4p7",1);
   tree->SetBranchStatus("pt_leadingjet_pt30_eta2p5",1);

   tree->SetBranchAddress("Run", &Run);
   tree->SetBranchAddress("Event", &Event);
   tree->SetBranchAddress("LumiSect", &LumiSect);
   tree->SetBranchAddress("nVtx", &nVtx);
   tree->SetBranchAddress("passedTrig", &passedTrig);
   tree->SetBranchAddress("passedFullSelection", &passedFullSelection);
   tree->SetBranchAddress("passedZ4lSelection", &passedZ4lSelection);
   tree->SetBranchAddress("passedZXCRSelection", &passedZXCRSelection);
   tree->SetBranchAddress("passSmartCut", &passSmartCut);
   tree->SetBranchAddress("nZXCRFailedLeptons", &nZXCRFailedLeptons);
   tree->SetBranchAddress("finalState", &finalState);
   tree->SetBranchAddress("dataMCWeight", &dataMCWeight);
   tree->SetBranchAddress("pileupWeight", &pileupWeight);
   tree->SetBranchAddress("genWeight", &genWeight);
   tree->SetBranchAddress("sumweight", &sumweight);
   tree->SetBranchAddress("crossSection", &crossSection);
   tree->SetBranchAddress("k_qqZZ_qcd_M", &k_qqZZ_qcd_M);
   tree->SetBranchAddress("k_qqZZ_ewk", &k_qqZZ_ewk);
   tree->SetBranchAddress("k_ggZZ", &k_ggZZ);
   tree->SetBranchAddress("lep_id", &lep_id);
   tree->SetBranchAddress("lep_pt", &lep_pt);
   tree->SetBranchAddress("lep_eta", &lep_eta);
   tree->SetBranchAddress("lep_phi", &lep_phi);
   tree->SetBranchAddress("lep_mass", &lep_mass);
   tree->SetBranchAddress("lep_tightId", &lep_tightId);
   tree->SetBranchAddress("lep_RelIso", &lep_RelIso);
   tree->SetBranchAddress("lep_RelIsoNoFSR", &lep_RelIsoNoFSR);
   tree->SetBranchAddress("lep_Hindex", &lep_Hindex_stdvec);
   tree->SetBranchAddress("pTL1", &pTL1);
   tree->SetBranchAddress("pTL2", &pTL2);
   tree->SetBranchAddress("pTL3", &pTL3);
   tree->SetBranchAddress("pTL4", &pTL4);
   tree->SetBranchAddress("idL1", &idL1);
   tree->SetBranchAddress("idL2", &idL2);
   tree->SetBranchAddress("idL3", &idL3);
   tree->SetBranchAddress("idL4", &idL4);
   tree->SetBranchAddress("etaL1", &etaL1);
   tree->SetBranchAddress("etaL2", &etaL2);
   tree->SetBranchAddress("etaL3", &etaL3);
   tree->SetBranchAddress("etaL4", &etaL4);
   tree->SetBranchAddress("phiL1", &phiL1);
   tree->SetBranchAddress("phiL2", &phiL2);
   tree->SetBranchAddress("phiL3", &phiL3);
   tree->SetBranchAddress("phiL4", &phiL4);
   tree->SetBranchAddress("deltaphiL13", &deltaphiL13);
   tree->SetBranchAddress("deltaphiL14", &deltaphiL14);
   tree->SetBranchAddress("deltaphiL23", &deltaphiL23);
   tree->SetBranchAddress("deltaphiL24", &deltaphiL24);
   tree->SetBranchAddress("deltaphiZZ", &deltaphiZZ);
   tree->SetBranchAddress("mass4l", &mass4l);
   tree->SetBranchAddress("mass4mu", &mass4mu);
   tree->SetBranchAddress("mass4e", &mass4e);
   tree->SetBranchAddress("mass2e2mu", &mass2e2mu);
   tree->SetBranchAddress("pT4l", &pT4l);
   tree->SetBranchAddress("massZ1", &massZ1);
   tree->SetBranchAddress("massZ2", &massZ2);
   tree->SetBranchAddress("njets_pt30_eta4p7", &njets_pt30_eta4p7);
   tree->SetBranchAddress("njets_pt30_eta2p5", &njets_pt30_eta2p5);
   tree->SetBranchAddress("met", &met);
   tree->SetBranchAddress("pTj1", &pTj1);
   tree->SetBranchAddress("etaj1", &etaj1);
   tree->SetBranchAddress("qgj1", &qgj1);
   tree->SetBranchAddress("pTj2", &pTj2);
   tree->SetBranchAddress("etaj2", &etaj2);
   tree->SetBranchAddress("qgj2", &qgj2);
   //tree->SetBranchAddress("pt_leadingjet_pt30_eta4p7", &pt_leadingjet_pt30_eta4p7);
   //tree->SetBranchAddress("pt_leadingjet_pt30_eta2p5", &pt_leadingjet_pt30_eta2p5);

}
