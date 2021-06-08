from CRABClient.UserUtilities import config
config = config()

## Name of output directory ##
config.General.requestName = 'MuOnia_Run2018D-UL2018_MiniAODv2-v1_SR'
config.General.workArea    = 'crab_projects'

## Input analyzer pset ## 
config.JobType.pluginName  = 'analysis'
config.JobType.psetName    = 'ConfFile_cfg_LowPt_MuOnia_2018.py'
config.JobType.inputFiles  = ['lowPtEleReg_2018_02062020_nv.db',
                              'pileup_ALL.root',
                             'pileup_2018.root',
                             'pileup_2017.root',
                             'pileup_2016.root',
                              'nvtx_weights_2018UL.root',
                             'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt',
                             'Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt',
                              'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt']
config.JobType.allowUndistributedCMSSW = True

## Input Data ##
#config.Data.inputDataset   = '/MuOnia/Run2018B-12Nov2019_UL2018-v1/MINIAOD'
#config.Data.inputDBS = 'global'
config.Data.userInputFiles = open('MuOnia_Run2018D-UL2018_MiniAODv2-v1.txt').readlines()
config.Data.unitsPerJob    = 1
config.Data.splitting      = 'FileBased' 

## Where to run ##
#config.Site.whitelist     = ['T1_US_FNAL']

## Output Data ##
config.Data.outputPrimaryDataset = 'MuOnia_Run2018D-UL2018_MiniAODv2-v1'
config.Data.publication   = False
config.Site.storageSite   = 'T2_CH_CERN'
config.Data.outLFNDirBase = '/store/group/phys_egamma/soffi/TQ-DATA/'
