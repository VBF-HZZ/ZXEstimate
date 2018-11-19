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

const double pdg_massZ1 = 91.1876;

// define vars and branches
float mass4l,massZ1,massZ2;
float eventWeight, dataMCWeight, crossSection;
ULong64_t Run, LumiSect, Event;
int finalState, nVtx;
bool passedFullSelection, passedZ1LSelection, passedZXCRSelection, passedZ4lSelection;
vector<float> *lep_pt = 0; TBranch *b_lep_pt = 0;
vector<float> *lep_eta = 0; TBranch *b_lep_eta = 0;
vector<float> *lep_phi = 0; TBranch *b_lep_phi = 0;
vector<float> *lep_mass = 0; TBranch *b_lep_mass = 0;
vector<float> *lepFSR_pt = 0; TBranch *b_lepFSR_pt = 0;
vector<float> *lepFSR_eta = 0; TBranch *b_lepFSR_eta = 0;
vector<float> *lepFSR_phi = 0; TBranch *b_lepFSR_phi = 0;
vector<float> *lepFSR_mass = 0; TBranch *b_lepFSR_mass = 0;
int lep_Hindex[4];
vector<int>* lep_Hindex_stdvec = 0;
vector<int> *lep_id = 0; TBranch *b_lep_id = 0;
vector<int> *lep_tightId = 0; TBranch *b_lep_tightId = 0;
vector<float> *lep_RelIsoNoFSR = 0; TBranch *b_lep_RelIsoNoFSR = 0;
float met = 0.;

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

void setTree( TTree* tree, bool isHZZTree=false
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
    tree->SetBranchAddress("met",&met);
    if (isHZZTree) {
        tree->SetBranchAddress("lep_Hindex",&lep_Hindex);
    } else {
        tree->SetBranchAddress("lep_Hindex",&lep_Hindex_stdvec);
    };
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

void setTreeStatus(TTree* tree){
    tree->SetBranchStatus("*",0);

    tree->SetBranchStatus("Run",1);
    tree->SetBranchStatus("LumiSect",1);
    tree->SetBranchStatus("Event",1);
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
    tree->SetBranchStatus("passedZ4lSelection",1);
    tree->SetBranchStatus("passedZ1LSelection",1);
    tree->SetBranchStatus("passedFullSelection",1);
    tree->SetBranchStatus("passedZXCRSelection",1);
    tree->SetBranchStatus("finalState",1);
    tree->SetBranchStatus("dataMCWeight",1);
    tree->SetBranchStatus("mass4l",1);
    tree->SetBranchStatus("massZ1",1);
    tree->SetBranchStatus("massZ2",1);
    tree->SetBranchStatus("met",1);

}
