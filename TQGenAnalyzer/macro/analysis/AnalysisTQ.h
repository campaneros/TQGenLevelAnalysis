//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 12 10:59:33 2021 by ROOT version 6.14/09
// from TTree tree/tree
// found on file: /eos/cms/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/ntuple_ggXToYYTo2mu2e_m26_PseudoScalar_13TeV_106X_PRIVATE_MATTIA_100K.root
//////////////////////////////////////////////////////////

#ifndef AnalysisTQ_h
#define AnalysisTQ_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class AnalysisTQ {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           sampleID;
   Float_t         xsec;
   Int_t           run;
   Int_t           event;
   Int_t           lumi;
   Int_t           nEle;
   Int_t           nMu;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Int_t           nvtx;
   Float_t         rho;
   Int_t           npu;
   Float_t         puw_2016;
   Float_t         puw_2017;
   Float_t         puw_2018;
   //   Float_t         nvtxw_2018;
   Float_t         puw_ALL;
   Int_t           HLT_Dimuon13_Upsilon_v_2016;
   Int_t           HLT_Dimuon8_Upsilon_Barrel_v_2016;
   Int_t           HLT_Dimuon12_Upsilon_eta1p5_v_2017;
   Int_t           HLT_Dimuon24_Upsilon_noCorrL1_v_2017;
   Int_t           HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017;
   Int_t           HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017;
   Int_t           HLT_Dimuon12_Upsilon_y1p4_v_2018;
   Int_t           HLT_Dimuon24_Upsilon_noCorrL1_v_2018;
   Int_t           HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018;
   Int_t           HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018;
   Float_t         TQ_genMass;
   vector<float>   *genLep_pt;
   vector<float>   *genLep_mass;
   vector<float>   *genLep_eta;
   vector<float>   *genLep_phi;
   vector<int>     *genLep_pdgId;
   vector<float>   *genMom_pt;
   vector<float>   *genMom_mass;
   vector<float>   *genMom_eta;
   vector<float>   *genMom_phi;
   vector<int>     *genMom_pdgId;
   Int_t           nTQReco;
   vector<float>   *recoTQ_pt;
   vector<float>   *recoTQ_eta;
   vector<float>   *recoTQ_phi;
   vector<float>   *recoTQ_mass;
   vector<float>   *recoTQ_massErr;
   vector<float>   *recoTQ_vtxchi2;
   vector<float>   *recoTQ_vtxndof;
   vector<float>   *recoTQ_vtxprob;
   vector<float>   *recoTQ_Y1pt;
   vector<float>   *recoTQ_Y1eta;
   vector<float>   *recoTQ_Y1phi;
   vector<float>   *recoTQ_Y1mass;
   vector<float>   *recoTQ_Y1massErr;
   vector<float>   *recoTQ_Y1vtxchi2;
   vector<float>   *recoTQ_Y1vtxndof;
   vector<float>   *recoTQ_Y1vtxprob;
   vector<float>   *recoTQ_Y2pt;
   vector<float>   *recoTQ_Y2eta;
   vector<float>   *recoTQ_Y2phi;
   vector<float>   *recoTQ_Y2mass;
   vector<float>   *recoTQ_Y2massErr;
   vector<float>   *recoTQ_Y2vtxchi2;
   vector<float>   *recoTQ_Y2vtxndof;
   vector<float>   *recoTQ_Y2vtxprob;
   vector<int>     *recoTQ_leptype1;
   vector<float>   *recoTQ_pt1;
   vector<float>   *recoTQ_eta1;
   vector<float>   *recoTQ_phi1;
   vector<float>   *recoTQ_charge1;
   vector<float>   *recoTQ_mass1;
   vector<int>     *recoTQ_softID1;
   vector<int>     *recoTQ_leptype2;
   vector<float>   *recoTQ_pt2;
   vector<float>   *recoTQ_eta2;
   vector<float>   *recoTQ_phi2;
   vector<float>   *recoTQ_charge2;
   vector<float>   *recoTQ_mass2;
   vector<int>     *recoTQ_softID2;
   vector<int>     *recoTQ_leptype3;
   vector<float>   *recoTQ_pt3;
   vector<float>   *recoTQ_pt3mode;
   vector<float>   *recoTQ_eta3;
   vector<float>   *recoTQ_phi3;
   vector<float>   *recoTQ_charge3;
   vector<float>   *recoTQ_mass3;
   vector<int>     *recoTQ_softID3;
   vector<float>   *recoTQ_mvaValue3;
   vector<float>   *recoTQ_mvaPFValue3;
   vector<int>     *recoTQ_isPF3;
   vector<int>     *recoTQ_isLowPt3;
   vector<int>     *recoTQ_isPFoverlap3;
   vector<int>     *recoTQ_leptype4;
   vector<float>   *recoTQ_pt4;
   vector<float>   *recoTQ_pt4mode;
   vector<float>   *recoTQ_eta4;
   vector<float>   *recoTQ_phi4;
   vector<float>   *recoTQ_charge4;
   vector<float>   *recoTQ_mass4;
   vector<int>     *recoTQ_softID4;
   vector<float>   *recoTQ_mvaValue4;
   vector<float>   *recoTQ_mvaPFValue4;
   vector<int>     *recoTQ_isPF4;
   vector<int>     *recoTQ_isLowPt4;
   vector<int>     *recoTQ_isPFoverlap4;

   // List of branches
   TBranch        *b_sampleID;   //!
   TBranch        *b_xsec;   //!
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_vx;   //!
   TBranch        *b_vy;   //!
   TBranch        *b_vz;   //!
   TBranch        *b_nvtx;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_npu;   //!
   TBranch        *b_puw_2016;   //!
   TBranch        *b_puw_2017;   //!
   TBranch        *b_puw_2018;   //!
   //   TBranch        *b_nvtxw_2018;   //!
   TBranch        *b_puw_ALL;   //!
   TBranch        *b_HLT_Dimuon13_Upsilon_v_2016;   //!
   TBranch        *b_HLT_Dimuon8_Upsilon_Barrel_v_2016;   //!
   TBranch        *b_HLT_Dimuon12_Upsilon_eta1p5_v_2017;   //!
   TBranch        *b_HLT_Dimuon24_Upsilon_noCorrL1_v_2017;   //!
   TBranch        *b_HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017;   //!
   TBranch        *b_HLT_Dimuon12_Upsilon_y1p4_v_2018;   //!
   TBranch        *b_HLT_Dimuon24_Upsilon_noCorrL1_v_2018;   //!
   TBranch        *b_HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018;   //!
   TBranch        *b_TQ_genMass;   //!
   TBranch        *b_genLep_pt;   //!
   TBranch        *b_genLep_mass;   //!
   TBranch        *b_genLep_eta;   //!
   TBranch        *b_genLep_phi;   //!
   TBranch        *b_genLep_pdgId;   //!
   TBranch        *b_genMom_pt;   //!
   TBranch        *b_genMom_mass;   //!
   TBranch        *b_genMom_eta;   //!
   TBranch        *b_genMom_phi;   //!
   TBranch        *b_genMom_pdgId;   //!
   TBranch        *b_nTQReco;   //!
   TBranch        *b_recoTQ_pt;   //!
   TBranch        *b_recoTQ_eta;   //!
   TBranch        *b_recoTQ_phi;   //!
   TBranch        *b_recoTQ_mass;   //!
   TBranch        *b_recoTQ_massErr;   //!
   TBranch        *b_recoTQ_vtxchi2;   //!
   TBranch        *b_recoTQ_vtxndof;   //!
   TBranch        *b_recoTQ_vtxprob;   //!
   TBranch        *b_recoTQ_Y1pt;   //!
   TBranch        *b_recoTQ_Y1eta;   //!
   TBranch        *b_recoTQ_Y1phi;   //!
   TBranch        *b_recoTQ_Y1mass;   //!
   TBranch        *b_recoTQ_Y1massErr;   //!
   TBranch        *b_recoTQ_Y1vtxchi2;   //!
   TBranch        *b_recoTQ_Y1vtxndof;   //!
   TBranch        *b_recoTQ_Y1vtxprob;   //!
   TBranch        *b_recoTQ_Y2pt;   //!
   TBranch        *b_recoTQ_Y2eta;   //!
   TBranch        *b_recoTQ_Y2phi;   //!
   TBranch        *b_recoTQ_Y2mass;   //!
   TBranch        *b_recoTQ_Y2massErr;   //!
   TBranch        *b_recoTQ_Y2vtxchi2;   //!
   TBranch        *b_recoTQ_Y2vtxndof;   //!
   TBranch        *b_recoTQ_Y2vtxprob;   //!
   TBranch        *b_recoTQ_leptype1;   //!
   TBranch        *b_recoTQ_pt1;   //!
   TBranch        *b_recoTQ_eta1;   //!
   TBranch        *b_recoTQ_phi1;   //!
   TBranch        *b_recoTQ_charge1;   //!
   TBranch        *b_recoTQ_mass1;   //!
   TBranch        *b_recoTQ_softID1;   //!
   TBranch        *b_recoTQ_leptype2;   //!
   TBranch        *b_recoTQ_pt2;   //!
   TBranch        *b_recoTQ_eta2;   //!
   TBranch        *b_recoTQ_phi2;   //!
   TBranch        *b_recoTQ_charge2;   //!
   TBranch        *b_recoTQ_mass2;   //!
   TBranch        *b_recoTQ_softID2;   //!
   TBranch        *b_recoTQ_leptype3;   //!
   TBranch        *b_recoTQ_pt3;   //!
   TBranch        *b_recoTQ_pt3mode;   //!
   TBranch        *b_recoTQ_eta3;   //!
   TBranch        *b_recoTQ_phi3;   //!
   TBranch        *b_recoTQ_charge3;   //!
   TBranch        *b_recoTQ_mass3;   //!
   TBranch        *b_recoTQ_softID3;   //!
   TBranch        *b_recoTQ_mvaValue3;   //!
   TBranch        *b_recoTQ_mvaPFValue3;   //!
   TBranch        *b_recoTQ_isPF3;   //!
   TBranch        *b_recoTQ_isLowPt3;   //!
   TBranch        *b_recoTQ_isPFoverlap3;   //!
   TBranch        *b_recoTQ_leptype4;   //!
   TBranch        *b_recoTQ_pt4;   //!
   TBranch        *b_recoTQ_pt4mode;   //!
   TBranch        *b_recoTQ_eta4;   //!
   TBranch        *b_recoTQ_phi4;   //!
   TBranch        *b_recoTQ_charge4;   //!
   TBranch        *b_recoTQ_mass4;   //!
   TBranch        *b_recoTQ_softID4;   //!
   TBranch        *b_recoTQ_mvaValue4;   //!
   TBranch        *b_recoTQ_mvaPFValue4;   //!
   TBranch        *b_recoTQ_isPF4;   //!
   TBranch        *b_recoTQ_isLowPt4;   //!
   TBranch        *b_recoTQ_isPFoverlap4;   //!

   AnalysisTQ(TTree *tree=0);
   virtual ~AnalysisTQ();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual float DeltaR(float eta1,float phi1,float eta2,float phi2);
   virtual void     Loop(std::string mass, int tot, int trigger);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef AnalysisTQ_cxx
AnalysisTQ::AnalysisTQ(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/MuOnia_Run2018B-UL2018_MiniAODv2-v1/crab_MuOnia_Run2018B-UL2018_MiniAODv2-v1/210514_125650/0000/ntuple_tetraquarks_wLowPt_74.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/MuOnia_Run2018B-UL2018_MiniAODv2-v1/crab_MuOn\
ia_Run2018B-UL2018_MiniAODv2-v1/210514_125650/0000/ntuple_tetraquarks_wLowPt_74.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/eos/cms/store/group/phys_egamma/soffi/TQ-DATA/MuOnia_Run2018B-UL2018_MiniAODv2-v1/crab_MuOn\
ia_Run2018B-UL2018_MiniAODv2-v1/210514_125650/0000/ntuple_tetraquarks_wLowPt_74.root:/GenAnalysis");
      dir->GetObject("tree",tree);

   }
   Init(tree);
}

AnalysisTQ::~AnalysisTQ()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t AnalysisTQ::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t AnalysisTQ::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void AnalysisTQ::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   genLep_pt = 0;
   genLep_mass = 0;
   genLep_eta = 0;
   genLep_phi = 0;
   genLep_pdgId = 0;
   genMom_pt = 0;
   genMom_mass = 0;
   genMom_eta = 0;
   genMom_phi = 0;
   genMom_pdgId = 0;
   recoTQ_pt = 0;
   recoTQ_eta = 0;
   recoTQ_phi = 0;
   recoTQ_mass = 0;
   recoTQ_massErr = 0;
   recoTQ_vtxchi2 = 0;
   recoTQ_vtxndof = 0;
   recoTQ_vtxprob = 0;
   recoTQ_Y1pt = 0;
   recoTQ_Y1eta = 0;
   recoTQ_Y1phi = 0;
   recoTQ_Y1mass = 0;
   recoTQ_Y1massErr = 0;
   recoTQ_Y1vtxchi2 = 0;
   recoTQ_Y1vtxndof = 0;
   recoTQ_Y1vtxprob = 0;
   recoTQ_Y2pt = 0;
   recoTQ_Y2eta = 0;
   recoTQ_Y2phi = 0;
   recoTQ_Y2mass = 0;
   recoTQ_Y2massErr = 0;
   recoTQ_Y2vtxchi2 = 0;
   recoTQ_Y2vtxndof = 0;
   recoTQ_Y2vtxprob = 0;
   recoTQ_leptype1 = 0;
   recoTQ_pt1 = 0;
   recoTQ_eta1 = 0;
   recoTQ_phi1 = 0;
   recoTQ_charge1 = 0;
   recoTQ_mass1 = 0;
   recoTQ_softID1 = 0;
   recoTQ_leptype2 = 0;
   recoTQ_pt2 = 0;
   recoTQ_eta2 = 0;
   recoTQ_phi2 = 0;
   recoTQ_charge2 = 0;
   recoTQ_mass2 = 0;
   recoTQ_softID2 = 0;
   recoTQ_leptype3 = 0;
   recoTQ_pt3 = 0;
   recoTQ_pt3mode = 0;
   recoTQ_eta3 = 0;
   recoTQ_phi3 = 0;
   recoTQ_charge3 = 0;
   recoTQ_mass3 = 0;
   recoTQ_softID3 = 0;
   recoTQ_mvaValue3 = 0;
   recoTQ_mvaPFValue3 = 0;
   recoTQ_isPF3 = 0;
   recoTQ_isLowPt3 = 0;
   recoTQ_isPFoverlap3 = 0;
   recoTQ_leptype4 = 0;
   recoTQ_pt4 = 0;
   recoTQ_pt4mode = 0;
   recoTQ_eta4 = 0;
   recoTQ_phi4 = 0;
   recoTQ_charge4 = 0;
   recoTQ_mass4 = 0;
   recoTQ_softID4 = 0;
   recoTQ_mvaValue4 = 0;
   recoTQ_mvaPFValue4 = 0;
   recoTQ_isPF4 = 0;
   recoTQ_isLowPt4 = 0;
   recoTQ_isPFoverlap4 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("sampleID", &sampleID, &b_sampleID);
   fChain->SetBranchAddress("xsec", &xsec, &b_xsec);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("vx", &vx, &b_vx);
   fChain->SetBranchAddress("vy", &vy, &b_vy);
   fChain->SetBranchAddress("vz", &vz, &b_vz);
   fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("npu", &npu, &b_npu);
   fChain->SetBranchAddress("puw_2016", &puw_2016, &b_puw_2016);
   fChain->SetBranchAddress("puw_2017", &puw_2017, &b_puw_2017);
   fChain->SetBranchAddress("puw_2018", &puw_2018, &b_puw_2018);
   //   fChain->SetBranchAddress("nvtxw_2018", &nvtxw_2018, &b_nvtxw_2018);
   fChain->SetBranchAddress("puw_ALL", &puw_ALL, &b_puw_ALL);
   fChain->SetBranchAddress("HLT_Dimuon13_Upsilon_v_2016", &HLT_Dimuon13_Upsilon_v_2016, &b_HLT_Dimuon13_Upsilon_v_2016);
   fChain->SetBranchAddress("HLT_Dimuon8_Upsilon_Barrel_v_2016", &HLT_Dimuon8_Upsilon_Barrel_v_2016, &b_HLT_Dimuon8_Upsilon_Barrel_v_2016);
   fChain->SetBranchAddress("HLT_Dimuon12_Upsilon_eta1p5_v_2017", &HLT_Dimuon12_Upsilon_eta1p5_v_2017, &b_HLT_Dimuon12_Upsilon_eta1p5_v_2017);
   fChain->SetBranchAddress("HLT_Dimuon24_Upsilon_noCorrL1_v_2017", &HLT_Dimuon24_Upsilon_noCorrL1_v_2017, &b_HLT_Dimuon24_Upsilon_noCorrL1_v_2017);
   fChain->SetBranchAddress("HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017", &HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017, &b_HLT_Dimuon24_Upsilon_noCorrL1_v_2017);
   fChain->SetBranchAddress("HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017", &HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017, &b_HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017);
   fChain->SetBranchAddress("HLT_Dimuon12_Upsilon_y1p4_v_2018", &HLT_Dimuon12_Upsilon_y1p4_v_2018, &b_HLT_Dimuon12_Upsilon_y1p4_v_2018);
   fChain->SetBranchAddress("HLT_Dimuon24_Upsilon_noCorrL1_v_2018", &HLT_Dimuon24_Upsilon_noCorrL1_v_2018, &b_HLT_Dimuon24_Upsilon_noCorrL1_v_2018);
   fChain->SetBranchAddress("HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018", &HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018, &b_HLT_Dimuon24_Upsilon_noCorrL1_v_2018);
   fChain->SetBranchAddress("HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018", &HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018, &b_HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018);
   fChain->SetBranchAddress("TQ_genMass", &TQ_genMass, &b_TQ_genMass);
   fChain->SetBranchAddress("genLep_pt", &genLep_pt, &b_genLep_pt);
   fChain->SetBranchAddress("genLep_mass", &genLep_mass, &b_genLep_mass);
   fChain->SetBranchAddress("genLep_eta", &genLep_eta, &b_genLep_eta);
   fChain->SetBranchAddress("genLep_phi", &genLep_phi, &b_genLep_phi);
   fChain->SetBranchAddress("genLep_pdgId", &genLep_pdgId, &b_genLep_pdgId);
   fChain->SetBranchAddress("genMom_pt", &genMom_pt, &b_genMom_pt);
   fChain->SetBranchAddress("genMom_mass", &genMom_mass, &b_genMom_mass);
   fChain->SetBranchAddress("genMom_eta", &genMom_eta, &b_genMom_eta);
   fChain->SetBranchAddress("genMom_phi", &genMom_phi, &b_genMom_phi);
   fChain->SetBranchAddress("genMom_pdgId", &genMom_pdgId, &b_genMom_pdgId);
   fChain->SetBranchAddress("nTQReco", &nTQReco, &b_nTQReco);
   fChain->SetBranchAddress("recoTQ_pt", &recoTQ_pt, &b_recoTQ_pt);
   fChain->SetBranchAddress("recoTQ_eta", &recoTQ_eta, &b_recoTQ_eta);
   fChain->SetBranchAddress("recoTQ_phi", &recoTQ_phi, &b_recoTQ_phi);
   fChain->SetBranchAddress("recoTQ_mass", &recoTQ_mass, &b_recoTQ_mass);
   fChain->SetBranchAddress("recoTQ_massErr", &recoTQ_massErr, &b_recoTQ_massErr);
   fChain->SetBranchAddress("recoTQ_vtxchi2", &recoTQ_vtxchi2, &b_recoTQ_vtxchi2);
   fChain->SetBranchAddress("recoTQ_vtxndof", &recoTQ_vtxndof, &b_recoTQ_vtxndof);
   fChain->SetBranchAddress("recoTQ_vtxprob", &recoTQ_vtxprob, &b_recoTQ_vtxprob);
   fChain->SetBranchAddress("recoTQ_Y1pt", &recoTQ_Y1pt, &b_recoTQ_Y1pt);
   fChain->SetBranchAddress("recoTQ_Y1eta", &recoTQ_Y1eta, &b_recoTQ_Y1eta);
   fChain->SetBranchAddress("recoTQ_Y1phi", &recoTQ_Y1phi, &b_recoTQ_Y1phi);
   fChain->SetBranchAddress("recoTQ_Y1mass", &recoTQ_Y1mass, &b_recoTQ_Y1mass);
   fChain->SetBranchAddress("recoTQ_Y1massErr", &recoTQ_Y1massErr, &b_recoTQ_Y1massErr);
   fChain->SetBranchAddress("recoTQ_Y1vtxchi2", &recoTQ_Y1vtxchi2, &b_recoTQ_Y1vtxchi2);
   fChain->SetBranchAddress("recoTQ_Y1vtxndof", &recoTQ_Y1vtxndof, &b_recoTQ_Y1vtxndof);
   fChain->SetBranchAddress("recoTQ_Y1vtxprob", &recoTQ_Y1vtxprob, &b_recoTQ_Y1vtxprob);
   fChain->SetBranchAddress("recoTQ_Y2pt", &recoTQ_Y2pt, &b_recoTQ_Y2pt);
   fChain->SetBranchAddress("recoTQ_Y2eta", &recoTQ_Y2eta, &b_recoTQ_Y2eta);
   fChain->SetBranchAddress("recoTQ_Y2phi", &recoTQ_Y2phi, &b_recoTQ_Y2phi);
   fChain->SetBranchAddress("recoTQ_Y2mass", &recoTQ_Y2mass, &b_recoTQ_Y2mass);
   fChain->SetBranchAddress("recoTQ_Y2massErr", &recoTQ_Y2massErr, &b_recoTQ_Y2massErr);
   fChain->SetBranchAddress("recoTQ_Y2vtxchi2", &recoTQ_Y2vtxchi2, &b_recoTQ_Y2vtxchi2);
   fChain->SetBranchAddress("recoTQ_Y2vtxndof", &recoTQ_Y2vtxndof, &b_recoTQ_Y2vtxndof);
   fChain->SetBranchAddress("recoTQ_Y2vtxprob", &recoTQ_Y2vtxprob, &b_recoTQ_Y2vtxprob);
   fChain->SetBranchAddress("recoTQ_leptype1", &recoTQ_leptype1, &b_recoTQ_leptype1);
   fChain->SetBranchAddress("recoTQ_pt1", &recoTQ_pt1, &b_recoTQ_pt1);
   fChain->SetBranchAddress("recoTQ_eta1", &recoTQ_eta1, &b_recoTQ_eta1);
   fChain->SetBranchAddress("recoTQ_phi1", &recoTQ_phi1, &b_recoTQ_phi1);
   fChain->SetBranchAddress("recoTQ_charge1", &recoTQ_charge1, &b_recoTQ_charge1);
   fChain->SetBranchAddress("recoTQ_mass1", &recoTQ_mass1, &b_recoTQ_mass1);
   fChain->SetBranchAddress("recoTQ_softID1", &recoTQ_softID1, &b_recoTQ_softID1);
   fChain->SetBranchAddress("recoTQ_leptype2", &recoTQ_leptype2, &b_recoTQ_leptype2);
   fChain->SetBranchAddress("recoTQ_pt2", &recoTQ_pt2, &b_recoTQ_pt2);
   fChain->SetBranchAddress("recoTQ_eta2", &recoTQ_eta2, &b_recoTQ_eta2);
   fChain->SetBranchAddress("recoTQ_phi2", &recoTQ_phi2, &b_recoTQ_phi2);
   fChain->SetBranchAddress("recoTQ_charge2", &recoTQ_charge2, &b_recoTQ_charge2);
   fChain->SetBranchAddress("recoTQ_mass2", &recoTQ_mass2, &b_recoTQ_mass2);
   fChain->SetBranchAddress("recoTQ_softID2", &recoTQ_softID2, &b_recoTQ_softID2);
   fChain->SetBranchAddress("recoTQ_leptype3", &recoTQ_leptype3, &b_recoTQ_leptype3);
   fChain->SetBranchAddress("recoTQ_pt3", &recoTQ_pt3, &b_recoTQ_pt3);
   fChain->SetBranchAddress("recoTQ_pt3mode", &recoTQ_pt3mode, &b_recoTQ_pt3mode);
   fChain->SetBranchAddress("recoTQ_eta3", &recoTQ_eta3, &b_recoTQ_eta3);
   fChain->SetBranchAddress("recoTQ_phi3", &recoTQ_phi3, &b_recoTQ_phi3);
   fChain->SetBranchAddress("recoTQ_charge3", &recoTQ_charge3, &b_recoTQ_charge3);
   fChain->SetBranchAddress("recoTQ_mass3", &recoTQ_mass3, &b_recoTQ_mass3);
   fChain->SetBranchAddress("recoTQ_softID3", &recoTQ_softID3, &b_recoTQ_softID3);
   fChain->SetBranchAddress("recoTQ_mvaValue3", &recoTQ_mvaValue3, &b_recoTQ_mvaValue3);
   fChain->SetBranchAddress("recoTQ_mvaPFValue3", &recoTQ_mvaPFValue3, &b_recoTQ_mvaPFValue3);
   fChain->SetBranchAddress("recoTQ_isPF3", &recoTQ_isPF3, &b_recoTQ_isPF3);
   fChain->SetBranchAddress("recoTQ_isLowPt3", &recoTQ_isLowPt3, &b_recoTQ_isLowPt3);
   fChain->SetBranchAddress("recoTQ_isPFoverlap3", &recoTQ_isPFoverlap3, &b_recoTQ_isPFoverlap3);
   fChain->SetBranchAddress("recoTQ_leptype4", &recoTQ_leptype4, &b_recoTQ_leptype4);
   fChain->SetBranchAddress("recoTQ_pt4", &recoTQ_pt4, &b_recoTQ_pt4);
   fChain->SetBranchAddress("recoTQ_pt4mode", &recoTQ_pt4mode, &b_recoTQ_pt4mode);
   fChain->SetBranchAddress("recoTQ_eta4", &recoTQ_eta4, &b_recoTQ_eta4);
   fChain->SetBranchAddress("recoTQ_phi4", &recoTQ_phi4, &b_recoTQ_phi4);
   fChain->SetBranchAddress("recoTQ_charge4", &recoTQ_charge4, &b_recoTQ_charge4);
   fChain->SetBranchAddress("recoTQ_mass4", &recoTQ_mass4, &b_recoTQ_mass4);
   fChain->SetBranchAddress("recoTQ_softID4", &recoTQ_softID4, &b_recoTQ_softID4);
   fChain->SetBranchAddress("recoTQ_mvaValue4", &recoTQ_mvaValue4, &b_recoTQ_mvaValue4);
   fChain->SetBranchAddress("recoTQ_mvaPFValue4", &recoTQ_mvaPFValue4, &b_recoTQ_mvaPFValue4);
   fChain->SetBranchAddress("recoTQ_isPF4", &recoTQ_isPF4, &b_recoTQ_isPF4);
   fChain->SetBranchAddress("recoTQ_isLowPt4", &recoTQ_isLowPt4, &b_recoTQ_isLowPt4);
   fChain->SetBranchAddress("recoTQ_isPFoverlap4", &recoTQ_isPFoverlap4, &b_recoTQ_isPFoverlap4);
   Notify();
}

Bool_t AnalysisTQ::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void AnalysisTQ::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t AnalysisTQ::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef AnalysisTQ_cxx
