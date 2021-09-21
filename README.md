# TQGenLevelAnalysis

#instruction for 10_2_5

scram project -n CMSSW-102X-GenAnalysis CMSSW CMSSW_10_2_15
cd CMSSW-102X-GenAnalysis/src
cmsenv


#setup CMS low pt electrons stuff needed
git cms-addpkg RecoEgamma/EgammaElectronProducers
cd $CMSSW_BASE/src
scram b -j8 # repeat if necesssary

git clone --single-branch --branch from-CMSSW_10_2_15_2020Sept15 https://github.com/CMSBParking/RecoEgamma-ElectronIdentification.git $CMSSW_BASE/external/$SCRAM_ARCH/data/RecoEgamma/ElectronIdentification/data



#clone github repo (better first to fork in your own github and then clone yours)
git clone https://github.com/lsoffi/TQGenLevelAnalysis.git




#compile
cd TQGenLevelAnalysis/TQGenAnalyzer/
scram b


#run in local
cmsRun python/ConfFile_cfg.py



#TO DO: port this to 10_6_2















#usefule links:
- example of relval w/ needed collections:https://cmsweb.cern.ch/das/request?instance=prod/global&input=file+dataset%3D%2FRelValZEE_13%2FCMSSW_10_6_20-PU_106X_mc2017_realistic_v9_miniv2-v1%2FMINIAODSIM
- file copied here: /afs/cern.ch/user/m/mcampana/public/B7CAA14B-69E0-6540-8719-0236FB37D7C9.root

https://github.com/cms-sw/cmssw/blob/CMSSW_7_4_X/PhysicsTools/PatAlgos/python/slimming/prunedGenParticles_cfi.py

https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookWriteFrameworkModule

https://pdg.lbl.gov/2019/reviews/rpp2018-rev-monte-carlo-numbering.pdf
