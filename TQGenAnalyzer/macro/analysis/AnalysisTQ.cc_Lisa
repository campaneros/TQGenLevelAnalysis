
#define AnalysisTQ_cxx
#include "AnalysisTQ.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
using namespace std;
#include <stdio.h>
#include <iostream>

float AnalysisTQ::DeltaR(float eta1,float phi1,float eta2,float phi2)
{
  float deltaPhi = TMath::Abs(phi1-phi2);
  float deltaEta = eta1-eta2;
  if(deltaPhi > TMath::Pi())
    deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
}

void AnalysisTQ::Loop(std::string mass,int tot,int trigger)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   
   int counter[14]={0};
   int counterBIS=0;
   int counterTRIS=0;

   double massnom;
   if(mass=="7" || mass=="9")massnom=3.09;
   else massnom=9.46;
   TH1F* hnvtxw_2018;
   TFile* fnvtxw_2018= TFile::Open("../nvtx_weights_2018UL_postsel.root");
   hnvtxw_2018= (TH1F*)fnvtxw_2018->Get("rescaledWeights");

   hnvtxw_2018->Draw();
   //   fnvtxw_2018->Close();



   TFile* fout = new TFile(("fout_m"+mass+"_TQ.root").c_str(),"RECREATE");   
   TTree tree_red("tree_red","");

   Float_t e_pt1; 
   Float_t e_pt2;
   Float_t m_pt1;
   Float_t m_pt2;
   Float_t e_eta1;
   Float_t e_eta2;
   Float_t e_phi1;
   Float_t e_phi2;
   Float_t e_mvaValue1;
   Float_t e_mvaPFValue1;
   Float_t e_mvaValue2;
   Float_t e_mvaPFValue2;
   Float_t m_eta1;
   Float_t m_eta2;
   Float_t m_phi1;
   Float_t m_phi2;
   Int_t e_isPF1;
   Int_t e_isPF2;
   Float_t TQ_vtxprob;
   Float_t Ym_vtxprob;
   Float_t Ye_vtxprob;
   Float_t TQ_mass_tilde; 
   Float_t TQ_mass; 
   Float_t Ym_mass; 
   Float_t Ye_mass; 
   Float_t TQ_pt; 
   Float_t Ym_pt; 
   Float_t Ye_pt; 
   Float_t TQ_eta; 
   Float_t Ym_eta; 
   Float_t Ye_eta; 
   Float_t mass_Err;
   Float_t x_sec;
   Float_t puw2018;

   Float_t nvtxw2018;

   Int_t n_vtx;


   
   tree_red.Branch("e_isPF1",&e_isPF1,"e_isPF1/I");
   tree_red.Branch("e_isPF2",&e_isPF2,"e_isPF2/I");
   tree_red.Branch("e_pt1",&e_pt1,"e_pt1/F");
   tree_red.Branch("e_pt2",&e_pt2,"e_pt2/F");
   tree_red.Branch("m_pt1",&m_pt1,"m_pt1/F");
   tree_red.Branch("m_pt2",&m_pt2,"m_pt2/F");
   tree_red.Branch("e_eta1",&e_eta1,"e_eta1/F");
   tree_red.Branch("e_eta2",&e_eta2,"e_eta2/F");
   tree_red.Branch("e_phi1",&e_phi1,"e_phi1/F");
   tree_red.Branch("e_phi2",&e_phi2,"e_phi2/F");
   tree_red.Branch("e_mvaValue1", &e_mvaValue1, "e_mvaValue1/F");
   tree_red.Branch("e_mvaPFValue1", &e_mvaPFValue1, "e_mvaPFValue1/F");
   tree_red.Branch("e_mvaValue2", &e_mvaPFValue2, "e_mvaValue2/F");
   tree_red.Branch("e_mvaPFValue2", &e_mvaPFValue2, "e_mvaPFValue/F");
   tree_red.Branch("m_eta1",&m_eta1,"m_eta1/F");
   tree_red.Branch("m_eta2",&m_eta2,"m_eta2/F");
   tree_red.Branch("m_phi1",&m_phi1,"m_phi1/F");
   tree_red.Branch("m_phi2",&m_phi2,"m_phi2/F");
   tree_red.Branch("TQ_vtxprob",&TQ_vtxprob,"TQ_vtxprob/F");
   tree_red.Branch("Ym_vtxprob",&Ym_vtxprob,"Ym_vtxprob/F");
   tree_red.Branch("Ye_vtxprob",&Ye_vtxprob,"Ye_vtxprob/F");
   tree_red.Branch("TQ_mass",&TQ_mass,"TQ_mass/F");
   tree_red.Branch("TQ_mass_tilde",&TQ_mass_tilde,"TQ_mass_tilde/F");
   tree_red.Branch("Ym_mass",&Ym_mass,"Ym_mass/F");
   tree_red.Branch("Ye_mass",&Ye_mass,"Ye_mass/F");
   tree_red.Branch("TQ_pt",&TQ_pt,"TQ_pt/F");
   tree_red.Branch("Ym_pt",&Ym_pt,"Ym_pt/F");
   tree_red.Branch("Ye_pt",&Ye_pt,"Ye_pt/F");
   tree_red.Branch("TQ_eta",&TQ_eta,"TQ_eta/F");
   tree_red.Branch("Ym_eta",&Ym_eta,"Ym_eta/F");
   tree_red.Branch("Ye_eta",&Ye_eta,"Ye_eta/F");
   tree_red.Branch("mass_Err", &mass_Err, "mass_Err/F");
   tree_red.Branch("x_sec", &x_sec, "x_sec/F");
   tree_red.Branch("puw2018", &puw2018, "puw2018/F");
   tree_red.Branch("nvtxw2018", &nvtxw2018, "nvtxw2018/F");
   tree_red.Branch("n_vtx", &n_vtx, "n_vtx/I");


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      int nTQwithAtLeast2mu=0;
      int nTQwithAtLeast2muPtEtaID=0;
      int nTQwithAtLeast2muPtEtaIDVtxProb=0;
      int nTQwithAtLeast2muPtEtaIDVtxProbMass=0;
      int nTQwithAtLeast2muPtEtaIDVtxProbMassPt=0;
      int nTQwithAtLeast2el=0;
      int nTQwithAtLeast2elOver=0;
      int nTQwithAtLeast2elOverPtEtaID=0;
      int nTQwithAtLeast2elOverPtEtaIDLp=0;
      int nTQwithAtLeast2elOverPtEtaIDLpVtxProb=0;
      int nTQwithAtLeast2elOverPtEtaIDLpVtxProbMass=0;
      int nTQwithDeltaR=0;
      int nTQwithVtxProb=0;
      //      std::cout<< "---------------------------------------------" <<std::endl;

      counter[0]++;

      int best_cand=999;
      float prob_cand=0;
      int reco_type=-1;
      float mva_sum = -999.;
      float mva_mix_sum= 0.; 

      // ------------- TQ -------------- //
      for(int i=0; i< nTQReco; i++){

	//muons

	if((*recoTQ_pt1)[i]<2.5 || (*recoTQ_pt2)[i]<2.5 )continue;

	nTQwithAtLeast2mu++;

	if((*recoTQ_softID1)[i]==0 || (*recoTQ_softID2)[i]==0) continue;

	nTQwithAtLeast2muPtEtaID++;
                                 
	if((*recoTQ_Y1vtxprob)[i]<0.05)continue;
      
        nTQwithAtLeast2muPtEtaIDVtxProb++;


        if ((*recoTQ_Y1pt)[i]<12.) continue;

      
        nTQwithAtLeast2muPtEtaIDVtxProbMass++;

        if((*recoTQ_Y1mass)[i]<7.) continue;

        nTQwithAtLeast2muPtEtaIDVtxProbMassPt++;



	//electrons
	if(((*recoTQ_charge3)[i]*(*recoTQ_charge4)[i])>0 )continue;

        nTQwithAtLeast2el++;

	if((*recoTQ_isPFoverlap3)[i] || (*recoTQ_isPFoverlap4)[i])continue;

        nTQwithAtLeast2elOver++;

	bool isPt3wrong = ((*recoTQ_isPF3)[i]==1 && (*recoTQ_pt3)[i]<1) || ((*recoTQ_isPF3)[i]==0 && (*recoTQ_pt3mode)[i]<1);
	bool isPt4wrong = ((*recoTQ_isPF4)[i]==1 && (*recoTQ_pt4)[i]<1) || ((*recoTQ_isPF4)[i]==0 && (*recoTQ_pt4mode)[i]<1);
	bool isEta3wrong = fabs((*recoTQ_eta3)[i])>2.5;
	bool isEta4wrong = fabs((*recoTQ_eta4)[i])>2.5;
	bool isID3wrong = ((*recoTQ_isPF3)[i]==1 && (*recoTQ_mvaPFValue3)[i]<-2) || ((*recoTQ_isPF3)[i]==0 && (*recoTQ_mvaValue3)[i]<3);
	bool isID4wrong = ((*recoTQ_isPF4)[i]==1 && (*recoTQ_mvaPFValue4)[i]<-2) || ((*recoTQ_isPF4)[i]==0 && (*recoTQ_mvaValue4)[i]<3);

	if(isPt3wrong || isPt4wrong || isEta3wrong || isEta4wrong || isID3wrong || isID4wrong)continue;
	

        bool isPF = (*recoTQ_isPF3)[i]==1  && (*recoTQ_isPF4)[i]==1;
        bool isMix = ((*recoTQ_isPF3)[i]==1 && (*recoTQ_isPF4)[i]==0) || ((*recoTQ_isPF3)[i]==0 && (*recoTQ_isPF4)[i]==1);
        bool isLP = (*recoTQ_isPF3)[i]==0  && (*recoTQ_isPF4)[i]==0;

        nTQwithAtLeast2elOverPtEtaID++;


        if(isLP) continue;

        
        nTQwithAtLeast2elOverPtEtaIDLp++;


	//select TQ with highest vtx prob
	if((*recoTQ_Y2vtxprob)[i]<0.05)continue;

        nTQwithAtLeast2elOverPtEtaIDLpVtxProb++;

        if((*recoTQ_Y2mass)[i]<4.) continue;
 
        nTQwithAtLeast2elOverPtEtaIDLpVtxProbMass++;

	float dR12=DeltaR((*recoTQ_eta1)[i],(*recoTQ_phi1)[i],(*recoTQ_eta2)[i],(*recoTQ_phi2)[i]);
	float dR13=DeltaR((*recoTQ_eta1)[i],(*recoTQ_phi1)[i],(*recoTQ_eta3)[i],(*recoTQ_phi3)[i]);
	float dR14=DeltaR((*recoTQ_eta1)[i],(*recoTQ_phi1)[i],(*recoTQ_eta4)[i],(*recoTQ_phi4)[i]);
	float dR23=DeltaR((*recoTQ_eta2)[i],(*recoTQ_phi2)[i],(*recoTQ_eta3)[i],(*recoTQ_phi3)[i]);
	float dR24=DeltaR((*recoTQ_eta2)[i],(*recoTQ_phi2)[i],(*recoTQ_eta4)[i],(*recoTQ_phi4)[i]);
	float dR34=DeltaR((*recoTQ_eta3)[i],(*recoTQ_phi3)[i],(*recoTQ_eta4)[i],(*recoTQ_phi4)[i]);

	if(dR12<0.02 || dR13<0.02 ||dR14<0.02 ||dR23<0.02 ||dR24<0.02 ||dR34<0.02 )continue;
	nTQwithDeltaR++;

	if((*recoTQ_vtxprob)[i]<=0)continue;

        nTQwithVtxProb++;


        if(isMix && (*recoTQ_isPF3)[i]==1){
           mva_mix_sum = (*recoTQ_mvaPFValue3)[i] + (*recoTQ_mvaValue4)[i];
        }else if(isMix && (*recoTQ_isPF3)[i]==0){
           mva_mix_sum = (*recoTQ_mvaPFValue4)[i] + (*recoTQ_mvaValue3)[i];
        }


        if (isPF && reco_type!=1){
          reco_type = 1;
          mva_sum = (*recoTQ_mvaPFValue3)[i] + (*recoTQ_mvaPFValue4)[i];
          best_cand = i;
        }else if(isPF && reco_type==1 && ((*recoTQ_mvaPFValue3)[i] + (*recoTQ_mvaPFValue4)[i])>mva_sum){
          reco_type = 1;
          mva_sum = (*recoTQ_mvaPFValue3)[i] + (*recoTQ_mvaPFValue4)[i];
          best_cand = i;
        }else if(isMix && reco_type!=1 && mva_mix_sum>mva_sum){
          reco_type = 0;
          mva_sum = mva_mix_sum;
          best_cand = i;
        }


	
/*	if((*recoTQ_Y2vtxprob)[i]> prob_cand){

	  prob_cand = (*recoTQ_Y2vtxprob)[i];
	  best_cand= i;
	}

*/	

      }
      

      //increase counters
      if(nTQwithAtLeast2mu>0)counter[1]++;
      if(nTQwithAtLeast2muPtEtaID>0)counter[2]++;      
      if(nTQwithAtLeast2muPtEtaIDVtxProb>0)counter[3]++;
      if(nTQwithAtLeast2muPtEtaIDVtxProbMass>0)counter[4]++;
      if(nTQwithAtLeast2muPtEtaIDVtxProbMassPt>0)counter[5]++;

      if(nTQwithAtLeast2el>0)counter[6]++;
      if(nTQwithAtLeast2elOver>0)counter[7]++;
      if(nTQwithAtLeast2elOverPtEtaID>0)counter[8]++;
      if(nTQwithAtLeast2elOverPtEtaIDLp>0)counter[9]++;
      if(nTQwithAtLeast2elOverPtEtaIDLpVtxProb>0)counter[10]++;
      if(nTQwithAtLeast2elOverPtEtaIDLpVtxProbMass>0)counter[11]++;
      if(nTQwithDeltaR>0)counter[12]++;
      if(nTQwithVtxProb>0)counter[13]++;
      
      //fillign reduced tree with candidate infos
      if(best_cand<999){

	e_pt1=(*recoTQ_isPF3)[best_cand]==1?  (*recoTQ_pt3)[best_cand] : (*recoTQ_pt3mode)[best_cand]; 
	e_pt2=(*recoTQ_isPF4)[best_cand]==1?  (*recoTQ_pt4)[best_cand] : (*recoTQ_pt4mode)[best_cand];
	e_eta1=(*recoTQ_eta3)[best_cand];
	e_eta2=(*recoTQ_eta4)[best_cand];
	e_phi1=(*recoTQ_phi3)[best_cand];
	e_phi2=(*recoTQ_phi4)[best_cand];
	e_isPF1=(*recoTQ_isPF3)[best_cand];
	e_isPF2=(*recoTQ_isPF4)[best_cand];
        e_mvaValue1=(*recoTQ_mvaValue3)[best_cand];
        e_mvaPFValue1=(*recoTQ_mvaPFValue3)[best_cand];
        e_mvaValue2=(*recoTQ_mvaValue4)[best_cand];
        e_mvaPFValue2=(*recoTQ_mvaPFValue4)[best_cand];


	m_pt1=(*recoTQ_pt1)[best_cand];
	m_pt2=(*recoTQ_pt2)[best_cand];
	m_eta1=(*recoTQ_eta1)[best_cand];
	m_eta2=(*recoTQ_eta2)[best_cand];
	m_phi1=(*recoTQ_phi1)[best_cand];
	m_phi2=(*recoTQ_phi2)[best_cand];

	Ym_vtxprob=(*recoTQ_Y1vtxprob)[best_cand];
	Ym_mass=(*recoTQ_Y1mass)[best_cand]; 
	Ym_pt=(*recoTQ_Y1pt)[best_cand]; 
	Ym_eta=(*recoTQ_Y1eta)[best_cand]; 

	Ye_vtxprob=(*recoTQ_Y2vtxprob)[best_cand];
	Ye_mass=(*recoTQ_Y2mass)[best_cand]; 
	Ye_pt=(*recoTQ_Y2pt)[best_cand]; 
	Ye_eta=(*recoTQ_Y2eta)[best_cand]; 

	TQ_vtxprob=(*recoTQ_vtxprob)[best_cand]; 
	TQ_mass=(*recoTQ_mass)[best_cand]; 
	TQ_mass_tilde=(*recoTQ_mass)[best_cand]-(*recoTQ_Y1mass)[best_cand]+9.46; 
	TQ_pt=(*recoTQ_pt)[best_cand]; 
	TQ_eta=(*recoTQ_eta)[best_cand];
        mass_Err= (*recoTQ_massErr)[best_cand]; 
        x_sec = xsec;
        puw2018 = puw_2018;
     
	if(nvtx>=0 && nvtx<=100)nvtxw2018 = hnvtxw_2018->GetBinContent(nvtx+1);//nvtxw_2018;
        //nvtxw2018 =0.;
        n_vtx = nvtx;

	tree_red.Fill();
      }
 }

   //printing results
   std::cout<<" tot: "<<tot<<std::endl;
   std::cout<<" trigger: "<<trigger<<std::endl;
   std::cout<<" 2mu reco: "<<counter[0]<<std::endl;
   std::cout<<" 2mu reco pt eta: "<<counter[1]<<std::endl;
   std::cout<<" 2mu reco pt eta id: "<<counter[2]<<std::endl;
   std::cout<<" 2mu reco pt eta id vtx: "<<counter[3]<<std::endl;
   std::cout<<" 2mu reco pt eta id vtx mass: "<<counter[4]<<std::endl;
   std::cout<<" 2mu reco pt eta id vtx mass pt: "<<counter[5]<<std::endl;

   std::cout<<" 2e reco: "<<counter[6]<<std::endl;
   std::cout<<" 2e reco no overlap: "<<counter[7]<<std::endl;
   std::cout<<" 2e reco no overlap pt eta id : "<<counter[8]<<std::endl;
   std::cout<<" 2e reco no overlap pt eta id no lp: "<<counter[9]<<std::endl;
   std::cout<<" 2e reco no overlap pt eta id no lp vtx: "<<counter[10]<<std::endl;
   std::cout<<" 2e reco no overlap pt eta id no lp vtx mass(Ye): "<<counter[11]<<std::endl;
   std::cout<<" TQ deltaR: "<<counter[12]<<std::endl;
   std::cout<<" TQ vtx: "<<counter[13]<<std::endl;
      

   //creating efficiency counters
   TH1F* h_counter = new TH1F("h_counter", "",16,0,16);
   TH1F* eff_counter = new TH1F("eff_counter", "",16,0,16);
   TH1F* effrel_counter = new TH1F("effrel_counter", "",16,0,16);
   h_counter->SetBinContent(1,tot);
   h_counter->SetBinContent(2,trigger);
   for(int i=0;i<14;i++) h_counter->SetBinContent(i+3, counter[i]);
   for(int i=0;i<14;i++) {
     double eff= (float)counter[i]/counter[0];
     eff_counter->SetBinContent(i+3, eff);
     eff_counter->SetBinError(i+3, sqrt((eff*(1-eff))/counter[0]));
   }
   eff_counter->SetBinContent(1, 1);
   eff_counter->SetBinError(1, 0);
   eff_counter->SetBinContent(2, (int)trigger/tot);
   eff_counter->SetBinError(1, sqrt(((int)trigger/tot*(1-(int)trigger/tot))/tot));
   
   for(int i=0;i<14;i++) {
     double eff;
     if(i!=0) eff= (float)counter[i]/counter[i-1];
     else eff=(float)counter[i]/trigger;
     double efferr;
     if(i!=0)efferr= sqrt((eff*(1-eff))/counter[i-1]);
     else efferr=0.;
     effrel_counter->SetBinContent(i+3, eff);
     effrel_counter->SetBinError(i+3, efferr);
   }
   
   effrel_counter->SetBinContent(1, 1);
   effrel_counter->SetBinError(1, 0);
   effrel_counter->SetBinContent(2, (int)trigger/tot);
   effrel_counter->SetBinError(1, sqrt(((int)trigger/tot*(1-(int)trigger/tot))/tot));
   

   h_counter->GetXaxis()->SetBinLabel(1 ," Total");
   h_counter->GetXaxis()->SetBinLabel(2 ," Trigger");
   h_counter->GetXaxis()->SetBinLabel(3 ," >= 1 TQ");
   h_counter->GetXaxis()->SetBinLabel(4 ," nDiMu >1");
   h_counter->GetXaxis()->SetBinLabel(5 ,"softID==1");
   h_counter->GetXaxis()->SetBinLabel(6 ,"#mu#mu vtx prob >0.1");
   h_counter->GetXaxis()->SetBinLabel(7 ,"#mu#mu mass> 7 GeV");
   h_counter->GetXaxis()->SetBinLabel(8 ,"#mu#mu p_{T} > 12 GeV");
   h_counter->GetXaxis()->SetBinLabel(9,"nDiEle>1");
   h_counter->GetXaxis()->SetBinLabel(10,"no overlap");
   h_counter->GetXaxis()->SetBinLabel(11,"ID==1");
   h_counter->GetXaxis()->SetBinLabel(12 ,"no LP-LP");
   h_counter->GetXaxis()->SetBinLabel(13 ,"ee vtx prob >0.1");
   h_counter->GetXaxis()->SetBinLabel(14 ,"ee mass > 4 GeV");
   h_counter->GetXaxis()->SetBinLabel(15 ,"TQ all dR ok");
   h_counter->GetXaxis()->SetBinLabel(16 ,"TQ vtx prob >0.1");

   eff_counter->GetXaxis()->SetBinLabel(1 ," Total");
   eff_counter->GetXaxis()->SetBinLabel(2 ," Trigger");
   eff_counter->GetXaxis()->SetBinLabel(3 ," >= 1 TQ");
   eff_counter->GetXaxis()->SetBinLabel(4 ," nDiMu >1");
   eff_counter->GetXaxis()->SetBinLabel(5 ,"softID==1");
   eff_counter->GetXaxis()->SetBinLabel(6 ,"#mu#mu vtx prob >0.1");
   eff_counter->GetXaxis()->SetBinLabel(7 ,"#mu#mu mass > 7 GeV");
   eff_counter->GetXaxis()->SetBinLabel(8 , "#mu#mu p_{T} >12 GeV");
   eff_counter->GetXaxis()->SetBinLabel(9 ,"nDiEle>0");
   eff_counter->GetXaxis()->SetBinLabel(10,"no overlap");
   eff_counter->GetXaxis()->SetBinLabel(11 ,"ID==1");
   eff_counter->GetXaxis()->SetBinLabel(12 , "no LP-LP");
   eff_counter->GetXaxis()->SetBinLabel(13 ,"ee vtx prob >0.1");
   eff_counter->GetXaxis()->SetBinLabel(14 , "ee mass > 4 GeV");
   eff_counter->GetXaxis()->SetBinLabel(15 , "TQ all dR ok");
   eff_counter->GetXaxis()->SetBinLabel(16 , "TQ vtx prob >0.1");

   effrel_counter->GetXaxis()->SetBinLabel(1 ," Total");
   effrel_counter->GetXaxis()->SetBinLabel(2 ," Trigger");
   effrel_counter->GetXaxis()->SetBinLabel(3 ," nTQ >=1");
   effrel_counter->GetXaxis()->SetBinLabel(4 ," nDiMu >1");
   effrel_counter->GetXaxis()->SetBinLabel(5 ,"softID==1");
   effrel_counter->GetXaxis()->SetBinLabel(6 ,"#mu#mu vtx prob >0.1");
   effrel_counter->GetXaxis()->SetBinLabel(7 ,"#mu#mu m > 7 GeV");
   effrel_counter->GetXaxis()->SetBinLabel(8 ,"#mu#mu p_{T} > 12 GeV");
   effrel_counter->GetXaxis()->SetBinLabel(9,"nDiEle>1");
   effrel_counter->GetXaxis()->SetBinLabel(10,"no overlap");
   effrel_counter->GetXaxis()->SetBinLabel(11,"ID==1");
   effrel_counter->GetXaxis()->SetBinLabel(12,"!LP-LP");
   effrel_counter->GetXaxis()->SetBinLabel(13, "ee mass > 4 GeV");
   effrel_counter->GetXaxis()->SetBinLabel(14 ,"ee vtx prob >0.1");
   effrel_counter->GetXaxis()->SetBinLabel(15 ,"TQ all dR ok");
   effrel_counter->GetXaxis()->SetBinLabel(16 ,"TQ vtx prob >0.1");




   //saving on file   
   fout->cd();
   tree_red.Write();
   h_counter->Write();
   eff_counter->Write();
   effrel_counter->Write();
   fout->Write();
   fout->Close();


}




