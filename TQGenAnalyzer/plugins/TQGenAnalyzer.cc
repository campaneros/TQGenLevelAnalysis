// -*-C++ -*-
//
// Package:    GenAnalysis/TQGenAnalyzer
// Class:      TQGenAnalyzer
//
/**\class TQGenAnalyzer TQGenAnalyzer.cc GenAnalysis/TQGenAnalyzer/plugins/TQGenAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Livia Soffi
//         Created:  Mon, 01 Mar 2021 11:15:18 GMT
//
//

// system include files
#include <memory>
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/CandAlgos/interface/ModifyObjectValueBase.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Common/interface/Association.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Common/interface/RefToPtr.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaReco/interface/ElectronSeed.h"
#include "DataFormats/EgammaReco/interface/ElectronSeedFwd.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/TrajectorySeed/interface/TrajectorySeed.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/DeDxData.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"


// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "SimDataFormats/Associations/interface/MuonToTrackingParticleAssociator.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include <SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h>

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "RecoEgamma/ElectronIdentification/interface/ElectronIDAlgo.h"

#include "CommonTools/CandAlgos/interface/ModifyObjectValueBase.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/KinematicFitPrimitives/interface/ParticleMass.h"
#include "RecoVertex/KinematicFitPrimitives/interface/MultiTrackKinematicConstraint.h"
#include <RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h>
// #include "RecoVertex/KinematicFitPrimitives/interface/"
#include "RecoVertex/KinematicFit/interface/KinematicConstrainedVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/TwoTrackMassKinematicConstraint.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFit/interface/MassKinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicVertex.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicTree.h"
// root include files
#include "TTree.h"
#include "TCanvas.h"
#include "TLorentzVector.h"

// system include files
#include <memory>
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/CandAlgos/interface/ModifyObjectValueBase.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/CaloRecHit/interface/CaloCluster.h"
#include "DataFormats/CaloRecHit/interface/CaloClusterFwd.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Common/interface/Association.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Common/interface/RefToBase.h"
#include "DataFormats/Common/interface/RefToPtr.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaReco/interface/ElectronSeed.h"
#include "DataFormats/EgammaReco/interface/ElectronSeedFwd.h"
#include "DataFormats/EgammaReco/interface/SuperCluster.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/TrajectorySeed/interface/TrajectorySeed.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/DeDxData.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Common/interface/TriggerResults.h"


#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/EDGetToken.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/Associations/interface/MuonToTrackingParticleAssociator.h"
#include "SimTracker/Records/interface/TrackAssociatorRecord.h"
#include "SimDataFormats/TrackingAnalysis/interface/TrackingVertex.h"

#include "RecoEgamma/ElectronIdentification/interface/ElectronIDAlgo.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"


#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"

#include "RecoVertex/KalmanVertexFit/interface/KalmanVertexFitter.h"
#include "RecoVertex/KinematicFitPrimitives/interface/ParticleMass.h"
#include "RecoVertex/KinematicFitPrimitives/interface/MultiTrackKinematicConstraint.h"
#include <RecoVertex/KinematicFitPrimitives/interface/KinematicParticleFactoryFromTransientTrack.h>
#include "RecoVertex/KinematicFit/interface/KinematicConstrainedVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/TwoTrackMassKinematicConstraint.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleVertexFitter.h"
#include "RecoVertex/KinematicFit/interface/KinematicParticleFitter.h"
#include "RecoVertex/KinematicFit/interface/MassKinematicConstraint.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicVertex.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicParticle.h"
#include "RecoVertex/KinematicFitPrimitives/interface/RefCountedKinematicTree.h"

#include "KinVtxFitter.h"

// root include files
#include "TTree.h"
#include "TLorentzVector.h"



#define MAX_PU_REWEIGHT 100
#define LEP_SIGMA 0.0000001

namespace reco { typedef edm::Ptr<GsfElectron> GsfElectronPtr; }


struct tree_struc_{
  
  int year;
  int sampleID;
  float xsec;
  float massRef;
  int nvtx;
  float rho;
  int npu;
  float puw_2016;
  float puw_2017;
  float puw_2018;
  float puw_ALL;


  float nvtxw_2016;
  float nvtxw_2017;
  float nvtxw_2018;
  float nvtxw_ALL;
  int run;
  int lumi;
  long unsigned int event;
  int nEle;
  int nMu;
  float TQ_genMass;

  //2016 MuOnia
  int HLT_Dimuon13_Upsilon_v_2016;
  int HLT_Dimuon8_Upsilon_Barrel_v_2016;


  //2017 MuOnia
  int HLT_Dimuon12_Upsilon_eta1p5_v_2017;
  int HLT_Dimuon24_Upsilon_noCorrL1_v_2017;
  int HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017;
  int HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017;
  

  //2018 MuOnia
  int HLT_Dimuon0_prescaled_2018;
  int HLT_Dimuon12_Upsilon_y1p4_v_2018;
  int HLT_Dimuon24_Upsilon_noCorrL1_v_2018;
  int HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018;
  int HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018;


  
  std::vector<float>            genLep_pt;
  std::vector<float>            genLep_eta;
  std::vector<float>            genLep_mass;
  std::vector<float>            genLep_phi;
  std::vector<int>            genLep_pdgId;
  std::vector<float>            genMom_pt;
  std::vector<float>            genMom_eta;
  std::vector<float>            genMom_mass;
  std::vector<float>            genMom_phi;
  std::vector<int>            genMom_pdgId;

  int nMediumDimu;
  int nSoftDimu;
  /*
  int nMuReco;
  std::vector<float>            recoMu_pt;
  std::vector<float>            recoMu_eta;
  std::vector<float>            recoMu_mass;
  std::vector<float>            recoMu_phi;
  std::vector<int>              recoMu_charge;
  std::vector<float>            recoMu_dR1;
  std::vector<float>            recoMu_dR2;
  std::vector<int>              recoMu_matchid1;
  std::vector<int>              recoMu_matchid2;
  std::vector<int>              recoMu_looseID;
  std::vector<int>              recoMu_softID;
  //below variables are those applied in softID. Cuts can be seen here:https://cmssdt.cern.ch/lxr/source/DataFormats/MuonReco/src/MuonSelectors.cc?v=CMSSW_10_6_20
  std::vector<int>              recoMu_nTrkLayers;
  std::vector<int>              recoMu_nPixLayers;
  std::vector<int>              recoMu_isHQ;
  std::vector<float>              recoMu_dxy;
  std::vector<float>              recoMu_dz;
  std::vector<int>              recoMu_isTrigMatch;
  std::vector<float>              recoMu_drTrigMatch;


  //dimuon pairs
  int nDimuReco;
  std::vector<float>            recoDimu_vx;
  std::vector<float>            recoDimu_vy;
  std::vector<float>            recoDimu_vz;
  std::vector<float>            recoDimu_vtxchi2;
  std::vector<float>            recoDimu_vtxndof;
  std::vector<float>            recoDimu_vtxprob;
  std::vector<int>            recoDimu_index1;  
  std::vector<float>            recoDimu_pt1;  
  std::vector<float>            recoDimu_eta1;
  std::vector<float>            recoDimu_phi1;
  std::vector<float>            recoDimu_charge1;
  std::vector<float>            recoDimu_mass1;        
  std::vector<int>            recoDimu_softID1;        
  std::vector<int>            recoDimu_index2;  
  std::vector<float>            recoDimu_pt2;  
  std::vector<float>            recoDimu_eta2;
  std::vector<float>            recoDimu_phi2;
  std::vector<float>            recoDimu_charge2;
  std::vector<float>            recoDimu_mass2;        
  std::vector<int>            recoDimu_softID2;        
  std::vector<float>            recoDimu_pt;        
  std::vector<float>            recoDimu_eta;        
  std::vector<float>            recoDimu_phi;        
  std::vector<float>            recoDimu_mass;        
  std::vector<float>            recoDimu_massErr;        
  std::vector<int>              recoDimu_isTrigMatch1;
  std::vector<float>              recoDimu_drTrigMatch1;
  std::vector<int>              recoDimu_isTrigMatch2;
  std::vector<float>              recoDimu_drTrigMatch2;


  //electrons
  int nEleReco;
  int nPFEleReco;
  int nLowPtEleReco;
  std::vector<float>            recoEle_pt;
  std::vector<float>            recoEle_eta;
  std::vector<float>            recoEle_mass;
  std::vector<float>            recoEle_phi;
  std::vector<int>              recoEle_charge;
  std::vector<float>              recoEle_vx;
  std::vector<float>              recoEle_vy;
  std::vector<float>              recoEle_vz;
  std::vector<float>            recoEle_dR1;
  std::vector<float>            recoEle_dR2;
  std::vector<int>              recoEle_matchid1;
  std::vector<int>              recoEle_matchid2;
  std::vector<float>recoEle_E_ecal_preReg;
  std::vector<float>recoEle_E_ecal_postReg;
  std::vector<float>recoEle_E_ecaltrk_preReg;
  std::vector<float>recoEle_E_ecaltrk_postReg;
  std::vector<float>recoEle_rawE;
  std::vector<float>recoEle_corrEcalE;
  std::vector<float>recoEle_gsfTrkChi2;
  std::vector<float>recoEle_passConvVeto;
  std::vector<float>recoEle_isPF;
  std::vector<float>recoEle_mvaPFValue;
  std::vector<float>recoEle_isPFoverlap;
  std::vector<float>recoEle_isLowPt;
  std::vector<float>recoEle_mvaValue;
  std::vector<float>            recoEle_ptmode;
  std::vector<float>            recoEle_etamode;
  std::vector<float>            recoEle_phimode;

  std::vector<float>            recoEle_p;

  //dielectron pairs
  int nDieleReco;
  std::vector<float>            recoDiele_vx;
  std::vector<float>            recoDiele_vy;
  std::vector<float>            recoDiele_vz;
  std::vector<float>            recoDiele_vtxchi2;
  std::vector<float>            recoDiele_vtxndof;
  std::vector<float>            recoDiele_vtxprob;
  std::vector<int>            recoDiele_index1;  
  std::vector<int>            recoDiele_index2;  
  std::vector<float>            recoDiele_pt1;  
  std::vector<float>            recoDiele_eta1;
  std::vector<float>            recoDiele_phi1;
  std::vector<float>            recoDiele_charge1;
  std::vector<float>            recoDiele_mass1;        
  std::vector<float>            recoDiele_mvaValue1;        
  std::vector<float>            recoDiele_mvaPFValue1;        
  std::vector<int>            recoDiele_isPF1;        
  std::vector<int>            recoDiele_isLowPt1;        
  std::vector<int>            recoDiele_isPFoverlap1;        
  std::vector<float>            recoDiele_pt2;  
  std::vector<float>            recoDiele_eta2;
  std::vector<float>            recoDiele_phi2;
  std::vector<float>            recoDiele_charge2;
  std::vector<float>            recoDiele_mass2;        
  std::vector<float>            recoDiele_mvaValue2;        
  std::vector<float>            recoDiele_mvaPFValue2;        
  std::vector<int>            recoDiele_isPF2;        
  std::vector<int>            recoDiele_isLowPt2;        
  std::vector<int>            recoDiele_isPFoverlap2;        
  std::vector<float>            recoDiele_pt;        
  std::vector<float>            recoDiele_eta;        
  std::vector<float>            recoDiele_phi;        
  std::vector<float>            recoDiele_mass;        
  std::vector<float>            recoDiele_massErr;        
  std::vector<float>            recoDiele_pt1mode;
  std::vector<float>            recoDiele_eta1mode;
  std::vector<float>            recoDiele_phi1mode;
  std::vector<float>            recoDiele_pt2mode;
  std::vector<float>            recoDiele_eta2mode;
  std::vector<float>            recoDiele_phi2mode;
  */
 
  //TQ
  int nTQReco;
  std::vector<float>            recoTQ_pt;
  std::vector<float>            recoTQ_eta;
  std::vector<float>            recoTQ_phi;
  std::vector<float>            recoTQ_mass;
  std::vector<float>            recoTQ_massErr;
  std::vector<float>            recoTQ_vtxchi2;
  std::vector<float>            recoTQ_vtxndof;
  std::vector<float>            recoTQ_vtxprob;


  std::vector<float>            recoTQ_Y1pt;
  std::vector<float>            recoTQ_Y1eta;
  std::vector<float>            recoTQ_Y1phi;
  std::vector<float>            recoTQ_Y1mass;
  std::vector<float>            recoTQ_Y1massErr;
  std::vector<float>            recoTQ_Y1vtxchi2;
  std::vector<float>            recoTQ_Y1vtxndof;
  std::vector<float>            recoTQ_Y1vtxprob;

  std::vector<float>            recoTQ_Y2pt;
  std::vector<float>            recoTQ_Y2eta;
  std::vector<float>            recoTQ_Y2phi;
  std::vector<float>            recoTQ_Y2mass;
  std::vector<float>            recoTQ_Y2massErr;
  std::vector<float>            recoTQ_Y2vtxchi2;
  std::vector<float>            recoTQ_Y2vtxndof;
  std::vector<float>            recoTQ_Y2vtxprob;


  std::vector<int>            recoTQ_leptype1;
  std::vector<float>            recoTQ_pt1;
  std::vector<float>            recoTQ_eta1;
  std::vector<float>            recoTQ_phi1;
  std::vector<float>            recoTQ_charge1;
  std::vector<float>            recoTQ_mass1;
  std::vector<int>            recoTQ_softID1;
  std::vector<int>            recoTQ_mediumID1;

  std::vector<int>            recoTQ_leptype2;
  std::vector<float>            recoTQ_pt2;
  std::vector<float>            recoTQ_eta2;
  std::vector<float>            recoTQ_phi2;
  std::vector<float>            recoTQ_charge2;
  std::vector<float>            recoTQ_mass2;
  std::vector<int>            recoTQ_softID2;
  std::vector<int>            recoTQ_mediumID2;

  std::vector<int>              recoTQ_isTrigMatch1;                                                                                                        
  std::vector<float>              recoTQ_drTrigMatch1;                                                                                                      
  std::vector<int>              recoTQ_isTrigMatch2;                                                                                                        
  std::vector<float>              recoTQ_drTrigMatch2;

  std::vector<int>            recoTQ_leptype3;
  std::vector<float>            recoTQ_pt3;
  std::vector<float>            recoTQ_pt3mode;
  std::vector<float>            recoTQ_eta3;
  std::vector<float>            recoTQ_phi3;
  std::vector<float>            recoTQ_charge3;
  std::vector<float>            recoTQ_mass3;
  std::vector<int>            recoTQ_softID3;
  std::vector<int>            recoTQ_mediumID3;
  std::vector<float>            recoTQ_mvaValue3;
  std::vector<float>            recoTQ_mvaPFValue3;
  std::vector<int>            recoTQ_isPF3;
  std::vector<int>            recoTQ_isLowPt3;
  std::vector<int>            recoTQ_isPFoverlap3;


  std::vector<int>            recoTQ_leptype4;
  std::vector<float>            recoTQ_pt4;
  std::vector<float>            recoTQ_pt4mode;
  std::vector<float>            recoTQ_eta4;
  std::vector<float>            recoTQ_phi4;
  std::vector<float>            recoTQ_charge4;
  std::vector<float>            recoTQ_mass4;
  std::vector<int>            recoTQ_softID4;
  std::vector<int>            recoTQ_mediumID4;
  std::vector<float>            recoTQ_mvaValue4;
  std::vector<float>            recoTQ_mvaPFValue4;
  std::vector<int>            recoTQ_isPF4;
  std::vector<int>            recoTQ_isLowPt4;
  std::vector<int>            recoTQ_isPFoverlap4;




  float vx;
  float vy;
  float vz;

};


class TQGenAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TQGenAnalyzer(const edm::ParameterSet&);
      ~TQGenAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;
  void initTreeStructure();
  void clearVectors(); 

  void SetPuWeights(int year, double* puw_array);
  float GetPUWeight(int npu,int year);

  void SetNVTXWeights(int year, double* puw_array);
  float GetNVTXWeight(int npu,int year);

  // ---------- member data -------------------- //
  edm::Service<TFileService> fs;
  edm::EDGetTokenT<GenEventInfoProduct>genInfoToken_;
  
  const edm::EDGetTokenT< edm::View<reco::GenParticle> > prunedGenParticles_; // MINIAOD
  edm::Handle< edm::View<reco::GenParticle> > genParticlesH_;

  const edm::EDGetTokenT< std::vector<pat::Muon> > patMuons_; // MINIAOD
  edm::Handle< std::vector<pat::Muon> > patMuonsH_;

  const edm::EDGetTokenT<pat::ElectronCollection> lowpt_src_;
  const edm::EDGetTokenT<pat::ElectronCollection> pf_src_;
  
  const edm::EDGetTokenT< std::vector<reco::Vertex> > vtx_; // MINIAOD
  edm::Handle< std::vector<reco::Vertex>> vtxH_;
  
  const edm::EDGetTokenT< double > rho_; // MINIAOD
  edm::Handle< double> rhoH_;
  
  const edm::EDGetTokenT<edm::View<PileupSummaryInfo> > PileUp_;
  edm:: Handle<edm::View< PileupSummaryInfo> > PileUpH_;
  
  const edm::EDGetTokenT< edm::TriggerResults> triggerBits_;
  edm::Handle<edm::TriggerResults> triggerBitsH_;
  
  const edm::EDGetTokenT<std::vector<pat::TriggerObjectStandAlone>> triggerObjects_;
  edm::Handle<std::vector<pat::TriggerObjectStandAlone>> triggerObjectsH_;
  std::vector<std::string> HLTPaths_;
   const double dr_cleaning_;
   const double dz_cleaning_;

   //setup mva ID for PF electrons

   const edm::EDGetTokenT< edm::ValueMap<float> > mvaValuePF_; 
   edm::Handle< edm::ValueMap<float> > mvaValuePFH_;


  
  int year_;
  int sampleIndex_;
  float xsec_;    // pb
  float massRef_;
   double puweights2016_[100];
   double puweights2017_[100];
   double puweights2018_[100];
   double puweightsALL_[100];

   double nvtxweights2016_[100];
   double nvtxweights2017_[100];
   double nvtxweights2018_[100];
   double nvtxweightsALL_[100];

   // setup tree;
  TTree* tree;
  tree_struc_ tree_;

  TH1F* h_counter;

};


 TQGenAnalyzer::TQGenAnalyzer(const edm::ParameterSet& iConfig)
   :
   prunedGenParticles_(consumes< edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("prunedGenParticles"))),
   genParticlesH_(),
   patMuons_(consumes< std::vector<pat::Muon> >(iConfig.getParameter<edm::InputTag>("patMuons"))),
   patMuonsH_(),
   lowpt_src_{ consumes<pat::ElectronCollection>( iConfig.getParameter<edm::InputTag>("lowptSrc") )},
   pf_src_{ consumes<pat::ElectronCollection>( iConfig.getParameter<edm::InputTag>("pfSrc") )},
   vtx_(consumes<std::vector<reco::Vertex>>(iConfig.getParameter<edm::InputTag>("vtx"))),
   vtxH_(),
   rho_(consumes<double>(iConfig.getParameter<edm::InputTag>("rho"))),
   rhoH_(),
   PileUp_(consumes<edm::View<PileupSummaryInfo> >(iConfig.getParameter<edm::InputTag> ("PileUp"))),
   PileUpH_(),
   triggerBits_( consumes<edm::TriggerResults>( iConfig.getParameter<edm::InputTag>( "bits" ))),
   triggerBitsH_(),
   triggerObjects_(consumes<std::vector<pat::TriggerObjectStandAlone>>(iConfig.getParameter<edm::InputTag>("objects"))),
   triggerObjectsH_(),
   HLTPaths_(iConfig.getParameter<std::vector<std::string>>("HLTPaths")),
   dr_cleaning_(iConfig.getParameter<double>("drForCleaning")),
   dz_cleaning_(iConfig.getParameter<double>("dzForCleaning")),
   mvaValuePF_(consumes< edm::ValueMap<float> >(iConfig.getParameter<edm::InputTag>("mvaValuePF"))),
   mvaValuePFH_()


 {


   // Event stuff
   year_   = iConfig.getUntrackedParameter<int>("year",0);
   sampleIndex_   = iConfig.getUntrackedParameter<int>("sampleIndex",0);
   xsec_          = iConfig.getUntrackedParameter<double>("sampleXsec",1.);
   massRef_          = iConfig.getUntrackedParameter<double>("massRef",1.);

 }


 TQGenAnalyzer::~TQGenAnalyzer()
 {

    // do anything here that needs to be done at desctruction time
    // (e.g. close files, deallocate resources etc.)

 }


 //
 // member functions
 //

 // ------------ method called for each event  ------------
 void
 TQGenAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
 {

     iEvent.getByToken(prunedGenParticles_, genParticlesH_);
     iEvent.getByToken(patMuons_,patMuonsH_);
     edm::Handle<pat::ElectronCollection> lowpt;
     iEvent.getByToken(lowpt_src_, lowpt);
     edm::Handle<pat::ElectronCollection> pf;
     iEvent.getByToken(pf_src_, pf);
     iEvent.getByToken(vtx_,vtxH_);
     iEvent.getByToken(rho_,rhoH_);
     iEvent.getByToken(PileUp_,PileUpH_);
     iEvent.getByToken( triggerBits_, triggerBitsH_ );
     iEvent.getByToken(mvaValuePF_, mvaValuePFH_); 

     edm::ESHandle<MagneticField> bFieldHandle;
     iSetup.get<IdealMagneticFieldRecord>().get(bFieldHandle);
     edm::ESHandle<TransientTrackBuilder> theB ;
     iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",theB);


     using namespace edm;

     //2016 MuOnia                                                                                                                                               
     int HLT_Dimuon13_Upsilon_v_2016=0;
     int HLT_Dimuon8_Upsilon_Barrel_v_2016=0;

     //2017 MuOnia                                                                                                                                               
     int HLT_Dimuon12_Upsilon_eta1p5_v_2017=0;
     int HLT_Dimuon24_Upsilon_noCorrL1_v_2017=0;
     int HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017=0;
     int HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017=0;

     //2018 MuOnia
     int     HLT_Dimuon0_1_2018=0;
     int     HLT_Dimuon0_2_2018=0;
     int     HLT_Dimuon0_3_2018=0;
     int     HLT_Dimuon0_4_2018=0;
     int     HLT_Dimuon0_5_2018=0;

     int HLT_Dimuon0_prescaled_2018=0;
     int HLT_Dimuon12_Upsilon_y1p4_v_2018=0;
     int HLT_Dimuon24_Upsilon_noCorrL1_v_2018=0;
     int HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018=0;
     int HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018=0;


     std::vector<float>genLep_pt;
     std::vector<float>genLep_mass;
     std::vector<float>genLep_eta;
     std::vector<float>genLep_phi;
     std::vector<int>genLep_pdgId;

     std::vector<float>genMom_pt;
     std::vector<float>genMom_mass;
     std::vector<float>genMom_eta;
     std::vector<float>genMom_phi;
     std::vector<int>genMom_pdgId;

     std::vector<float>recoMu_pt;
     std::vector<float>recoMu_mass;
     std::vector<float>recoMu_eta;
     std::vector<float>recoMu_phi;
     std::vector<float>recoMu_dR1;
     std::vector<float>recoMu_dR2;
     std::vector<int>              recoMu_charge;
     std::vector<int>              recoMu_matchid1;
     std::vector<int>              recoMu_matchid2;
     std::vector<int>              recoMu_looseID;
     std::vector<int>              recoMu_softID;
     std::vector<int>              recoMu_nTrkLayers;
     std::vector<int>              recoMu_nPixLayers;
     std::vector<int>              recoMu_isHQ;
     std::vector<float>              recoMu_dxy;
     std::vector<float>              recoMu_dz;
     std::vector<int>              recoMu_isTrigMatch;
     std::vector<float>              recoMu_drTrigMatch;

     std::vector<float>            recoDimu_vx;
     std::vector<float>            recoDimu_vy;
     std::vector<float>            recoDimu_vz;
     std::vector<float>            recoDimu_vtxchi2;
     std::vector<float>            recoDimu_vtxndof;
     std::vector<float>            recoDimu_vtxprob;

     std::vector<int>            recoDimu_index1;  
     std::vector<int>            recoDimu_index2;  
     std::vector<float>            recoDimu_pt1;  
     std::vector<float>            recoDimu_eta1;
     std::vector<float>            recoDimu_phi1;
     std::vector<float>            recoDimu_charge1;
     std::vector<float>            recoDimu_mass1;        
     std::vector<float>            recoDimu_softID1;        
     std::vector<float>            recoDimu_mediumID1;        
     std::vector<float>            recoDimu_pt2;  
     std::vector<float>            recoDimu_eta2;
     std::vector<float>            recoDimu_phi2;
     std::vector<float>            recoDimu_charge2;
     std::vector<float>            recoDimu_mass2;        
     std::vector<float>            recoDimu_softID2;        
     std::vector<float>            recoDimu_mediumID2;        
     std::vector<float>            recoDimu_pt;        
     std::vector<float>            recoDimu_eta;        
     std::vector<float>            recoDimu_phi;        
     std::vector<float>            recoDimu_mass;        
     std::vector<float>            recoDimu_massErr;        
     std::vector<int>              recoDimu_isTrigMatch1;
     std::vector<float>              recoDimu_drTrigMatch1;
     std::vector<int>              recoDimu_isTrigMatch2;
     std::vector<float>              recoDimu_drTrigMatch2;
  

     std::vector<float>recoEle_pt;
     std::vector<float>recoEle_mass;
     std::vector<float>recoEle_eta;
     std::vector<float>recoEle_phi;
     std::vector<float>recoEle_dR1;
     std::vector<float>recoEle_dR2;
     std::vector<int>              recoEle_charge;
     std::vector<float>              recoEle_vx;
     std::vector<float>              recoEle_vy;
     std::vector<float>              recoEle_vz;
     std::vector<int>              recoEle_matchid1;
     std::vector<int>              recoEle_matchid2;
     std::vector<float>recoEle_E_ecal_preReg;
     std::vector<float>recoEle_E_ecal_postReg;
     std::vector<float>recoEle_E_ecaltrk_preReg;
     std::vector<float>recoEle_E_ecaltrk_postReg;
     std::vector<float>recoEle_rawE;
     std::vector<float>recoEle_corrEcalE;
     std::vector<float>recoEle_gsfTrkChi2;
     std::vector<float>recoEle_passConvVeto;
     std::vector<float>recoEle_isPF;
     std::vector<float>recoEle_mvaPFValue;
     std::vector<float>recoEle_mvaValue;
     std::vector<float>recoEle_isPFoverlap;
     std::vector<float>recoEle_isLowPt;
     
     std::vector<float>recoEle_ptmode;
     std::vector<float>recoEle_etamode;
     std::vector<float>recoEle_phimode;

     std::vector<float>recoEle_p;

     std::vector<float>            recoDiele_vx;
     std::vector<float>            recoDiele_vy;
     std::vector<float>            recoDiele_vz;
     std::vector<float>            recoDiele_vtxchi2;
     std::vector<float>            recoDiele_vtxndof;
     std::vector<float>            recoDiele_vtxprob;
     std::vector<int>            recoDiele_index1;  
     std::vector<int>            recoDiele_index2;  
     std::vector<float>            recoDiele_pt1;  
     std::vector<float>            recoDiele_eta1;
     std::vector<float>            recoDiele_phi1;
     std::vector<float>            recoDiele_charge1;
     std::vector<float>            recoDiele_mass1;        
     std::vector<float>            recoDiele_pt2;  
     std::vector<float>            recoDiele_eta2;
     std::vector<float>            recoDiele_phi2;
     std::vector<float>            recoDiele_charge2;
     std::vector<float>            recoDiele_mass2;        
     std::vector<float>            recoDiele_mvaValue1;        
     std::vector<float>            recoDiele_mvaPFValue1;        

     std::vector<float>            recoDiele_mvaValue2;        
     std::vector<float>            recoDiele_mvaPFValue2;        

     std::vector<int>            recoDiele_isPF1;        
     std::vector<int>            recoDiele_isLowPt1;        
     std::vector<int>            recoDiele_isPFoverlap1;        
     std::vector<int>            recoDiele_isPF2;        
     std::vector<int>            recoDiele_isLowPt2;        
     std::vector<int>            recoDiele_isPFoverlap2;        
     std::vector<float>            recoDiele_pt;        
     std::vector<float>            recoDiele_eta;        
     std::vector<float>            recoDiele_phi;        
     std::vector<float>            recoDiele_mass;        
     std::vector<float>            recoDiele_massErr;        

     std::vector<float>recoDiele_pt1mode;
     std::vector<float>recoDiele_eta1mode;
     std::vector<float>recoDiele_phi1mode;
     std::vector<float>recoDiele_pt2mode;
     std::vector<float>recoDiele_eta2mode;
     std::vector<float>recoDiele_phi2mode;

  //TQ
  std::vector<float>            recoTQ_pt;
  std::vector<float>            recoTQ_eta;
  std::vector<float>            recoTQ_phi;
  std::vector<float>            recoTQ_mass;
  std::vector<float>            recoTQ_massErr;
  std::vector<float>            recoTQ_vtxchi2;
  std::vector<float>            recoTQ_vtxndof;
  std::vector<float>            recoTQ_vtxprob;

  std::vector<float>            recoTQ_Y1pt;
  std::vector<float>            recoTQ_Y1eta;
  std::vector<float>            recoTQ_Y1phi;
  std::vector<float>            recoTQ_Y1mass;
  std::vector<float>            recoTQ_Y1massErr;
  std::vector<float>            recoTQ_Y1vtxchi2;
  std::vector<float>            recoTQ_Y1vtxndof;
  std::vector<float>            recoTQ_Y1vtxprob;

  std::vector<float>            recoTQ_Y2pt;
  std::vector<float>            recoTQ_Y2eta;
  std::vector<float>            recoTQ_Y2phi;
  std::vector<float>            recoTQ_Y2mass;
  std::vector<float>            recoTQ_Y2massErr;
  std::vector<float>            recoTQ_Y2vtxchi2;
  std::vector<float>            recoTQ_Y2vtxndof;
  std::vector<float>            recoTQ_Y2vtxprob;


  std::vector<int>            recoTQ_leptype1;
  std::vector<float>            recoTQ_pt1;
  std::vector<float>            recoTQ_eta1;
  std::vector<float>            recoTQ_phi1;
  std::vector<float>            recoTQ_charge1;
  std::vector<float>            recoTQ_mass1;
  std::vector<int>            recoTQ_softID1;
  std::vector<int>            recoTQ_mediumID1;


  std::vector<int>            recoTQ_leptype2;
  std::vector<float>            recoTQ_pt2;
  std::vector<float>            recoTQ_eta2;
  std::vector<float>            recoTQ_phi2;
  std::vector<float>            recoTQ_charge2;
  std::vector<float>            recoTQ_mass2;
  std::vector<int>            recoTQ_softID2;
  std::vector<int>            recoTQ_mediumID2;


  std::vector<int>              recoTQ_isTrigMatch1;                                                                                                        
  std::vector<float>              recoTQ_drTrigMatch1;                                                                                                      
  std::vector<int>              recoTQ_isTrigMatch2;                                                                                                        
  std::vector<float>              recoTQ_drTrigMatch2;


  std::vector<int>            recoTQ_leptype3;
  std::vector<float>            recoTQ_pt3;
  std::vector<float>            recoTQ_pt3mode;
  std::vector<float>            recoTQ_eta3;
  std::vector<float>            recoTQ_phi3;
  std::vector<float>            recoTQ_charge3;
  std::vector<float>            recoTQ_mass3;
  std::vector<int>            recoTQ_softID3;
  std::vector<int>            recoTQ_mediumID3;
  std::vector<float>            recoTQ_mvaValue3;
  std::vector<float>            recoTQ_mvaPFValue3;
  std::vector<int>            recoTQ_isPF3;
  std::vector<int>            recoTQ_isLowPt3;
  std::vector<int>            recoTQ_isPFoverlap3;


  std::vector<int>            recoTQ_leptype4;
  std::vector<float>            recoTQ_pt4;
  std::vector<float>            recoTQ_pt4mode;
  std::vector<float>            recoTQ_eta4;
  std::vector<float>            recoTQ_phi4;
  std::vector<float>            recoTQ_charge4;
  std::vector<float>            recoTQ_mass4;
  std::vector<int>            recoTQ_softID4;
  std::vector<int>            recoTQ_mediumID4;
  std::vector<float>            recoTQ_mvaValue4;
  std::vector<float>            recoTQ_mvaPFValue4;
  std::vector<int>            recoTQ_isPF4;
  std::vector<int>            recoTQ_isLowPt4;
  std::vector<int>            recoTQ_isPFoverlap4;


     // --- sample info (0:signal, <0 background, >0 data)
     int sampleID = sampleIndex_;
     int year=year_;
     float xsec=1.;
     float massRef=massRef_;//3.09 if JPsi 9.46 is Upsilon
     if(sampleID<=0) xsec=xsec_;

     // ---------- TRIGGER -------------------- //
     /*
      -----------------------------------------
      year dataset     unprescaled
      -----------------------------------------
      2016 MuOnia HLT_Dimuon13_Upsilon_v_2016=0;
      2016 MuOnia HLT_Dimuon8_Upsilon_Barrel_v_2016=0;

     2017 MuOnia   HLT_Dimuon12_Upsilon_eta1p5_v_2017=0;
     2017 MuOnia   HLT_Dimuon24_Upsilon_noCorrL1_v_2017=0;
     2017 MuOnia   HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017=0;
     2017 MuOnia   HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017=0;
      
      2018 MuOnia  HLT_Dimuon12_Upsilon_y1p4_v_2018;
      2018 MuOnia  HLT_Dimuon24_Upsilon_noCorrL1_v_2018;
      2018 MuOnia  HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018;
      2018 MuOnia  HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018;
      

                   prescaled
       2018 MuOnia HLT_Dimuon0_Upsilon_L1_4p5NoOS_v || HLT_Dimuon0_Upsilon_L1_4p5_v ||HLT_Dimuon0_Upsilon_L1_4p5er2p0M_v || HLT_Dimuon0_Upsilon_L1_4p5er2p0_v || HLT_Dimuon0_Upsilon_L1_5M_v

      */

     
     const edm::TriggerNames &triggerNames = iEvent.triggerNames( *triggerBitsH_ );

     //  vector<std::string> const &names = triggerNames.triggerNames();  
     
     for( unsigned index = 0; index < triggerNames.size(); ++index ) {

       //2016
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon13_Upsilon") )HLT_Dimuon13_Upsilon_v_2016=triggerBitsH_->accept( index ); 
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon8_Upsilon_Barrel") )HLT_Dimuon8_Upsilon_Barrel_v_2016=triggerBitsH_->accept( index ); 


       //2017
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon12_Upsilon_eta1p5") )HLT_Dimuon12_Upsilon_eta1p5_v_2017=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon24_Upsilon_noCorrL1") )HLT_Dimuon24_Upsilon_noCorrL1_v_2017=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon") )HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon") )HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017=triggerBitsH_->accept( index );

       //2018
       //       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("") )triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon12_Upsilon_y1p4") )HLT_Dimuon12_Upsilon_y1p4_v_2018=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon24_Upsilon_noCorrL1") )HLT_Dimuon24_Upsilon_noCorrL1_v_2018=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon") )HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon") )HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018=triggerBitsH_->accept( index );


       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon0_Upsilon_L1_4p5NoOS_v")) HLT_Dimuon0_1_2018=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon0_Upsilon_L1_4p5_v")) HLT_Dimuon0_2_2018=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon0_Upsilon_L1_4p5er2p0M_v")) HLT_Dimuon0_3_2018=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon0_Upsilon_L1_4p5er2p0_v")) HLT_Dimuon0_4_2018=triggerBitsH_->accept( index );
       if( (TString::Format((triggerNames.triggerName( index )).c_str())).Contains("HLT_Dimuon0_Upsilon_L1_5M_v")) HLT_Dimuon0_5_2018=triggerBitsH_->accept( index );


 

       
       
     }

     HLT_Dimuon0_prescaled_2018 = HLT_Dimuon0_1_2018 || HLT_Dimuon0_2_2018 || HLT_Dimuon0_3_2018 || HLT_Dimuon0_4_2018 || HLT_Dimuon0_5_2018 ;


       
     // ---------- GENERAL INFOS -------------------- //
     unsigned long int event = iEvent.id().event();   
     int run                 = iEvent.id().run();
     int lumi                = iEvent.luminosityBlock();
     int nEle=0;
     int nMu=0;
     int nMuReco=0;
     int nEleReco=0;
     int nPFEleReco=0;
     int nLowPtEleReco=0;
     int nDimuReco=0;
     int nMediumDimu=0;
     int nSoftDimu=0;
     int nDieleReco=0;
     int nTQReco=0;

     TLorentzVector* lep1=new TLorentzVector();
     TLorentzVector* lep2=new TLorentzVector();
     TLorentzVector* lep3=new TLorentzVector();
     TLorentzVector* lep0=new TLorentzVector();
  
     float vx;
     float vy;
     float vz;


     //     std::cout<<"-----------------------------------------------------"<<std::endl;
	
     
     float puw_2016 = 1.;
     float puw_2017 = 1.;
     float puw_2018 = 1.;
     float puw_ALL = 1.;
     float nvtxw_2016 = 1.;
     float nvtxw_2017 = 1.;
     float nvtxw_2018 = 1.;
     float nvtxw_ALL = 1.;
     int npu      = -1;
  
     // ---------- GEN LEVEL INFO -------------------- //
     if(sampleID <=0){
     for (const auto & genpar_iter : *genParticlesH_){ // loop over genparticles
       //       std::cout<<"status: "<<genpar_iter.status()<<" pdgid: "<<genpar_iter.pdgId()<<" pt: "<<genpar_iter.pt()<<" mass: "<<genpar_iter.mass()<<" eta: "<<genpar_iter.eta()<<" phi: "<<genpar_iter.phi()<<" mom pdgId: "<<genpar_iter.mother(0)->pdgId()<<" mom mass: "<<genpar_iter.mother(0)->mass()<<std::endl;
       if(abs(genpar_iter.pdgId())!=13 && abs(genpar_iter.pdgId())!=11)continue;


       if(genpar_iter.mother(0)->pdgId()<20 || genpar_iter.mother(0)->pdgId()>50) continue;
    
       

    
       genLep_pt.push_back(genpar_iter.pt());
       genLep_mass.push_back(genpar_iter.mass());
       genLep_eta.push_back(genpar_iter.eta());
       genLep_phi.push_back(genpar_iter.phi());
       genLep_pdgId.push_back(genpar_iter.pdgId());
    

       genMom_pt.push_back(genpar_iter.mother(0)->pt());
       genMom_mass.push_back(genpar_iter.mother(0)->mass());
       genMom_eta.push_back(genpar_iter.mother(0)->eta());
       genMom_phi.push_back(genpar_iter.mother(0)->phi());
       genMom_pdgId.push_back(genpar_iter.mother(0)->pdgId());
    
       if(abs(genpar_iter.pdgId())==11)nEle++;
       if(abs(genpar_iter.pdgId())==13)nMu++;
    
     }


       npu = 0;
       for( unsigned int PVI = 0; PVI < PileUpH_->size(); ++PVI ) {
 	Int_t pu_bunchcrossing = PileUpH_->ptrAt( PVI )->getBunchCrossing();
 	if( pu_bunchcrossing == 0 ) {
 	  npu = PileUpH_->ptrAt( PVI )->getTrueNumInteractions();
 	}
       }

       puw_2016 = GetPUWeight(npu,2016);
       puw_2017 = GetPUWeight(npu,2017);
       puw_2018 = GetPUWeight(npu,2018);
       puw_ALL = GetPUWeight(npu,0);

     }


     // ---------- VERTICES -------------------- //
     const reco::Vertex & pv = vtxH_->front(); 
     vx=pv.x();
     vy=pv.y();
     vz=pv.z();
     int nvtx=vtxH_->size();

     if(sampleID <=0){
       nvtxw_2016 = GetNVTXWeight(nvtx,2016);
       nvtxw_2017 = GetNVTXWeight(nvtx,2017);
       nvtxw_2018 = GetNVTXWeight(nvtx,2018);
       nvtxw_ALL = GetNVTXWeight(nvtx,0);
     }
     //saving rho
     float rho = *(rhoH_.product());



     // ---------- MUONS -------------------- //
     for (const auto & mu_iter : *patMuonsH_){
       nMuReco++;

       float dR=999.;
       float dRMin1=999.;
       float dRMin2=999.;
       int recomatchid1=999;
       int recomatchid2=999;
       int recolooseID=999;
       int recosoftID=999;     
       int recontrklayers=999;
       int reconpixlayers=999;
       int recoishq=999;
       float recodxy=999.;
       float recodz=999.;


       float recopt;
       float recoeta;
       float recophi;
       float recomass;
       int recocharge=999;


       float eta=mu_iter.eta();
       float phi=mu_iter.phi();
    
       //store kinematics
       recopt=mu_iter.pt();
       recoeta=mu_iter.eta();
       recophi=mu_iter.phi();
       recomass=mu_iter.mass();
       recocharge=mu_iter.charge();
    

       //store ID variables
       recolooseID=muon::isLooseMuon(mu_iter);
       recosoftID=muon::isSoftMuon(mu_iter, pv);
       //recontrklayers=mu_iter.innerTrack()->hitPattern().trackerLayersWithMeasurement();
       //reconpixlayers=mu_iter.innerTrack()->hitPattern().pixelLayersWithMeasurement();
       //recoishq=1;//mu_iter.innerTrack()->quality(reco::Track::highPurity); 
       //      recodxy=mu_iter.innerTrack()->dxy(pv.position());
       //recodz=mu_iter.innerTrack()->dz(pv.position());




       //compute dR matching w/ each gen muon      
       for(unsigned int i=0;i<genLep_pdgId.size();i++){
 	if(abs(genLep_pdgId[i])!=13)continue;
	if(genLep_pdgId[i]==13 && recocharge==1)continue;
	if(genLep_pdgId[i]==-13 && recocharge==-1)continue;
 	dR= deltaR(eta,phi,genLep_eta[i],genLep_phi[i]);
 	if(dR<dRMin1){
 	  dRMin1=dR;
 	  recomatchid1=i;
 	}
       }
    
    
       for(unsigned int i=0;i<genLep_pdgId.size();i++){
 	if(abs(genLep_pdgId[i])!=13)continue;
	if(genLep_pdgId[i]==13 && recocharge==1)continue;
	if(genLep_pdgId[i]==-13 && recocharge==-1)continue;

 	if(i==(unsigned int)recomatchid1)continue;
 	dR= deltaR(eta,phi,genLep_eta[i],genLep_phi[i]);
 	if(dR<dRMin2){
 	  dRMin2=dR;
 	  recomatchid2=i;
 	}
       }
    

    
       recoMu_pt.push_back(recopt);
       recoMu_mass.push_back(recomass);
       recoMu_eta.push_back(recoeta);
       recoMu_phi.push_back(recophi);
       recoMu_charge.push_back(recocharge);

       recoMu_dR1.push_back(dRMin1);
       recoMu_dR2.push_back(dRMin2);
       recoMu_matchid1.push_back(recomatchid1);
       recoMu_matchid2.push_back(recomatchid2);
       recoMu_looseID.push_back(recolooseID);
       recoMu_softID.push_back(recosoftID);
       recoMu_nTrkLayers.push_back(recontrklayers);
       recoMu_nPixLayers.push_back(reconpixlayers);
       recoMu_isHQ.push_back(recoishq);
       recoMu_dxy.push_back(recodxy);
       recoMu_dz.push_back(recodz);


       //check if this muon fires a trigger
       std::vector<int> frs(HLTPaths_.size(),0); //path fires for each reco muon
       std::vector<float> temp_matched_to(HLTPaths_.size(),1000.);
       std::vector<float> temp_DR(HLTPaths_.size(),1000.);
       std::vector<float> temp_DPT(HLTPaths_.size(),1000.);
       
       int whichTrigFired=999;
       float drMin=1;
       int ipath=-1;
       if(mu_iter.triggerObjectMatches().size()==0)continue;
	 
       for (const std::string path: HLTPaths_){
	 ipath++;
	 char cstr[ (path+"*").size() + 1];
	 strcpy( cstr, (path+"*").c_str() );
	 std::vector<float> temp_dr(mu_iter.triggerObjectMatches().size(),1000.);
	 std::vector<float> temp_dpt(mu_iter.triggerObjectMatches().size(),1000.);
	 std::vector<float> temp_pt(mu_iter.triggerObjectMatches().size(),1000.);

	   for(size_t i=0; i<mu_iter.triggerObjectMatches().size();i++){

	     if(mu_iter.triggerObjectMatch(i)!=0 && mu_iter.triggerObjectMatch(i)->hasPathName(cstr,true,true)){
	       frs[ipath]=1;
	       float dr=deltaR(mu_iter.triggerObjectMatch(i)->eta(),mu_iter.triggerObjectMatch(i)->phi(),mu_iter.eta(),mu_iter.phi());
	       float dpt=(mu_iter.triggerObjectMatch(i)->pt()-mu_iter.pt())/mu_iter.triggerObjectMatch(i)->pt();
	       temp_dr[i]=dr;
	       temp_dpt[i]=dpt;
	       temp_pt[i]=mu_iter.triggerObjectMatch(i)->pt(); 
	     }
	   }
	   temp_DR[ipath]=*min_element(temp_dr.begin(),temp_dr.end());
	   int position=std::min_element(temp_dr.begin(),temp_dr.end()) - temp_dr.begin();
	   temp_DPT[ipath]=temp_dpt[position];
	   temp_matched_to[ipath]=temp_pt[position];
	   
	   if(temp_DR[ipath]<drMin){
	     whichTrigFired = ipath;
	     drMin= temp_DR[ipath];
	   }
		  
       }       
       recoMu_isTrigMatch.push_back(whichTrigFired);
       recoMu_drTrigMatch.push_back(drMin);


     }


     // ---------- DIMUONS -------------------- //			
     size_t imu1=-1;
     size_t imu2=-1;
     std::vector<reco::TransientTrack> recoDimu_TT1;
     std::vector<reco::TransientTrack> recoDimu_TT2;

     for (const pat::Muon & mu1 : *patMuonsH_){
       imu1++;
       if(mu1.pt()<2.5)continue;
       if(abs(mu1.eta())>2.5)continue;


       //check if this muon fires a trigger

       std::vector<float> temp_matched_to(HLTPaths_.size(),1000.);
       std::vector<float> temp_DR(HLTPaths_.size(),1000.);
       std::vector<float> temp_DPT(HLTPaths_.size(),1000.);
       
       int whichTrigFired1=999;
       float drMin1=1;
       int ipath=-1;
       if(mu1.triggerObjectMatches().size()==0)continue;
	 
       for (const std::string path: HLTPaths_){
	 ipath++;
	 char cstr[ (path+"*").size() + 1];
	 strcpy( cstr, (path+"*").c_str() );
	 std::vector<float> temp_dr(mu1.triggerObjectMatches().size(),1000.);
	 std::vector<float> temp_dpt(mu1.triggerObjectMatches().size(),1000.);
	 std::vector<float> temp_pt(mu1.triggerObjectMatches().size(),1000.);

	   for(size_t i=0; i<mu1.triggerObjectMatches().size();i++){

	     if(mu1.triggerObjectMatch(i)!=0 && mu1.triggerObjectMatch(i)->hasPathName(cstr,true,true)){
	       float dr=deltaR(mu1.triggerObjectMatch(i)->eta(),mu1.triggerObjectMatch(i)->phi(),mu1.eta(),mu1.phi());
	       float dpt=(mu1.triggerObjectMatch(i)->pt()-mu1.pt())/mu1.triggerObjectMatch(i)->pt();
	       temp_dr[i]=dr;
	       temp_dpt[i]=dpt;
	       temp_pt[i]=mu1.triggerObjectMatch(i)->pt(); 
	     }
	   }
	   temp_DR[ipath]=*min_element(temp_dr.begin(),temp_dr.end());
	   int position=std::min_element(temp_dr.begin(),temp_dr.end()) - temp_dr.begin();
	   temp_DPT[ipath]=temp_dpt[position];
	   temp_matched_to[ipath]=temp_pt[position];
	   
	   if(temp_DR[ipath]<drMin1){
	     whichTrigFired1 = ipath;
	     drMin1= temp_DR[ipath];
	   }
		  
       }       

       imu2=-1;
       // for (pat::MuonCollection::const_iterator mu2 = patMuonsH_.begin(); mu2 != patMuonsH_.end(); ++mu2){
       for (const pat::Muon & mu2 : *patMuonsH_){
	 imu2++;
	 if(imu2<=imu1)continue;
	 if(mu2.pt()<2.5)continue;
	 if(abs(mu2.eta())>2.5)continue;
	 if(mu1.charge()*mu2.charge()>0)continue;
    	 		 
	 //run kinematic fit
	
	 reco::TransientTrack mu1TT = theB->build(mu1.bestTrack());
	 reco::TransientTrack mu2TT = theB->build(mu2.bestTrack());
	 
	 float chi = 0.;
	 float ndf = 0.;
	 double muon_mass = 0.1056583;
	 float muon_sigma = 0.0000001;
	 
	
	 KinematicParticleFactoryFromTransientTrack pFactory;
	 std::vector<RefCountedKinematicParticle> allParticles;
	 allParticles.push_back(pFactory.particle (mu1TT,muon_mass,chi,ndf,muon_sigma));
	 allParticles.push_back(pFactory.particle (mu2TT,muon_mass,chi,ndf,muon_sigma));
	 KinematicParticleVertexFitter fitter;
	

	KinVtxFitter fitter2(
			   {mu1TT,mu2TT},
			   {muon_mass,muon_mass},
			   {muon_sigma,muon_sigma} //some small sigma for the lepton mass
		      );
	
	if(!fitter2.success()) continue; 
	if(fitter2.prob()<0.05)continue;

       //       std::cout<<"ind1: "<<imu1<<" ind2: "<<imu2<<" pt1: "<<mu1.pt()<<" pt2: "<<mu2.pt()<<" eta1: "<<mu1.eta()<<" eta2: "<<mu2.eta()<<" phi1: "<<mu1.phi()<<" phi2: "<<mu2.phi()<<" ch1: "<<mu1.charge()<<" ch2: "<<mu2.charge()<<std::endl;	 
       

	//check if this muon fires a trigger
	std::vector<float> temp_matched_to(HLTPaths_.size(),1000.);
	std::vector<float> temp_DR(HLTPaths_.size(),1000.);
	std::vector<float> temp_DPT(HLTPaths_.size(),1000.);
       
	int whichTrigFired2=999;
	float drMin2=1;
	int ipath=-1;
	if(mu2.triggerObjectMatches().size()==0)continue;
	
	for (const std::string path: HLTPaths_){
	  ipath++;
	  char cstr[ (path+"*").size() + 1];
	  strcpy( cstr, (path+"*").c_str() );
	  std::vector<float> temp_dr(mu2.triggerObjectMatches().size(),1000.);
	  std::vector<float> temp_dpt(mu2.triggerObjectMatches().size(),1000.);
	  std::vector<float> temp_pt(mu2.triggerObjectMatches().size(),1000.);
	  
	  for(size_t i=0; i<mu2.triggerObjectMatches().size();i++){

	    if(mu2.triggerObjectMatch(i)!=0 && mu2.triggerObjectMatch(i)->hasPathName(cstr,true,true)){
	      float dr=deltaR(mu2.triggerObjectMatch(i)->eta(),mu2.triggerObjectMatch(i)->phi(),mu2.eta(),mu2.phi());
	      float dpt=(mu2.triggerObjectMatch(i)->pt()-mu2.pt())/mu2.triggerObjectMatch(i)->pt();
	      temp_dr[i]=dr;
	      temp_dpt[i]=dpt;
	      temp_pt[i]=mu2.triggerObjectMatch(i)->pt(); 
	    }
	  }
	  temp_DR[ipath]=*min_element(temp_dr.begin(),temp_dr.end());
	  int position=std::min_element(temp_dr.begin(),temp_dr.end()) - temp_dr.begin();
	  temp_DPT[ipath]=temp_dpt[position];
	  temp_matched_to[ipath]=temp_pt[position];
	  
	  if(temp_DR[ipath]<drMin2){
	    whichTrigFired2 = ipath;
	    drMin2= temp_DR[ipath];
	  }
		  
       }       
       recoDimu_isTrigMatch1.push_back(whichTrigFired1);
       recoDimu_drTrigMatch1.push_back(drMin1);
       recoDimu_isTrigMatch2.push_back(whichTrigFired2);
       recoDimu_drTrigMatch2.push_back(drMin2);



	recoDimu_TT1.push_back(mu1TT);
	recoDimu_TT2.push_back(mu2TT);
	
	recoDimu_pt1.push_back(mu1.pt());
	recoDimu_index1.push_back(imu1);
	recoDimu_index2.push_back(imu2);
	recoDimu_eta1.push_back(mu1.eta());
	recoDimu_phi1.push_back(mu1.phi());
	recoDimu_charge1.push_back(mu1.charge());
	recoDimu_mass1.push_back(mu1.mass());
	recoDimu_softID1.push_back(muon::isSoftMuon(mu1, pv));
	recoDimu_mediumID1.push_back(muon::isMediumMuon(mu1));
	
	
	recoDimu_pt2.push_back(mu2.pt());
	recoDimu_eta2.push_back(mu2.eta());
	recoDimu_phi2.push_back(mu2.phi());
	recoDimu_charge2.push_back(mu2.charge());
	recoDimu_mass2.push_back(mu2.mass());
	recoDimu_softID2.push_back(muon::isSoftMuon(mu2, pv));
	recoDimu_mediumID2.push_back(muon::isMediumMuon(mu2));
	
	recoDimu_vx.push_back(fitter2.fitted_vtx().x());
	recoDimu_vy.push_back(fitter2.fitted_vtx().y());
	recoDimu_vz.push_back(fitter2.fitted_vtx().z());
	recoDimu_vtxchi2.push_back(fitter2.chi2());
	recoDimu_vtxndof.push_back(fitter2.dof());
	recoDimu_vtxprob.push_back(fitter2.prob());
	auto fit_p4 = fitter2.fitted_p4();
	recoDimu_pt.push_back(fit_p4.pt());        
	recoDimu_eta.push_back(fit_p4.eta());        
	recoDimu_phi.push_back(fit_p4.phi());        
	
	recoDimu_mass.push_back(fitter2.fitted_candidate().mass());        
	recoDimu_massErr.push_back(sqrt(fitter2.fitted_candidate().kinematicParametersError().matrix()(6,6)));        
       
	
	nDimuReco++;

	if(muon::isMediumMuon(mu2) && muon::isMediumMuon(mu1)&&fitter2.prob()>0.05)nMediumDimu++;
	if(muon::isSoftMuon(mu1, pv)&&muon::isSoftMuon(mu2, pv)&&fitter2.prob()>0.05)nSoftDimu++;


    }
 }


     // ---------- PF ELECTRONS -------------------- //
    size_t ipfele=-1;
    for(auto ele : *pf) {
      ipfele++;
      nEleReco++;
      nPFEleReco++;
      float dR=999.;
      float dRMin1=999.;
      float dRMin2=999.;
      int recomatchid1=999;
      int recomatchid2=999;

      float recopt=ele.pt();
      float recoeta=ele.eta();
      float recophi=ele.phi();
      float recomass=ele.mass();
      int recocharge=ele.charge();

      float recovx=ele.vx();
      float recovy=ele.vy();
      float recovz=ele.vz();

      
      float recorawe=ele.superCluster()->rawEnergy();
      float recocorrecale=ele.correctedEcalEnergy();
      float recotrkchi2=ele.gsfTrack()->normalizedChi2();
      int recoconvveto=ele.passConversionVeto();
      


      float recoptmode=ele.gsfTrack()->ptMode();
      float recoetamode=ele.gsfTrack()->etaMode();
      float recophimode=ele.gsfTrack()->phiMode();


      float recop=ele.p();

      
      for(unsigned int i=0;i<genLep_pdgId.size();i++){
	if(abs(genLep_pdgId[i])!=11)continue;
	
	if(genLep_pdgId[i]==11 && recocharge==1)continue;
	if(genLep_pdgId[i]==-11 && recocharge==-1)continue;
	
	dR= deltaR(recoeta,recophi,genLep_eta[i],genLep_phi[i]);
	if(dR<dRMin1){
	  dRMin1=dR;
	  recomatchid1=i;
	}
      }
      
      
      for(unsigned int i=0;i<genLep_pdgId.size();i++){
	if(abs(genLep_pdgId[i])!=11)continue;
	if(genLep_pdgId[i]==11 && recocharge==1)continue;
	if(genLep_pdgId[i]==-11 && recocharge==-1)continue;


	if(i==(unsigned int)recomatchid1)continue;
	dR= deltaR(recoeta,recophi,genLep_eta[i],genLep_phi[i]);
	if(dR<dRMin2){
	  dRMin2=dR;
	  recomatchid2=i;
	}
      }
      
      int recoispf=1;
      int recoislowpt=0;
      int recoispfoverlap=0;


      
      float mvaPF_value = -999.;
      edm::Ref<pat::ElectronCollection> ref(pf,ipfele);
      mvaPF_value = float((*mvaValuePFH_)[ref]);
      
      float mva_value = -999.;

      recoEle_pt.push_back(recopt);
      recoEle_mass.push_back(recomass);
      recoEle_eta.push_back(recoeta);
      recoEle_phi.push_back(recophi);
      recoEle_charge.push_back(recocharge);


      recoEle_ptmode.push_back(recoptmode);
      recoEle_etamode.push_back(recoetamode);
      recoEle_phimode.push_back(recophimode);


      recoEle_p.push_back(recop);

      recoEle_vx.push_back(recovx);
      recoEle_vy.push_back(recovy);
      recoEle_vz.push_back(recovz);

      recoEle_dR1.push_back(dRMin1);
      recoEle_dR2.push_back(dRMin2);
      recoEle_matchid1.push_back(recomatchid1);
      recoEle_matchid2.push_back(recomatchid2);

      recoEle_rawE.push_back(recorawe);
      recoEle_corrEcalE.push_back(recocorrecale);
      recoEle_gsfTrkChi2.push_back(recotrkchi2);
      recoEle_passConvVeto.push_back(recoconvveto);

      recoEle_isPF.push_back(recoispf);
      recoEle_isLowPt.push_back(recoislowpt);
      recoEle_isPFoverlap.push_back(recoispfoverlap);

      recoEle_mvaPFValue.push_back(mvaPF_value);
      recoEle_mvaValue.push_back(mva_value);

      //      std::cout<<" index: "<<ipfele<<" ch: "<<recoEle_charge[ipfele]<<" pt: "<<recoEle_pt[ipfele]<<" isPF: "<<recoEle_isPF[ipfele]<<" isLP: "<<recoEle_isLowPt[ipfele]<<" overlap: "<<recoEle_isPFoverlap[ipfele]<<std::endl;
      
      float recopre_ecal     = -999.;
      float recopre_ecaltrk  = -999.;
      float recopost_ecal    = -999.;
      float recopost_ecaltrk = -999.;
      
      recopre_ecal = ele.correctedEcalEnergy();
      recopre_ecaltrk = ele.energy();
      recopost_ecal = ele.correctedEcalEnergy();
      recopost_ecaltrk = ele.energy();
      
      recoEle_E_ecal_preReg.push_back(recopre_ecal);
      recoEle_E_ecal_postReg.push_back(recopost_ecal);
      recoEle_E_ecaltrk_preReg.push_back(recopre_ecaltrk);
      recoEle_E_ecaltrk_postReg.push_back(recopost_ecaltrk);

    }
    
    
    unsigned int nPFEle=recoEle_pt.size();

     // ---------- LOW PT ELECTRONS -------------------- //
     if(lowpt.isValid()){
       
       for(auto ele : *lowpt) {

	float dR=999.;
	float dRMin1=999.;
	float dRMin2=999.;
	int recomatchid1=999;
	int recomatchid2=999;

	float recopt=ele.pt();
	float recoeta=ele.eta();
	float recophi=ele.phi();
	float recomass=ele.mass();
	int recocharge=ele.charge();

	float recoptmode=ele.gsfTrack()->ptMode();
	float recoetamode=ele.gsfTrack()->etaMode();
	float recophimode=ele.gsfTrack()->phiMode();


	float recop=ele.p();


	float recovx=ele.vx();
	float recovy=ele.vy();
	float recovz=ele.vz();
	
	int recoispfoverlap=0;

	// ---------- REMOVE OVERLAP WITH PF -------------------- //
	   
	bool clean_out = false;
	for(unsigned int iEle=0; iEle<nPFEle; ++iEle) {
	  
	  clean_out |= (
			fabs(recoEle_vz[iEle] - recovz) < dz_cleaning_ &&
			reco::deltaR(recoeta, recophi, recoEle_eta[iEle], recoEle_phi[iEle]) < dr_cleaning_   );
	  
	  //	  std::cout<<"dz: "<<fabs(recoEle_vz[iEle] - recovz)<<" lp eta: "<<recoeta<<" reco eta: "<<recoEle_eta[iEle]<<" lp phi: "<<recophi<<" reco phi: "<<recoEle_phi[iEle]<<" clean? "<<clean_out<<std::endl;
	}
	
            
      int recoispf=0;
      int recoislowpt=1;
      if(clean_out) recoispfoverlap=1;
      else recoispfoverlap=0;
 
      if(recoispfoverlap==0) nEleReco++;
      if(recoispfoverlap==0) nLowPtEleReco++;
      
      float recorawe=ele.superCluster()->rawEnergy();
      float recocorrecale=ele.correctedEcalEnergy();
      float recotrkchi2=ele.gsfTrack()->normalizedChi2();
      int recoconvveto=ele.passConversionVeto();
      

      
      for(unsigned int i=0;i<genLep_pdgId.size();i++){
	if(abs(genLep_pdgId[i])!=11)continue;
	if(genLep_pdgId[i]==11 && recocharge==1)continue;
	if(genLep_pdgId[i]==-11 && recocharge==-1)continue;

	dR= deltaR(recoeta,recophi,genLep_eta[i],genLep_phi[i]);
	if(dR<dRMin1){
	  dRMin1=dR;
	  recomatchid1=i;
	}
      }
      
      
      for(unsigned int i=0;i<genLep_pdgId.size();i++){
	if(abs(genLep_pdgId[i])!=11)continue;
	if(genLep_pdgId[i]==11 && recocharge==1)continue;
	if(genLep_pdgId[i]==-11 && recocharge==-1)continue;

	if(i==(unsigned int)recomatchid1)continue;
	dR= deltaR(recoeta,recophi,genLep_eta[i],genLep_phi[i]);
	if(dR<dRMin2){
	  dRMin2=dR;
	  recomatchid2=i;
	}
      }



      
      float mvaPF_value = -999.;      
      float mva_value = -999.;
      mva_value=ele.isElectronIDAvailable("ID") ? ele.electronID("ID") : -100. ;
      
      
      recoEle_pt.push_back(recopt);
      recoEle_mass.push_back(recomass);
      recoEle_eta.push_back(recoeta);
      recoEle_phi.push_back(recophi);
      recoEle_charge.push_back(recocharge);

      recoEle_ptmode.push_back(recoptmode);
      recoEle_etamode.push_back(recoetamode);
      recoEle_phimode.push_back(recophimode);

      recoEle_p.push_back(recop);


      recoEle_vx.push_back(recovx);
      recoEle_vy.push_back(recovy);
      recoEle_vz.push_back(recovz);


      recoEle_dR1.push_back(dRMin1);
      recoEle_dR2.push_back(dRMin2);
      recoEle_matchid1.push_back(recomatchid1);
      recoEle_matchid2.push_back(recomatchid2);

      recoEle_rawE.push_back(recorawe);
      recoEle_corrEcalE.push_back(recocorrecale);
      recoEle_gsfTrkChi2.push_back(recotrkchi2);
      recoEle_passConvVeto.push_back(recoconvveto);

      recoEle_isPF.push_back(recoispf);
      recoEle_isLowPt.push_back(recoislowpt);
      recoEle_isPFoverlap.push_back(recoispfoverlap);

      recoEle_mvaPFValue.push_back(mvaPF_value);

      recoEle_mvaValue.push_back(mva_value);


      // ---------- REGRESSION: TO BE APPLIED -------------------- //
    float recopre_ecal     = -999.;
    float recopre_ecaltrk  = -999.;
    float recopost_ecal    = -999.;
    float recopost_ecaltrk = -999.;


    recopre_ecal = ele.correctedEcalEnergy();
    recopre_ecaltrk = ele.energy();
    recopost_ecal = ele.correctedEcalEnergy();
    recopost_ecaltrk = ele.energy();

    recoEle_E_ecal_preReg.push_back(recopre_ecal);
    recoEle_E_ecal_postReg.push_back(recopost_ecal);
    recoEle_E_ecaltrk_preReg.push_back(recopre_ecaltrk);
    recoEle_E_ecaltrk_postReg.push_back(recopost_ecaltrk);

       }
 

    }




     // ----------------- DIELECTRON PF-PF -------------------- //
     size_t iel1=-1;
     size_t iel2=-1;
     std::vector<reco::TransientTrack> recoDiele_TT1;
     std::vector<reco::TransientTrack> recoDiele_TT2;

     for (const pat::Electron & el1 : *pf){
       iel1++;
       if(el1.pt()<2.)continue;
       if(abs(el1.eta())>2.5)continue;

       iel2=-1;

       for (const pat::Electron & el2 : *pf){
	 iel2++;
	 if(iel2<=iel1)continue;
	 if(el2.pt()<2.)continue;
	 if(abs(el2.eta())>2.5)continue;
	 //	 if(el1.charge()*el2.charge()>0)continue;
    

	 
	

	
       //run kinematic fit
	
       reco::TransientTrack el1TT = (*theB).build( el1.gsfTrack() );
       reco::TransientTrack el2TT = (*theB).build( el2.gsfTrack() );

	float chi = 0.;
	float ndf = 0.;
	double elon_mass = 0.005056583;
	float elon_sigma = 0.0000001;

	KinVtxFitter fitter(
			   {el1TT,el2TT},
			   {elon_mass,elon_mass},
			   {elon_sigma,elon_sigma} //some small sigma for the lepton mass
		      );
	
       if(!fitter.success()) continue; 
       //       std::cout<<" prob: "<<fitter.prob()<<std::endl;

       recoDiele_TT1.push_back(el1TT);
       recoDiele_TT2.push_back(el2TT);
       
       recoDiele_vx.push_back(fitter.fitted_vtx().x());
       recoDiele_vy.push_back(fitter.fitted_vtx().y());
       recoDiele_vz.push_back(fitter.fitted_vtx().z());
       recoDiele_vtxchi2.push_back(fitter.chi2());
       recoDiele_vtxndof.push_back(fitter.dof());
       recoDiele_vtxprob.push_back(fitter.prob());
       auto fit_p4 = fitter.fitted_p4();
       recoDiele_pt.push_back(fit_p4.pt());
       recoDiele_eta.push_back(fit_p4.eta());
       recoDiele_phi.push_back(fit_p4.phi());
       recoDiele_mass.push_back(fitter.fitted_candidate().mass());
       recoDiele_massErr.push_back(sqrt(fitter.fitted_candidate().kinematicParametersError().matrix()(6,6)));

       //       std::cout<<"ind1: "<<iel1<<" ind2: "<<iel2<<" pt1: "<<el1.pt()<<" pt2: "<<el2.pt()<<" eta1: "<<el1.eta()<<" eta2: "<<el2.eta()<<" phi1: "<<el1.phi()<<" phi2: "<<el2.phi()<<" ch1: "<<el1.charge()<<" ch2: "<<el2.charge()<<std::endl;
       
       recoDiele_index1.push_back(iel1);
       recoDiele_index2.push_back(iel2);
       recoDiele_pt1.push_back(el1.pt());
       recoDiele_eta1.push_back(el1.eta());
       recoDiele_phi1.push_back(el1.phi());
       recoDiele_charge1.push_back(el1.charge());
       recoDiele_mass1.push_back(el1.mass());
       recoDiele_isPF1.push_back(1);
       recoDiele_isLowPt1.push_back(0);
       recoDiele_isPFoverlap1.push_back(0);
       recoDiele_mvaValue1.push_back(-999.);

       float mvaPF_value1 = -999.;
       edm::Ref<pat::ElectronCollection> ref1(pf,iel1);
       mvaPF_value1 = float((*mvaValuePFH_)[ref1]);
       recoDiele_mvaPFValue1.push_back(mvaPF_value1);


       recoDiele_pt1mode.push_back(el1.gsfTrack()->pt());
       recoDiele_eta1mode.push_back(el1.gsfTrack()->eta());
       recoDiele_phi1mode.push_back(el1.gsfTrack()->phi());
       recoDiele_pt2mode.push_back(el2.gsfTrack()->pt());
       recoDiele_eta2mode.push_back(el2.gsfTrack()->eta());
       recoDiele_phi2mode.push_back(el2.gsfTrack()->phi());


       recoDiele_pt2.push_back(el2.pt());
       recoDiele_eta2.push_back(el2.eta());
       recoDiele_phi2.push_back(el2.phi());
       recoDiele_charge2.push_back(el2.charge());
       recoDiele_mass2.push_back(el2.mass());
       recoDiele_isPF2.push_back(1);
       recoDiele_isLowPt2.push_back(0);
       recoDiele_isPFoverlap2.push_back(0);
       recoDiele_mvaValue2.push_back(-999.);
       float mvaPF_value2 = -999.;
       edm::Ref<pat::ElectronCollection> ref2(pf,iel2);
       mvaPF_value2 = float((*mvaValuePFH_)[ref2]);
       recoDiele_mvaPFValue2.push_back(mvaPF_value2);

       
       nDieleReco++;



    }
 }



     // ----------------- DIELECTRON LP-LP -------------------- //
     size_t lp_iel1=-1;
     size_t lp_iel2=-1;
     for (const pat::Electron & el1 : *lowpt){
       lp_iel1++;
       if(el1.pt()<2.)continue;
       if(abs(el1.eta())>2.5)continue;

       lp_iel2=-1;
       // for (pat::MuonCollection::const_iterator mu2 = patMuonsH_.begin(); mu2 != patMuonsH_.end(); ++mu2){
       for (const pat::Electron & el2 : *lowpt){
	 lp_iel2++;
	 if(lp_iel2<=lp_iel1)continue;
	 if(el2.pt()<2.)continue;
	 if(abs(el2.eta())>2.5)continue;
	 //if(el1.charge()*el2.charge()>0)continue;
    

	 //	std::cout<<" pt1: "<<el1.pt()<<" pt2: "<<el2.pt()<<" eta1: "<<el1.eta()<<" eta2: "<<el2.eta()<<" phi1: "<<el1.phi()<<" phi2: "<<el2.phi()<<" ch1: "<<el1.charge()<<" ch2: "<<el2.charge()<<std::endl;

	
       //run kinematic fit
	
       reco::TransientTrack el1TT = (*theB).build( el1.gsfTrack() );
       reco::TransientTrack el2TT = (*theB).build( el2.gsfTrack() );

	float chi = 0.;
	float ndf = 0.;
	double elon_mass = 0.005056583;
	float elon_sigma = 0.0000001;

	KinVtxFitter fitter(
			   {el1TT,el2TT},
			   {elon_mass,elon_mass},
			   {elon_sigma,elon_sigma} //some small sigma for the lepton mass
		      );
	
       if(!fitter.success()) continue; 

       recoDiele_TT1.push_back(el1TT);
       recoDiele_TT2.push_back(el2TT);


       //       std::cout<<" prob: "<<fitter.prob()<<std::endl;
       recoDiele_vx.push_back(fitter.fitted_vtx().x());
       recoDiele_vy.push_back(fitter.fitted_vtx().y());
       recoDiele_vz.push_back(fitter.fitted_vtx().z());
       recoDiele_vtxchi2.push_back(fitter.chi2());
       recoDiele_vtxndof.push_back(fitter.dof());
       recoDiele_vtxprob.push_back(fitter.prob());
       auto fit_p4 = fitter.fitted_p4();
       recoDiele_pt.push_back(fit_p4.pt());
       recoDiele_eta.push_back(fit_p4.eta());
       recoDiele_phi.push_back(fit_p4.phi());
       recoDiele_mass.push_back(fitter.fitted_candidate().mass());
       recoDiele_massErr.push_back(sqrt(fitter.fitted_candidate().kinematicParametersError().matrix()(6,6)));


       	bool clean_out1 = false;
	bool clean_out2 = false;
	for(unsigned int iEle=0; iEle<nPFEle; ++iEle) {
	  
	  clean_out1 |= (
			 fabs(recoEle_vz[iEle] - el1.vz()) < dz_cleaning_ &&
			 reco::deltaR(el1.eta(), el1.phi(), recoEle_eta[iEle], recoEle_phi[iEle]) < dr_cleaning_   );
	  clean_out2 |= (
			 fabs(recoEle_vz[iEle] - el2.vz()) < dz_cleaning_ &&
			 reco::deltaR(el2.eta(), el2.phi(), recoEle_eta[iEle], recoEle_phi[iEle]) < dr_cleaning_   );
	  
	}
	
            
      int recoisoverlap1=0;
      if(clean_out1) recoisoverlap1=1;
      else recoisoverlap1=0;
      int recoisoverlap2=0;
      if(clean_out2) recoisoverlap2=1;
      else recoisoverlap2=0;
	

       recoDiele_index1.push_back(lp_iel1);
       recoDiele_index2.push_back(lp_iel2);
       recoDiele_pt1.push_back(el1.pt());
       recoDiele_eta1.push_back(el1.eta());
       recoDiele_phi1.push_back(el1.phi());
       recoDiele_charge1.push_back(el1.charge());
       recoDiele_mass1.push_back(el1.mass());
       recoDiele_isPF1.push_back(0);
       recoDiele_isLowPt1.push_back(1);
       recoDiele_isPFoverlap1.push_back(recoisoverlap1);
       recoDiele_mvaPFValue1.push_back(-999.);

       recoDiele_pt1mode.push_back(el1.gsfTrack()->pt());
       recoDiele_eta1mode.push_back(el1.gsfTrack()->eta());
       recoDiele_phi1mode.push_back(el1.gsfTrack()->phi());
       recoDiele_pt2mode.push_back(el2.gsfTrack()->pt());
       recoDiele_eta2mode.push_back(el2.gsfTrack()->eta());
       recoDiele_phi2mode.push_back(el2.gsfTrack()->phi());


       float mva_value1 = -999.;
       mva_value1=el1.isElectronIDAvailable("ID") ? el1.electronID("ID") : -100. ;
       recoDiele_mvaValue1.push_back(mva_value1);
       //       std::cout<<"lplp"<<std::endl;

       recoDiele_pt2.push_back(el2.pt());
       recoDiele_eta2.push_back(el2.eta());
       recoDiele_phi2.push_back(el2.phi());
       recoDiele_charge2.push_back(el2.charge());
       recoDiele_mass2.push_back(el2.mass());
       recoDiele_isPF2.push_back(0);
       recoDiele_isLowPt2.push_back(1);
       recoDiele_isPFoverlap2.push_back(recoisoverlap2);
       recoDiele_mvaPFValue2.push_back(-999.);
       float mva_value2 = -999.;
       mva_value2=el2.isElectronIDAvailable("ID") ? el2.electronID("ID") : -100. ;
       recoDiele_mvaValue2.push_back(mva_value2);

       
       nDieleReco++;



    }
 }



     // ----------------- DIELECTRON LP-PF -------------------- //
     size_t llpp_iel1=-1;
     size_t pf_iel2=-1;
     for (const pat::Electron & el1 : *lowpt){
       llpp_iel1++;
       if(el1.pt()<2.)continue;
       if(abs(el1.eta())>2.5)continue;

       pf_iel2=-1;
       // for (pat::MuonCollection::const_iterator mu2 = patMuonsH_.begin(); mu2 != patMuonsH_.end(); ++mu2){
       for (const pat::Electron & el2 : *pf){
	 pf_iel2++;
	 if(el2.pt()<2.)continue;
	 if(abs(el2.eta())>2.5)continue;
	 //	 if(el1.charge()*el2.charge()>0)continue;
    

	 //	std::cout<<" pt1: "<<el1.pt()<<" pt2: "<<el2.pt()<<" eta1: "<<el1.eta()<<" eta2: "<<el2.eta()<<" phi1: "<<el1.phi()<<" phi2: "<<el2.phi()<<" ch1: "<<el1.charge()<<" ch2: "<<el2.charge()<<std::endl;

	
       //run kinematic fit
	
       reco::TransientTrack el1TT = (*theB).build( el1.gsfTrack() );
       reco::TransientTrack el2TT = (*theB).build( el2.gsfTrack() );

	float chi = 0.;
	float ndf = 0.;
	double elon_mass = 0.005056583;
	float elon_sigma = 0.0000001;

	KinVtxFitter fitter(
			   {el1TT,el2TT},
			   {elon_mass,elon_mass},
			   {elon_sigma,elon_sigma} //some small sigma for the lepton mass
		      );
	
       if(!fitter.success()) continue; 

       recoDiele_TT1.push_back(el1TT);
       recoDiele_TT2.push_back(el2TT);

       //       std::cout<<" prob: "<<fitter.prob()<<std::endl;
       recoDiele_vx.push_back(fitter.fitted_vtx().x());
       recoDiele_vy.push_back(fitter.fitted_vtx().y());
       recoDiele_vz.push_back(fitter.fitted_vtx().z());
       recoDiele_vtxchi2.push_back(fitter.chi2());
       recoDiele_vtxndof.push_back(fitter.dof());
       recoDiele_vtxprob.push_back(fitter.prob());
       auto fit_p4 = fitter.fitted_p4();
       recoDiele_pt.push_back(fit_p4.pt());
       recoDiele_eta.push_back(fit_p4.eta());
       recoDiele_phi.push_back(fit_p4.phi());
       recoDiele_mass.push_back(fitter.fitted_candidate().mass());
       recoDiele_massErr.push_back(sqrt(fitter.fitted_candidate().kinematicParametersError().matrix()(6,6)));


       	bool clean_out1 = false;

	for(unsigned int iEle=0; iEle<nPFEle; ++iEle) {
	  
	  clean_out1 |= (
			 fabs(recoEle_vz[iEle] - el1.vz()) < dz_cleaning_ &&
			 reco::deltaR(el1.eta(), el1.phi(), recoEle_eta[iEle], recoEle_phi[iEle]) < dr_cleaning_   );
	}
	
            
      int recoisoverlap1=0;
      if(clean_out1) recoisoverlap1=1;
      else recoisoverlap1=0;
	
      recoDiele_index1.push_back(llpp_iel1);
      recoDiele_index2.push_back(pf_iel2);
      recoDiele_pt1.push_back(el1.pt());
      recoDiele_eta1.push_back(el1.eta());
      recoDiele_phi1.push_back(el1.phi());
      recoDiele_charge1.push_back(el1.charge());
      recoDiele_mass1.push_back(el1.mass());
      recoDiele_isPF1.push_back(0);
      recoDiele_isLowPt1.push_back(1);
      recoDiele_isPFoverlap1.push_back(recoisoverlap1);
      recoDiele_mvaPFValue1.push_back(-999.);
       
       recoDiele_pt1mode.push_back(el1.gsfTrack()->pt());
       recoDiele_eta1mode.push_back(el1.gsfTrack()->eta());
       recoDiele_phi1mode.push_back(el1.gsfTrack()->phi());
       recoDiele_pt2mode.push_back(el2.gsfTrack()->pt());
       recoDiele_eta2mode.push_back(el2.gsfTrack()->eta());
       recoDiele_phi2mode.push_back(el2.gsfTrack()->phi());


       float mva_value1 = -999.;
       mva_value1=el1.isElectronIDAvailable("ID") ? el1.electronID("ID") : -100. ;
       recoDiele_mvaValue1.push_back(mva_value1);

       //       std::cout<<"lppf"<<std::endl;
       recoDiele_pt2.push_back(el2.pt());
       recoDiele_eta2.push_back(el2.eta());
       recoDiele_phi2.push_back(el2.phi());
       recoDiele_charge2.push_back(el2.charge());
       recoDiele_mass2.push_back(el2.mass());
       recoDiele_isPF2.push_back(1);
       recoDiele_isLowPt2.push_back(0);
       recoDiele_isPFoverlap2.push_back(0);
       recoDiele_mvaValue2.push_back(-999.);
       float mvaPF_value2 = -999.;
       edm::Ref<pat::ElectronCollection> ref(pf,pf_iel2);
       mvaPF_value2 = float((*mvaValuePFH_)[ref]);
       recoDiele_mvaPFValue2.push_back(mvaPF_value2);

       
       nDieleReco++;



       }
     }


     //select now best mumu pair:
     double deltamass_dimucand=999;
     int dimucand=999;

     for(int idimu=0;idimu<nDimuReco;idimu++){
       if(recoDimu_isTrigMatch1[idimu]>10 || recoDimu_isTrigMatch2[idimu]>10 || recoDimu_drTrigMatch1[idimu]>0.1 || recoDimu_drTrigMatch2[idimu]>0.1)continue;
       if(recoDimu_isTrigMatch1[idimu]!=recoDimu_isTrigMatch2[idimu])continue;
       if(abs(recoDimu_mass[idimu]-massRef)<deltamass_dimucand){
	 deltamass_dimucand=abs(recoDimu_mass[idimu]-massRef);
	 dimucand=idimu;
       }

     }



       //reconstruct TQ

       for(int idimu=0;idimu<nDimuReco;idimu++){

	 if(idimu!=dimucand)continue;

	 reco::TransientTrack mu1TT = recoDimu_TT1[idimu];
	 reco::TransientTrack mu2TT = recoDimu_TT2[idimu];


	 int idiel=0;
	 for( idiel=0;idiel<nDieleReco;idiel++){

	 reco::TransientTrack el1TT = recoDiele_TT1[idiel] ;
	 reco::TransientTrack el2TT = recoDiele_TT2[idiel] ;



	 float chi = 0.;
	 float ndf = 0.;
	 double muon_mass = 0.1056583;
	 float muon_sigma = 0.0000001;
	 double elon_mass = 0.005056583;
	 float elon_sigma = 0.0000001;
	 
	 KinVtxFitter fitter(
			     {mu1TT,mu2TT,el1TT,el2TT},
			     {muon_mass,muon_mass,elon_mass,elon_mass},
			     {muon_sigma,muon_sigma,elon_sigma,elon_sigma} //some small sigma for the lepton mass
			      );
	 
	 if(!fitter.success()) continue; 
       
	 recoTQ_vtxchi2.push_back(fitter.chi2());
	 recoTQ_vtxndof.push_back(fitter.dof());
	 recoTQ_vtxprob.push_back(fitter.prob());
	 
	 auto fit_p4 = fitter.fitted_p4();
	 recoTQ_pt.push_back(fit_p4.pt());
	 recoTQ_eta.push_back(fit_p4.eta());
	 recoTQ_phi.push_back(fit_p4.phi());
	 recoTQ_mass.push_back(fitter.fitted_candidate().mass());
	 recoTQ_massErr.push_back(sqrt(fitter.fitted_candidate().kinematicParametersError().matrix()(6,6)));

	 recoTQ_Y1pt.push_back(recoDimu_pt[idimu]);
	 recoTQ_Y1eta.push_back(recoDimu_eta[idimu]);
	 recoTQ_Y1phi.push_back(recoDimu_phi[idimu]);
	 recoTQ_Y1mass.push_back(recoDimu_mass[idimu]);
	 recoTQ_Y1massErr.push_back(recoDimu_massErr[idimu]);
	 recoTQ_Y1vtxchi2.push_back(recoDimu_vtxchi2[idimu]);
	 recoTQ_Y1vtxndof.push_back(recoDimu_vtxndof[idimu]);
	 recoTQ_Y1vtxprob.push_back(recoDimu_vtxprob[idimu]);


	 recoTQ_leptype1.push_back(0); //0 muons 1 electrons
	 recoTQ_pt1.push_back(recoDimu_pt1[idimu]);
	 recoTQ_eta1.push_back(recoDimu_eta1[idimu]);
	 recoTQ_phi1.push_back(recoDimu_phi1[idimu]);
	 recoTQ_charge1.push_back(recoDimu_charge1[idimu]);
	 recoTQ_mass1.push_back(recoDimu_mass1[idimu]);
	 recoTQ_softID1.push_back(recoDimu_softID1[idimu]);
	 recoTQ_mediumID1.push_back(recoDimu_mediumID1[idimu]);
	 

	 recoTQ_leptype2.push_back(0); 
	 recoTQ_pt2.push_back(recoDimu_pt2[idimu]);
	 recoTQ_eta2.push_back(recoDimu_eta2[idimu]);
	 recoTQ_phi2.push_back(recoDimu_phi2[idimu]);
	 recoTQ_charge2.push_back(recoDimu_charge2[idimu]);
	 recoTQ_mass2.push_back(recoDimu_mass2[idimu]);
	 recoTQ_softID2.push_back(recoDimu_softID2[idimu]);
	 recoTQ_mediumID2.push_back(recoDimu_mediumID2[idimu]);

         recoTQ_isTrigMatch1.push_back(recoDimu_isTrigMatch1[idimu]);                                                                                    
	 recoTQ_drTrigMatch1.push_back(recoDimu_drTrigMatch1[idimu]);
         recoTQ_isTrigMatch2.push_back(recoDimu_isTrigMatch2[idimu]); 
	 recoTQ_drTrigMatch2.push_back(recoDimu_drTrigMatch2[idimu]);

  

	 recoTQ_Y2pt.push_back(recoDiele_pt[idiel]);
	 recoTQ_Y2eta.push_back(recoDiele_eta[idiel]);
	 recoTQ_Y2phi.push_back(recoDiele_phi[idiel]);
	 recoTQ_Y2mass.push_back(recoDiele_mass[idiel]);
	 recoTQ_Y2massErr.push_back(recoDiele_massErr[idiel]);
	 recoTQ_Y2vtxchi2.push_back(recoDiele_vtxchi2[idiel]);
	 recoTQ_Y2vtxndof.push_back(recoDiele_vtxndof[idiel]);
	 recoTQ_Y2vtxprob.push_back(recoDiele_vtxprob[idiel]);



	 //	 std::cout<<"idimu: "<<idimu<<" idiel: "<<idiel<<" TQmass: "<<fitter.fitted_candidate().mass()<<" Y1: " << recoDimu_mass[idimu]<<" Y2: "<<recoDiele_mass[idiel]<<std::endl;

	 recoTQ_leptype3.push_back(1);
         recoTQ_pt3.push_back(recoDiele_pt1[idiel]);
         recoTQ_pt3mode.push_back(recoDiele_pt1mode[idiel]);
         recoTQ_eta3.push_back(recoDiele_eta1mode[idiel]);
         recoTQ_phi3.push_back(recoDiele_phi1mode[idiel]);
         recoTQ_charge3.push_back(recoDiele_charge1[idiel]);
         recoTQ_mass3.push_back(recoDiele_mass1[idiel]);
         recoTQ_softID3.push_back(-999);
         recoTQ_mediumID3.push_back(-999);
         recoTQ_mvaValue3.push_back(recoDiele_mvaValue1[idiel]);
         recoTQ_mvaPFValue3.push_back(recoDiele_mvaPFValue1[idiel]);
         recoTQ_isPF3.push_back(recoDiele_isPF1[idiel]);
         recoTQ_isLowPt3.push_back(recoDiele_isLowPt1[idiel]);
         recoTQ_isPFoverlap3.push_back(recoDiele_isPFoverlap1[idiel]);


	 recoTQ_leptype4.push_back(1);
         recoTQ_pt4.push_back(recoDiele_pt2[idiel]);
         recoTQ_pt4mode.push_back(recoDiele_pt2mode[idiel]);
         recoTQ_eta4.push_back(recoDiele_eta2mode[idiel]);
         recoTQ_phi4.push_back(recoDiele_phi2mode[idiel]);
         recoTQ_charge4.push_back(recoDiele_charge2[idiel]);
         recoTQ_mass4.push_back(recoDiele_mass2[idiel]);
         recoTQ_softID4.push_back(-999);
         recoTQ_mediumID4.push_back(-999);
         recoTQ_mvaValue4.push_back(recoDiele_mvaValue2[idiel]);
         recoTQ_mvaPFValue4.push_back(recoDiele_mvaPFValue2[idiel]);
         recoTQ_isPF4.push_back(recoDiele_isPF2[idiel]);
         recoTQ_isLowPt4.push_back(recoDiele_isLowPt2[idiel]);
         recoTQ_isPFoverlap4.push_back(recoDiele_isPFoverlap2[idiel]);


	 nTQReco++;
	 }

	 
       }


       h_counter->Fill(1);
     
       bool triggerOK=0;
       //       if(sampleID <=0)triggerOK=1;
       
       if(year==2016){
	 triggerOK = HLT_Dimuon13_Upsilon_v_2016||HLT_Dimuon8_Upsilon_Barrel_v_2016 ;
       }else if(year==2017){
	 triggerOK = HLT_Dimuon12_Upsilon_eta1p5_v_2017 || HLT_Dimuon24_Upsilon_noCorrL1_v_2017 ||HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017 ||HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017;
       }else if(year==2018){
	 triggerOK = HLT_Dimuon12_Upsilon_y1p4_v_2018 || HLT_Dimuon24_Upsilon_noCorrL1_v_2018 || HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018 || HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018;
       }



       //perform trigger studies: need prescaled trigger fired
       //       triggerOK=HLT_Dimuon0_prescaled_2018;    
       
       if(triggerOK)h_counter->Fill(3);
              
       initTreeStructure();
       clearVectors();


    tree_.run=run;
    tree_.event=event;
    tree_.lumi=lumi;
    tree_.nEle=nEle;
    tree_.nMu=nMu;
    tree_.vx=vx;
    tree_.vy=vy;
    tree_.vz=vz;
    tree_.nvtx=nvtx;
    tree_.rho=rho;
    tree_.npu=npu;
    tree_.puw_2016=puw_2016;
    tree_.puw_2017=puw_2017;
    tree_.puw_2018=puw_2018;
    tree_.puw_ALL=puw_ALL;

    tree_.nvtxw_2016=nvtxw_2016;
    tree_.nvtxw_2017=nvtxw_2017;
    tree_.nvtxw_2018=nvtxw_2018;
    tree_.nvtxw_ALL=nvtxw_ALL;
    

    tree_.HLT_Dimuon13_Upsilon_v_2016=HLT_Dimuon13_Upsilon_v_2016;
    tree_.HLT_Dimuon8_Upsilon_Barrel_v_2016=HLT_Dimuon8_Upsilon_Barrel_v_2016;


    tree_.HLT_Dimuon12_Upsilon_eta1p5_v_2017=HLT_Dimuon12_Upsilon_eta1p5_v_2017;
    tree_.HLT_Dimuon24_Upsilon_noCorrL1_v_2017=HLT_Dimuon24_Upsilon_noCorrL1_v_2017;
    tree_.HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017=HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017;
    tree_.HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017=HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017;

    tree_.HLT_Dimuon0_prescaled_2018 = HLT_Dimuon0_prescaled_2018;
    tree_.HLT_Dimuon12_Upsilon_y1p4_v_2018=HLT_Dimuon12_Upsilon_y1p4_v_2018;
    tree_.HLT_Dimuon24_Upsilon_noCorrL1_v_2018=HLT_Dimuon24_Upsilon_noCorrL1_v_2018;
    tree_.HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018=HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018;
    tree_.HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018=HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018;

    tree_.year=year;
    tree_.sampleID=sampleID;
    tree_.xsec=xsec;


    for(unsigned int i=0;i<genLep_pt.size();i++){
      tree_.genLep_pt.push_back(genLep_pt[i]);
      tree_.genLep_mass.push_back(genLep_mass[i]);
      tree_.genLep_eta.push_back(genLep_eta[i]);
      tree_.genLep_phi.push_back(genLep_phi[i]);
      tree_.genLep_pdgId.push_back(genLep_pdgId[i]);

      tree_.genMom_pt.push_back(genMom_pt[i]);
      tree_.genMom_mass.push_back(genMom_mass[i]);
      tree_.genMom_eta.push_back(genMom_eta[i]);
      tree_.genMom_phi.push_back(genMom_phi[i]);
      tree_.genMom_pdgId.push_back(genMom_pdgId[i]);
    

      if(i==0)lep0->SetPtEtaPhiM(genLep_pt[i],genLep_eta[i],genLep_phi[i],genLep_mass[i]);
      if(i==1)lep1->SetPtEtaPhiM(genLep_pt[i],genLep_eta[i],genLep_phi[i],genLep_mass[i]);
      if(i==2)lep2->SetPtEtaPhiM(genLep_pt[i],genLep_eta[i],genLep_phi[i],genLep_mass[i]);
      if(i==3)lep3->SetPtEtaPhiM(genLep_pt[i],genLep_eta[i],genLep_phi[i],genLep_mass[i]);
    }

    TLorentzVector TQ(*lep0+*lep1+*lep2+*lep3);
    tree_.TQ_genMass=TQ.M();

    /*
    tree_.nMuReco=nMuReco;
    for(unsigned int i=0;i<recoMu_pt.size();i++){
      tree_.recoMu_pt.push_back(recoMu_pt[i]);
      tree_.recoMu_mass.push_back(recoMu_mass[i]);
      tree_.recoMu_eta.push_back(recoMu_eta[i]);
      tree_.recoMu_phi.push_back(recoMu_phi[i]);   
      tree_.recoMu_charge.push_back(recoMu_charge[i]);   

      tree_.recoMu_dR1.push_back(recoMu_dR1[i]);   
      tree_.recoMu_matchid1.push_back(recoMu_matchid1[i]);   
      tree_.recoMu_dR2.push_back(recoMu_dR2[i]);   
      tree_.recoMu_matchid2.push_back(recoMu_matchid2[i]);   
      tree_.recoMu_looseID.push_back(recoMu_looseID[i]);   
      tree_.recoMu_softID.push_back(recoMu_softID[i]);   
      tree_.recoMu_nTrkLayers.push_back(recoMu_nTrkLayers[i]);   
      tree_.recoMu_nPixLayers.push_back(recoMu_nPixLayers[i]);   
      tree_.recoMu_isHQ.push_back(recoMu_isHQ[i]);   
      tree_.recoMu_dxy.push_back(recoMu_dxy[i]);   
      tree_.recoMu_dz.push_back(recoMu_dz[i]);   
      tree_.recoMu_isTrigMatch.push_back(recoMu_isTrigMatch[i]);   
      tree_.recoMu_drTrigMatch.push_back(recoMu_drTrigMatch[i]);   
      
    }

    
    
    tree_.nDimuReco=nDimuReco;
    for(unsigned int i=0;i<recoDimu_vx.size();i++){
       
      tree_.recoDimu_vx.push_back(           recoDimu_vx[i]);	      
      tree_.recoDimu_vy.push_back(	     recoDimu_vy[i]);	      
      tree_.recoDimu_vz.push_back(	     recoDimu_vz[i]);	      
      tree_.recoDimu_vtxchi2.push_back(     recoDimu_vtxchi2[i]);  
      tree_.recoDimu_vtxndof.push_back(     recoDimu_vtxndof[i]);  
      tree_.recoDimu_vtxprob.push_back(     recoDimu_vtxprob[i]);  
      tree_.recoDimu_index1.push_back(  	     recoDimu_index1[i]);      
      tree_.recoDimu_index2.push_back(  	     recoDimu_index2[i]);      
      tree_.recoDimu_pt1.push_back(  	     recoDimu_pt1[i]);      
      tree_.recoDimu_pt1.push_back(  	     recoDimu_pt1[i]);      
      tree_.recoDimu_eta1.push_back(	     recoDimu_eta1[i]);     
      tree_.recoDimu_phi1.push_back(	     recoDimu_phi1[i]);     
      tree_.recoDimu_charge1.push_back(     recoDimu_charge1[i]);  
      tree_.recoDimu_mass1.push_back(       recoDimu_mass1[i]);     
      tree_.recoDimu_softID1.push_back(       recoDimu_softID1[i]);     
      tree_.recoDimu_pt2.push_back(  	     recoDimu_pt2[i]);      
      tree_.recoDimu_eta2.push_back(	     recoDimu_eta2[i]);     
      tree_.recoDimu_phi2.push_back(	     recoDimu_phi2[i]);     
      tree_.recoDimu_charge2.push_back(     recoDimu_charge2[i]);  
      tree_.recoDimu_mass2.push_back(       recoDimu_mass2[i]);         
      tree_.recoDimu_softID2.push_back(       recoDimu_softID2[i]);       
      tree_.recoDimu_pt.push_back(       recoDimu_pt[i]);           
      tree_.recoDimu_eta.push_back(       recoDimu_eta[i]);           
      tree_.recoDimu_phi.push_back(       recoDimu_phi[i]);           
      tree_.recoDimu_mass.push_back(       recoDimu_mass[i]);           
      tree_.recoDimu_massErr.push_back(       recoDimu_massErr[i]);           
      tree_.recoDimu_isTrigMatch1.push_back(recoDimu_isTrigMatch1[i]);   
      tree_.recoDimu_drTrigMatch1.push_back(recoDimu_drTrigMatch1[i]);   
      tree_.recoDimu_isTrigMatch2.push_back(recoDimu_isTrigMatch2[i]);   
      tree_.recoDimu_drTrigMatch2.push_back(recoDimu_drTrigMatch2[i]);   
      
      }

    
    tree_.nEleReco=nEleReco;
    tree_.nPFEleReco=nPFEleReco;
    tree_.nLowPtEleReco=nLowPtEleReco;
    for(unsigned int i=0;i<recoEle_pt.size();i++){
      tree_.recoEle_pt.push_back(recoEle_pt[i]);
      tree_.recoEle_mass.push_back(recoEle_mass[i]);
      tree_.recoEle_eta.push_back(recoEle_eta[i]);
      tree_.recoEle_phi.push_back(recoEle_phi[i]);   
      tree_.recoEle_charge.push_back(recoEle_charge[i]);   

      tree_.recoEle_ptmode.push_back(recoEle_ptmode[i]);
      tree_.recoEle_etamode.push_back(recoEle_etamode[i]);
      tree_.recoEle_phimode.push_back(recoEle_phimode[i]);

      tree_.recoEle_p.push_back(recoEle_p[i]);

      tree_.recoEle_vx.push_back(recoEle_vx[i]);   
      tree_.recoEle_vy.push_back(recoEle_vy[i]);   
      tree_.recoEle_vz.push_back(recoEle_vz[i]);   

      tree_.recoEle_dR1.push_back(recoEle_dR1[i]);   
      tree_.recoEle_matchid1.push_back(recoEle_matchid1[i]);   
      tree_.recoEle_dR2.push_back(recoEle_dR2[i]);   
      tree_.recoEle_matchid2.push_back(recoEle_matchid2[i]);   
      tree_.recoEle_E_ecal_preReg.push_back(recoEle_E_ecal_preReg[i]);   
      tree_.recoEle_E_ecal_postReg.push_back(recoEle_E_ecal_postReg[i]);   
      tree_.recoEle_E_ecaltrk_preReg.push_back(recoEle_E_ecaltrk_preReg[i]);   
      tree_.recoEle_E_ecaltrk_postReg.push_back(recoEle_E_ecaltrk_postReg[i]);   

      tree_.recoEle_rawE.push_back(recoEle_rawE[i]);
      tree_.recoEle_corrEcalE.push_back(recoEle_corrEcalE[i]);
      tree_.recoEle_gsfTrkChi2.push_back(recoEle_gsfTrkChi2[i]);
      tree_.recoEle_passConvVeto.push_back(recoEle_passConvVeto[i]);
      tree_.recoEle_isPF.push_back(recoEle_isPF[i]);

      tree_.recoEle_isLowPt.push_back(recoEle_isLowPt[i]);
      tree_.recoEle_isPFoverlap.push_back(recoEle_isPFoverlap[i]);
      tree_.recoEle_mvaPFValue.push_back(recoEle_mvaPFValue[i]);
      tree_.recoEle_mvaValue.push_back(recoEle_mvaValue[i]);

    }

    tree_.nDieleReco=nDieleReco;
    for(unsigned int i=0;i<recoDiele_vx.size();i++){
      
      tree_.recoDiele_vx.push_back(           recoDiele_vx[i]);	      
      tree_.recoDiele_vy.push_back(	     recoDiele_vy[i]);	      
      tree_.recoDiele_vz.push_back(	     recoDiele_vz[i]);	      
      tree_.recoDiele_vtxchi2.push_back(     recoDiele_vtxchi2[i]);  
      tree_.recoDiele_vtxndof.push_back(     recoDiele_vtxndof[i]);  
      tree_.recoDiele_vtxprob.push_back(     recoDiele_vtxprob[i]);  
      tree_.recoDiele_index1.push_back(  	     recoDiele_index1[i]);      
      tree_.recoDiele_index2.push_back(  	     recoDiele_index2[i]);      
      tree_.recoDiele_pt1.push_back(  	     recoDiele_pt1[i]);      
      tree_.recoDiele_eta1.push_back(	     recoDiele_eta1[i]);     
      tree_.recoDiele_phi1.push_back(	     recoDiele_phi1[i]);     
      tree_.recoDiele_charge1.push_back(     recoDiele_charge1[i]);  
      tree_.recoDiele_mass1.push_back(       recoDiele_mass1[i]);     
      tree_.recoDiele_mvaValue1.push_back(       recoDiele_mvaValue1[i]);     
      tree_.recoDiele_mvaPFValue1.push_back(       recoDiele_mvaPFValue1[i]);     
      tree_.recoDiele_isPF1.push_back(       recoDiele_isPF1[i]);     
      tree_.recoDiele_isLowPt1.push_back(       recoDiele_isLowPt1[i]);     
      tree_.recoDiele_isPFoverlap1.push_back(       recoDiele_isPFoverlap1[i]);     
      tree_.recoDiele_pt2.push_back(  	     recoDiele_pt2[i]);      
      tree_.recoDiele_eta2.push_back(	     recoDiele_eta2[i]);     
      tree_.recoDiele_phi2.push_back(	     recoDiele_phi2[i]);     
      tree_.recoDiele_charge2.push_back(     recoDiele_charge2[i]);  
      tree_.recoDiele_mass2.push_back(       recoDiele_mass2[i]);           
      tree_.recoDiele_mvaValue2.push_back(       recoDiele_mvaValue2[i]);     
      tree_.recoDiele_mvaPFValue2.push_back(       recoDiele_mvaPFValue2[i]);     
      tree_.recoDiele_isPF2.push_back(       recoDiele_isPF2[i]);     
      tree_.recoDiele_isLowPt2.push_back(       recoDiele_isLowPt2[i]);     
      tree_.recoDiele_isPFoverlap2.push_back(       recoDiele_isPFoverlap2[i]);     
      tree_.recoDiele_pt.push_back(       recoDiele_pt[i]);           
      tree_.recoDiele_eta.push_back(       recoDiele_eta[i]);           
      tree_.recoDiele_phi.push_back(       recoDiele_phi[i]);           
      tree_.recoDiele_mass.push_back(       recoDiele_mass[i]);           
      tree_.recoDiele_massErr.push_back(       recoDiele_massErr[i]);           

      tree_.recoDiele_pt1mode.push_back(recoDiele_pt1mode[i]);
      tree_.recoDiele_eta1mode.push_back(recoDiele_eta1mode[i]);
      tree_.recoDiele_phi1mode.push_back(recoDiele_phi1mode[i]);
      tree_.recoDiele_pt2mode.push_back(recoDiele_pt2mode[i]);
      tree_.recoDiele_eta2mode.push_back(recoDiele_eta2mode[i]);
      tree_.recoDiele_phi2mode.push_back(recoDiele_phi2mode[i]);

             
    }
    */    


    tree_.nSoftDimu=nSoftDimu;
    tree_.nMediumDimu=nMediumDimu;
  // TQ
    tree_.nTQReco=nTQReco;
    for(unsigned int i=0;i<recoTQ_pt.size();i++){
        tree_.recoTQ_pt.push_back(	  	       recoTQ_pt[i]);		       
	tree_.recoTQ_eta.push_back(	  	       recoTQ_eta[i]);		       
	tree_.recoTQ_phi.push_back(	  	       recoTQ_phi[i]);		       
	tree_.recoTQ_mass.push_back(	  	       recoTQ_mass[i]);		       
	tree_.recoTQ_massErr.push_back(	          recoTQ_massErr[i]);	  	       
	tree_.recoTQ_vtxchi2.push_back(	          recoTQ_vtxchi2[i]);	  	       
	tree_.recoTQ_vtxndof.push_back(	          recoTQ_vtxndof[i]);	  	       
	tree_.recoTQ_vtxprob.push_back(	          recoTQ_vtxprob[i]);	  	       

        tree_.recoTQ_Y1pt.push_back(	  	       recoTQ_Y1pt[i]);		       
	tree_.recoTQ_Y1eta.push_back(	  	       recoTQ_Y1eta[i]);		       
	tree_.recoTQ_Y1phi.push_back(	  	       recoTQ_Y1phi[i]);		       
	tree_.recoTQ_Y1mass.push_back(	  	       recoTQ_Y1mass[i]);		       
	tree_.recoTQ_Y1massErr.push_back(	          recoTQ_Y1massErr[i]);	  	       
	tree_.recoTQ_Y1vtxchi2.push_back(	          recoTQ_Y1vtxchi2[i]);	  	       
	tree_.recoTQ_Y1vtxndof.push_back(	          recoTQ_Y1vtxndof[i]);	  	       
	tree_.recoTQ_Y1vtxprob.push_back(	          recoTQ_Y1vtxprob[i]);	  	       


        tree_.recoTQ_Y2pt.push_back(	  	       recoTQ_Y2pt[i]);		       
	tree_.recoTQ_Y2eta.push_back(	  	       recoTQ_Y2eta[i]);		       
	tree_.recoTQ_Y2phi.push_back(	  	       recoTQ_Y2phi[i]);		       
	tree_.recoTQ_Y2mass.push_back(	  	       recoTQ_Y2mass[i]);		       
	tree_.recoTQ_Y2massErr.push_back(	          recoTQ_Y2massErr[i]);	  	       
	tree_.recoTQ_Y2vtxchi2.push_back(	          recoTQ_Y2vtxchi2[i]);	  	       
	tree_.recoTQ_Y2vtxndof.push_back(	          recoTQ_Y2vtxndof[i]);	  	       
	tree_.recoTQ_Y2vtxprob.push_back(	          recoTQ_Y2vtxprob[i]);	  	       
        				                                               

        tree_.recoTQ_leptype1.push_back(       	     recoTQ_leptype1[i]);	       
	tree_.recoTQ_pt1.push_back(	       	       recoTQ_pt1[i]);		       
	tree_.recoTQ_eta1.push_back(	       	       recoTQ_eta1[i]);		       
	tree_.recoTQ_phi1.push_back(	       	       recoTQ_phi1[i]);		       
	tree_.recoTQ_charge1.push_back(	          recoTQ_charge1[i]);	  	       
	tree_.recoTQ_mass1.push_back(	       	       recoTQ_mass1[i]);	       	  
        tree_.recoTQ_softID1.push_back(	       	     recoTQ_softID1[i]);	       	  
        tree_.recoTQ_mediumID1.push_back(	       	     recoTQ_mediumID1[i]);	       	  
        				                                               
        tree_.recoTQ_leptype2.push_back(       	     recoTQ_leptype2[i]);	       
	tree_.recoTQ_pt2.push_back(	       	       recoTQ_pt2[i]);		       
	tree_.recoTQ_eta2.push_back(	       	       recoTQ_eta2[i]);		       
	tree_.recoTQ_phi2.push_back(	       	       recoTQ_phi2[i]);		       
	tree_.recoTQ_charge2.push_back(	          recoTQ_charge2[i]);	  	       
	tree_.recoTQ_mass2.push_back(	       	       recoTQ_mass2[i]);	       	  
        tree_.recoTQ_softID2.push_back(	       	     recoTQ_softID2[i]);	       	  
        tree_.recoTQ_mediumID2.push_back(	       	     recoTQ_mediumID2[i]);	       	  

	tree_.recoTQ_isTrigMatch1.push_back(    recoTQ_isTrigMatch1[i]);
	tree_.recoTQ_drTrigMatch1.push_back(    recoTQ_drTrigMatch1[i]);
	tree_.recoTQ_isTrigMatch2.push_back(    recoTQ_isTrigMatch2[i]);
	tree_.recoTQ_drTrigMatch2.push_back(    recoTQ_drTrigMatch2[i]);
                                                                                                       

        tree_.recoTQ_leptype3.push_back(       	     recoTQ_leptype3[i]);	       
	tree_.recoTQ_pt3.push_back(	       	       recoTQ_pt3[i]);		       
	tree_.recoTQ_pt3mode.push_back(	       	       recoTQ_pt3mode[i]);		       
	tree_.recoTQ_eta3.push_back(	       	       recoTQ_eta3[i]);		       
	tree_.recoTQ_phi3.push_back(	       	       recoTQ_phi3[i]);		       
	tree_.recoTQ_charge3.push_back(	          recoTQ_charge3[i]);	  	       
	tree_.recoTQ_mass3.push_back(	       	       recoTQ_mass3[i]);	       	  
        tree_.recoTQ_softID3.push_back(	       	     recoTQ_softID3[i]);	       	  
        tree_.recoTQ_mediumID3.push_back(	       	     recoTQ_mediumID3[i]);	       	  
	tree_.recoTQ_mvaValue3.push_back(      	       recoTQ_mvaValue3[i]);	       
	tree_.recoTQ_mvaPFValue3.push_back(    	       recoTQ_mvaPFValue3[i]);	       
        tree_.recoTQ_isPF3.push_back(	       	     recoTQ_isPF3[i]);		       
        tree_.recoTQ_isLowPt3.push_back(       	     recoTQ_isLowPt3[i]);	       
        tree_.recoTQ_isPFoverlap3.push_back(      	     recoTQ_isPFoverlap3[i]);    	  
        				                                               
        				                                               
        tree_.recoTQ_leptype4.push_back(       	     recoTQ_leptype4[i]);	       
	tree_.recoTQ_pt4.push_back(	       	       recoTQ_pt4[i]);		       
	tree_.recoTQ_pt4mode.push_back(	       	       recoTQ_pt4mode[i]);		       
	tree_.recoTQ_eta4.push_back(	       	       recoTQ_eta4[i]);		       
	tree_.recoTQ_phi4.push_back(	       	       recoTQ_phi4[i]);		       
	tree_.recoTQ_charge4.push_back(	          recoTQ_charge4[i]);	  	       
	tree_.recoTQ_mass4.push_back(	       	       recoTQ_mass4[i]);	       	  
        tree_.recoTQ_softID4.push_back(	       	     recoTQ_softID4[i]);	       	  
        tree_.recoTQ_mediumID4.push_back(	       	     recoTQ_mediumID4[i]);	       	  
	tree_.recoTQ_mvaValue4.push_back(      	       recoTQ_mvaValue4[i]);	       
	tree_.recoTQ_mvaPFValue4.push_back(    	       recoTQ_mvaPFValue4[i]);	       
        tree_.recoTQ_isPF4.push_back(	       	     recoTQ_isPF4[i]);		       
        tree_.recoTQ_isLowPt4.push_back(       	     recoTQ_isLowPt4[i]);	       
        tree_.recoTQ_isPFoverlap4.push_back(            recoTQ_isPFoverlap4[i]);       

 }




    if(nTQReco>0 && triggerOK)    tree->Fill();

 }


void TQGenAnalyzer::beginJob()
{
  std::cout << "Starting job" << std::endl;
  SetPuWeights(2016,puweights2016_);
  SetPuWeights(2017,puweights2017_);
  SetPuWeights(2018,puweights2018_);
  SetPuWeights(0,puweightsALL_);

  SetNVTXWeights(2016,nvtxweights2016_);
  SetNVTXWeights(2017,nvtxweights2017_);
  SetNVTXWeights(2018,nvtxweights2018_);
  SetNVTXWeights(0,nvtxweightsALL_);

  // --- set up output tree
  h_counter = fs->make<TH1F>("h_counter","h_counter",2,0,4);
  tree = fs->make<TTree>("tree","tree");
  tree->Branch("year", &tree_.year, "year/I");
  tree->Branch("sampleID", &tree_.sampleID, "sampleID/I");
  tree->Branch("xsec", &tree_.xsec, "xsec/F");
  tree->Branch("run", &tree_.run, "run/I");
  tree->Branch("event", &tree_.event, "event/I");
  tree->Branch("lumi", &tree_.lumi, "lumi/I");
  tree->Branch("nEle", &tree_.nEle, "nEle/I");
  tree->Branch("nMu", &tree_.nMu, "nMu/I");
  tree->Branch("vx", &tree_.vx, "vx/F");
  tree->Branch("vy", &tree_.vy, "vy/F");
  tree->Branch("vz", &tree_.vz, "vz/F");
  tree->Branch("nvtx", &tree_.nvtx, "nvtx/I");
  tree->Branch("rho", &tree_.rho, "rho/F");
  tree->Branch("npu", &tree_.npu, "npu/I");
  tree->Branch("puw_2016", &tree_.puw_2016, "puw_2016/F");
  tree->Branch("puw_2017", &tree_.puw_2017, "puw_2017/F");
  tree->Branch("puw_2018", &tree_.puw_2018, "puw_2018/F");
  tree->Branch("puw_ALL", &tree_.puw_ALL, "puw_ALL/F");


  tree->Branch("nvtxw_2016", &tree_.nvtxw_2016, "nvtxw_2016/F");
  tree->Branch("nvtxw_2017", &tree_.nvtxw_2017, "nvtxw_2017/F");
  tree->Branch("nvtxw_2018", &tree_.nvtxw_2018, "nvtxw_2018/F");
  tree->Branch("nvtxw_ALL", &tree_.nvtxw_ALL, "nvtxw_ALL/F");



  tree->Branch("HLT_Dimuon13_Upsilon_v_2016",&tree_.HLT_Dimuon13_Upsilon_v_2016,"HLT_Dimuon13_Upsilon_v_2016/I");
  tree->Branch("HLT_Dimuon8_Upsilon_Barrel_v_2016",&tree_.HLT_Dimuon8_Upsilon_Barrel_v_2016,"HLT_Dimuon8_Upsilon_Barrel_v_2016/I");

  tree->Branch("HLT_Dimuon12_Upsilon_eta1p5_v_2017",&tree_.HLT_Dimuon12_Upsilon_eta1p5_v_2017,"HLT_Dimuon12_Upsilon_eta1p5_v_2017/I");
  tree->Branch("HLT_Dimuon24_Upsilon_noCorrL1_v_2017",&tree_.HLT_Dimuon24_Upsilon_noCorrL1_v_2017,"HLT_Dimuon24_Upsilon_noCorrL1_v_2017/I");
  tree->Branch("HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017",&tree_.HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2017,"HLT_Dimuon24_Upsilon_noCorrL1_v_2017/I");
  tree->Branch("HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017",&tree_.HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017,"HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2017/I");

  tree->Branch("HLT_Dimuon0_prescaled_2018",&tree_.HLT_Dimuon0_prescaled_2018,"HLT_Dimuon0_prescaled_2018/I");
  tree->Branch("HLT_Dimuon12_Upsilon_y1p4_v_2018",&tree_.HLT_Dimuon12_Upsilon_y1p4_v_2018,"HLT_Dimuon12_Upsilon_y1p4_v_2018/I");
  tree->Branch("HLT_Dimuon24_Upsilon_noCorrL1_v_2018",&tree_.HLT_Dimuon24_Upsilon_noCorrL1_v_2018,"HLT_Dimuon24_Upsilon_noCorrL1_v_2018/I");
  tree->Branch("HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018",&tree_.HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon_v_2018,"HLT_Dimuon24_Upsilon_noCorrL1_v_2018/I");
  tree->Branch("HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018",&tree_.HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018,"HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL_v_2018/I");


 
  tree->Branch("TQ_genMass", &tree_.TQ_genMass, "TQ_genMass/F");
  tree->Branch("genLep_pt",     &tree_.genLep_pt);
  tree->Branch("genLep_mass",      &tree_.genLep_mass);
  tree->Branch("genLep_eta",&tree_.genLep_eta);
  tree->Branch("genLep_phi",&tree_.genLep_phi);
  tree->Branch("genLep_pdgId",&tree_.genLep_pdgId);
  tree->Branch("genMom_pt",     &tree_.genMom_pt);
  tree->Branch("genMom_mass",      &tree_.genMom_mass);
  tree->Branch("genMom_eta",&tree_.genMom_eta);
  tree->Branch("genMom_phi",&tree_.genMom_phi);
  tree->Branch("genMom_pdgId",&tree_.genMom_pdgId);
  /*
  tree->Branch("nMuReco", &tree_.nMuReco, "nMuReco/I");
  tree->Branch("recoMu_pt",     &tree_.recoMu_pt);
  tree->Branch("recoMu_mass",      &tree_.recoMu_mass);
  tree->Branch("recoMu_eta",&tree_.recoMu_eta);
  tree->Branch("recoMu_phi",&tree_.recoMu_phi);
  tree->Branch("recoMu_charge",&tree_.recoMu_charge);
  tree->Branch("recoMu_dR1",&tree_.recoMu_dR1);
  tree->Branch("recoMu_matchid1",&tree_.recoMu_matchid1);
  tree->Branch("recoMu_dR2",&tree_.recoMu_dR2);
  tree->Branch("recoMu_matchid2",&tree_.recoMu_matchid2);
  tree->Branch("recoMu_looseID",&tree_.recoMu_looseID);
  tree->Branch("recoMu_softID",&tree_.recoMu_softID);
  tree->Branch("recoMu_nTrkLayers",&tree_.recoMu_nTrkLayers);
  tree->Branch("recoMu_nPixLayers",&tree_.recoMu_nPixLayers);
  tree->Branch("recoMu_isHQ",&tree_.recoMu_isHQ);
  tree->Branch("recoMu_dxy",&tree_.recoMu_dxy);
  tree->Branch("recoMu_dz",&tree_.recoMu_dz);

  tree->Branch("nDimuReco", &tree_.nDimuReco, "nDimuReco/I");
  tree->Branch("recoDimu_vx",     &tree_.recoDimu_vx);
  tree->Branch("recoDimu_vy",     &tree_.recoDimu_vy);
  tree->Branch("recoDimu_vz",     &tree_.recoDimu_vz);
  tree->Branch("recoDimu_vtxchi2",     &tree_.recoDimu_vtxchi2);
  tree->Branch("recoDimu_vtxndof",     &tree_.recoDimu_vtxndof);
  tree->Branch("recoDimu_vtxprob",     &tree_.recoDimu_vtxprob);
  tree->Branch("recoDimu_index1",     &tree_.recoDimu_index1);
  tree->Branch("recoDimu_index2",     &tree_.recoDimu_index2);
  tree->Branch("recoDimu_pt1",     &tree_.recoDimu_pt1);
  tree->Branch("recoDimu_eta1",     &tree_.recoDimu_eta1);
  tree->Branch("recoDimu_phi1",     &tree_.recoDimu_phi1);
  tree->Branch("recoDimu_charge1",     &tree_.recoDimu_charge1);
  tree->Branch("recoDimu_mass1",     &tree_.recoDimu_mass1);
  tree->Branch("recoDimu_softID1",     &tree_.recoDimu_softID1);
  tree->Branch("recoDimu_pt2",     &tree_.recoDimu_pt2);
  tree->Branch("recoDimu_eta2",     &tree_.recoDimu_eta2);
  tree->Branch("recoDimu_phi2",     &tree_.recoDimu_phi2);
  tree->Branch("recoDimu_charge2",     &tree_.recoDimu_charge2);
  tree->Branch("recoDimu_mass2",     &tree_.recoDimu_mass2);
  tree->Branch("recoDimu_softID2",     &tree_.recoDimu_softID2);
  tree->Branch("recoDimu_pt",     &tree_.recoDimu_pt);
  tree->Branch("recoDimu_eta",     &tree_.recoDimu_eta);
  tree->Branch("recoDimu_phi",     &tree_.recoDimu_phi);
  tree->Branch("recoDimu_mass",     &tree_.recoDimu_mass);
  tree->Branch("recoDimu_massErr",     &tree_.recoDimu_massErr);


  tree->Branch("nEleReco", &tree_.nEleReco, "nEleReco/I");
  tree->Branch("nPFEleReco", &tree_.nPFEleReco, "nPFEleReco/I");
  tree->Branch("nLowPtEleReco", &tree_.nLowPtEleReco, "nLowPtEleReco/I");
  tree->Branch("recoEle_pt",     &tree_.recoEle_pt);
  tree->Branch("recoEle_mass",      &tree_.recoEle_mass);
  tree->Branch("recoEle_eta",&tree_.recoEle_eta);
  tree->Branch("recoEle_phi",&tree_.recoEle_phi);
  tree->Branch("recoEle_charge",&tree_.recoEle_charge);

  tree->Branch("recoEle_ptmode",     &tree_.recoEle_ptmode);
  tree->Branch("recoEle_etamode",     &tree_.recoEle_etamode);
  tree->Branch("recoEle_phimode",     &tree_.recoEle_phimode);

  tree->Branch("recoEle_p",     &tree_.recoEle_p);

  tree->Branch("recoEle_vx",&tree_.recoEle_vx);
  tree->Branch("recoEle_vy",&tree_.recoEle_vy);
  tree->Branch("recoEle_vz",&tree_.recoEle_vz);

  tree->Branch("recoEle_dR1",&tree_.recoEle_dR1);
  tree->Branch("recoEle_matchid1",&tree_.recoEle_matchid1);
  tree->Branch("recoEle_dR2",&tree_.recoEle_dR2);
  tree->Branch("recoEle_matchid2",&tree_.recoEle_matchid2);
  tree->Branch("recoEle_E_ecal_preReg",&tree_.recoEle_E_ecal_preReg);
  tree->Branch("recoEle_E_ecal_postReg",&tree_.recoEle_E_ecal_postReg);
  tree->Branch("recoEle_E_ecaltrk_preReg",&tree_.recoEle_E_ecaltrk_preReg);
  tree->Branch("recoEle_E_ecaltrk_postReg",&tree_.recoEle_E_ecaltrk_postReg);

  tree->Branch("recoEle_rawE",&tree_.recoEle_rawE);
  tree->Branch("recoEle_corrEcalE", &tree_.recoEle_corrEcalE);
  tree->Branch("recoEle_gsfTrkChi2",&tree_.recoEle_gsfTrkChi2);
  tree->Branch("recoEle_passConvVeto",&tree_.recoEle_passConvVeto);
  tree->Branch("recoEle_isPF",&tree_.recoEle_isPF);

  tree->Branch("recoEle_isLowPt",&tree_.recoEle_isLowPt);

  tree->Branch("recoEle_isPFoverlap",&tree_.recoEle_isPFoverlap);

  tree->Branch("recoEle_mvaPFValue",&tree_.recoEle_mvaPFValue);

  tree->Branch("recoEle_mvaValue",&tree_.recoEle_mvaValue);


  tree->Branch("nDieleReco", &tree_.nDieleReco, "nDieleReco/I");
  tree->Branch("recoDiele_vx",     &tree_.recoDiele_vx);
  tree->Branch("recoDiele_vy",     &tree_.recoDiele_vy);
  tree->Branch("recoDiele_vz",     &tree_.recoDiele_vz);
  tree->Branch("recoDiele_vtxchi2",     &tree_.recoDiele_vtxchi2);
  tree->Branch("recoDiele_vtxndof",     &tree_.recoDiele_vtxndof);
  tree->Branch("recoDiele_vtxprob",     &tree_.recoDiele_vtxprob);
  tree->Branch("recoDiele_index1",     &tree_.recoDiele_index1);
  tree->Branch("recoDiele_index2",     &tree_.recoDiele_index2);
  tree->Branch("recoDiele_pt1",     &tree_.recoDiele_pt1);
  tree->Branch("recoDiele_eta1",     &tree_.recoDiele_eta1);
  tree->Branch("recoDiele_phi1",     &tree_.recoDiele_phi1);
  tree->Branch("recoDiele_charge1",     &tree_.recoDiele_charge1);
  tree->Branch("recoDiele_mass1",     &tree_.recoDiele_mass1);
  tree->Branch("recoDiele_mvaValue1",     &tree_.recoDiele_mvaValue1);
  tree->Branch("recoDiele_mvaPFValue1",     &tree_.recoDiele_mvaPFValue1);
  tree->Branch("recoDiele_isPF1",     &tree_.recoDiele_isPF1);
  tree->Branch("recoDiele_isLowPt1",     &tree_.recoDiele_isLowPt1);
  tree->Branch("recoDiele_isPFoverlap1",     &tree_.recoDiele_isPFoverlap1);
  tree->Branch("recoDiele_pt2",     &tree_.recoDiele_pt2);
  tree->Branch("recoDiele_eta2",     &tree_.recoDiele_eta2);
  tree->Branch("recoDiele_phi2",     &tree_.recoDiele_phi2);
  tree->Branch("recoDiele_charge2",     &tree_.recoDiele_charge2);
  tree->Branch("recoDiele_mass2",     &tree_.recoDiele_mass2);
  tree->Branch("recoDiele_mvaValue2",     &tree_.recoDiele_mvaValue2);
  tree->Branch("recoDiele_mvaPFValue2",     &tree_.recoDiele_mvaPFValue2);
  tree->Branch("recoDiele_isPF2",     &tree_.recoDiele_isPF2);
  tree->Branch("recoDiele_isLowPt2",     &tree_.recoDiele_isLowPt2);
  tree->Branch("recoDiele_isPFoverlap2",     &tree_.recoDiele_isPFoverlap2);
  tree->Branch("recoDiele_pt",     &tree_.recoDiele_pt);
  tree->Branch("recoDiele_eta",     &tree_.recoDiele_eta);
  tree->Branch("recoDiele_phi",     &tree_.recoDiele_phi);
  tree->Branch("recoDiele_mass",     &tree_.recoDiele_mass);
  tree->Branch("recoDiele_massErr",     &tree_.recoDiele_massErr);
  
  tree->Branch("recoDiele_pt1mode",     &tree_.recoDiele_pt1mode);
  tree->Branch("recoDiele_eta1mode",     &tree_.recoDiele_eta1mode);
  tree->Branch("recoDiele_phi1mode",     &tree_.recoDiele_phi1mode);
  tree->Branch("recoDiele_pt2mode",     &tree_.recoDiele_pt2mode);
  tree->Branch("recoDiele_eta2mode",     &tree_.recoDiele_eta2mode);
  tree->Branch("recoDiele_phi2mode",     &tree_.recoDiele_phi2mode);

  */  


  tree->Branch("nSoftDimu", &tree_.nSoftDimu, "nSoftDimu/I");
  tree->Branch("nMediumDimu", &tree_.nMediumDimu, "nMediumDimu/I");

  tree->Branch("nTQReco", &tree_.nTQReco, "nTQReco/I");
  tree->Branch("recoTQ_pt"            ,&tree_.recoTQ_pt);		      	
  tree->Branch("recoTQ_eta"           ,&tree_.recoTQ_eta);		      
  tree->Branch("recoTQ_phi"           ,&tree_.recoTQ_phi);		      
  tree->Branch("recoTQ_mass"          ,&tree_.recoTQ_mass);		      
  tree->Branch("recoTQ_massErr"       ,&tree_.recoTQ_massErr);	  	      
  tree->Branch("recoTQ_vtxchi2"       ,&tree_.recoTQ_vtxchi2);	  	      
  tree->Branch("recoTQ_vtxndof"       ,&tree_.recoTQ_vtxndof);	  	      
  tree->Branch("recoTQ_vtxprob"       ,&tree_.recoTQ_vtxprob);	  	      


tree->Branch("recoTQ_Y1pt"            ,&tree_.recoTQ_Y1pt);		      	
tree->Branch("recoTQ_Y1eta"           ,&tree_.recoTQ_Y1eta);		      
tree->Branch("recoTQ_Y1phi"           ,&tree_.recoTQ_Y1phi);		      
tree->Branch("recoTQ_Y1mass"          ,&tree_.recoTQ_Y1mass);		      
tree->Branch("recoTQ_Y1massErr"       ,&tree_.recoTQ_Y1massErr);	  	      
tree->Branch("recoTQ_Y1vtxchi2"       ,&tree_.recoTQ_Y1vtxchi2);	  	      
tree->Branch("recoTQ_Y1vtxndof"       ,&tree_.recoTQ_Y1vtxndof);	  	      
tree->Branch("recoTQ_Y1vtxprob"       ,&tree_.recoTQ_Y1vtxprob);	  	      



tree->Branch("recoTQ_Y2pt"            ,&tree_.recoTQ_Y2pt);		      	
tree->Branch("recoTQ_Y2eta"           ,&tree_.recoTQ_Y2eta);		      
tree->Branch("recoTQ_Y2phi"           ,&tree_.recoTQ_Y2phi);		      
tree->Branch("recoTQ_Y2mass"          ,&tree_.recoTQ_Y2mass);		      
tree->Branch("recoTQ_Y2massErr"       ,&tree_.recoTQ_Y2massErr);	  	      
tree->Branch("recoTQ_Y2vtxchi2"       ,&tree_.recoTQ_Y2vtxchi2);	  	      
tree->Branch("recoTQ_Y2vtxndof"       ,&tree_.recoTQ_Y2vtxndof);	  	      
tree->Branch("recoTQ_Y2vtxprob"       ,&tree_.recoTQ_Y2vtxprob);	  	      
                                      					
                                      					
 tree->Branch("recoTQ_leptype1"     ,&tree_.recoTQ_leptype1);	      	
 tree->Branch("recoTQ_pt1"          ,&tree_.recoTQ_pt1   );		      
 tree->Branch("recoTQ_eta1"         ,&tree_.recoTQ_eta1  );		      
 tree->Branch("recoTQ_phi1"         ,&tree_.recoTQ_phi1  );		      
 tree->Branch("recoTQ_charge1"      ,&tree_.recoTQ_charge1  );	  	      
 tree->Branch("recoTQ_mass1"        ,&tree_.recoTQ_mass1 );	      	
 tree->Branch("recoTQ_softID1"      ,&tree_.recoTQ_softID1 );	      	
 tree->Branch("recoTQ_mediumID1"      ,&tree_.recoTQ_mediumID1 );	      	
				                                        
 tree->Branch("recoTQ_leptype2"     ,&tree_.recoTQ_leptype2);	      	
 tree->Branch("recoTQ_pt2"          ,&tree_.recoTQ_pt2   );		      
 tree->Branch("recoTQ_eta2"         ,&tree_.recoTQ_eta2  );		      
 tree->Branch("recoTQ_phi2"         ,&tree_.recoTQ_phi2  );		      
 tree->Branch("recoTQ_charge2"      ,&tree_.recoTQ_charge2  );	  	      
 tree->Branch("recoTQ_mass2"        ,&tree_.recoTQ_mass2 );	      	
 tree->Branch("recoTQ_softID2"      ,&tree_.recoTQ_softID2 );	      	
 tree->Branch("recoTQ_mediumID2"      ,&tree_.recoTQ_mediumID2 );	      	

  tree->Branch("recoTQ_isTrigMatch1"      ,&tree_.recoTQ_isTrigMatch1 );
  tree->Branch("recoTQ_drTrigMatch1"      ,&tree_.recoTQ_drTrigMatch1 );
  tree->Branch("recoTQ_isTrigMatch2"      ,&tree_.recoTQ_isTrigMatch2 );
  tree->Branch("recoTQ_drTrigMatch2"      ,&tree_.recoTQ_drTrigMatch2 );

 tree->Branch("recoTQ_leptype3"     ,&tree_.recoTQ_leptype3);	      	
 tree->Branch("recoTQ_pt3"          ,&tree_.recoTQ_pt3   );		      
 tree->Branch("recoTQ_pt3mode"          ,&tree_.recoTQ_pt3mode   );		      
 tree->Branch("recoTQ_eta3"         ,&tree_.recoTQ_eta3  );		      
 tree->Branch("recoTQ_phi3"         ,&tree_.recoTQ_phi3  );		      
 tree->Branch("recoTQ_charge3"      ,&tree_.recoTQ_charge3  );	  	      
 tree->Branch("recoTQ_mass3"        ,&tree_.recoTQ_mass3 );	      	
 tree->Branch("recoTQ_softID3"      ,&tree_.recoTQ_softID3 );	      	
 tree->Branch("recoTQ_mediumID3"      ,&tree_.recoTQ_mediumID3 );	      	
 tree->Branch("recoTQ_mvaValue3"    ,&tree_.recoTQ_mvaValue3);	      	
 tree->Branch("recoTQ_mvaPFValue3"  ,&tree_.recoTQ_mvaPFValue3);	      
 tree->Branch("recoTQ_isPF3"        ,&tree_.recoTQ_isPF3   );		      
 tree->Branch("recoTQ_isLowPt3"     ,&tree_.recoTQ_isLowPt3);	      	
 tree->Branch("recoTQ_isPFoverlap3" ,&tree_.recoTQ_isPFoverlap3);	      
				                                        
 tree->Branch("recoTQ_leptype4"     ,&tree_.recoTQ_leptype4);	      	
 tree->Branch("recoTQ_pt4"          ,&tree_.recoTQ_pt4   );		      
 tree->Branch("recoTQ_pt4mode"          ,&tree_.recoTQ_pt4mode   );		      
 tree->Branch("recoTQ_eta4"         ,&tree_.recoTQ_eta4  );		      
 tree->Branch("recoTQ_phi4"         ,&tree_.recoTQ_phi4  );		      
 tree->Branch("recoTQ_charge4"      ,&tree_.recoTQ_charge4  );	  	      
 tree->Branch("recoTQ_mass4"        ,&tree_.recoTQ_mass4 );	      	
 tree->Branch("recoTQ_softID4"      ,&tree_.recoTQ_softID4 );	      	
 tree->Branch("recoTQ_mediumID4"      ,&tree_.recoTQ_mediumID4 );	      	
 tree->Branch("recoTQ_mvaValue4"    ,&tree_.recoTQ_mvaValue4);	      	
 tree->Branch("recoTQ_mvaPFValue4"  ,&tree_.recoTQ_mvaPFValue4);	      
 tree->Branch("recoTQ_isPF4"        ,&tree_.recoTQ_isPF4   );		      
 tree->Branch("recoTQ_isLowPt4"     ,&tree_.recoTQ_isLowPt4);	      	
 tree->Branch("recoTQ_isPFoverlap4" ,&tree_.recoTQ_isPFoverlap4);	      
                                      




}

void
TQGenAnalyzer::endJob()
{
}

void
TQGenAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}


void TQGenAnalyzer::initTreeStructure()
{
  
  tree_.run= -500.;
  tree_.lumi= -500.;
  tree_.event= 0.;


}

void TQGenAnalyzer::clearVectors()
{

  tree_.genLep_pt.clear();
  tree_.genLep_mass.clear();
  tree_.genLep_eta.clear();
  tree_.genLep_phi.clear();
  tree_.genLep_pdgId.clear();
  tree_.genMom_pt.clear();
  tree_.genMom_mass.clear();
  tree_.genMom_eta.clear();
  tree_.genMom_phi.clear();
  tree_.genMom_pdgId.clear();

  /*
  tree_.recoMu_pt.clear();
  tree_.recoMu_mass.clear();
  tree_.recoMu_eta.clear();
  tree_.recoMu_phi.clear();
  tree_.recoMu_charge.clear();
  tree_.recoMu_dR1.clear();
  tree_.recoMu_dR2.clear();
  tree_.recoMu_matchid1.clear();
  tree_.recoMu_matchid2.clear();
  tree_.recoMu_looseID.clear();
  tree_.recoMu_softID.clear();
  tree_.recoMu_nTrkLayers.clear();
  tree_.recoMu_nPixLayers.clear();
  tree_.recoMu_isHQ.clear();
  tree_.recoMu_dxy.clear();
  tree_.recoMu_dz.clear();

  tree_.recoDimu_vx.clear();
  tree_.recoDimu_vy.clear() ;
  tree_.recoDimu_vz.clear();
  tree_.recoDimu_vtxchi2.clear();
  tree_.recoDimu_vtxndof.clear();
  tree_.recoDimu_vtxprob.clear();
  tree_.recoDimu_index1.clear();
  tree_.recoDimu_index2.clear();
  tree_.recoDimu_pt1.clear();
  tree_.recoDimu_eta1.clear();
  tree_.recoDimu_phi1.clear();
  tree_.recoDimu_charge1.clear();
  tree_.recoDimu_mass1.clear();
  tree_.recoDimu_softID1.clear();
  tree_.recoDimu_pt2.clear();
  tree_.recoDimu_eta2.clear();
  tree_.recoDimu_phi2.clear();
  tree_.recoDimu_charge2.clear();
  tree_.recoDimu_mass2.clear();
  tree_.recoDimu_softID2.clear();
  tree_.recoDimu_pt.clear();
  tree_.recoDimu_eta.clear();
  tree_.recoDimu_phi.clear();
  tree_.recoDimu_mass.clear();
  tree_.recoDimu_massErr.clear();


  tree_.recoEle_pt.clear();
  tree_.recoEle_mass.clear();
  tree_.recoEle_eta.clear();
  tree_.recoEle_phi.clear();
  tree_.recoEle_charge.clear();

  tree_.recoEle_ptmode.clear();
  tree_.recoEle_etamode.clear();
  tree_.recoEle_phimode.clear();

  tree_.recoEle_p.clear();

  tree_.recoEle_vx.clear();
  tree_.recoEle_vy.clear();
  tree_.recoEle_vz.clear();

  tree_.recoEle_dR1.clear();
  tree_.recoEle_dR2.clear();
  tree_.recoEle_matchid1.clear();
  tree_.recoEle_matchid2.clear();
  tree_.recoEle_E_ecal_preReg.clear();
  tree_.recoEle_E_ecal_postReg.clear();
  tree_.recoEle_E_ecaltrk_preReg.clear();
  tree_.recoEle_E_ecaltrk_postReg.clear();

  tree_.recoEle_rawE.clear();
  tree_.recoEle_corrEcalE.clear();
  tree_.recoEle_gsfTrkChi2.clear();
  tree_.recoEle_passConvVeto.clear();
  tree_.recoEle_isPF.clear();

  tree_.recoEle_isLowPt.clear();
  tree_.recoEle_isPFoverlap.clear();

  tree_.recoEle_mvaPFValue.clear();
  
  tree_.recoEle_mvaValue.clear();


  tree_.recoDiele_vx.clear();
  tree_.recoDiele_vy.clear() ;
  tree_.recoDiele_vz.clear();
  tree_.recoDiele_vtxchi2.clear();
  tree_.recoDiele_vtxndof.clear();
  tree_.recoDiele_vtxprob.clear();
  tree_.recoDiele_index1.clear();
  tree_.recoDiele_index2.clear();
  tree_.recoDiele_pt1.clear();
  tree_.recoDiele_eta1.clear();
  tree_.recoDiele_phi1.clear();
  tree_.recoDiele_charge1.clear();
  tree_.recoDiele_mass1.clear();
  tree_.recoDiele_mvaValue1.clear();
  tree_.recoDiele_mvaPFValue1.clear();
  tree_.recoDiele_isPF1.clear();
  tree_.recoDiele_isLowPt1.clear();
  tree_.recoDiele_isPFoverlap1.clear();
  tree_.recoDiele_pt2.clear();
  tree_.recoDiele_eta2.clear();
  tree_.recoDiele_phi2.clear();
  tree_.recoDiele_charge2.clear();
  tree_.recoDiele_mass2.clear();
  tree_.recoDiele_mvaValue1.clear();
  tree_.recoDiele_mvaPFValue1.clear();

  tree_.recoDiele_isPF2.clear();
  tree_.recoDiele_isLowPt2.clear();
  tree_.recoDiele_isPFoverlap2.clear();
  tree_.recoDiele_pt.clear();
  tree_.recoDiele_eta.clear();
  tree_.recoDiele_phi.clear();
  tree_.recoDiele_mass.clear();
  tree_.recoDiele_massErr.clear();

  tree_.recoDiele_pt1mode.clear();
  tree_.recoDiele_eta1mode.clear();
  tree_.recoDiele_phi1mode.clear();
  tree_.recoDiele_pt2mode.clear();
  tree_.recoDiele_eta2mode.clear();
  tree_.recoDiele_phi2mode.clear();
  */  
tree_.recoTQ_pt.clear();		      	
tree_.recoTQ_eta.clear();		
tree_.recoTQ_phi.clear();		
tree_.recoTQ_mass.clear();		
tree_.recoTQ_massErr.clear();	  	
tree_.recoTQ_vtxchi2.clear();	  	
tree_.recoTQ_vtxndof.clear();	  	
tree_.recoTQ_vtxprob.clear();	  	


tree_.recoTQ_Y1pt.clear();		      	
tree_.recoTQ_Y1eta.clear();		
tree_.recoTQ_Y1phi.clear();		
tree_.recoTQ_Y1mass.clear();		
tree_.recoTQ_Y1massErr.clear();	  	
tree_.recoTQ_Y1vtxchi2.clear();	  	
tree_.recoTQ_Y1vtxndof.clear();	  	
tree_.recoTQ_Y1vtxprob.clear();	  	


tree_.recoTQ_Y2pt.clear();		      	
tree_.recoTQ_Y2eta.clear();		
tree_.recoTQ_Y2phi.clear();		
tree_.recoTQ_Y2mass.clear();		
tree_.recoTQ_Y2massErr.clear();	  	
tree_.recoTQ_Y2vtxchi2.clear();	  	
tree_.recoTQ_Y2vtxndof.clear();	  	
tree_.recoTQ_Y2vtxprob.clear();	  	
					
					
tree_.recoTQ_leptype1.clear();	      	
tree_.recoTQ_pt1   .clear();		
 tree_.recoTQ_eta1  .clear();		
tree_.recoTQ_phi1  .clear();		
tree_.recoTQ_charge1  .clear();	  	
tree_.recoTQ_mass1 .clear();	      	
tree_.recoTQ_softID1 .clear();	      	
tree_.recoTQ_mediumID1 .clear();	      	
                                  
tree_.recoTQ_leptype2.clear();	      	
tree_.recoTQ_pt2   .clear();		
tree_.recoTQ_eta2  .clear();		
tree_.recoTQ_phi2  .clear();		
 tree_.recoTQ_charge2  .clear();	  	
 tree_.recoTQ_mass2 .clear();	      	
 tree_.recoTQ_softID2 .clear();	      	
tree_.recoTQ_mediumID2 .clear();	      	
 
 tree_.recoTQ_isTrigMatch1.clear();
 tree_.recoTQ_drTrigMatch1.clear();
 tree_.recoTQ_isTrigMatch2.clear();
 tree_.recoTQ_drTrigMatch2.clear();

 tree_.recoTQ_leptype3.clear();	      	
tree_.recoTQ_pt3   .clear();		
tree_.recoTQ_pt3mode   .clear();		
tree_.recoTQ_eta3  .clear();		
tree_.recoTQ_phi3  .clear();		
tree_.recoTQ_charge3  .clear();	  	
tree_.recoTQ_mass3 .clear();	      	
tree_.recoTQ_softID3 .clear();	      	
tree_.recoTQ_mediumID3 .clear();	      	
tree_.recoTQ_mvaValue3.clear();	      	
tree_.recoTQ_mvaPFValue3.clear();	
tree_.recoTQ_isPF3   .clear();		
tree_.recoTQ_isLowPt3.clear();	      	
tree_.recoTQ_isPFoverlap3.clear();	
                                  
tree_.recoTQ_leptype4.clear();	      	
tree_.recoTQ_pt4   .clear();		
tree_.recoTQ_pt4mode   .clear();		
tree_.recoTQ_eta4  .clear();		
tree_.recoTQ_phi4  .clear();		
tree_.recoTQ_charge4  .clear();	  	
tree_.recoTQ_mass4 .clear();	      	
tree_.recoTQ_softID4 .clear();	      	
tree_.recoTQ_mediumID4 .clear();	      	
tree_.recoTQ_mvaValue4.clear();	      	
tree_.recoTQ_mvaPFValue4.clear();	
tree_.recoTQ_isPF4   .clear();		
tree_.recoTQ_isLowPt4.clear();	      	
tree_.recoTQ_isPFoverlap4.clear();	







}

float TQGenAnalyzer::GetPUWeight(int npu,int year) {
  
  float weight=1;
  if (sampleIndex_<=0 && npu<100){
    if(year==2016)weight = puweights2016_[npu];
    if(year==2017)weight = puweights2017_[npu];
    if(year==2018)weight = puweights2018_[npu];
    if(year==0)weight = puweightsALL_[npu];

  }

  return weight;
}




void TQGenAnalyzer::SetPuWeights(int year,double* puw_array) {

  std::string puWeightFile;
  if(year==2016) puWeightFile="pileup_2016.root";
  else   if(year==2017) puWeightFile="pileup_2017.root";
  else   if(year==2018) puWeightFile="pileup_2018.root";
  else   if(year==0) puWeightFile="pileup_ALL.root";
  puWeightFile="pileup_2018.root";
  if (puWeightFile == "") {
    std::cout << "you need a weights file to use this function" << std::endl;
    return;
  }

  std::cout << "PU REWEIGHTING:: Using file " << puWeightFile << std::endl;

  TFile *f_pu  = new TFile(puWeightFile.c_str(),"READ");
  f_pu->cd();

  TH1D* pu_data = (TH1D*) f_pu->Get("pileup");
  //  pu_data->Sumw2();
  pu_data->Scale(1./pu_data->Integral());

  double MC_weights_2016UL[100]={1.00402360149e-05, 5.76498797172e-05, 7.37891400294e-05, 0.000110932895295, 0.000158857714773,
				 0.000368637432599, 0.000893114107873, 0.00189700774575, 0.00358880167437, 0.00636052573486,
				 0.0104173961179, 0.0158122597405, 0.0223785660712, 0.0299186888073, 0.0380275944896,
				 0.0454313901624, 0.0511181088317, 0.0547434577348, 0.0567906239028, 0.0577145461461,
				 0.0578176902735, 0.0571251566494, 0.0555456541498, 0.053134383488, 0.0501519041462,
				 0.0466815838899, 0.0429244592524, 0.0389566776898, 0.0348507152776, 0.0307356862528,
				 0.0267712092206, 0.0229720184534, 0.0193388653099, 0.0159602510813, 0.0129310510552,
				 0.0102888654183, 0.00798782770975, 0.00606651703058, 0.00447820948367, 0.00321589786478,
				 0.0022450422045, 0.00151447388514, 0.000981183695515, 0.000609670479759, 0.000362193408119,
				 0.000211572646801, 0.000119152364744, 6.49133515399e-05, 3.57795801581e-05, 1.99043569043e-05,
				 1.13639319832e-05, 6.49624103579e-06, 3.96626216416e-06, 2.37910222874e-06, 1.50997403362e-06,
				 1.09816650247e-06, 7.31298519122e-07, 6.10398791529e-07, 3.74845774388e-07, 2.65177281359e-07,
				 2.01923536742e-07, 1.39347583555e-07, 8.32600052913e-08, 6.04932421298e-08, 6.52536630583e-08,
				 5.90574603808e-08, 2.29162474068e-08, 1.97294602668e-08, 1.7731096903e-08, 3.57547932012e-09,
				 1.35039815662e-09, 8.50071242076e-09, 5.0279187473e-09, 4.93736669066e-10, 8.13919708923e-10,
				 5.62778926097e-09, 5.15140589469e-10, 8.21676746568e-10, 0.0, 1.49166873577e-09,
				 8.43517992503e-09, 0.0, 0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0, 0.0,0.0};
  

  double MC_weights_2017UL[100]={1.1840841518e-05, 3.46661037703e-05, 8.98772521472e-05, 7.47400487733e-05, 0.000123005176624,
				 0.000156501700614, 0.000154660478659, 0.000177496185603, 0.000324149805611, 0.000737524009713,
				 0.00140432980253, 0.00244424508696, 0.00380027898037, 0.00541093042612, 0.00768803501793,
				 0.010828224552, 0.0146608623707, 0.01887739113, 0.0228418813823, 0.0264817796874,
				 0.0294637401336, 0.0317960986171, 0.0336645950831, 0.0352638818387, 0.036869429333,
				 0.0382797316998, 0.039386705577, 0.0398389681346, 0.039646211131, 0.0388392805703,
				 0.0374195678161, 0.0355377892706, 0.0333383902828, 0.0308286549265, 0.0282914440969,
				 0.0257860718304, 0.02341635055, 0.0213126338243, 0.0195035612803, 0.0181079838989,
				 0.0171991315458, 0.0166377598339, 0.0166445341361, 0.0171943735369, 0.0181980997278,
				 0.0191339792146, 0.0198518804356, 0.0199714909193, 0.0194616474094, 0.0178626975229,
				 0.0153296785464, 0.0126789254325, 0.0100766041988, 0.00773867100481, 0.00592386091874,
				 0.00434706240169, 0.00310217013427, 0.00213213401899, 0.0013996000761, 0.000879148859271,
				 0.000540866009427, 0.000326115560156, 0.000193965828516, 0.000114607606623, 6.74262828734e-05,
				 3.97805301078e-05, 2.19948704638e-05, 9.72007976207e-06, 4.26179259146e-06, 2.80015581327e-06,
				 1.14675436465e-06, 2.52452411995e-07, 9.08394910044e-08, 1.14291987912e-08, 0.0,
				 0.0, 0.0, 0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0, 0.0, 0.0,
				 0.0, 0.0, 0.0, 0.0,0.0};

  double MC_weights_2018UL[100]={8.89374611122e-07, 1.1777062868e-05, 3.99725585118e-05, 0.000129888015252, 0.000265224848687,
				 0.000313088635109, 0.000353781668514, 0.000508787237162, 0.000873670065767, 0.00147166880932,
				 0.00228230649018, 0.00330375581273, 0.00466047608406, 0.00624959203029, 0.00810375867901,
				 0.010306521821, 0.0129512453978, 0.0160303925502, 0.0192913204592, 0.0223108613632,
				 0.0249798930986, 0.0273973789867, 0.0294402350483, 0.031029854302, 0.0324583524255,
				 0.0338264469857, 0.0351267479019, 0.0360320204259, 0.0367489568401, 0.0374133183052,
				 0.0380352633799, 0.0386200967002, 0.039124376968, 0.0394201612616, 0.0394673457109,
				 0.0391705388069, 0.0384758587461, 0.0372984548399, 0.0356497876549, 0.0334655175178,
				 0.030823567063, 0.0278340752408, 0.0246009685048, 0.0212676009273, 0.0180250593982,
				 0.0149129830776, 0.0120582333486, 0.00953400069415, 0.00738546929512, 0.00563442079939,
				 0.00422052915668, 0.00312446316347, 0.00228717533955, 0.00164064894334, 0.00118425084792,
				 0.000847785826565, 0.000603466454784, 0.000419347268964, 0.000291768785963, 0.000199761337863,
				 0.000136624574661, 9.46855200945e-05, 6.80243180179e-05, 4.94806013765e-05, 3.53122628249e-05,
				 2.556765786e-05, 1.75845711623e-05, 1.23828210848e-05, 9.31669724108e-06, 6.0713272037e-06,
				 3.95387384933e-06, 2.02760874107e-06, 1.22535149516e-06, 9.79612472109e-07, 7.61730246474e-07,
				 4.2748847738e-07, 2.41170461205e-07, 1.38701083552e-07, 3.37678010922e-08, 0.0,
				 0.01e-07, 0.01e-07, 0.01e-07, 0.01e-07, 0.01e-07,
				 0.01e-07, 0.01e-07, 0.01e-07, 0.01e-07, 0.01e-07,
				 0.01e-07, 0.01e-07, 0.01e-07, 0.01e-07, 0.01e-07,
				 0.01e-07, 0.01e-07, 0.01e-07, 0.01e-07, 0.01e-07};


  TH1F* pu_MC_2018UL = new TH1F("pu_MC_2018UL","",100,0,100);
  for(int i=0;i<100;i++) pu_MC_2018UL->SetBinContent(i+1,MC_weights_2018UL[i]);
  //pu_MC_2018UL->Sumw2();
  pu_MC_2018UL->Scale(1./pu_MC_2018UL->Integral());



  TH1F *myClone = (TH1F*)pu_data->Clone("myClone");
  //  myClone->Sumw2();
  myClone->Divide(pu_MC_2018UL);
  myClone->SetTitle("weights");
  myClone->SetName("weights");
  myClone->Scale(1./myClone->Integral());

  TH1F* weightedNpu= (TH1F*)pu_MC_2018UL->Clone("weightedNvtx");
  //  weightedNpu->Sumw2();
  weightedNpu->Multiply(myClone);

  TH1F* weights = (TH1F*)myClone->Clone("rescaledWeights");
  //  weights->Sumw2();
  weights->Scale( pu_MC_2018UL->Integral() / weightedNpu->Integral() );
  

  for(int i=0;i<100;i++){
    puw_array[i]=weights->GetBinContent(i+1);
  }

    
}




float TQGenAnalyzer::GetNVTXWeight(int nvtx,int year) {
  
  float weight=1;
  if (sampleIndex_<=0 && nvtx<100){
    if(year==2016)weight = nvtxweights2016_[nvtx];
    if(year==2017)weight = nvtxweights2017_[nvtx];
    if(year==2018)weight = nvtxweights2018_[nvtx];
    if(year==0)weight = nvtxweightsALL_[nvtx];

  }

  return weight;
}




void TQGenAnalyzer::SetNVTXWeights(int year,double* puw_array) {

  std::string puWeightFile;
  if(year==2016) puWeightFile="pileup_2016.root";
  else   if(year==2017) puWeightFile="pileup_2017.root";
  else   if(year==2018) puWeightFile="pileup_2018.root";
  else   if(year==0) puWeightFile="pileup_ALL.root";
  puWeightFile="nvtx_weights_2018UL.root";
  if (puWeightFile == "") {
    std::cout << "you need a weights file to use this function" << std::endl;
    return;
  }

  std::cout << "NVTX REWEIGHTING:: Using file " << puWeightFile << std::endl;

  TFile *f_pu  = new TFile(puWeightFile.c_str(),"READ");
  f_pu->cd();

  TH1F*  weights= (TH1F*) f_pu->Get("rescaledWeights");

  for(int i=0;i<100;i++){
    puw_array[i]=weights->GetBinContent(i+1);
  }

    
}




DEFINE_FWK_MODULE(TQGenAnalyzer);
