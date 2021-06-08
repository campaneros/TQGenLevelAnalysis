
void makeWeights(){

  /*TFile* fdataA = new TFile("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/ntuple_MuOnia_Run2018A-UL2018_MiniAODv2-v1_WithTrigMatch.root");
  TFile* fdataB = new TFile("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/ntuple_MuOnia_Run2018B-UL2018_MiniAODv2-v1_WithTrigMatch.root");
  TFile* fdataC = new TFile("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/ntuple_MuOnia_Run2018C-UL2018_MiniAODv2-v1_WithTrigMatch.root");
  TFile* fdataD = new TFile("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/ntuple_MuOnia_Run2018D-UL2018_MiniAODv2-v1_WithTrigMatch.root");
  
  TTree* tdataA = (TTree*) fdataA->Get("GenAnalysis/tree");
  TH1F* hdataA = new TH1F("hdataA","",100,0,100);
  tdataA->Draw("nvtx>>hdataA");
  TTree* tdataB = (TTree*) fdataB->Get("GenAnalysis/tree");
  TH1F* hdataB = new TH1F("hdataB","",100,0,100);
  tdataB->Draw("nvtx>>hdataB");
  TTree* tdataC = (TTree*) fdataC->Get("GenAnalysis/tree");
  TH1F* hdataC = new TH1F("hdataC","",100,0,100);
  tdataC->Draw("nvtx>>hdataC");
  TTree* tdataD = (TTree*) fdataD->Get("GenAnalysis/tree");
  TH1F* hdataD = new TH1F("hdataD","",100,0,100);
  tdataD->Draw("nvtx>>hdataD");
  

  hdataA->Add(hdataB);
  hdataA->Add(hdataC);
  hdataA->Add(hdataD);

  TFile* fMC = new TFile("/eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_SPS_inclusive_ggToYYTo2mu2e_2018_PRIVATE_MATTIA_600K_wTrigger.root");
  TTree* tMC = (TTree*) fMC->Get("GenAnalysis/tree");
  TH1F* hMC = new TH1F("hMC","",100,0,100);
  tMC->Draw("nvtx>>hMC");

*/

  TFile* fdataPostSel = new TFile("analysis/fout_mRun2018ABCD_trigger_TQ.root");
  TTree* tdataA = (TTree*) fdataPostSel->Get("tree_red");
  TH1F* hdataA = new TH1F("hdataA","",100,0,100);
  tdataA->Draw("n_vtx>>hdataA");


  TFile* fMC = new TFile("analysis/fout_mSPSwTrigger_TQ.root");
  TTree* tMC = (TTree*) fMC->Get("tree_red");
  TH1F* hMC = new TH1F("hMC","",100,0,100);
  tMC->Draw("n_vtx>>hMC");


  TCanvas* c = new TCanvas("c","",1);
  c->cd();
  hdataA->Sumw2();
  hdataA->Scale(1./hdataA->Integral());
  hdataA->Draw();
  hMC->Sumw2();
  hMC->Scale(1./hMC->Integral());
  hMC->Draw("histsame");
  

  TH1F *nvtxweights = (TH1F*)hdataA->Clone("weights");
  nvtxweights->Divide(hMC);
  nvtxweights->SetTitle("weights");
  nvtxweights->SetName("weights");
  nvtxweights->Scale(1./nvtxweights->Integral());


  
  TH1F* weightedNvtx= (TH1F*)hMC->Clone("weightedNvtx");
  weightedNvtx->Multiply(nvtxweights);
  
  // Rescaling weights in order to preserve same integral of events     
  TH1F* weights = (TH1F*)nvtxweights->Clone("rescaledWeights");
  weights->Scale( hMC->Integral() / weightedNvtx->Integral() );

  //  weights->Scale(1./weights->Integral());
 
  TH1F* hMC2 = new TH1F("hMC2","",100,0,100);
  for(int i=0;i<100;i++)hMC2->SetBinContent(i,hMC->GetBinContent(i)*weights->GetBinContent(i));
  hMC2->SetLineColor(kRed);
  hMC2->Draw("histsame");
  
  std::cout<<hMC->Integral()<<" "<<hMC2->Integral()<<std::endl;

  TFile* fdataout = new TFile("nvtx_weights_2018UL_postsel.root", "RECREATE");
  fdataout->cd();
  hdataA->Write();
  hMC->Write();
  nvtxweights->Write();
  weights->Write();
  fdataout->Write();
  fdataout->Close();

  
}
