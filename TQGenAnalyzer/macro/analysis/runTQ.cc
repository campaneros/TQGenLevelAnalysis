
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

  TChain t ("GenAnalysis/tree");
  if(mass=="5")t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m5_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="7")t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m7_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="9")t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m9_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="14")t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m14_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="18")t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m18_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="22")t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m22_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="26")t.Add("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m26_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  std::cout<<" entries: "<<t.GetEntries()<<std::endl;
  //================ Run analysis
  AnalysisTQ ana( &t );
  ana.Loop(mass);
  
  return 0;
}


void runTQAll(){

  //  runTQ("5");
  //runTQ("7");
  //runTQ("9");
  runTQ("14");
  runTQ("18");
  runTQ("22");
  runTQ("26");

}
