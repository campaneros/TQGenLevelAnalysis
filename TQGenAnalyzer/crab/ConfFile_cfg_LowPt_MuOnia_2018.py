import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes
import FWCore.ParameterSet.VarParsing as VarParsing
from PhysicsTools.NanoAOD.common_cff import *

process = cms.Process("GenAnalysis")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("Configuration.Geometry.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load("Geometry.CaloEventSetup.CaloTowerConstituents_cfi")
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")

process.ntuplizer_seq = cms.Sequence()


#1. setting GT
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '106X_dataRun2_v24')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",
                                # replace 'myfile.root' with the source file you want to use
                                fileNames = cms.untracked.vstring(
#                                    'file:/afs/cern.ch/work/m/mcampana/public/Tetraquark/file_Livia/3BD19FEE-D15E-E94A-8BD6-6E9FD51C30DD.root'
'/store/data/Run2018B/MuOnia/MINIAOD/UL2018_MiniAODv2-v1/30001/1DEB10DF-DED6-EB41-9F81-E9FAC4C14E50.root',
#'/store/data/Run2018B/MuOnia/MINIAOD/UL2018_MiniAODv2-v1/30001/1FCA1F99-E4E6-4245-B805-6C129C6E1999.root',
#'/store/data/Run2018B/MuOnia/MINIAOD/UL2018_MiniAODv2-v1/30001/2CE85E03-23C8-664B-A387-A609BF45DBFA.root',
#'/store/data/Run2018B/MuOnia/MINIAOD/UL2018_MiniAODv2-v1/30001/4E420F59-A2A1-544B-B7B6-D020C8833EE2.root',
#'/store/data/Run2018B/MuOnia/MINIAOD/UL2018_MiniAODv2-v1/30001/57DF48CC-2B91-544F-BCA8-A7D6C689BF04.root',
#'/store/data/Run2018B/MuOnia/MINIAOD/UL2018_MiniAODv2-v1/30001/5A489C88-595E-A748-B3DC-155619EFB607.root',
#'/store/data/Run2018B/MuOnia/MINIAOD/UL2018_MiniAODv2-v1/30001/5D12A107-F424-864D-AFD4-486FE7E29D0D.root',
#'/store/data/Run2018B/MuOnia/MINIAOD/UL2018_MiniAODv2-v1/30001/6A6D66E6-6641-9E40-9D65-AB861267DA3E.root'


              )
                            )

process.TFileService = cms.Service("TFileService",
    fileName = cms.string("ntuple_tetraquarks_wLowPt.root")
)


#2. setting input variables
options = VarParsing.VarParsing('analysis')
options.register ('isMC',
                  False, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.bool,           # string, int, float, bool
                  "Bool isMC")
options.register ('isSignal',
                  False, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.bool,           # string, int, float, bool
                  "Bool isSignal")
options.register ('isUpsilon',
                  True, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.bool,           # string, int, float, bool
                  "Bool isSignal")
options.parseArguments()

if options.isMC and options.isSignal :
    print'Sample is MC Signal'
    xsec=1.
if not options.isMC : xsec=1.

if options.isMC and not options.isSignal : print'Sample is MC Background'
if not options.isMC  : print'Sample is Data'

if options.isMC and options.isSignal : index = 0
if options.isMC and not options.isSignal : index = -100
if not options.isMC : index=100

year=2018
if options.isUpsilon :
    massRef=9.46
else:
    massRef=3.09

#3. setting up post reco tools from EGM to have all IDs and SS
from EgammaUser.EgammaPostRecoTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,era='2018-Prompt')  



#4. setting json file
if (options.isMC==False):
    print "applying json"
    process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
    #change json below once you run on new data
    JSONfile = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/Legacy_2018/Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt'
    myLumis = LumiList.LumiList(filename = JSONfile).getCMSSWString().split(',')
    process.source.lumisToProcess.extend(myLumis)
#    print myLumis



#5. setting regression
process.GlobalTag.toGet = cms.VPSet(
cms.PSet(record = cms.string("GBRDWrapperRcd"),
         label = cms.untracked.string("gsfElectron_eb_ecalOnly_05To50_mean"),
         tag = cms.string("gsfElectron_eb_ecalOnly_05To50_mean_2018V1"),
         connect = cms.string("sqlite_file:lowPtEleReg_2018_02062020_nv.db")),
cms.PSet(record = cms.string("GBRDWrapperRcd"),
         label = cms.untracked.string("gsfElectron_ee_ecalOnly_05To50_mean"),
         tag = cms.string("gsfElectron_ee_ecalOnly_05To50_mean_2018V1"),
         connect = cms.string("sqlite_file:lowPtEleReg_2018_02062020_nv.db")),
cms.PSet(record = cms.string("GBRDWrapperRcd"),
         label = cms.untracked.string("gsfElectron_eb_ecalOnly_05To50_sigma"),
         tag = cms.string("gsfElectron_eb_ecalOnly_05To50_sigma_2018V1"),
         connect = cms.string("sqlite_file:lowPtEleReg_2018_02062020_nv.db")),
cms.PSet(record = cms.string("GBRDWrapperRcd"),
         label = cms.untracked.string("gsfElectron_ee_ecalOnly_05To50_sigma"),
         tag = cms.string("gsfElectron_ee_ecalOnly_05To50_sigma_2018V1"),
         connect = cms.string("sqlite_file:lowPtEleReg_2018_02062020_nv.db")),
cms.PSet(record = cms.string("GBRDWrapperRcd"),
         label = cms.untracked.string("gsfElectron_eb_ecalTrk_05To50_mean"),
         tag = cms.string("gsfElectron_eb_ecalTrk_05To50_mean_2018V1"),
         connect = cms.string("sqlite_file:lowPtEleReg_2018_02062020_nv.db")),
cms.PSet(record = cms.string("GBRDWrapperRcd"),
         label = cms.untracked.string("gsfElectron_ee_ecalTrk_05To50_mean"),
         tag = cms.string("gsfElectron_ee_ecalTrk_05To50_mean_2018V1"),
         connect = cms.string("sqlite_file:lowPtEleReg_2018_02062020_nv.db")),
cms.PSet(record = cms.string("GBRDWrapperRcd"),
         label = cms.untracked.string("gsfElectron_eb_ecalTrk_05To50_sigma"),
         tag = cms.string("gsfElectron_eb_ecalTrk_05To50_sigma_2018V1"),
         connect = cms.string("sqlite_file:lowPtEleReg_2018_02062020_nv.db")),
cms.PSet(record = cms.string("GBRDWrapperRcd"),
         label = cms.untracked.string("gsfElectron_ee_ecalTrk_05To50_sigma"),
         tag = cms.string("gsfElectron_ee_ecalTrk_05To50_sigma_2018V1"),
         connect = cms.string("sqlite_file:lowPtEleReg_2018_02062020_nv.db")))


#from RecoEgamma.EgammaTools.regressionModifierNoPhoReg_cfi import regressionModifier106XUL
from RecoEgamma.EgammaTools.regressionModifier_cfi import regressionModifier106XUL
_gsfRegressionModifier = regressionModifier106XUL.clone(
    modifierName = 'EGRegressionModifierV3',
    rhoTag = 'fixedGridRhoFastjetAll', # this is ...Tmp in 10_2_X
    eleRegs = dict(
        ecalOnlyMean = dict(
            ebLowEtForestName = "gsfElectron_eb_ecalOnly_05To50_mean",
            ebHighEtForestName = "gsfElectron_eb_ecalOnly_05To50_mean",
            eeLowEtForestName = "gsfElectron_ee_ecalOnly_05To50_mean",
            eeHighEtForestName = "gsfElectron_ee_ecalOnly_05To50_mean",
            ),
        ecalOnlySigma = dict(
            ebLowEtForestName = "gsfElectron_eb_ecalOnly_05To50_sigma",
            ebHighEtForestName = "gsfElectron_eb_ecalOnly_05To50_sigma",
            eeLowEtForestName = "gsfElectron_ee_ecalOnly_05To50_sigma",
            eeHighEtForestName = "gsfElectron_ee_ecalOnly_05To50_sigma",
            ),
        epComb = dict(
            ecalTrkRegressionConfig = dict(
                ebLowEtForestName = "gsfElectron_eb_ecalTrk_05To50_mean",
                ebHighEtForestName = "gsfElectron_eb_ecalTrk_05To50_mean",
                eeLowEtForestName = "gsfElectron_ee_ecalTrk_05To50_mean",
                eeHighEtForestName = "gsfElectron_ee_ecalTrk_05To50_mean",
                ),
            ecalTrkRegressionUncertConfig = dict(
                ebLowEtForestName = "gsfElectron_eb_ecalTrk_05To50_sigma",
                ebHighEtForestName = "gsfElectron_eb_ecalTrk_05To50_sigma",
                eeLowEtForestName = "gsfElectron_ee_ecalTrk_05To50_sigma",
                eeHighEtForestName = "gsfElectron_ee_ecalTrk_05To50_sigma",
                ),
        ),
    ),
)

process.regressionForEle = cms.EDProducer(
    'ElectronRegresser',
    pfSrc = cms.InputTag('slimmedElectrons'),
    gsfRegressionConfig = _gsfRegressionModifier,
)

#5b retrained ID for PF low pt electrons

mvaConfigsForEleProducer = cms.VPSet( )
# Import and add all desired MVAs
from mvaElectronID_BParkRetrain_cff \
    import mvaEleID_BParkRetrain_producer_config
mvaConfigsForEleProducer.append( mvaEleID_BParkRetrain_producer_config )

process.electronMVAValueMapProducer = cms.EDProducer(
  'ElectronMVAValueMapProducer',
  # AOD case
  src = cms.InputTag('gedGsfElectrons'),  
  # miniAOD case
  #srcMiniAOD = cms.InputTag('slimmedElectrons',processName=cms.InputTag.skipCurrentProcess()),
  srcMiniAOD = cms.InputTag('regressionForEle:regressedElectrons'),

  # MVA configurations
  mvaConfigurations = mvaConfigsForEleProducer
)

process.egmGsfElectronIDs = cms.EDProducer(
    "VersionedGsfElectronIdProducer",
    physicsObjectSrc = cms.InputTag('gedGsfElectrons'),
    physicsObjectIDs = cms.VPSet( )
)

process.egmGsfElectronIDTask = cms.Task(
    process.electronMVAValueMapProducer,
    process.egmGsfElectronIDs,
)

process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDTask)


#6. setting Analyzer
Path=["HLT_Dimuon12_Upsilon_y1p4","HLT_Dimuon24_Upsilon_noCorrL1","HLT_DoubleMu3_DoubleEle7p5_CaloIdL_TrackIdL_Upsilon","HLT_DoubleMu5_Upsilon_DoubleEle3_CaloIdL_TrackIdL","HLT_Dimuon0_Upsilon_L1_4p5NoOS_v","HLT_Dimuon0_Upsilon_L1_4p5_v","HLT_Dimuon0_Upsilon_L1_4p5er2p0M_v","HLT_Dimuon0_Upsilon_L1_4p5er2p0_v","HLT_Dimuon0_Upsilon_L1_5M_v"]


process.GenAnalysis = cms.EDAnalyzer('TQGenAnalyzer',
                                     generatorInfo= cms.InputTag("generator"),
                                     prunedGenParticles    = cms.InputTag("prunedGenParticles"),
                                     patMuons = cms.InputTag("slimmedMuons"),
                                     pfSrc = cms.InputTag("regressionForEle:regressedElectrons"),                 # MINIAOD
                                     lowptSrc = cms.InputTag("slimmedLowPtElectrons"), #change when running on our old signals
                                     vtx=cms.InputTag("offlineSlimmedPrimaryVertices"),
                                     rho= cms.InputTag('fixedGridRhoAll'),
                                     PileUp = cms.InputTag('slimmedAddPileupInfo'),
                                     bits         = cms.InputTag("TriggerResults::HLT"),
                                     objects = cms.InputTag("slimmedPatTrigger"),
                                     HLTPaths=cms.vstring(Path),
                                     drForCleaning = cms.double(0.03),
                                     dzForCleaning = cms.double(0.5), ##keep tighter dZ to check overlap of pfEle with lowPt (?)
                                     mvaValuePF = cms.InputTag('electronMVAValueMapProducer:ElectronMVAEstimatorRun2BParkRetrainRawValues'),
                                     year  = cms.untracked.int32(year),
                                     sampleIndex  = cms.untracked.int32(index),
                                     sampleXsec  = cms.untracked.double(xsec),
                                     massRef  = cms.untracked.double(massRef),



                                )


#8. setting full path
process.electronsBParkSequence = cms.Sequence(
  process.regressionForEle+
  process.egmGsfElectronIDSequence
)
#process.Seq = cms.Sequence(process.electronsBParkSequence+process.GenAnalysis)
#process.p = cms.Path((process.egammaPostRecoSeq+process.electronsBParkSequence) + process.GenAnalysis)
process.p = cms.Path((process.electronsBParkSequence) + process.GenAnalysis)

