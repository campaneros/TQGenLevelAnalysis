
// last commit by $Id: analysis.cc,v 1.1 2013/01/31 15:32:00 soffi Exp $
//
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector2.h>
#include <TVector3.h>
#include <TAxis.h>

#include "AnalysisTQ.h"

using namespace std;

R__LOAD_LIBRARY(AnalysisTQ.cc+g);

int runTQ(std::string mass){
//  gROOT->ProcessLine(".L AnalysisTQ.cc+g");
  //  gROOT->ProcessLine("AnalysisTQ_cc.so");
  TH1F* h_counter;
  TChain t ("GenAnalysis/tree");
  if(mass=="5"){
    t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m5_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    TFile* f = new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m5_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    h_counter=(TH1F*)f->Get("GenAnalysis/h_counter");
  }else if(mass=="7"){
    t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m7_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    TFile* f = new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m7_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    h_counter=(TH1F*)f->Get("GenAnalysis/h_counter");
  }else if(mass=="9"){
    t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m9_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    TFile* f = new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m9_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    h_counter=(TH1F*)f->Get("GenAnalysis/h_counter");
  }else if(mass=="14"){
    t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m14_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    TFile* f = new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m14_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    h_counter=(TH1F*)f->Get("GenAnalysis/h_counter");
  }else if(mass=="18"){
    t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m18_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    TFile* f = new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m18_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    h_counter=(TH1F*)f->Get("GenAnalysis/h_counter");
  }else if(mass=="22"){
    t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m22_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    TFile* f = new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m22_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    h_counter=(TH1F*)f->Get("GenAnalysis/h_counter");
  }else if(mass=="26"){
    t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m26_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    TFile* f = new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m26_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
    h_counter=(TH1F*)f->Get("GenAnalysis/h_counter");
  }

  if(mass=="Run2018B"){
    t.Add("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/ntuple_MuOnia_Run2018B-UL2018_MiniAODv2-v1.root");
    TFile* f = new TFile("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/ntuple_MuOnia_Run2018B-UL2018_MiniAODv2-v1.root");
    h_counter=(TH1F*)f->Get("GenAnalysis/h_counter");
  }
  if(mass=="Run2018C"){
    t.Add("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/ntuple_MuOnia_Run2018C-UL2018_MiniAODv2-v1.root");
    TFile* f = new TFile("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/ntuple_MuOnia_Run2018C-UL2018_MiniAODv2-v1.root");
    h_counter=(TH1F*)f->Get("GenAnalysis/h_counter");
  }

  std::cout<<" entries: "<<t.GetEntries()<<std::endl;

  int tot = h_counter->GetBinContent(1);
  int trigger = h_counter->GetBinContent(2);
  std::cout<<tot<<" "<<trigger<<std::endl;
  //================ Run analysis
  AnalysisTQ ana( &t );
  ana.Loop(mass,tot,trigger);
  
  return 0;
}


void runTQAll(){

  runTQ("5");
  runTQ("7");
  runTQ("9");
  runTQ("14");
  runTQ("18");
  runTQ("22");
  runTQ("26");

}