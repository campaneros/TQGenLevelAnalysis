from CRABClient.UserUtilities import config
config = config()

## Name of output directory ##
config.General.requestName = 'ggXToYYTo2mu2e_m26_PseudoScalar_13TeV'
config.General.workArea    = 'crab_projects'

## Input analyzer pset ## 
config.JobType.pluginName  = 'analysis'
config.JobType.psetName    = 'ConfFile_cfg.py'
#config.JobType.pyCfgParams = ['globalTag=92X_dataRun2_Prompt_v7','useOOTPhotons=True']
config.JobType.inputFiles  = ['lowPtEleReg_2017UL_25112020.db',
                              'pileup_ALL.root',
                             'pileup_2018.root',
                             'pileup_2017.root',
                             'pileup_2016.root',
                             'Cert_314472-325175_13TeV_Legacy2018_Collisions18_JSON.txt',
                             'Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt',
                              'Cert_271036-284044_13TeV_Legacy2016_Collisions16_JSON.txt']
config.JobType.allowUndistributedCMSSW = True

## Input Data ##
config.Data.inputDataset   = '/private_XToJJTo2mu2e_7GeV_pseudoscalar/mcampana-privateBPH_2021May03-1fc3ecee7c51c31cd349cc9364673796/USER'
#config.Data.userInputFiles = open('ggXToYYTo2mu2e_m26_PseudoScalar_13TeV.txt').readlines()
config.Data.unitsPerJob    = 1
config.Data.splitting      = 'FileBased' 
config.Data.inputDBS='https://cmsweb.cern.ch/dbs/prod/phys03/DBSReader'




## Where to run ##
#config.Site.whitelist     = ['T1_US_FNAL']

## Output Data ##
config.Data.outLFNDirBase='/store/user/mcampana/ggXToJJTo2mu2e_7GeV_pseudoscalar/'
config.Data.publication   = False
config.Site.storageSite   = 'T2_IT_Rome'
#config.Data.outLFNDirBase = '/store/group/phys_egamma/soffi/ggXToYYTo2mu2e/'
