#include"TPaveText.h"
#include "TChain.h"
#include "TH1F.h"
#include <vector>
#include <cmath>
#include "TFile.h"
#include "TLegend.h"
#include "TPad.h"
#include "TCanvas.h"
#include "THStack.h"
#include "TStyle.h"
#include <stdio.h>
#include "TCanvas.h"
#include "TPad.h"
#include "TH1F.h"
#include "THStack.h"
#include "TProfile.h"
#include "TH2D.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TColor.h"
#include "TLatex.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
  


TGraphErrors* makeCutFlowTableGen(std::string mass, bool isRel){
  TFile* f;

  if(mass=="9") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m9_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="14") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m14_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_20K.root");
  if(mass=="26") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m26_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="22") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m22_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="18") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m18_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");

  //  TFile* f = new TFile("../crab/ntuple_tetraquarks_wLowPt_fixedOverlap.root");
  TTree* tree= (TTree*) f->Get("GenAnalysis/tree");
  TH1F* h_tot= new TH1F("h_tot", "h_tot",100, 0, 100); 
  TH1F* h_acc1= new TH1F("h_acc1", "h_acc1",100, 0, 100); 
  TH1F* h_acc2= new TH1F("h_acc2", "h_acc2",100, 0, 100); 
  TH1F* h_2recomu= new TH1F("h_2recomu", "h_2recomu",100, 0, 100); 
  TH1F* h_1mumatch= new TH1F("h_1mumatch", "h_1mumatch",100, 0, 100); 
  TH1F* h_2mumatch= new TH1F("h_2mumatch", "h_2mumatch",100, 0, 100); 

double tot=  tree->GetEntries();
double acc1= tree->GetEntries("(genLep_pt[0]>1)&& (genLep_pt[1]>1)&& (genLep_pt[2]>1 )&& (genLep_pt[3]>1 )");
double acc2=  tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5)");
double reco2mu=  tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1");
double mu1match = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1)>0)");
double mu2match = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1)>1)");
double mu2pt = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1 && recoMu_pt>1)>1)");
double mu2pteta = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1 && recoMu_pt>1 && abs(recoMu_eta)<2.5)>1)");
double mu2ptetaid = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1 && recoMu_pt>1 && abs(recoMu_eta)<2.5 &&recoMu_softID==1)>1)");

double reco2el = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1 && recoMu_pt>1 && abs(recoMu_eta)<2.5 &&recoMu_softID==1)>1) &&nEleReco>1 && (Sum$(recoEle_isPFoverlap==0)>1)");
double el1match = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1 && recoMu_pt>1 && abs(recoMu_eta)<2.5 &&recoMu_softID==1)>1) &&nEleReco>1 && (Sum$(recoEle_isPFoverlap==0 && recoEle_dR1<0.1)>0)");
double el2match = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1 && recoMu_pt>1 && abs(recoMu_eta)<2.5 &&recoMu_softID==1)>1) &&nEleReco>1 && (Sum$(recoEle_isPFoverlap==0&&recoEle_dR1<0.1)>1)");
double el2pt = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1 && recoMu_pt>1 && abs(recoMu_eta)<2.5 &&recoMu_softID==1)>1) &&nEleReco>1 && (Sum$(recoEle_isPFoverlap==0&&recoEle_dR1<0.1 && recoEle_pt>1)>1)");
double el2pteta = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1 && recoMu_pt>1 && abs(recoMu_eta)<2.5 &&recoMu_softID==1)>1) &&nEleReco>1 && (Sum$(recoEle_isPFoverlap==0&&recoEle_dR1<0.1 && recoEle_pt>1 && abs(recoEle_eta)<2.5)>1)");
double el2ptetaid = tree->GetEntries("(genLep_pt[0]>1 && abs(genLep_eta[0])<2.5)&& (genLep_pt[1]>1 &&abs(genLep_eta[1])<2.5)&& (genLep_pt[2]>1 &&abs(genLep_eta[2])<2.5)&& (genLep_pt[3]>1 &&abs(genLep_eta[3])<2.5) &&nMuReco>1 && (Sum$(recoMu_dR1<0.1 && recoMu_pt>1 && abs(recoMu_eta)<2.5 &&recoMu_softID==1)>1) &&nEleReco>1 && (Sum$(recoEle_isPFoverlap==0&&recoEle_dR1<0.1 && recoEle_pt>1 && abs(recoEle_eta)<2.5 && ((recoEle_isPF && recoEle_mvaPFValue>-2)||(recoEle_isLowPt &&recoEle_mvaValue>2)))>1)");


 float effrel_0=(float)tot/tot;
 float efftot_0=(float)tot/tot;
 float effrel_1=(float)acc1/tot;
 float efftot_1=(float)acc1/tot;
 float effrel_2=(float)acc2/acc1;
 float efftot_2=(float)acc2/tot;
 float effrel_3=(float)reco2mu/acc2;
 float efftot_3=(float)reco2mu/tot;
 float effrel_4=(float)mu1match/reco2mu;
 float efftot_4=(float)mu1match/tot;
 float effrel_5=(float)mu2match/mu1match;
 float efftot_5=(float)mu2match/tot;
 float effrel_6=(float)mu2pt/mu2match;
 float efftot_6=(float)mu2pt/tot;
 float effrel_7=(float)mu2pteta/mu2pt;
 float efftot_7=(float)mu2pteta/tot;
 float effrel_8=(float)mu2ptetaid/mu2pteta;
 float efftot_8=(float)mu2ptetaid/tot;
 float effrel_9=(float)reco2el/mu2ptetaid;
 float efftot_9=(float)reco2el/tot;
 float effrel_10=(float)el1match/reco2el;
 float efftot_10=(float)el1match/tot;
 float effrel_11=(float)el2match/el1match;
 float efftot_11=(float)el2match/tot;
 float effrel_12=(float)el2pt/el2match;
 float efftot_12=(float)el2pt/tot;
 float effrel_13=(float)el2pteta/el2pt;
 float efftot_13=(float)el2pteta/tot;
 float effrel_14=(float)el2ptetaid/el2pteta;
 float efftot_14=(float)el2ptetaid/tot;



  std::cout<<"\t------------------ CUT FLOW ---------------"<<std::endl;
  std::cout<<"\t cut \t # evts \t eff rel. \t eff tot"<<std::endl;
  std::cout<<"\t Tot Events: "<<"\t"<<tot<<"\t"<<effrel_0<<"\t"<<efftot_0<<std::endl;
  std::cout<<"\t 2#mu +2e w/ pt>1 GeV: \t"<<acc1<<"\t"<<effrel_1<<"\t"<<efftot_1<<std::endl;
  std::cout<<"\t ... \t and |#eta|<2.5 \t"<<acc2<<"\t"<<effrel_2<<"\t"<<efftot_2<<std::endl;
  std::cout<<"\t ... \t and nMu>1: \t"<<reco2mu<<"\t"<<effrel_3<<"\t"<<efftot_3<<std::endl;
  std::cout<<"\t ... \t 1mu match: \t"<<mu1match<<"\t"<<effrel_4<<"\t"<<efftot_4<<std::endl;
  std::cout<<"\t ... \t and 2mu match: \t"<<mu2match<<"\t"<<effrel_5<<"\t"<<efftot_5<<std::endl;
  std::cout<<"\t ... \t and pt>1 GeV: \t"<<mu2pt<<"\t"<<effrel_6<<"\t"<<efftot_6<<std::endl;
  std::cout<<"\t ... \t and |#eta|<2.5: \t"<<mu2pteta<<"\t"<<effrel_7<<"\t"<<efftot_7<<std::endl;
  std::cout<<"\t ... \t and softID: \t"<<mu2ptetaid<<"\t"<<effrel_8<<"\t"<<efftot_8<<std::endl;
  std::cout<<"\t ... \t and nEle>1: \t"<<reco2el<<"\t"<<effrel_9<<"\t"<<efftot_9<<std::endl;
  std::cout<<"\t ... \t 1el match: \t"<<el1match<<"\t"<<effrel_10<<"\t"<<efftot_10<<std::endl;
  std::cout<<"\t ... \t and 2el match: \t"<<el2match<<"\t"<<effrel_11<<"\t"<<efftot_11<<std::endl;
  std::cout<<"\t ... \t and pt>1 GeV: \t"<<el2pt<<"\t"<<effrel_12<<"\t"<<efftot_12<<std::endl;
  std::cout<<"\t ... \t and |#eta|<2.5: \t"<<el2pteta<<"\t"<<effrel_13<<"\t"<<efftot_13<<std::endl;
  std::cout<<"\t ... \t and mvaok: \t"<<el2ptetaid<<"\t"<<effrel_14<<"\t"<<efftot_14<<std::endl;


  double effrel[15]={effrel_0,effrel_1,effrel_2,effrel_3,effrel_4,effrel_5,effrel_6,effrel_7,effrel_8,effrel_9,effrel_10,effrel_11,effrel_12,effrel_13,effrel_14};
  double efftot[15]={efftot_0,efftot_1,efftot_2,efftot_3,efftot_4,efftot_5,efftot_6,efftot_7,efftot_8,efftot_9,efftot_10,efftot_11,efftot_12,efftot_13,efftot_14};
  double events[15]={tot,acc1,acc2,reco2mu,mu1match,mu2match,mu2pt,mu2pteta,mu2ptetaid,reco2el,el1match,el2match,el2pt,el2pteta,el2ptetaid};
  double efftot_err[25]{0.};
  double effrel_err[25]{0.};
  for(int i=0;i<15;i++)effrel_err[i]=sqrt(effrel[i]*(1-effrel[i])/events[i]);
  for(int i=0;i<15;i++)efftot_err[i]=sqrt(efftot[i]*(1-efftot[i])/tot);
  double cutid[15]={0,2,4,6,8,10,12,14,16,18,20,22,24,26,28};
  double cutid_err[15]={1.};
  for(int i=0;i<15;i++)cutid_err[i]=1.;
  
  TGraphErrors*  g_tot = new TGraphErrors(15,cutid,efftot,cutid_err,efftot_err);
  TGraphErrors* g_rel = new TGraphErrors(15,cutid,effrel,cutid_err,effrel_err);
  

  TH1F* h=new TH1F("h","h",15,-1,29);
  h->GetXaxis()->SetBinLabel(1 ," Total");
  h->GetXaxis()->SetBinLabel(2 ,"p_{T,gen} >1 GeV");
  h->GetXaxis()->SetBinLabel(3 ,"|#eta_{gen}|<2.5");
  h->GetXaxis()->SetBinLabel(4 ," nMu >1");
  h->GetXaxis()->SetBinLabel(5 ,"1 #mu match");
  h->GetXaxis()->SetBinLabel(6 ,"2 #mu match");
  h->GetXaxis()->SetBinLabel(7 ,"#mu p_{T}> 1 GeV");
  h->GetXaxis()->SetBinLabel(8 ,"|#mu #eta|<2.5");
  h->GetXaxis()->SetBinLabel(9 ,"softID==1");
  h->GetXaxis()->SetBinLabel(10,"nEle>1");
  h->GetXaxis()->SetBinLabel(11,"1 e match");
  h->GetXaxis()->SetBinLabel(12,"2 e match");
  h->GetXaxis()->SetBinLabel(13,"e p_{T}> 1 GeV");
  h->GetXaxis()->SetBinLabel(14,"|e #eta|<2.5");
  h->GetXaxis()->SetBinLabel(15,"ID==1");
  h->GetYaxis()->SetTitle("Efficieincy");
  TCanvas* c = new TCanvas("c","c",900,400);
  c->cd();
  h->Draw("hist");
  g_tot->Draw("PEsame");
  c->SaveAs(("~/www/TQ-WORK/eff/efftot_m"+mass+".png").c_str());
  c->SaveAs(("~/www/TQ-WORK/eff/efftot_m"+mass+".pdf").c_str());


  c->cd();
  h->Draw("hist");
  g_rel->Draw("PEsame");
  c->SaveAs(("~/www/TQ-WORK/eff/effrel_m"+mass+".png").c_str());
  c->SaveAs(("~/www/TQ-WORK/eff/effrel_m"+mass+".pdf").c_str());
  
  if(isRel) return g_rel;
  else return g_tot;
  
}



void compareEffGen(){

  TGraphErrors* g_tot_7=   makeCutFlowTableGen("7",0);
  TGraphErrors* g_rel_7=   makeCutFlowTableGen("7",1);

  TGraphErrors* g_tot_9=   makeCutFlowTableGen("9",0);
  TGraphErrors* g_rel_9=   makeCutFlowTableGen("9",1);
  //  TGraphErrors* g_tot_14=   makeCutFlowTableGen("14",0);
  //TGraphErrors* g_rel_14=   makeCutFlowTableGen("14",1);

  TGraphErrors* g_tot_26=   makeCutFlowTableGen("26",0);
  TGraphErrors* g_rel_26=   makeCutFlowTableGen("26",1);

  TGraphErrors* g_tot_22=   makeCutFlowTableGen("22",0);
  TGraphErrors* g_rel_22=   makeCutFlowTableGen("22",1);

  TGraphErrors* g_tot_18=   makeCutFlowTableGen("18",0);
  TGraphErrors* g_rel_18=   makeCutFlowTableGen("18",1);


  TH1F* h=new TH1F("h","h",15,-1,29);
  h->GetXaxis()->SetBinLabel(1 ," Total");
  h->GetXaxis()->SetBinLabel(2 ,"p_{T,gen} >1 GeV");
  h->GetXaxis()->SetBinLabel(3 ,"|#eta_{gen}|<2.5");
  h->GetXaxis()->SetBinLabel(4 ," nMu >1");
  h->GetXaxis()->SetBinLabel(5 ,"1 #mu match");
  h->GetXaxis()->SetBinLabel(6 ,"2 #mu match");
  h->GetXaxis()->SetBinLabel(7 ,"#mu p_{T}> 1 GeV");
  h->GetXaxis()->SetBinLabel(8 ,"|#mu #eta|<2.5");
  h->GetXaxis()->SetBinLabel(9 ,"softID==1");
  h->GetXaxis()->SetBinLabel(10,"nEle>1");
  h->GetXaxis()->SetBinLabel(11,"1 e match");
  h->GetXaxis()->SetBinLabel(12,"2 e match");
  h->GetXaxis()->SetBinLabel(13,"e p_{T}> 1 GeV");
  h->GetXaxis()->SetBinLabel(14,"|e #eta|<2.5");
  h->GetXaxis()->SetBinLabel(15,"ID==1");
  h->GetYaxis()->SetTitle("Efficieincy");
  TLegend* leg1 = new TLegend(0.5,0.6, 0.85,0.9);
  leg1->SetFillColor(kWhite);
  leg1->SetBorderSize(0);
  leg1->SetHeader("Cut Flow - Absolute Efficiencies");
  leg1->AddEntry(g_tot_7," m_{TQ} = 7 GeV" , "PLE");
  leg1->AddEntry(g_tot_9," m_{TQ} = 9 GeV" , "PLE");
  leg1->AddEntry(g_tot_18," m_{TQ} = 18 GeV" , "PLE");
  leg1->AddEntry(g_tot_22," m_{TQ} = 22 GeV" , "PLE");
  leg1->AddEntry(g_tot_26," m_{TQ} = 26 GeV" , "PLE");

  TLegend* leg2 = new TLegend(0.2,0.15, 0.6,0.4);
  leg2->SetFillColor(kWhite);
  leg2->SetBorderSize(0);
  leg2->SetHeader("Cut Flow - Relative Efficiencies");
  leg2->AddEntry(g_tot_7," m_{TQ} = 7 GeV" , "PLE");
  leg2->AddEntry(g_tot_9," m_{TQ} = 9 GeV" , "PLE");
  leg2->AddEntry(g_tot_18," m_{TQ} = 18 GeV" , "PLE");
  leg2->AddEntry(g_tot_22," m_{TQ} = 22 GeV" , "PLE");
  leg2->AddEntry(g_tot_26," m_{TQ} = 26 GeV" , "PLE");



  TCanvas* c = new TCanvas("c","c",900,400);
  c->cd();
  h->Draw("hist");
  g_tot_7->SetMarkerColor(kBlue);
  g_tot_7->SetMarkerStyle(25);
  g_tot_7->SetLineColor(kBlue);
  g_tot_9->SetMarkerColor(kRed);
  g_tot_9->SetMarkerStyle(23);
  g_tot_9->SetLineColor(kRed);
  g_tot_18->SetMarkerColor(kMagenta);
  g_tot_18->SetMarkerStyle(22);
  g_tot_18->SetLineColor(kMagenta);
  g_tot_22->SetMarkerColor(kOrange+8);
  g_tot_22->SetMarkerStyle(22);
  g_tot_22->SetLineColor(kOrange+8);
  g_tot_7->Draw("PEsame");
  g_tot_9->Draw("PEsame");
  g_tot_18->Draw("PEsame");
  g_tot_22->Draw("PEsame");
  g_tot_26->Draw("PEsame");
  leg1->Draw("same");
  c->SaveAs("~/www/TQ-WORK/eff/efftot_compareEff.png");
  c->SaveAs("~/www/TQ-WORK/eff/efftot_compareEff.pdf");


  c->cd();

  h->Draw("hist");
  g_rel_7->SetMarkerColor(kBlue);
  g_rel_7->SetMarkerStyle(25);
  g_rel_7->SetLineColor(kBlue);
  g_rel_9->SetMarkerColor(kRed);
  g_rel_9->SetMarkerStyle(23);
  g_rel_9->SetLineColor(kRed);
  g_rel_18->SetMarkerColor(kMagenta);
  g_rel_18->SetMarkerStyle(22);
  g_rel_18->SetLineColor(kMagenta);
  g_rel_22->SetMarkerColor(kOrange+8);
  g_rel_22->SetMarkerStyle(22);
  g_rel_22->SetLineColor(kOrange+8);
  g_rel_7->Draw("PEsame");
  g_rel_9->Draw("PEsame");
  g_rel_18->Draw("PEsame");
  g_rel_22->Draw("PEsame");
  g_rel_26->Draw("PEsame");


  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/eff/effrel_compareEff.png");
  c->SaveAs("~/www/TQ-WORK/eff/effrel_compareEff.pdf");
 
}

void plotTriggerPerformance(){
  TFile* f= new TFile("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/ntuple_MuOnia_Run2018ABCD-UL2018_MiniAODv2-v1_wPrescaledTrigger.root");
  TTree* t = (TTree*)f->Get("GenAnalysis/tree");

  TH1F* hnum_pt = new TH1F("hnum_pt", "hnum", 60,0,60);
  TH1F* hden_pt = new TH1F("hden_pt", "hden", 60,0,60);
  TH1F* hnum_eta = new TH1F("hnum_eta", "hnum", 20,-5,5);
  TH1F* hden_eta = new TH1F("hden_eta", "hden", 20,-5,5);
  hnum_pt->Sumw2();
  hden_pt->Sumw2();
  hnum_eta->Sumw2();
  hden_eta->Sumw2();
  t->Draw("recoTQ_Y1pt>>hnum_pt","HLT_Dimuon0_prescaled_2018&&recoTQ_Y1vtxprob>0.5&&recoTQ_softID1&&recoTQ_softID2&&recoTQ_Y1pt<100&&(HLT_Dimuon12_Upsilon_y1p4_v_2018||HLT_Dimuon24_Upsilon_noCorrL1_v_2018)");
  t->Draw("recoTQ_Y1pt>>hden_pt","HLT_Dimuon0_prescaled_2018&&recoTQ_Y1vtxprob>0.5&&recoTQ_softID1&&recoTQ_softID2&&recoTQ_Y1pt<100");
  t->Draw("recoTQ_Y1eta>>hnum_eta","HLT_Dimuon0_prescaled_2018&&recoTQ_Y1vtxprob>0.5&&recoTQ_softID1&&recoTQ_softID2&&recoTQ_Y1pt<100&&(HLT_Dimuon12_Upsilon_y1p4_v_2018||HLT_Dimuon24_Upsilon_noCorrL1_v_2018)");
  t->Draw("recoTQ_Y1eta>>hden_eta","HLT_Dimuon0_prescaled_2018&&recoTQ_Y1vtxprob>0.5&&recoTQ_softID1&&recoTQ_softID2&&recoTQ_Y1pt<100");

  hnum_pt->Divide(hden_pt);
  hnum_eta->Divide(hden_eta);
  


  TFile* fsig = new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m26_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K_woTrigger.root");
  TTree* tsig = (TTree*)fsig->Get("GenAnalysis/tree");
  TH1F* hsig_pt = new TH1F("hsig_pt", "hsig_pt", 60,0,60);
  TH1F* hsig_eta = new TH1F("hsig_eta", "hsig_eta", 20,-5,5);
  hsig_pt->Sumw2();
  hsig_eta->Sumw2();
  tsig->Draw("recoTQ_Y1pt>>hsig_pt","(HLT_Dimuon0_prescaled_2018&&recoTQ_Y1vtxprob>0.5&&recoTQ_softID1&&recoTQ_softID2&&recoTQ_Y1pt<100)*nvtxw_2018");
  tsig->Draw("recoTQ_Y1eta>>hsig_eta","(HLT_Dimuon0_prescaled_2018&&recoTQ_Y1vtxprob>0.5&&recoTQ_softID1&&recoTQ_softID2&&recoTQ_Y1pt<100)*nvtxw_2018");
  hsig_pt->SetLineColor(kOrange+6);
  hsig_eta->SetLineColor(kOrange+6);


  double tot = t->GetEntries("HLT_Dimuon0_prescaled_2018&&(HLT_Dimuon12_Upsilon_y1p4_v_2018||HLT_Dimuon24_Upsilon_noCorrL1_v_2018)");
  double dimu12 = t->GetEntries("HLT_Dimuon0_prescaled_2018&&(HLT_Dimuon12_Upsilon_y1p4_v_2018)&&!HLT_Dimuon24_Upsilon_noCorrL1_v_2018");
  double dimu24 = t->GetEntries("HLT_Dimuon0_prescaled_2018&&(HLT_Dimuon24_Upsilon_noCorrL1_v_2018)");
  
  std::cout<<tot<<" 12: "<<dimu12<<" 24: "<<dimu24<<std::endl;

  TH1F* h_trig = new TH1F("h_trig","h_trig", 2,0,2);
  h_trig->SetBinContent(1,dimu12/tot);
  h_trig->SetBinContent(2,dimu24/tot);
  h_trig->GetYaxis()->SetTitle("Fired trigger fractions");
  h_trig->GetXaxis()->SetBinLabel(1,"HLT_Dimuon12");
  h_trig->GetXaxis()->SetBinLabel(2,"HLT_Dimuon24");

  TCanvas* c = new TCanvas("c","c",1);
  c->cd();
  h_trig->SetFillColor(kOrange+6);
  h_trig->Draw("hist");
  c->SaveAs("~/www/TQ-WORK/kin/trigger_fractions.png");
  c->SaveAs("~/www/TQ-WORK/kin/trigger_fractions.pdf");

  TLegend* leg1 = new TLegend(0.5,0.6, 0.8,0.74);
  leg1->SetFillColor(kWhite);
  leg1->AddEntry(hnum_pt," #splitline{Trigger Efficiency:}{2018 UL Data (58.93 fb^{-1})}" , "PLE");
  leg1->AddEntry(hsig_pt," TQ: 26 GeV" , "LE");
  

  hnum_pt->GetXaxis()->SetTitle("#Upsilon_{#mu#mu} p_{T} [GeV]");
  //  hnum_pt->GetYaxis()->SetTitle("Trigger Efficiency");
  hnum_pt->Draw("PE");
  hsig_pt->Scale(5./hsig_pt->Integral());
  hsig_pt->Draw("histsame");
  leg1->Draw("same");
  c->SaveAs("~/www/TQ-WORK/kin/trigger_efficiency_vs_pt.png");
  c->SaveAs("~/www/TQ-WORK/kin/trigger_efficiency_vs_pt.pdf");
  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/kin/trigger_efficiency_vs_pt_LOG.png");
  c->SaveAs("~/www/TQ-WORK/kin/trigger_efficiency_vs_pt_LOG.pdf");

  c->SetLogy(0);
  //  hnum_eta->GetYaxis()->SetTitle("Trigger Efficiency");
  hnum_eta->GetXaxis()->SetTitle("#Upsilon_{#mu#mu} #eta");
  hnum_eta->Draw("PE");
  hsig_eta->Scale(5./hsig_eta->Integral());
  hsig_eta->Draw("histsame");
  leg1->Draw("same");
  c->SaveAs("~/www/TQ-WORK/kin/trigger_efficiency_vs_eta.png");
  c->SaveAs("~/www/TQ-WORK/kin/trigger_efficiency_vs_eta.pdf");
  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/kin/trigger_efficiency_vs_eta_LOG.png");
  c->SaveAs("~/www/TQ-WORK/kin/trigger_efficiency_vs_eta_LOG.pdf");


}

void compareEffDi(){

  /*
  

  TFile* f5= new TFile("analysis/fout_m5.root");
  TFile* f7= new TFile("analysis/fout_m7.root");
  TFile* f9= new TFile("analysis/fout_m9.root");
  */
  TFile* f26= new TFile("analysis/fout_m26wTrigger_TQ.root");
  TFile* f20= new TFile("analysis/fout_m20wTrigger_TQ.root");
  //TFile* f22= new TFile("analysis/fout_m22_TQ.root");
  TFile* f18= new TFile("analysis/fout_m18wTrigger_TQ.root");
  //TFile* f14= new TFile("analysis/fout_m14_TQ.root");
  /*
  TH1F* eff_5 =  (TH1F*)f5->Get("eff_counter");
  TH1F* effrel_5 =  (TH1F*)f5->Get("effrel_counter");
  TH1F* eff_7 =  (TH1F*)f7->Get("eff_counter");
  TH1F* effrel_7 =  (TH1F*)f7->Get("effrel_counter");
  TH1F* eff_9 =  (TH1F*)f9->Get("eff_counter");
  TH1F* effrel_9 =  (TH1F*)f9->Get("effrel_counter");
  TH1F* eff_14 =  (TH1F*)f14->Get("eff_counter");
  TH1F* effrel_14 =  (TH1F*)f14->Get("effrel_counter");
  */
  TH1F* eff_18 =  (TH1F*)f18->Get("eff_counter");
  TH1F* effrel_18 =  (TH1F*)f18->Get("effrel_counter");
  //TH1F* eff_22 =  (TH1F*)f22->Get("eff_counter");
  //TH1F* effrel_22 =  (TH1F*)f22->Get("effrel_counter");
  TH1F* eff_20 =  (TH1F*)f20->Get("eff_counter");
  TH1F* effrel_20 =  (TH1F*)f20->Get("effrel_counter");
  TH1F* eff_26 =  (TH1F*)f26->Get("eff_counter");
  TH1F* effrel_26 =  (TH1F*)f26->Get("effrel_counter");


  TLegend* leg1 = new TLegend(0.58,0.63, 0.85,0.85);
  leg1->SetFillColor(kWhite);
  //  leg1->SetBorderSize(0);
  leg1->SetHeader("Cut Flow - Absolute Efficiencies");
  /*  leg1->AddEntry(eff_5," m_{TQ} = 5 GeV" , "PLE");
  leg1->AddEntry(eff_7," m_{TQ} = 7 GeV" , "PLE");
  leg1->AddEntry(eff_9," m_{TQ} = 9 GeV" , "PLE");
  */
  //  leg1->AddEntry(eff_14," m_{TQ} = 14 GeV" , "PLE");
  leg1->AddEntry(eff_18," m_{TQ} = 18 GeV" , "PLE");
  leg1->AddEntry(eff_20," m_{TQ} = 20 GeV" , "PLE");
  leg1->AddEntry(eff_26," m_{TQ} = 26 GeV" , "PLE");


  TCanvas* c = new TCanvas("c","c",900,400);
  c->cd();
  c->SetLogy();
  /*  eff_5->SetMarkerColor(kYellow+2);
  eff_5->SetMarkerStyle(24);
  eff_5->SetLineColor(kYellow+2);
  eff_7->SetMarkerColor(kBlue+1);
  eff_7->SetMarkerStyle(25);
  eff_7->SetLineColor(kBlue+1);
  eff_9->SetMarkerColor(kCyan+2);
  eff_9->SetMarkerStyle(23);
  eff_9->SetLineColor(kCyan+2);
  eff_14->SetMarkerColor(kRed+2);
  eff_14->SetMarkerStyle(26);
  eff_14->SetLineColor(kRed+2);*/
  eff_18->SetMarkerColor(kGreen-6);
  eff_18->SetMarkerStyle(22);
  eff_18->SetLineColor(kGreen-6);
  /*  eff_22->SetMarkerColor(kOrange-3);
  eff_22->SetMarkerStyle(21);
  eff_22->SetLineColor(kOrange-3);
  */
  eff_20->SetMarkerColor(kOrange+6);
  eff_20->SetMarkerStyle(21);
  eff_20->SetLineColor(kOrange+6);
  eff_26->SetMarkerColor(kPink-9);
  eff_26->SetMarkerStyle(20);
  eff_26->SetLineColor(kPink-9);

  /*eff_5->Draw("PE");
  eff_7->Draw("PEsame");
  eff_9->Draw("PEsame");
  */
  eff_18->Draw("PE");
  eff_20->Draw("PEsame");
  eff_26->Draw("PEsame");
  leg1->Draw("same");
  c->SaveAs("~/www/TQ-WORK/eff/efftot_compareEffDi.png");
  c->SaveAs("~/www/TQ-WORK/eff/efftot_compareEffDi.pdf");


  c->cd();
  c->SetLogy(0);

  /*effrel_5->SetMarkerColor(kYellow+2);
  effrel_5->SetMarkerStyle(24);
  effrel_5->SetLineColor(kYellow+2);
  effrel_7->SetMarkerColor(kBlue+1);
  effrel_7->SetMarkerStyle(25);
  effrel_7->SetLineColor(kBlue+1);
  effrel_9->SetMarkerColor(kCyan+2);
  effrel_9->SetMarkerStyle(23);
  effrel_9->SetLineColor(kCyan+2);
  effrel_14->SetMarkerColor(kRed+2);
  effrel_14->SetMarkerStyle(26);
  effrel_14->SetLineColor(kRed+2);
  */  effrel_18->SetMarkerColor(kGreen-6);
  effrel_18->SetMarkerStyle(22);
  effrel_18->SetLineColor(kGreen-6);
  /*  effrel_22->SetMarkerColor(kOrange-3);
  effrel_22->SetMarkerStyle(21);
  effrel_22->SetLineColor(kOrange-3);
  */  effrel_20->SetMarkerColor(kOrange+6);
  effrel_20->SetMarkerStyle(21);
  effrel_20->SetLineColor(kOrange+6);
  effrel_26->SetMarkerColor(kPink-9);
  effrel_26->SetMarkerStyle(20);
  effrel_26->SetLineColor(kPink-9);
  /*  effrel_5->Draw("pe");
  effrel_7->Draw("pesame");
  effrel_9->Draw("pesame");
  */
  effrel_18->Draw("pe");
  effrel_20->Draw("pesame");
  effrel_26->Draw("pesame");
  //  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/eff/effrel_compareEffDi.png");
  c->SaveAs("~/www/TQ-WORK/eff/effrel_compareEffDi.pdf");
 
  
  //plot eff vs mass (last bin of absolute trend
  double effvsmass[3] = {(double)eff_18->GetBinContent(13),(double)eff_20->GetBinContent(13),(double)eff_26->GetBinContent(13)};
  double efferrvsmass[3] = {(double)eff_18->GetBinError(13),(double)eff_20->GetBinError(13),(double)eff_26->GetBinError(13)};
  double mass[3] = {18,20,26};
  double masserr[7]={0};
  TGraphErrors* g = new TGraphErrors(3,mass, effvsmass,masserr,efferrvsmass);
  TH1F* h = new TH1F("h","",30,0,30);
  h->GetYaxis()->SetRangeUser(0.0000001,1);
  h->GetYaxis()->SetTitle("Total Efficiency");
  h->GetXaxis()->SetTitle("m_{TQ} [GeV]");
  h->Draw();
  
  TF1* f1 = new TF1("f1", "[1]*pow(x,0.5*[2])", 0,30);
  
  g->Draw("PEsame");
  //  g->Fit("f1","R");
  c->SaveAs("~/www/TQ-WORK/eff/effvsmass.png");
  c->SaveAs("~/www/TQ-WORK/eff/effvsmass.pdf");
  
  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/eff/effvsmass_LOG.png");
  c->SaveAs("~/www/TQ-WORK/eff/effvsmass_LOG.pdf");
  
}

void compareSigVsSPSandDPS(){
  TFile* f26= new TFile("analysis/fout_m26wTrigger_TQ.root");
  TFile* fSPS= new TFile("analysis/fout_mSPSwTrigger_TQ.root");
  TFile* fDPS= new TFile("analysis/fout_mDPSwTrigger_TQ.root");
  TFile* fdata2018=new TFile("analysis/fout_mRun2018ABCD_trigger_TQ.root");

  TTree* t26= (TTree*) f26->Get("tree_red");
  TTree* tSPS= (TTree*) fSPS->Get("tree_red");
  TTree* tDPS= (TTree*) fDPS->Get("tree_red");
  TTree* tdata2018= (TTree*) fdata2018->Get("tree_red");

  TH1F* Ye_26 = new TH1F("Ye_26", "",80,0,20);
  TH1F* Ye_SPS = new TH1F("Ye_SPS", "",80,0,20);
  TH1F* Ye_DPS = new TH1F("Ye_DPS", "",80,0,20);
  TH1F* Ym_26 = new TH1F("Ym_26", "",80,0,20);
  TH1F* Ym_SPS = new TH1F("Ym_SPS", "",80,0,20);
  TH1F* Ym_DPS = new TH1F("Ym_DPS", "",80,0,20);

  TH1F* pt_Ye_26 = new TH1F("pt_Ye_26", "",80,0,80);
  TH1F* pt_Ye_SPS = new TH1F("pt_Ye_SPS", "",80,0,80);
  TH1F* pt_Ye_DPS = new TH1F("pt_Ye_DPS", "",80,0,80);
  TH1F* pt_Ym_26 = new TH1F("pt_Ym_26", "",80,0,80);
  TH1F* pt_Ym_SPS = new TH1F("pt_Ym_SPS", "",80,0,80);
  TH1F* pt_Ym_DPS = new TH1F("pt_Ym_DPS", "",80,0,80);


  TH1F* eta_Ye_26 = new TH1F("eta_Ye_26", "",80,-10,10);
  TH1F* eta_Ye_SPS = new TH1F("eta_Ye_SPS", "",80,-10,10);
  TH1F* eta_Ye_DPS = new TH1F("eta_Ye_DPS", "",80,-10,10);
  TH1F* eta_Ym_26 = new TH1F("eta_Ym_26", "",80,-10,10);
  TH1F* eta_Ym_SPS = new TH1F("eta_Ym_SPS", "",80,-10,10);
  TH1F* eta_Ym_DPS = new TH1F("eta_Ym_DPS", "",80,-10,10);

  TH1F* mass_26 = new TH1F("mass_26", "",30,10,40);
  TH1F* mass_SPS = new TH1F("mass_SPS", "",30,10,40);
  TH1F* mass_DPS = new TH1F("mass_DPS", "",30,10,40);
  TH1F* tmass_26 = new TH1F("tmass_26", "",30,10,40);
  TH1F* tmass_SPS = new TH1F("tmass_SPS", "",30,10,40);
  TH1F* tmass_DPS = new TH1F("tmass_DPS", "",30,10,40);
  TH1F* pt_26 = new TH1F("pt_26", "",40,0,80);
  TH1F* pt_SPS = new TH1F("pt_SPS", "",40,0,80);
  TH1F* pt_DPS = new TH1F("pt_DPS", "",40,0,80);

  TH1F* eta_26 = new TH1F("eta_26", "",40,-10,10);
  TH1F* eta_SPS = new TH1F("eta_SPS", "",40,-10,10);
  TH1F* eta_DPS = new TH1F("eta_DPS", "",40,-10,10);

  TH1F* nvtx_26 = new TH1F("nvtx_26", "",50,0,100);
  TH1F* nvtx_26_w = new TH1F("nvtx_26_w", "",50,0,100);
  TH1F* nvtx_SPS = new TH1F("nvtx_SPS", "",50,0,100);
  TH1F* nvtx_SPS_w = new TH1F("nvtx_SPS_w", "",50,0,100);
  TH1F* nvtx_DPS = new TH1F("nvtx_DPS", "",50,0,100);
  TH1F* nvtx_DPS_w = new TH1F("nvtx_DPS_w", "",50,0,100);
  TH1F* nvtx_data2018 = new TH1F("nvtx_data2018", "",50,0,100);
  
  t26->Draw("TQ_mass>>mass_26","nvtxw2018");
  t26->Draw("TQ_mass_tilde>>tmass_26","nvtxw2018");
  t26->Draw("TQ_pt>>pt_26","nvtxw2018");
  t26->Draw("TQ_eta>>eta_26","nvtxw2018");
  t26->Draw("Ym_mass>>Ym_26","nvtxw2018");
  t26->Draw("Ym_pt>>pt_Ym_26","nvtxw2018");
  t26->Draw("Ym_eta>>eta_Ym_26","nvtxw2018");
  t26->Draw("Ye_mass>>Ye_26","nvtxw2018");
  t26->Draw("Ye_pt>>pt_Ye_26","nvtxw2018");
  t26->Draw("Ye_eta>>eta_Ye_26","nvtxw2018");
  t26->Draw("n_vtx>>nvtx_26_w","nvtxw2018");
  t26->Draw("n_vtx>>nvtx_26");

  
  tSPS->Draw("TQ_mass>>mass_SPS","nvtxw2018");
  tSPS->Draw("TQ_mass_tilde>>tmass_SPS","nvtxw2018");
  tSPS->Draw("TQ_pt>>pt_SPS","nvtxw2018");
  tSPS->Draw("TQ_eta>>eta_SPS","nvtxw2018");
  tSPS->Draw("Ym_mass>>Ym_SPS","nvtxw2018");
  tSPS->Draw("Ym_pt>>pt_Ym_SPS","nvtxw2018");
  tSPS->Draw("Ym_eta>>eta_Ym_SPS","nvtxw2018");
  tSPS->Draw("Ye_mass>>Ye_SPS","nvtxw2018");
  tSPS->Draw("Ye_pt>>pt_Ye_SPS","nvtxw2018");
  tSPS->Draw("Ye_eta>>eta_Ye_SPS","nvtxw2018");
  tSPS->Draw("n_vtx>>nvtx_SPS_w","nvtxw2018");
  tSPS->Draw("n_vtx>>nvtx_SPS");


  tDPS->Draw("TQ_mass>>mass_DPS","nvtxw2018");
  tDPS->Draw("TQ_mass_tilde>>tmass_DPS","nvtxw2018");
  tDPS->Draw("TQ_pt>>pt_DPS","nvtxw2018");
  tDPS->Draw("TQ_eta>>eta_DPS","nvtxw2018");
  tDPS->Draw("Ym_mass>>Ym_DPS","nvtxw2018");
  tDPS->Draw("Ym_pt>>pt_Ym_DPS","nvtxw2018");
  tDPS->Draw("Ym_eta>>eta_Ym_DPS","nvtxw2018");
  tDPS->Draw("Ye_mass>>Ye_DPS","nvtxw2018");
  tDPS->Draw("Ye_pt>>pt_Ye_DPS","nvtxw2018");
  tDPS->Draw("Ye_eta>>eta_Ye_DPS","nvtxw2018");
  tDPS->Draw("n_vtx>>nvtx_DPS");
  tDPS->Draw("n_vtx>>nvtx_DPS_w","nvtxw2018");

  tdata2018->Draw("n_vtx>>nvtx_data2018");


  Ye_26->SetLineColor(kOrange+8);
  Ye_26->SetMarkerColor(kOrange+8);

  std::cout<<nvtx_26_w->Integral()<<" "<<nvtx_26->Integral()<<std::endl;

  Ye_SPS->SetLineColor(kGreen+2);
  Ye_SPS->SetMarkerColor(kGreen+2);
  Ym_SPS->SetLineColor(kGreen+2);
  Ym_SPS->SetMarkerColor(kGreen+2);
  mass_SPS->SetLineColor(kGreen+2);
  mass_SPS->SetMarkerColor(kGreen+2);
  pt_SPS->SetLineColor(kGreen+2);
  pt_SPS->SetMarkerColor(kGreen+2);
  tmass_SPS->SetLineColor(kGreen+2);
  tmass_SPS->SetMarkerColor(kGreen+2);
  eta_SPS->SetLineColor(kGreen+2);
  eta_SPS->SetMarkerColor(kGreen+2);
  pt_Ye_SPS->SetLineColor(kGreen+2);
  pt_Ye_SPS->SetMarkerColor(kGreen+2);
  eta_Ye_SPS->SetLineColor(kGreen+2);
  eta_Ye_SPS->SetMarkerColor(kGreen+2);
  pt_Ym_SPS->SetLineColor(kGreen+2);
  pt_Ym_SPS->SetMarkerColor(kGreen+2);
  eta_Ym_SPS->SetLineColor(kGreen+2);
  eta_Ym_SPS->SetMarkerColor(kGreen+2);
  nvtx_SPS->SetLineColor(kGreen+2);
  nvtx_SPS->SetMarkerColor(kGreen+2);

  nvtx_SPS_w->SetLineColor(kGreen+5);
  nvtx_SPS_w->SetMarkerColor(kGreen+5);

  TLegend* leg2 = new TLegend(0.6,0.55, 0.85,0.85);
  leg2->SetFillColor(kWhite);
  //  leg2->SetHeader("Signal Shapes");
  leg2->AddEntry(Ye_26," TQ: 26 GeV" , "LE");
  leg2->AddEntry(Ye_SPS,"SPS(YY)" , "LE");
  leg2->AddEntry(Ye_DPS,"DPS(YY)" , "LE");


  TLegend* leg3 = new TLegend(0.2,0.55, 0.45,0.85);
  leg3->SetFillColor(kWhite);
  //  leg3->SetHeader("Signal Shapes");
  leg3->AddEntry(Ye_26," TQ: 26 GeV" , "LE");
  leg3->AddEntry(Ye_SPS,"SPS(YY)" , "LE");
  leg3->AddEntry(Ye_DPS,"DPS(YY)" , "LE");


  TCanvas* c = new TCanvas("c","c",800,600);
  c->cd();
  mass_26->SetLineColor(kOrange+8);
  mass_26->SetMarkerColor(kOrange+8);
  mass_26->GetXaxis()->SetTitle("m_{TQ} [GeV]");
  mass_26->GetYaxis()->SetTitle("A.U.");
  mass_26->DrawNormalized("HIST");
  mass_SPS->DrawNormalized("HISTSAME");
  mass_DPS->DrawNormalized("HISTSAME");
  leg3->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/mass_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/mass_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/mass_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/mass_shapes_LOG.pdf");


  c->SetLogy(0);
  tmass_26->SetLineColor(kOrange+8);
  tmass_26->SetMarkerColor(kOrange+8);
  tmass_26->GetXaxis()->SetTitle("#tilde{m}_{TQ} [GeV]");
  tmass_26->GetYaxis()->SetTitle("A.U.");
  tmass_26->DrawNormalized("HIST");
  tmass_SPS->DrawNormalized("HISTSAME");
  tmass_DPS->DrawNormalized("HISTSAME");
  leg3->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/tmass_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/tmass_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/tmass_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/tmass_shapes_LOG.pdf");


  c->SetLogy(0);

  pt_26->SetLineColor(kOrange+8);
  pt_26->SetMarkerColor(kOrange+8);
  pt_26->GetXaxis()->SetTitle("p_{T,TQ} [GeV]");
  pt_26->GetYaxis()->SetTitle("A.U.");
  pt_26->DrawNormalized("HIST");
  pt_SPS->DrawNormalized("HISTSAME");
  pt_DPS->DrawNormalized("HISTSAME");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/pt_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/pt_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/pt_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/pt_shapes_LOG.pdf");

  c->SetLogy(0);
  eta_26->SetLineColor(kOrange+8);
  eta_26->SetMarkerColor(kOrange+8);
  eta_26->GetXaxis()->SetTitle("#eta_{TQ} [GeV]");
  eta_26->GetYaxis()->SetTitle("A.U.");
  eta_26->DrawNormalized("HIST");
  eta_SPS->DrawNormalized("HISTSAME");
  eta_DPS->DrawNormalized("HISTSAME");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/eta_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/eta_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/eta_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/eta_shapes_LOG.pdf");

  c->SetLogy(0);
  Ym_26->SetLineColor(kOrange+8);
  Ym_26->SetMarkerColor(kOrange+8);
  Ym_26->GetXaxis()->SetTitle("m_{Ym} [GeV]");
  Ym_26->GetYaxis()->SetTitle("A.U.");
  Ym_26->DrawNormalized("HIST");
  Ym_SPS->DrawNormalized("HISTSAME");
  Ym_DPS->DrawNormalized("HISTSAME");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/Ym_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/Ym_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/Ym_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/Ym_shapes_LOG.pdf");

  c->SetLogy(0);
  pt_Ym_26->SetLineColor(kOrange+8);
  pt_Ym_26->SetMarkerColor(kOrange+8);
  pt_Ym_26->GetXaxis()->SetTitle("p_{T,Ym} [GeV]");
  pt_Ym_26->GetYaxis()->SetTitle("A.U.");
  pt_Ym_26->DrawNormalized("HIST");
  pt_Ym_SPS->DrawNormalized("HISTSAME");
  pt_Ym_DPS->DrawNormalized("HISTSAME");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/pt_Ym_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/pt_Ym_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/pt_Ym_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/pt_Ym_shapes_LOG.pdf");


  c->SetLogy(0);
  eta_Ym_26->SetLineColor(kOrange+8);
  eta_Ym_26->SetMarkerColor(kOrange+8);
  eta_Ym_26->GetXaxis()->SetTitle("#eta_{Ym} [GeV]");
  eta_Ym_26->GetYaxis()->SetTitle("A.U.");
  eta_Ym_26->DrawNormalized("HIST");
  eta_Ym_SPS->DrawNormalized("HISTSAME");
  eta_Ym_DPS->DrawNormalized("HISTSAME");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/eta_Ym_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/eta_Ym_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/eta_Ym_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/eta_Ym_shapes_LOG.pdf");


  c->SetLogy(0);
  pt_Ye_26->SetLineColor(kOrange+8);
  pt_Ye_26->SetMarkerColor(kOrange+8);
  pt_Ye_26->GetXaxis()->SetTitle("p_{T,Ye} [GeV]");
  pt_Ye_26->GetYaxis()->SetTitle("A.U.");
  pt_Ye_26->DrawNormalized("HIST");
  pt_Ye_SPS->DrawNormalized("HISTSAME");
  pt_Ye_DPS->DrawNormalized("HISTSAME");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/pt_Ye_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/pt_Ye_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/pt_Ye_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/pt_Ye_shapes_LOG.pdf");


  c->SetLogy(0);
  eta_Ye_26->SetLineColor(kOrange+8);
  eta_Ye_26->SetMarkerColor(kOrange+8);
  eta_Ye_26->GetXaxis()->SetTitle("#eta_{Ye} [GeV]");
  eta_Ye_26->GetYaxis()->SetTitle("A.U.");
  eta_Ye_26->DrawNormalized("HIST");
  eta_Ye_SPS->DrawNormalized("HISTSAME");
  eta_Ye_DPS->DrawNormalized("HISTSAME");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/eta_Ye_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/eta_Ye_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/eta_Ye_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/eta_Ye_shapes_LOG.pdf");

  c->SetLogy(0);
  Ye_26->SetLineColor(kOrange+8);
  Ye_26->SetMarkerColor(kOrange+8);
  Ye_26->GetXaxis()->SetTitle("m_{Ye} [GeV]");
  Ye_26->GetYaxis()->SetTitle("A.U.");
  Ye_26->DrawNormalized("HIST");
  Ye_SPS->DrawNormalized("HISTSAME");
  Ye_DPS->DrawNormalized("HISTSAME");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/Ye_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/Ye_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/Ye_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/Ye_shapes_LOG.pdf");


  c->SetLogy(0);
  nvtx_26->SetLineColor(kOrange+8);
  nvtx_26->SetMarkerColor(kOrange+8);
  nvtx_26->GetXaxis()->SetTitle("# vertices");
  nvtx_26->GetYaxis()->SetTitle("A.U.");
  nvtx_26->Scale(nvtx_data2018->Integral()/nvtx_26->Integral());
  nvtx_26_w->Scale(nvtx_data2018->Integral()/nvtx_26_w->Integral());
  nvtx_SPS->Scale(nvtx_data2018->Integral()/nvtx_SPS->Integral());
  nvtx_SPS_w->Scale(nvtx_data2018->Integral()/nvtx_SPS_w->Integral());
  nvtx_DPS->Scale(nvtx_data2018->Integral()/nvtx_DPS->Integral());
  nvtx_DPS_w->Scale(nvtx_data2018->Integral()/nvtx_DPS_w->Integral());
  nvtx_26->Draw("HIST");
  nvtx_26_w->Draw("HISTsame");
  nvtx_SPS->Draw("HIST");
  nvtx_SPS_w->Draw("HISTsame");
  //  nvtx_DPS->Draw("HIST");
  //  nvtx_DPS_w->Draw("HISTsame");
  nvtx_data2018->Draw("PESAME");
  //  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/bkg/nvtx_shapes.png");
  c->SaveAs("~/www/TQ-WORK/bkg/nvtx_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/bkg/nvtx_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/bkg/nvtx_shapes_LOG.pdf");

}


void plotMasses(){

  TFile* f7= new TFile("analysis/fout_m7.root");
  TFile* f9= new TFile("analysis/fout_m9.root");
  TFile* f26= new TFile("analysis/fout_m26_TQ.root");
  TFile* f22= new TFile("analysis/fout_m22_TQ.root");
  TFile* f18= new TFile("analysis/fout_m18_TQ.root");
  TFile* f14= new TFile("analysis/fout_m14_TQ.root");

  TTree* t7= (TTree*) f7->Get("tree_red");
  TTree* t9= (TTree*) f9->Get("tree_red");
  TTree* t14= (TTree*) f14->Get("tree_red");
  TTree* t18= (TTree*) f18->Get("tree_red");
  TTree* t22= (TTree*) f22->Get("tree_red");
  TTree* t26= (TTree*) f26->Get("tree_red");



  TH1F* mass_7 =  new TH1F("mass_7", "",120,0,60);
  TH1F* mass_9 =  new TH1F("mass_9", "",120,0,60);
  TH1F* mass_18 = new TH1F("mass_18", "",120,0,60);
  TH1F* mass_22 = new TH1F("mass_22", "",120,0,60);
  TH1F* mass_26 = new TH1F("mass_26", "",120,0,60);

  TH1F* Ye_7 =  new TH1F("Ye_7", "",80,0,20);
  TH1F* Ye_9 =  new TH1F("Ye_9", "",80,0,20);
  TH1F* Ye_18 = new TH1F("Ye_18", "",80,0,20);
  TH1F* Ye_22 = new TH1F("Ye_22", "",80,0,20);
  TH1F* Ye_26 = new TH1F("Ye_26", "",80,0,20);

  TH1F* Ye_PFPF_7 =  new TH1F("Ye_PFPF_7", "",80,0,20);
  TH1F* Ye_PFPF_9 =  new TH1F("Ye_PFPF_9", "",80,0,20);
  TH1F* Ye_PFPF_18 = new TH1F("Ye_PFPF_18", "",80,0,20);
  TH1F* Ye_PFPF_22 = new TH1F("Ye_PFPF_22", "",80,0,20);
  TH1F* Ye_PFPF_26 = new TH1F("Ye_PFPF_26", "",80,0,20);

  TH1F* Ye_PFLP_7 =  new TH1F("Ye_PFLP_7", "",80,0,20);
  TH1F* Ye_PFLP_9 =  new TH1F("Ye_PFLP_9", "",80,0,20);
  TH1F* Ye_PFLP_18 = new TH1F("Ye_PFLP_18", "",80,0,20);
  TH1F* Ye_PFLP_22 = new TH1F("Ye_PFLP_22", "",80,0,20);
  TH1F* Ye_PFLP_26 = new TH1F("Ye_PFLP_26", "",80,0,20);

  TH1F* Ye_LPLP_7 =  new TH1F("Ye_LPLP_7", "",80,0,20);
  TH1F* Ye_LPLP_9 =  new TH1F("Ye_LPLP_9", "",80,0,20);
  TH1F* Ye_LPLP_18 = new TH1F("Ye_LPLP_18", "",80,0,20);
  TH1F* Ye_LPLP_22 = new TH1F("Ye_LPLP_22", "",80,0,20);
  TH1F* Ye_LPLP_26 = new TH1F("Ye_LPLP_26", "",80,0,20);



  TH1F* Ym_7 =  new TH1F("Ym_7", "",80,0,20);
  TH1F* Ym_9 =  new TH1F("Ym_9", "",80,0,20);
  TH1F* Ym_18 = new TH1F("Ym_18", "",80,0,20);
  TH1F* Ym_22 = new TH1F("Ym_22", "",80,0,20);
  TH1F* Ym_26 = new TH1F("Ym_26", "",80,0,20);


  TH1F* pt_7 =  new TH1F("pt_7", "",60,0,30);
  TH1F* pt_9 =  new TH1F("pt_9", "",60,0,30);
  TH1F* pt_18 = new TH1F("pt_18", "",60,0,30);
  TH1F* pt_22 = new TH1F("pt_22", "",60,0,30);
  TH1F* pt_26 = new TH1F("pt_26", "",60,0,30);

  TH1F* eta_7 =  new TH1F("eta_7", "",48,-10,10);
  TH1F* eta_9 =  new TH1F("eta_9", "",48,-10,10);
  TH1F* eta_18 = new TH1F("eta_18", "",48,-10,10);
  TH1F* eta_22 = new TH1F("eta_22", "",48,-10,10);
  TH1F* eta_26 = new TH1F("eta_26", "",48,-10,10);

  t7->Draw("TQ_mass>>mass_7");
  t9->Draw("TQ_mass>>mass_9");
  t18->Draw("TQ_mass>>mass_18");
  t22->Draw("TQ_mass>>mass_22");
  t26->Draw("TQ_mass>>mass_26");

  t7->Draw("Ye_mass>>Ye_7");
  t9->Draw("Ye_mass>>Ye_9");
  t18->Draw("Ye_mass>>Ye_18");
  t22->Draw("Ye_mass>>Ye_22");
  t26->Draw("Ye_mass>>Ye_26");

  t7->Draw("Ye_mass>>Ye_PFPF_7", "e_isPF1&&e_isPF2");
  t9->Draw("Ye_mass>>Ye_PFPF_9", "e_isPF1&&e_isPF2");
  t18->Draw("Ye_mass>>Ye_PFPF_18", "e_isPF1&&e_isPF2");
  t22->Draw("Ye_mass>>Ye_PFPF_22", "e_isPF1&&e_isPF2");
  t26->Draw("Ye_mass>>Ye_PFPF_26", "e_isPF1&&e_isPF2");

  t7->Draw("Ye_mass>>Ye_PFLP_7", "(e_isPF1&&!e_isPF2)||(!e_isPF1&&e_isPF2)");
  t9->Draw("Ye_mass>>Ye_PFLP_9", "(e_isPF1&&!e_isPF2)||(!e_isPF1&&e_isPF2)");
  t18->Draw("Ye_mass>>Ye_PFLP_18", "(e_isPF1&&!e_isPF2)||(!e_isPF1&&e_isPF2)");
  t22->Draw("Ye_mass>>Ye_PFLP_22", "(e_isPF1&&!e_isPF2)||(!e_isPF1&&e_isPF2)");
  t26->Draw("Ye_mass>>Ye_PFLP_26", "(e_isPF1&&!e_isPF2)||(!e_isPF1&&e_isPF2)");

  t7->Draw("Ye_mass>>Ye_LPLP_7", "!e_isPF1&&!e_isPF2");
  t9->Draw("Ye_mass>>Ye_LPLP_9", "!e_isPF1&&!e_isPF2");
  t18->Draw("Ye_mass>>Ye_LPLP_18", "!e_isPF1&&!e_isPF2");
  t22->Draw("Ye_mass>>Ye_LPLP_22", "!e_isPF1&&!e_isPF2");
  t26->Draw("Ye_mass>>Ye_LPLP_26", "!e_isPF1&&!e_isPF2");


  t7->Draw("Ym_mass>>Ym_7");
  t9->Draw("Ym_mass>>Ym_9");
  t18->Draw("Ym_mass>>Ym_18");
  t22->Draw("Ym_mass>>Ym_22");
  t26->Draw("Ym_mass>>Ym_26");


  t7->Draw("TQ_pt>>pt_7");
  t9->Draw("TQ_pt>>pt_9");
  t18->Draw("TQ_pt>>pt_18");
  t22->Draw("TQ_pt>>pt_22");
  t26->Draw("TQ_pt>>pt_26");

  t7->Draw("TQ_eta>>eta_7");
  t9->Draw("TQ_eta>>eta_9");
  t18->Draw("TQ_eta>>eta_18");
  t22->Draw("TQ_eta>>eta_22");
  t26->Draw("TQ_eta>>eta_26");


  TLegend* leg1 = new TLegend(0.65,0.6, 0.85,0.85);
  leg1->SetFillColor(kWhite);
  //  leg1->SetBorderSize(0);
  leg1->SetHeader("Signal Shapes");
  //  leg1->AddEntry(mass_7," m_{TQ} = 7 GeV" , "PLE");
  // leg1->AddEntry(mass_9," m_{TQ} = 9 GeV" , "PLE");
  leg1->AddEntry(mass_18," m_{TQ} = 18 GeV" , "PLE");
  leg1->AddEntry(mass_22," m_{TQ} = 22 GeV" , "PLE");
  leg1->AddEntry(mass_26," m_{TQ} = 26 GeV" , "PLE");


  TLegend* leg2 = new TLegend(0.6,0.55, 0.85,0.85);
  leg2->SetFillColor(kWhite);
  leg2->SetHeader("Signal Shapes");
  //  leg2->AddEntry(Ye_18," m_{TQ} = 18 GeV" , "LE");
  leg2->AddEntry(Ye_PFPF_18," PF-PF" , "LE");
  leg2->AddEntry(Ye_PFLP_18," PF-LP" , "LE");
  leg2->AddEntry(Ye_LPLP_18," LP-LP" , "LE");



  TCanvas* c = new TCanvas("c","c",800,600);
  c->cd();

  mass_7->SetMarkerColor(kBlue);
  mass_7->SetMarkerStyle(25);
  mass_7->SetLineColor(kBlue);
  mass_9->SetMarkerColor(kRed);
  mass_9->SetMarkerStyle(23);
  mass_9->SetLineColor(kRed);
  mass_18->SetMarkerColor(kMagenta);
  mass_18->SetMarkerStyle(22);
  mass_18->SetLineColor(kMagenta);
  mass_22->SetMarkerColor(kOrange+8);
  mass_22->SetMarkerStyle(22);
  mass_22->SetLineColor(kOrange+8);
  mass_26->GetXaxis()->SetTitle("m_{TQ} [GeV]");
  mass_26->GetYaxis()->SetTitle("A.U.");
  mass_26->DrawNormalized("HIST");
  //  mass_9->DrawNormalized("HISTsame");
  mass_18->DrawNormalized("HISTsame");
  mass_22->DrawNormalized("HISTsame");
  //  mass_7->DrawNormalized("HISTsame");
  leg1->Draw("same");
  c->SaveAs("~/www/TQ-WORK/mass/mass_shapes.png");
  c->SaveAs("~/www/TQ-WORK/mass/mass_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/mass/mass_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/mass/mass_shapes_LOG.pdf");

  c->SetLogy(0);
  Ye_7->SetMarkerColor(kBlue);
  Ye_7->SetMarkerStyle(25);
  Ye_7->SetLineColor(kBlue);
  Ye_9->SetMarkerColor(kRed);
  Ye_9->SetMarkerStyle(23);
  Ye_9->SetLineColor(kRed);
  Ye_18->SetMarkerColor(kMagenta);
  Ye_18->SetMarkerStyle(22);
  Ye_18->SetLineColor(kMagenta);
  Ye_22->SetMarkerColor(kOrange+8);
  Ye_22->SetMarkerStyle(22);
  Ye_22->SetLineColor(kOrange+8);
  Ye_26->GetXaxis()->SetTitle("m_{ee} [GeV]");
  Ye_26->GetYaxis()->SetTitle("A.U.");

  Ye_26->DrawNormalized("HIST");
  //  Ye_9->DrawNormalized("HISTsame");
  Ye_18->DrawNormalized("HISTsame");
  Ye_22->DrawNormalized("HISTsame");
  //  Ye_7->DrawNormalized("HISTsame");
  leg1->Draw("same");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_shapes.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/mass/Ye_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_shapes_LOG.pdf");



  c->SetLogy(0);
  Ye_18->SetLineColor(kAzure+10);
  Ye_PFPF_18->SetLineColor(kSpring-6);
  Ye_PFLP_18->SetLineColor(kOrange+8);
  Ye_LPLP_18->SetLineColor(kMagenta-8);
  Ye_18->GetXaxis()->SetTitle("m_{ee} [GeV]");
  Ye_18->GetYaxis()->SetTitle("A.U.");
  Ye_18->Draw("HIST");
  Ye_PFPF_18->Draw("HISTsame");
  Ye_PFLP_18->Draw("HISTsame");
  Ye_LPLP_18->Draw("HISTsame");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m18_shapes.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m18_shapes.pdf");
  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m18_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m18_shapes_LOG.pdf");

  c->SetLogy(0);
  Ye_22->SetLineColor(kAzure+10);
  Ye_PFPF_22->SetLineColor(kSpring-6);
  Ye_PFLP_22->SetLineColor(kOrange+8);
  Ye_LPLP_22->SetLineColor(kMagenta-8);
  Ye_22->GetXaxis()->SetTitle("m_{ee} [GeV]");
  Ye_22->GetYaxis()->SetTitle("A.U.");
  Ye_22->Draw("HIST");
  Ye_PFPF_22->Draw("HISTsame");
  Ye_PFLP_22->Draw("HISTsame");
  Ye_LPLP_22->Draw("HISTsame");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m22_shapes.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m22_shapes.pdf");
  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m22_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m22_shapes_LOG.pdf");


  c->SetLogy(0);
  Ye_26->SetLineColor(kAzure+10);
  Ye_PFPF_26->SetLineColor(kSpring-6);
  Ye_PFLP_26->SetLineColor(kOrange+8);
  Ye_LPLP_26->SetLineColor(kMagenta-8);
  Ye_26->GetXaxis()->SetTitle("m_{ee} [GeV]");
  Ye_26->GetYaxis()->SetTitle("A.U.");
  Ye_26->Draw("HIST");
  Ye_PFPF_26->Draw("HISTsame");
  Ye_PFLP_26->Draw("HISTsame");
  Ye_LPLP_26->Draw("HISTsame");
  leg2->Draw("same");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m26_shapes.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m26_shapes.pdf");
  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m26_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ye_m26_shapes_LOG.pdf");





  c->SetLogy(0);
  Ym_7->SetMarkerColor(kBlue);
  Ym_7->SetMarkerStyle(25);
  Ym_7->SetLineColor(kBlue);
  Ym_9->SetMarkerColor(kRed);
  Ym_9->SetMarkerStyle(23);
  Ym_9->SetLineColor(kRed);
  Ym_18->SetMarkerColor(kMagenta);
  Ym_18->SetMarkerStyle(22);
  Ym_18->SetLineColor(kMagenta);
  Ym_22->SetMarkerColor(kOrange+8);
  Ym_22->SetMarkerStyle(22);
  Ym_22->SetLineColor(kOrange+8);
  Ym_26->GetXaxis()->SetTitle("m_{#mu#mu} [GeV]");
  Ym_26->GetYaxis()->SetTitle("A.U.");

  Ym_26->DrawNormalized("HIST");
  //  Ym_9->DrawNormalized("HISTsame");
  Ym_18->DrawNormalized("HISTsame");
  Ym_22->DrawNormalized("HISTsame");
  //  Ym_7->DrawNormalized("HISTsame");
  leg1->Draw("same");
  c->SaveAs("~/www/TQ-WORK/mass/Ym_shapes.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ym_shapes.pdf");

  c->SetLogy();
  c->SaveAs("~/www/TQ-WORK/mass/Ym_shapes_LOG.png");
  c->SaveAs("~/www/TQ-WORK/mass/Ym_shapes_LOG.pdf");


  c->SetLogy(0);
  eta_7->SetMarkerColor(kBlue);
  eta_7->SetMarkerStyle(25);
  eta_7->SetLineColor(kBlue);
  eta_9->SetMarkerColor(kRed);
  eta_9->SetMarkerStyle(23);
  eta_9->SetLineColor(kRed);
  eta_18->SetMarkerColor(kMagenta);
  eta_18->SetMarkerStyle(22);
  eta_18->SetLineColor(kMagenta);
  eta_22->SetMarkerColor(kOrange+8);
  eta_22->SetMarkerStyle(22);
  eta_22->SetLineColor(kOrange+8);

  eta_26->GetXaxis()->SetTitle("#eta_{TQ} ");
  eta_26->GetYaxis()->SetTitle("A.U.");

  eta_26->DrawNormalized("HIST");
  //  eta_9->DrawNormalized("HISTsame");
  eta_18->DrawNormalized("HISTsame");
  eta_22->DrawNormalized("HISTsame");
  //  eta_7->DrawNormalized("HISTsame");
  leg1->Draw("same");
  c->SaveAs("~/www/TQ-WORK/mass/eta_shapes.png");
  c->SaveAs("~/www/TQ-WORK/mass/eta_shapes.pdf");

  pt_7->SetMarkerColor(kBlue);
  pt_7->SetMarkerStyle(25);
  pt_7->SetLineColor(kBlue);
  pt_9->SetMarkerColor(kRed);
  pt_9->SetMarkerStyle(23);
  pt_9->SetLineColor(kRed);
  pt_18->SetMarkerColor(kMagenta);
  pt_18->SetMarkerStyle(22);
  pt_18->SetLineColor(kMagenta);
  pt_22->SetMarkerColor(kOrange+8);
  pt_22->SetMarkerStyle(22);
  pt_22->SetLineColor(kOrange+8);
  pt_18->GetXaxis()->SetTitle("p_{T,TQ} [GeV]");
  pt_18->GetYaxis()->SetTitle("A.U.");

  pt_18->DrawNormalized("HIST");
  //  pt_9->DrawNormalized("HISTsame");
  pt_26->DrawNormalized("HISTsame");
  pt_22->DrawNormalized("HISTsame");
  //  pt_7->DrawNormalized("HISTsame");
  leg1->Draw("same");
  c->SaveAs("~/www/TQ-WORK/mass/pt_shapes.png");
  c->SaveAs("~/www/TQ-WORK/mass/pt_shapes.pdf");
 
}






TH1F* makeLowPtPlots(std::string mass, int iplot){
  TFile* f;
  if(mass=="7") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m7_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="9") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToJJTo2mu2e/ntuple_ggXToJJTo2mu2e_m9_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="14") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m14_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_20K.root");
  if(mass=="26") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m26_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="22") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m22_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");
  if(mass=="18") f= new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m18_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root");

  TTree* tree= (TTree*) f->Get("GenAnalysis/tree");


  TH1F* gen_ele_pt = new TH1F("gen_ele_pt", "gen_ele_pt", 60, 0,30);
  TH1F* gen_ele_eta = new TH1F("gen_ele_eta", "gen_ele_eta", 60, -10,10);
  TH1F* gen_mu_pt = new TH1F("gen_mu_pt", "gen_mu_pt", 60, 0,30);
  TH1F* gen_mu_eta = new TH1F("gen_mu_eta", "gen_mu_eta", 60, -10,10);
  TH1F* ele_pt = new TH1F("ele_pt", "ele_pt", 60, 0,30);
  TH1F* ele_pt_lp = new TH1F("ele_pt_lp", "ele_pt_lp", 60, 0,30);
  TH1F* ele_pt_pf = new TH1F("ele_pt_pf", "ele_pt_pf", 60, 0,30);
  TH1F* ele_mva_lp = new TH1F("ele_mva_lp", "ele_mva_lp", 30, 0,15);
  TH1F* fake_mva_lp = new TH1F("fake_mva_lp", "fake_mva_lp", 30, 0,15);
  TH1F* ele_mva_pf = new TH1F("ele_mva_pf", "ele_mva_pf", 50, -10,15);
  TH1F* fake_mva_pf = new TH1F("fake_mva_pf", "fake_mva_pf", 50, -10,15);
  TH1F* mu_pt = new TH1F("mu_pt", "mu_pt", 60, 0,30);
  TH1F* mu_eta = new TH1F("mu_eta", "mu_eta", 60,-10,10);
  TH1F* ele_eta = new TH1F("ele_eta", "ele_eta", 60,-10,10);
  TH1F* ele_eta_lp = new TH1F("ele_eta_lp", "ele_eta_lp", 60,-10,10);
  TH1F* ele_eta_pf = new TH1F("ele_eta_pf", "ele_eta_pf", 60,-10,10);

  TH1F* nMuReco = new TH1F("nMuReco", "nMuReco", 5,0,5);
  TH1F* nEleReco = new TH1F("nEleReco", "nEleReco", 5,0,5);
  TH1F* nElePFReco = new TH1F("nElePFReco", "nElePFReco", 5,0,5);
  TH1F* nEleLPReco = new TH1F("nEleLPReco", "nEleLPReco", 5,0,5);

  

  TCanvas* c = new TCanvas("c","c",1);  
  // ----------------------- ELE PT -------------------------- //
  if(iplot==0 || iplot==1 || iplot==2){
    tree->Draw("recoEle_pt>>ele_pt",    "recoEle_isPFoverlap==0&&recoEle_dR1<0.1 && abs(recoEle_etamode)<2.5");
    tree->Draw("recoEle_pt>>ele_pt_pf", "recoEle_isPFoverlap==0&&recoEle_dR1<0.1 && abs(recoEle_etamode)<2.5 && recoEle_isPF==1");
    tree->Draw("recoEle_ptmode>>ele_pt_lp", "recoEle_isPFoverlap==0&&recoEle_dR1<0.1 && abs(recoEle_etamode)<2.5 && recoEle_isLowPt==1");

    c->cd();
    TLegend* leg1 = new TLegend(0.5,0.6, 0.85,0.9);
    leg1->SetFillColor(kWhite);
    leg1->SetBorderSize(0);
    leg1->SetHeader(("m_{TQ} = "+mass+" GeV").c_str());
    //    leg1->AddEntry(ele_pt,"All Electrons in |#eta| <2.5" , "L");
    leg1->AddEntry(ele_pt_pf,"PF Electrons" , "L");
    leg1->AddEntry(ele_pt_lp,"LP Electrons" , "L");
    
    ele_pt_pf->SetLineColor(kSpring-6);
    ele_pt_lp->SetLineColor(kOrange+8);
    ele_pt->SetLineColor(kAzure+10);
    ele_pt->GetYaxis()->SetTitle("Events / 0.5 GeV");
    ele_pt->GetXaxis()->SetTitle("Electron p_{T} [GeV]");
    ele_pt_lp->GetYaxis()->SetTitle("Events / 0.5 GeV");
    ele_pt_lp->GetXaxis()->SetTitle("Electron p_{T} [GeV]");
    ele_pt_pf->GetYaxis()->SetTitle("Events / 0.5 GeV");
    ele_pt_pf->GetXaxis()->SetTitle("Electron p_{T} [GeV]");
    //    ele_pt->Draw("hist");
    ele_pt_pf->Draw("hist");
    ele_pt_lp->Draw("histsame");
    leg1->Draw("same");
    c->SaveAs(("~/www/TQ-WORK/kin/pt_electrons_m"+mass+".png").c_str());
    c->SaveAs(("~/www/TQ-WORK/kin/pt_electrons_m"+mass+".pdf").c_str());
  }

  // ----------------------- MVA LP-------------------------- //
  if(iplot==3 || iplot==4){
    tree->Draw("recoEle_mvaValue>>ele_mva_lp", "recoEle_isPFoverlap==0&&recoEle_dR1<0.1 && abs(recoEle_etamode)<2.5 && recoEle_isLowPt==1");
    tree->Draw("recoEle_mvaValue>>fake_mva_lp", "recoEle_isPFoverlap==0&&recoEle_dR1>0.8 && abs(recoEle_etamode)<2.5 && recoEle_isLowPt==1");
    TLegend* leg2 = new TLegend(0.5,0.6, 0.85,0.9);
    leg2->SetFillColor(kWhite);
    leg2->SetBorderSize(0);
    leg2->SetHeader(("m_{TQ} = "+mass+" GeV").c_str());
    leg2->AddEntry(ele_mva_lp,"LP Electrons" , "L");
    leg2->AddEntry(fake_mva_lp,"LP Fakes" , "L");
    ele_mva_lp->SetLineColor(kBlue);
    fake_mva_lp->SetLineColor(kOrange+8);
    fake_mva_lp->GetYaxis()->SetTitle("A.U.");
    fake_mva_lp->GetXaxis()->SetTitle("Electron ID BDT Output");
    ele_mva_lp->GetYaxis()->SetTitle("A.U.");
    ele_mva_lp->GetXaxis()->SetTitle("Electron ID BDT Output");
    
    fake_mva_lp->DrawNormalized("hist");
    ele_mva_lp->DrawNormalized("histsame");
    leg2->Draw("same");
    c->SaveAs(("~/www/TQ-WORK/kin/mva_lp_electrons_m"+mass+".png").c_str());
    c->SaveAs(("~/www/TQ-WORK/kin/mva_lp_electrons_m"+mass+".pdf").c_str());
  }

  // ----------------------- MVA PF-------------------------- //
  if(iplot==5 || iplot==6){
    tree->Draw("recoEle_mvaPFValue>>ele_mva_pf", "recoEle_isPFoverlap==0&&recoEle_dR1<0.1 && abs(recoEle_etamode)<2.5 && recoEle_isPF==1");
    tree->Draw("recoEle_mvaPFValue>>fake_mva_pf", "recoEle_isPFoverlap==0&&recoEle_dR1>0.8 && abs(recoEle_etamode)<2.5 && recoEle_isPF==1");
    TLegend* leg3 = new TLegend(0.6,0.7, 0.85,0.9);
    leg3->SetFillColor(kWhite);
    leg3->SetBorderSize(0);
    leg3->SetHeader(("m_{TQ} = "+mass+" GeV").c_str());
    leg3->AddEntry(ele_mva_pf,"PF Electrons" , "L");
    leg3->AddEntry(fake_mva_pf,"PF Fakes" , "L");
    ele_mva_pf->SetLineColor(kBlue);
    fake_mva_pf->SetLineColor(kOrange+8);
    ele_mva_pf->GetYaxis()->SetTitle("A.U.");
    ele_mva_pf->GetXaxis()->SetTitle("Electron BDT Output");
    fake_mva_pf->GetYaxis()->SetTitle("A.U.");
    fake_mva_pf->GetXaxis()->SetTitle("Electron BDT Output");
    
    ele_mva_pf->DrawNormalized("hist");
    fake_mva_pf->DrawNormalized("histsame");
    leg3->Draw("same");
    c->SaveAs(("~/www/TQ-WORK/kin/mva_pf_electrons_m"+mass+".png").c_str());
    c->SaveAs(("~/www/TQ-WORK/kin/mva_pf_electrons_m"+mass+".pdf").c_str());
  }

  // ----------------------- Gen PT and ETA -------------------------- //
  if(iplot==7){
    tree->Draw("genLep_pt>>gen_ele_pt",    "abs(genLep_pdgId)==11");
    gen_ele_pt->GetYaxis()->SetTitle("A.U.");
    gen_ele_pt->GetXaxis()->SetTitle("Gen - Electron p_{T} [GeV]");
  }else if(iplot==8){
    tree->Draw("genLep_eta>>gen_ele_eta",    "abs(genLep_pdgId)==11");
    gen_ele_eta->GetYaxis()->SetTitle("A.U.");
    gen_ele_eta->GetXaxis()->SetTitle("Gen - Electron #eta");
  }else if(iplot==9){
    tree->Draw("genLep_pt>>gen_mu_pt",    "abs(genLep_pdgId)==13");
    gen_mu_pt->GetYaxis()->SetTitle("A.U.");
    gen_mu_pt->GetXaxis()->SetTitle("Gen - #mu p_{T} [GeV]");
  }else if(iplot==10){
    tree->Draw("genLep_eta>>gen_mu_eta",    "abs(genLep_pdgId)==13");
    gen_mu_eta->GetYaxis()->SetTitle("A.U.");
    gen_mu_eta->GetXaxis()->SetTitle("Gen - #mu #eta");
  }

  // ----------------------- MU PT -------------------------- //

  if(iplot==11){
    tree->Draw("recoMu_pt>>mu_pt",    "recoMu_dR1<0.1 && abs(recoMu_eta)<2.5");
    mu_pt->GetYaxis()->SetTitle("Events / 0.5 GeV");
    mu_pt->GetXaxis()->SetTitle("#mu p_{T} [GeV]");
  }
  // ----------------------- MU ETA -------------------------- //
  if(iplot==12){
    tree->Draw("recoMu_eta>>mu_eta",    "recoMu_dR1<0.1");
    mu_eta->GetYaxis()->SetTitle("Events / 0.5 GeV");
    mu_eta->GetXaxis()->SetTitle("#mu #eta ");
  }
  // ----------------------- ELE ETA -------------------------- //
  if(iplot==13 || iplot==14 || iplot==15){
    tree->Draw("recoEle_etamode>>ele_eta",    "recoEle_isPFoverlap==0&&recoEle_dR1<0.1 ");
    tree->Draw("recoEle_etamode>>ele_eta_pf", "recoEle_isPFoverlap==0&&recoEle_dR1<0.1  && recoEle_isPF==1");
    tree->Draw("recoEle_etamode>>ele_eta_lp", "recoEle_isPFoverlap==0&&recoEle_dR1<0.1  && recoEle_isLowPt==1");
    
    c->cd();
    TLegend* leg6 = new TLegend(0.5,0.6, 0.85,0.9);
    leg6->SetFillColor(kWhite);
    leg6->SetBorderSize(0);
    leg6->SetHeader(("m_{TQ} = "+mass+" GeV").c_str());
    //    leg6->AddEntry(ele_eta,"All Electrons" , "L");
    leg6->AddEntry(ele_eta_pf,"PF Electrons" , "L");
    leg6->AddEntry(ele_eta_lp,"LP Electrons" , "L");
    
    ele_eta_pf->SetLineColor(kSpring-6);
    ele_eta_lp->SetLineColor(kOrange+8);
    ele_eta->SetLineColor(kAzure+10);
    ele_eta->GetYaxis()->SetTitle("Events / 0.5 GeV");
    ele_eta->GetXaxis()->SetTitle("Electron #eta");
    ele_eta_lp->GetYaxis()->SetTitle("Events / 0.5 GeV");
    ele_eta_lp->GetXaxis()->SetTitle("Electron #eta");
    ele_eta_pf->GetYaxis()->SetTitle("Events / 0.5 GeV");
    ele_eta_pf->GetXaxis()->SetTitle("Electron #eta");
    //    ele_eta->Draw("hist");
    ele_eta_lp->Draw("hist");
    ele_eta_pf->Draw("histsame");
    leg6->Draw("same");
    c->SaveAs(("~/www/TQ-WORK/kin/eta_electrons_m"+mass+".png").c_str());
    c->SaveAs(("~/www/TQ-WORK/kin/eta_electrons_m"+mass+".pdf").c_str());
  }

  if(iplot==16){
    tree->Draw("Sum$(recoMu_pt>1 && fabs(recoMu_eta)<2.5 && recoMu_softID)>>nMuReco");
    nMuReco->GetYaxis()->SetTitle("Events ");
    nMuReco->GetXaxis()->SetTitle("Number of #mu passing acceptance && ID");
  }
  if(iplot==17 || iplot==18 || iplot==19){
    tree->Draw("Sum$(recoEle_isPFoverlap==0&&fabs(recoEle_eta)<2.5 && ((recoEle_isPF&&recoEle_pt>1&&recoEle_mvaPFValue>-2)||(recoEle_isLowPt&&recoEle_ptmode>1&&recoEle_mvaValue>3)))>>nEleReco");
    nEleReco->GetYaxis()->SetTitle("Events ");
    nEleReco->GetXaxis()->SetTitle("Number of e passing acceptance && ID");

    tree->Draw("Sum$(recoEle_isPF&&recoEle_isPFoverlap==0&&fabs(recoEle_eta)<2.5 && ((recoEle_isPF&&recoEle_pt>1&&recoEle_mvaPFValue>-2)||(recoEle_isLowPt&&recoEle_ptmode>1&&recoEle_mvaValue>3)))>>nElePFReco");
    nElePFReco->GetYaxis()->SetTitle("Events ");
    nElePFReco->GetXaxis()->SetTitle("Number of e passing acceptance && ID");

    tree->Draw("Sum$(recoEle_isLowPt&&recoEle_isPFoverlap==0&&fabs(recoEle_eta)<2.5 && ((recoEle_isPF&&recoEle_pt>1&&recoEle_mvaPFValue>-2)||(recoEle_isLowPt&&recoEle_ptmode>1&&recoEle_mvaValue>3)))>>nEleLPReco");
    nEleLPReco->GetYaxis()->SetTitle("Events ");
    nEleLPReco->GetXaxis()->SetTitle("Number of e passing acceptance && ID");

    c->cd();
    TLegend* leg7 = new TLegend(0.5,0.6, 0.85,0.9);
    leg7->SetFillColor(kWhite);
    leg7->SetBorderSize(0);
    leg7->SetHeader(("m_{TQ} = "+mass+" GeV").c_str());
    //    leg7->AddEntry(ele_eta,"All Electrons" , "L");
    leg7->AddEntry(nElePFReco,"PF Electrons" , "L");
    leg7->AddEntry(nEleLPReco,"LP Electrons" , "L");
    
    nElePFReco->SetLineColor(kSpring-6);
    nEleLPReco->SetLineColor(kOrange+8);
    nEleReco->SetLineColor(kAzure+10);
    //    nEleReco->Draw("hist");
    nEleLPReco->Draw("hist");
    nElePFReco->Draw("histsame");
    leg7->Draw("same");
    c->SaveAs(("~/www/TQ-WORK/kin/nEleReco_m"+mass+".png").c_str());
    c->SaveAs(("~/www/TQ-WORK/kin/nEleReco_m"+mass+".pdf").c_str());



  }


  if(iplot==0) return ele_pt;
  else if(iplot==1) return ele_pt_pf;
  else if(iplot==2) return ele_pt_lp;
  else if(iplot==3) return ele_mva_lp;
  else if(iplot==4) return fake_mva_lp;
  else if(iplot==5) return ele_mva_pf;
  else if(iplot==6) return fake_mva_pf;
  else if(iplot==7) return gen_ele_pt;
  else if(iplot==8) return gen_ele_eta;
  else if(iplot==9) return gen_mu_pt;
  else if(iplot==10) return gen_mu_eta;
  else if(iplot==11) return mu_pt;
  else if(iplot==12) return mu_eta;
  else if(iplot==13) return ele_eta;
  else if(iplot==14) return ele_eta_pf;
  else if(iplot==15) return ele_eta_lp;
  else if(iplot==16) return nMuReco;
  else if(iplot==17) return nEleReco;
  else if(iplot==18) return nElePFReco;
  else if(iplot==19) return nEleLPReco;
  
  
}


void compareKinPlots(){
  
  std::vector<std::string> name;
  name.push_back("ele_pt");
  name.push_back("ele_pt_pf");
  name.push_back("ele_pt_lp");
  name.push_back("ele_mva_lp");
  name.push_back("fake_mva_lp");
  name.push_back("ele_mva_pf");
  name.push_back("fake_mva_pf");
  name.push_back("gen_ele_pt");
  name.push_back("gen_ele_eta");
  name.push_back("gen_mu_pt");
  name.push_back("gen_mu_eta");
  name.push_back("mu_pt");
  name.push_back("mu_eta");
  name.push_back("ele_eta");
  name.push_back("ele_eta_pf");
  name.push_back("ele_eta_lp");
  name.push_back("nMuReco");
  name.push_back("nEleReco");
  name.push_back("nElePFReco");
  name.push_back("nEleLPReco");

  for(int i=0; i<20;i++){
  TH1F* pt_7=  makeLowPtPlots("7", i);
  TH1F* pt_9=  makeLowPtPlots("9", i);
  TH1F* pt_18=  makeLowPtPlots("18", i);
  TH1F* pt_22=  makeLowPtPlots("22", i);
  TH1F* pt_26=  makeLowPtPlots("26", i);
  pt_7->SetLineColor(kBlue+1);
  pt_9->SetLineColor(kCyan+2);
  pt_18->SetLineColor(kGreen-6);
  pt_22->SetLineColor(kOrange-3);
  pt_26->SetLineColor(kPink-9);

  TLegend* leg2 = new TLegend(0.6,0.65, 0.8,0.84);
  leg2->SetFillColor(kWhite);
  leg2->SetBorderSize(0);
  leg2->AddEntry(pt_7," m_{TQ} = 7 GeV" , "L");
  leg2->AddEntry(pt_9," m_{TQ} = 9 GeV" , "L");
  leg2->AddEntry(pt_18," m_{TQ} = 18 GeV" , "L");
  leg2->AddEntry(pt_22," m_{TQ} = 22 GeV" , "L");
  leg2->AddEntry(pt_26," m_{TQ} = 26 GeV" , "L");


  TCanvas* c = new TCanvas("c","c",1);
  c->cd();
  if(i!=8 && i!=10){
    pt_7->DrawNormalized("hist");
    pt_9->DrawNormalized("histsame");
    pt_18->DrawNormalized("histsame");
    pt_22->DrawNormalized("histsame");
    pt_26->DrawNormalized("histsame");
  }else{
    pt_26->DrawNormalized("hist");
    pt_22->DrawNormalized("histsame");
    pt_18->DrawNormalized("histsame");
    pt_9->DrawNormalized("histsame");
    pt_7->DrawNormalized("histsame");
  

  }
  leg2->Draw("same");
  c->SaveAs(("~/www/TQ-WORK/kin/"+name[i]+"_compareMasses.png").c_str());
  c->SaveAs(("~/www/TQ-WORK/kin/"+name[i]+"_compareMasses.pdf").c_str());
  }
  
}
