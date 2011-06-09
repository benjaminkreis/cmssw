// -*- C++ -*-
//
// Package:    HbbAnalyzerNew
// Class:      HbbAnalyzerNew
// 
/**\class HbbAnalyzerNew HbbAnalyzerNew.cc Analysis/HbbAnalyzer/src/HbbAnalyzerNew.cc

Description: <one line class summary>

Implementation:
<Notes on implementation>
*/
//
// Original Author:  David Lopes Pegna,Address unknown,NONE,
//         Created:  Thu Mar  5 13:51:28 EST 2009
// $Id: HbbAnalyzerNew.cc,v 1.2 2011/06/08 17:30:41 tboccali Exp $
//
//

#include "VHbbAnalysis/HbbAnalyzer/interface/HbbAnalyzerNew.h"
#include "VHbbAnalysis/HbbAnalyzer/interface/VHbbEvent.h"

#define GENPTOLOR(a) TLorentzVector((a).px(), (a).py(), (a).pz(), (a).energy())
#define GENPTOLORP(a) TLorentzVector((a)->px(), (a)->py(), (a)->pz(), (a)->energy())

HbbAnalyzerNew::HbbAnalyzerNew(const edm::ParameterSet& iConfig):
  eleLabel_(iConfig.getUntrackedParameter<edm::InputTag>("electronTag")),
  muoLabel_(iConfig.getUntrackedParameter<edm::InputTag>("muonTag")),
  jetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("jetTag")),
  subjetLabel_(iConfig.getUntrackedParameter<edm::InputTag>("subjetTag")),
  simplejet1Label_(iConfig.getUntrackedParameter<edm::InputTag>("simplejet1Tag")),
  simplejet2Label_(iConfig.getUntrackedParameter<edm::InputTag>("simplejet2Tag")),
  simplejet3Label_(iConfig.getUntrackedParameter<edm::InputTag>("simplejet3Tag")),
  simplejet4Label_(iConfig.getUntrackedParameter<edm::InputTag>("simplejet4Tag")),
  tauLabel_(iConfig.getUntrackedParameter<edm::InputTag>("tauTag")),
  metLabel_(iConfig.getUntrackedParameter<edm::InputTag>("metTag")),
  phoLabel_(iConfig.getUntrackedParameter<edm::InputTag>("photonTag")),
  dimuLabel_(iConfig.getUntrackedParameter<edm::InputTag>("dimuTag")),
  dielecLabel_(iConfig.getUntrackedParameter<edm::InputTag>("dielecTag")),
  hltResults_(iConfig.getUntrackedParameter<edm::InputTag>("hltResultsTag")),
  runOnMC_(iConfig.getParameter<bool>("runOnMC")) {


  //
  // put the setwhatproduced etc etc
 
  produces<VHbbEvent>();

 
}


HbbAnalyzerNew::~HbbAnalyzerNew(){
  
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
HbbAnalyzerNew::produce(edm::Event& iEvent, const edm::EventSetup& iSetup){
  using namespace edm;
  using namespace reco;
  
  
  std::auto_ptr<VHbbEvent> hbbInfo( new VHbbEvent() );
  
  //
  // ??
   
  // trigger
  edm::Handle<edm::TriggerResults>  hltresults;
  //iEvent.getByLabel("TriggerResults", hltresults);
   
  //edm::InputTag tag("TriggerResults::HLT");
  //  edm::InputTag tag("TriggerResults::HLT0");
  iEvent.getByLabel(hltResults_, hltresults);
   
  const edm::TriggerNames & triggerNames_ = iEvent.triggerNames(*hltresults);
   
  int ntrigs = hltresults->size();
  if (ntrigs==0){std::cout << "%HLTInfo -- No trigger name given in TriggerResults of the input " << std::endl;}

  for (int itrig = 0; itrig != ntrigs; ++itrig){

    TString trigName=triggerNames_.triggerName(itrig);
    bool accept = hltresults->accept(itrig);

    if (accept){(hbbInfo->triggerInfo.flag)[itrig] = 1;}
    else { (hbbInfo->triggerInfo.flag)[itrig] = 0;}

    //    std::cout << "%HLTInfo --  Number of HLT Triggers: " << ntrigs << std::endl;
    //    std::cout << "%HLTInfo --  HLTTrigger(" << itrig << "): " << trigName << " = " << accept << std::endl;
  }

  //
  // big bloat
  //


  int goodDoubleMu3=0,goodDoubleMu3_2=0,  
    goodMu9=0, goodIsoMu9=0, goodMu11=0, goodIsoMu13_3=0, goodMu15=0, goodMu15_1=0; 
  int goodDoubleElec10=0,goodDoubleElec15_1=0,goodDoubleElec17_1=0;
  int goodMet100=0;
  int goodSingleEle1=0,goodSingleEle2=0,goodSingleEle3=0,goodSingleEle4=0;
  int goodBtagMu1=0,goodBtagMu2=0,goodBtagMu0=0,goodBtagMu11=0;  
  int goodBtagMuJet1=0, goodBtagMuJet2=0, goodBtagMuJet3=0, goodBtagMuJet4=0; 
  int goodIsoMu15=0,goodIsoMu17v5=0,goodIsoMu17v6=0;

  for (int itrig = 0; itrig != ntrigs; ++itrig){
    TString trigName=triggerNames_.triggerName(itrig);
    if(strcmp(trigName,"HLT_Mu9")==0) goodMu9++;
    if(strcmp(trigName,"HLT_IsoMu9")==0) goodIsoMu9++;
    if(strcmp(trigName,"HLT_IsoMu13_v3")==0) goodIsoMu13_3++;
    if(strcmp(trigName,"HLT_Mu11")==0) goodMu11++;
    if(strcmp(trigName,"HLT_DoubleMu3")==0) goodDoubleMu3++;
    if(strcmp(trigName,"HLT_DoubleMu3_v2")==0) goodDoubleMu3_2++;
    if(strcmp(trigName,"HLT_Mu15")==0) goodMu15++;
    if(strcmp(trigName,"HLT_Mu15_v1")==0) goodMu15_1++;

    if(strcmp(trigName,"HLT_DoubleEle10_SW_L1R")==0) goodDoubleElec10++;
    if(strcmp(trigName,"HLT_DoubleEle15_SW_L1R_v1")==0) goodDoubleElec15_1++;
    if(strcmp(trigName,"HLT_DoubleEle17_SW_L1R_v1")==0) goodDoubleElec17_1++;
    if(strcmp(trigName,"HLT_MET100_v1")==0) goodMet100++;
    if(strcmp(trigName,"HLT_Ele15_SW_L1R")==0) goodSingleEle1++;
    if(strcmp(trigName,"HLT_Ele17_SW_TightEleId_L1R")==0) goodSingleEle2++;
    if(strcmp(trigName,"HLT_Ele17_SW_TighterEleIdIsol_L1R_v2")==0) goodSingleEle3++;
    if(strcmp(trigName,"HLT_Ele17_SW_TighterEleIdIsol_L1R_v3")==0) goodSingleEle4++;
    if(strcmp(trigName,"HLT_BTagMu_DiJet20U_v1")==0) goodBtagMu1++;
    if(strcmp(trigName,"HLT_BTagMu_DiJet30U_Mu5_v3")==0) goodBtagMu2++;
    if(strcmp(trigName,"HLT_BTagMu_Jet20U")==0) goodBtagMu0++;
    if(strcmp(trigName,"HLT_BTagMu_DiJet20U_Mu5_v1")==0) goodBtagMu11++;
    if(strcmp(trigName,"HLT_Mu17_CentralJet30_BTagIP_v2")==0) goodBtagMuJet1++;
    if(strcmp(trigName,"HLT_Mu17_CentralJet30_v2")==0) goodBtagMuJet2++;
    if(strcmp(trigName,"HLT_HT200_Mu5_PFMHT35_v2")==0) goodBtagMuJet3++;
    if(strcmp(trigName,"HLT_Mu12_CentralJet30_BTagIP_v2")==0) goodBtagMuJet4++;  

    if(strcmp(trigName,"HLT_IsoMu15_v5")==0) goodIsoMu15++; 
    if(strcmp(trigName,"HLT_IsoMu17_v5")==0) goodIsoMu17v5++;  
    if(strcmp(trigName,"HLT_IsoMu17_v6")==0) goodIsoMu17v6++;  
  }
  int itrig1=-99;
  if(goodMu9!=0) itrig1 = triggerNames_.triggerIndex("HLT_Mu9");
  int itrig2=-99;
  if(goodIsoMu9!=0) itrig2 = triggerNames_.triggerIndex("HLT_IsoMu9");
  int itrig3=-99;
  if(goodIsoMu13_3!=0) itrig3 = triggerNames_.triggerIndex("HLT_IsoMu13_v3"); 
  int itrig4=-99;
  if(goodMu11!=0) itrig4 = triggerNames_.triggerIndex("HLT_Mu11"); 
  int itrig5=-99;  
  if(goodDoubleMu3!=0) itrig5 = triggerNames_.triggerIndex("HLT_DoubleMu3"); 
  int itrig6=-99;
  if(goodDoubleMu3_2!=0) itrig6 = triggerNames_.triggerIndex("HLT_DoubleMu3_v2");
  int itrig7=-99;
  if(goodMu15!=0) itrig7 = triggerNames_.triggerIndex("HLT_Mu15");
  int itrig8=-99;
  if(goodMu15_1!=0) itrig8 = triggerNames_.triggerIndex("HLT_Mu15_v1"); 

  int itrig9=-99;
  if(goodDoubleElec10!=0) itrig9 = triggerNames_.triggerIndex("HLT_DoubleEle10_SW_L1R"); 
  int itrig10=-99;
  if(goodDoubleElec15_1!=0) itrig10 = triggerNames_.triggerIndex("HLT_DoubleEle15_SW_L1R_v1"); 
  int itrig11=-99;
  if(goodDoubleElec17_1!=0) itrig11 = triggerNames_.triggerIndex("HLT_DoubleEle17_SW_L1R_v1"); 
  int itrig12=-99;
  if(goodMet100!=0) itrig12 = triggerNames_.triggerIndex("HLT_MET100_v1"); 

  int itrig13=-99;
  if(goodSingleEle1!=0) itrig13 = triggerNames_.triggerIndex("HLT_Ele15_SW_L1R");
  int itrig14=-99;
  if(goodSingleEle2!=0) itrig14 = triggerNames_.triggerIndex("HLT_Ele17_SW_TightEleId_L1R");
  int itrig15=-99;
  if(goodSingleEle3!=0) itrig15 = triggerNames_.triggerIndex("HLT_Ele17_SW_TighterEleIdIsol_L1R_v2");
  int itrig16=-99;
  if(goodSingleEle4!=0) itrig16 = triggerNames_.triggerIndex("HLT_Ele17_SW_TighterEleIdIsol_L1R_v3");

  int itrig17=-99; 
  if(goodBtagMu1!=0) itrig17 = triggerNames_.triggerIndex("HLT_BTagMu_DiJet20U_v1");      
  int itrig18=-99;
  if(goodBtagMu2!=0) itrig18 = triggerNames_.triggerIndex("HLT_BTagMu_DiJet30U_Mu5_v3");    
  int itrig19=-99;
  if(goodBtagMu0!=0) itrig19 = triggerNames_.triggerIndex("HLT_BTagMu_Jet20U");
  int itrig20=-99;
  if(goodBtagMu11!=0) itrig20 = triggerNames_.triggerIndex("HLT_BTagMu_DiJet20U_Mu5_v1");
  int itrig21=-99;
  if(goodBtagMuJet1!=0) itrig21 = triggerNames_.triggerIndex("HLT_Mu17_CentralJet30_BTagIP_v2");
  int itrig22=-99;
  if(goodBtagMuJet2!=0) itrig22 = triggerNames_.triggerIndex("HLT_Mu17_CentralJet30_v2"); 
  int itrig23=-99;
  if(goodBtagMuJet3!=0) itrig23 = triggerNames_.triggerIndex("HLT_HT200_Mu5_PFMHT35_v2");
  int itrig231=-99;
  if(goodBtagMuJet4!=0) itrig231 = triggerNames_.triggerIndex("HLT_Mu12_CentralJet30_BTagIP_v2");  

  int itrig24=-99;
  if(goodIsoMu15!=0) itrig24 = triggerNames_.triggerIndex("HLT_IsoMu15_v5"); 
  int itrig25=-99;
  if(goodIsoMu17v5!=0) itrig25 = triggerNames_.triggerIndex("HLT_IsoMu17_v5");
  int itrig26=-99;
  if(goodIsoMu17v6!=0) itrig26 = triggerNames_.triggerIndex("HLT_IsoMu17_v6");
   
  if (itrig1!=-99 && hltresults->accept(itrig1))  hbbInfo->triggerInfo.triggerMu9=1; else hbbInfo->triggerInfo.triggerMu9=0;
  if (itrig2!=-99 && hltresults->accept(itrig2))  hbbInfo->triggerInfo.triggerIsoMu9=1; else hbbInfo->triggerInfo.triggerIsoMu9=0;
  if (itrig3!=-99 && hltresults->accept(itrig3))  hbbInfo->triggerInfo.triggerIsoMu13_3=1; else hbbInfo->triggerInfo.triggerIsoMu13_3=0;
  if (itrig4!=-99 && hltresults->accept(itrig4))  hbbInfo->triggerInfo.triggerMu11=1; else hbbInfo->triggerInfo.triggerMu11=0;
  if (itrig5!=-99 && hltresults->accept(itrig5))  hbbInfo->triggerInfo.triggerDoubleMu3=1; else hbbInfo->triggerInfo.triggerDoubleMu3=0; 
  if (itrig6!=-99 && hltresults->accept(itrig6))  hbbInfo->triggerInfo.triggerDoubleMu3_2=1; else hbbInfo->triggerInfo.triggerDoubleMu3_2=0;
  if (itrig7!=-99 && hltresults->accept(itrig7))  hbbInfo->triggerInfo.triggerMu15=1; else hbbInfo->triggerInfo.triggerMu15=0;
  if (itrig8!=-99 && hltresults->accept(itrig8))  hbbInfo->triggerInfo.triggerMu15_1=1; else hbbInfo->triggerInfo.triggerMu15_1=0;  
   
  if (itrig9!=-99 && hltresults->accept(itrig9))  hbbInfo->triggerInfo.triggerDoubleElec10=1; else hbbInfo->triggerInfo.triggerDoubleElec10=0;  
  if (itrig10!=-99 && hltresults->accept(itrig10))  hbbInfo->triggerInfo.triggerDoubleElec15_1=1; else hbbInfo->triggerInfo.triggerDoubleElec15_1=0;  
  if (itrig11!=-99 && hltresults->accept(itrig11))  hbbInfo->triggerInfo.triggerDoubleElec17_1=1; else hbbInfo->triggerInfo.triggerDoubleElec17_1=0;  
  if (itrig12!=-99 && hltresults->accept(itrig12))  hbbInfo->triggerInfo.triggerMet100_1=1; else hbbInfo->triggerInfo.triggerMet100_1=0;
   
  if (itrig13!=-99 && hltresults->accept(itrig13))  hbbInfo->triggerInfo.triggerSingleEle1=1; else hbbInfo->triggerInfo.triggerSingleEle1=0;
  if (itrig14!=-99 && hltresults->accept(itrig14))  hbbInfo->triggerInfo.triggerSingleEle2=1; else hbbInfo->triggerInfo.triggerSingleEle2=0;
  if (itrig15!=-99 && hltresults->accept(itrig15))  hbbInfo->triggerInfo.triggerSingleEle3=1; else hbbInfo->triggerInfo.triggerSingleEle3=0;
  if (itrig16!=-99 && hltresults->accept(itrig16))  hbbInfo->triggerInfo.triggerSingleEle4=1; else hbbInfo->triggerInfo.triggerSingleEle4=0;
   
  if (itrig17!=-99 && hltresults->accept(itrig17))  hbbInfo->triggerInfo.triggerBtagMu1=1; else hbbInfo->triggerInfo.triggerBtagMu1=0;   
  if (itrig18!=-99 && hltresults->accept(itrig18))  hbbInfo->triggerInfo.triggerBtagMu2=1; else hbbInfo->triggerInfo.triggerBtagMu2=0;
  if (itrig19!=-99 && hltresults->accept(itrig19))  hbbInfo->triggerInfo.triggerBtagMu0=1; else hbbInfo->triggerInfo.triggerBtagMu0=0;
  if (itrig20!=-99 && hltresults->accept(itrig20))  hbbInfo->triggerInfo.triggerBtagMu11=1; else hbbInfo->triggerInfo.triggerBtagMu11=0;
  if (itrig21!=-99 && hltresults->accept(itrig21))  hbbInfo->triggerInfo.triggerBtagMuJet1=1; else hbbInfo->triggerInfo.triggerBtagMuJet1=0;
  if (itrig22!=-99 && hltresults->accept(itrig22))  hbbInfo->triggerInfo.triggerBtagMuJet2=1; else hbbInfo->triggerInfo.triggerBtagMuJet2=0;
  if (itrig23!=-99 && hltresults->accept(itrig23))  hbbInfo->triggerInfo.triggerBtagMuJet3=1; else hbbInfo->triggerInfo.triggerBtagMuJet3=0;
  if (itrig231!=-99 && hltresults->accept(itrig231))  hbbInfo->triggerInfo.triggerBtagMuJet4=1; else hbbInfo->triggerInfo.triggerBtagMuJet4=0;
   
  if (itrig24!=-99 && hltresults->accept(itrig24))  hbbInfo->triggerInfo.triggerIsoMu15=1; else hbbInfo->triggerInfo.triggerIsoMu15=0;
  if (itrig25!=-99 && hltresults->accept(itrig25))  hbbInfo->triggerInfo.triggerIsoMu17v5=1; else hbbInfo->triggerInfo.triggerIsoMu17v5=0;
  if (itrig26!=-99 && hltresults->accept(itrig26))  hbbInfo->triggerInfo.triggerIsoMu17v6=1; else hbbInfo->triggerInfo.triggerIsoMu17v6=0;
   
  if (itrig1==-99)  hbbInfo->triggerInfo.triggerMu9=-99; 
  if (itrig2==-99)  hbbInfo->triggerInfo.triggerIsoMu9=-99; 
  if (itrig3==-99)  hbbInfo->triggerInfo.triggerIsoMu13_3=-99; 
  if (itrig4==-99)  hbbInfo->triggerInfo.triggerMu11=-99; 
  if (itrig5==-99)  hbbInfo->triggerInfo.triggerDoubleMu3=-99;
  if (itrig6==-99)  hbbInfo->triggerInfo.triggerDoubleMu3_2=-99; 
  if (itrig7==-99)  hbbInfo->triggerInfo.triggerMu15=-99;
  if (itrig8==-99)  hbbInfo->triggerInfo.triggerMu15_1=-99; 

  if (itrig9==-99)  hbbInfo->triggerInfo.triggerDoubleElec10=-99; 
  if (itrig10==-99)  hbbInfo->triggerInfo.triggerDoubleElec15_1=-99; 
  if (itrig11==-99)  hbbInfo->triggerInfo.triggerDoubleElec17_1=-99; 
  if (itrig12==-99) hbbInfo->triggerInfo.triggerMet100_1=-99;

  if (itrig13==-99) hbbInfo->triggerInfo.triggerSingleEle1=-99;
  if (itrig14==-99) hbbInfo->triggerInfo.triggerSingleEle2=-99;
  if (itrig15==-99) hbbInfo->triggerInfo.triggerSingleEle3=-99;
  if (itrig16==-99) hbbInfo->triggerInfo.triggerSingleEle4=-99;

  if(itrig17==-99)  hbbInfo->triggerInfo.triggerBtagMu1=-99;   
  if(itrig18==-99)  hbbInfo->triggerInfo.triggerBtagMu2=-99;
  if(itrig19==-99)  hbbInfo->triggerInfo.triggerBtagMu0=-99;
  if(itrig20==-99)  hbbInfo->triggerInfo.triggerBtagMu11=-99;
  if(itrig21==-99)  hbbInfo->triggerInfo.triggerBtagMuJet1=-99;
  if(itrig22==-99)  hbbInfo->triggerInfo.triggerBtagMuJet2=-99;
  if(itrig23==-99)  hbbInfo->triggerInfo.triggerBtagMuJet3=-99;
  if(itrig231==-99)  hbbInfo->triggerInfo.triggerBtagMuJet4=-99;

  if(itrig24==-99)  hbbInfo->triggerInfo.triggerIsoMu15=-99;
  if(itrig25==-99)  hbbInfo->triggerInfo.triggerIsoMu17v5=-99;
  if(itrig26==-99)  hbbInfo->triggerInfo.triggerIsoMu17v6=-99;

  //  MinDRMu=-99.,MCBestMuId=-99,MCBestMuMomId=-99,MCBestMuGMomId=-99;
  //  for(int i=0;i<50;i++) {DeltaRMu[i]=-99;}



  BeamSpot vertexBeamSpot;
  edm::Handle<reco::BeamSpot> recoBeamSpotHandle;
  iEvent.getByLabel("offlineBeamSpot",recoBeamSpotHandle);
  vertexBeamSpot = *recoBeamSpotHandle;
  /*
    double BSx=vertexBeamSpot.x0();
    double BSy=vertexBeamSpot.y0();
    double BSz=vertexBeamSpot.z0();
  */

  double MinVtxProb=-999.;
  int VtxIn=-99;
  
  Handle<reco::VertexCollection> recVtxs;
  iEvent.getByLabel("offlinePrimaryVertices", recVtxs);
  
  for(size_t i = 0; i < recVtxs->size(); ++ i) {
    const Vertex &vtx = (*recVtxs)[i];
    double RecVtxProb=TMath::Prob(vtx.chi2(),vtx.ndof());
    if(RecVtxProb>MinVtxProb){
      VtxIn=i;
      MinVtxProb=RecVtxProb;      
    }
  }

  const Vertex &RecVtx = (*recVtxs)[VtxIn];
  const Vertex &RecVtxFirst = (*recVtxs)[0];
  
  hbbInfo->pvInfo.firstPVInPT2 = TVector3(RecVtxFirst.x(), RecVtxFirst.y(), RecVtxFirst.z());
  hbbInfo->pvInfo.firstPVInProb = TVector3(RecVtx.x(), RecVtx.y(), RecVtx.z());

    
  edm::Handle<double> rhoHandle;
  iEvent.getByLabel(edm::InputTag("kt6PFJets", "rho"),rhoHandle); // configure srcRho = cms.InputTag('kt6PFJets")
  hbbInfo->puInfo.rho = *rhoHandle;
  
  //// real start
  
  
  Handle<GenParticleCollection> genParticles;
  
  bool printJet=0;
  
  
  if(runOnMC_){
    
    int Hin=-99,Win=-99,Zin=-99,bin=-99,bbarin=-99;
    
    iEvent.getByLabel("genParticles", genParticles);
    
    for(size_t i = 0; i < genParticles->size(); ++ i) {
      const GenParticle & p = (*genParticles)[i];
      int id = p.pdgId();
      int st = p.status();  
	
      if(id==25){
	  
	/*          int wh=0;
		    int nMoth = p.numberOfMothers();
		    for(size_t jj = 0; jj < nMoth; ++ jj) {
		    const Candidate * mom = p.mother( jj );
		    int nmomdau= mom->numberOfDaughters();
		    for(size_t j = 0; j < nmomdau; ++ j) {
		    const Candidate * Wmomdau = mom->daughter( j );
		    if(abs(Wmomdau->pdgId())==24) wh++;
		    }
		    }
		      
		    if(wh==0) continue;
	*/
	Hin=i; 
	hbbInfo->mcH.status=st;
	hbbInfo->mcH.charge=p.charge();
	if(p.mother(0)!=0) hbbInfo->mcH.momid=p.mother(0)->pdgId();
	if(p.mother(0)!=0 && p.mother(0)->mother(0)!=0) hbbInfo->mcH.gmomid=p.mother(0)->mother(0)->pdgId(); 
	hbbInfo->mcH.fourMomentum = GENPTOLOR(p);
	  
	int ndau = p.numberOfDaughters();
	for(int j = 0; j < ndau; ++ j) {
	  const Candidate * Hdau = p.daughter( j );
	  hbbInfo->mcH.dauid.push_back(Hdau->pdgId());
	  hbbInfo->mcH.dauFourMomentum.push_back(GENPTOLORP(Hdau));
	}
      }
	
	
      if(abs(id)==24){
	  
	Win=i;
	hbbInfo->mcW.status=st;
	hbbInfo->mcW.charge=p.charge();
	if(p.mother(0)!=0) hbbInfo->mcW.momid=p.mother(0)->pdgId();
	if(p.mother(0)!=0 && p.mother(0)->mother(0)!=0) hbbInfo->mcW.gmomid=p.mother(0)->mother(0)->pdgId();
	hbbInfo->mcW.fourMomentum=GENPTOLOR(p);

	int ndau = p.numberOfDaughters();
	for(int j = 0; j < ndau; ++ j) {
	  const Candidate * Wdau = p.daughter( j );
	  hbbInfo->mcW.dauid.push_back(Wdau->pdgId());
	  hbbInfo->mcW.dauFourMomentum.push_back(GENPTOLORP(Wdau));
	}
      }
	
      if(abs(id)==23){

	Zin=i;
	hbbInfo->mcZ.status=st;
	hbbInfo->mcZ.charge=p.charge();
	if(p.mother(0)!=0) hbbInfo->mcZ.momid=p.mother(0)->pdgId();
	if(p.mother(0)!=0 && p.mother(0)->mother(0)!=0) hbbInfo->mcZ.gmomid=p.mother(0)->mother(0)->pdgId();
	hbbInfo->mcZ.fourMomentum=GENPTOLOR(p);

	int ndau = p.numberOfDaughters();
	for(int j = 0; j < ndau; ++ j) {
	  const Candidate * Zdau = p.daughter( j );
	  hbbInfo->mcZ.dauid.push_back(Zdau->pdgId());
	  hbbInfo->mcZ.dauFourMomentum.push_back(GENPTOLOR(p));
	}
      }
      //
      // binfo
      //

      
      if(id==5){
	bin=i; 
	hbbInfo->mcB.status=st;
	hbbInfo->mcB.charge=p.charge();
	if(p.mother(0)!=0) hbbInfo->mcB.momid=p.mother(0)->pdgId();
	if(p.mother(0)!=0 && p.mother(0)->mother(0)!=0) hbbInfo->mcB.gmomid=p.mother(0)->mother(0)->pdgId(); 
      }
      
      if(id==-5){
	bbarin=i; 
	hbbInfo->mcBbar.status=st;
	hbbInfo->mcBbar.charge=p.charge();
	if(p.mother(0)!=0) hbbInfo->mcBbar.momid=p.mother(0)->pdgId();
	if(p.mother(0)!=0 && p.mother(0)->mother(0)!=0) hbbInfo->mcBbar.gmomid=p.mother(0)->mother(0)->pdgId(); 
      }
      
      if(abs(id)==4){
	hbbInfo->mcC.status=st;
	hbbInfo->mcC.charge=p.charge();
	if(p.mother(0)!=0) hbbInfo->mcC.momid=p.mother(0)->pdgId();
	if(p.mother(0)!=0 && p.mother(0)->mother(0)!=0) hbbInfo->mcC.gmomid=p.mother(0)->mother(0)->pdgId();
      }


    }


    if(bin!=-99 && bbarin!=-99){
      const Candidate & bGen = (*genParticles)[bin];
      const Candidate & bbarGen = (*genParticles)[bbarin]; 
      hbbInfo->mcB.fourMomentum=GENPTOLOR(bGen);
      hbbInfo->mcBbar.fourMomentum=GENPTOLOR(bbarGen);
      
      int nHDaubdau = bGen.numberOfDaughters();
      for(int j = 0; j < nHDaubdau; ++ j) {
	const Candidate * Bdau = bGen.daughter( j );
	hbbInfo->mcB.dauid.push_back(Bdau->pdgId());
	hbbInfo->mcB.dauFourMomentum.push_back(GENPTOLORP(Bdau));
      }
      int nHDaubbardau = bbarGen.numberOfDaughters();
      for(int j = 0; j < nHDaubbardau; ++ j) {
	const Candidate * Bbardau = bbarGen.daughter( j );
	hbbInfo->mcBbar.dauid.push_back(Bbardau->pdgId());
	hbbInfo->mcBbar.dauFourMomentum.push_back(GENPTOLORP(Bbardau));
      }

  

    }


  }   // isMC

  /////// end generator block    


  edm::Handle<edm::View<pat::Muon> > muonHandle;
  iEvent.getByLabel(muoLabel_,muonHandle);
  edm::View<pat::Muon> muons = *muonHandle;

  // hard jet   
  edm::Handle<edm::View<pat::Jet> > jetHandle;
  iEvent.getByLabel(jetLabel_,jetHandle);
  edm::View<pat::Jet> jets = *jetHandle;

  // sub jet   
  edm::Handle<edm::View<pat::Jet> > subjetHandle;
  iEvent.getByLabel(subjetLabel_,subjetHandle);
  edm::View<pat::Jet> subjets = *subjetHandle;

  // standard jets

  edm::Handle<edm::View<pat::Jet> > simplejet1Handle;
  iEvent.getByLabel(simplejet1Label_,simplejet1Handle);
  edm::View<pat::Jet> simplejets1 = *simplejet1Handle;

  edm::Handle<edm::View<pat::Jet> > simplejet2Handle;
  iEvent.getByLabel(simplejet2Label_,simplejet2Handle);
  edm::View<pat::Jet> simplejets2 = *simplejet2Handle;

  edm::Handle<edm::View<pat::Jet> > simplejet3Handle;
  iEvent.getByLabel(simplejet3Label_,simplejet3Handle);
  edm::View<pat::Jet> simplejets3 = *simplejet3Handle;

  edm::Handle<edm::View<pat::Jet> > simplejet4Handle;
  iEvent.getByLabel(simplejet4Label_,simplejet4Handle);
  edm::View<pat::Jet> simplejets4 = *simplejet4Handle;


  edm::Handle<edm::View<pat::Electron> > electronHandle;
  iEvent.getByLabel(eleLabel_,electronHandle);
  edm::View<pat::Electron> electrons = *electronHandle;

  edm::Handle<edm::View<pat::MET> > metHandle;
  iEvent.getByLabel(metLabel_,metHandle);
  edm::View<pat::MET> mets = *metHandle;

  //   edm::Handle<edm::View<pat::Photon> > phoHandle;
  //   iEvent.getByLabel(phoLabel_,phoHandle);
  //   edm::View<pat::Photon> photons = *phoHandle;

  edm::Handle<edm::View<pat::Tau> > tauHandle;
  iEvent.getByLabel(tauLabel_,tauHandle);
  edm::View<pat::Tau> taus = *tauHandle;

  edm::Handle<CandidateView> dimuons;
  iEvent.getByLabel(dimuLabel_,dimuons);

  edm::Handle<CandidateView> dielectrons;
  iEvent.getByLabel(dielecLabel_,dielectrons);


  for(edm::View<pat::Jet>::const_iterator jet_iter = simplejets1.begin(); jet_iter!=simplejets1.end(); ++jet_iter){
    //     if(jet_iter->pt()>50)
    //       njetscounter++;
    VHbbEvent::SimpleJet sj;
    sj.flavour = jet_iter->partonFlavour();


    sj.tche=jet_iter->bDiscriminator("trackCountingHighEffBJetTags");
    sj.tchp=jet_iter->bDiscriminator("trackCountingHighPurBJetTags");
    sj.jp=jet_iter->bDiscriminator("jetProbabilityBJetTags");
    sj.jpb=jet_iter->bDiscriminator("jetBProbabilityBJetTags");
    sj.ssvhe=jet_iter->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
    sj.csv=jet_iter->bDiscriminator("combinedSecondaryVertexBJetTags");
    sj.csvmva=jet_iter->bDiscriminator("combinedSecondaryVertexMVABJetTags");
    sj.charge=jet_iter->jetCharge();
    sj.ntracks=jet_iter->associatedTracks().size();
    sj.fourMomentum=GENPTOLORP(jet_iter);

    Particle::LorentzVector p4Jet = jet_iter->p4();

    if(runOnMC_){
      double minb1DR=9999.; 
      for(size_t i = 0; i < genParticles->size(); ++ i) {
	const GenParticle & p = (*genParticles)[i];
	int id = p.pdgId();
	if(abs(id)<=6 || id==21 || id==23 || abs(id)==24){
	  double bb1DR=TMath::Sqrt((p.eta()-p4Jet.eta())*(p.eta()-p4Jet.eta())+
				   (p.phi()-p4Jet.phi())*(p.phi()-p4Jet.phi()));
	  if(bb1DR<minb1DR) {minb1DR=bb1DR; sj.b1BestMCid=id; if(p.mother()!=0) sj.b1BestMCmomid=p.mother()->pdgId();}
	}
      }
    } //isMC    
    hbbInfo->simpleJets.push_back(sj);
    
  }
  
  
  for(edm::View<pat::Jet>::const_iterator jet_iter = simplejets2.begin(); jet_iter!=simplejets2.end(); ++jet_iter){
    
    VHbbEvent::SimpleJet sj;
    sj.flavour = jet_iter->partonFlavour();
    
    
    sj.tche=jet_iter->bDiscriminator("trackCountingHighEffBJetTags");
    sj.tchp=jet_iter->bDiscriminator("trackCountingHighPurBJetTags");
    sj.jp=jet_iter->bDiscriminator("jetProbabilityBJetTags");
    sj.jpb=jet_iter->bDiscriminator("jetBProbabilityBJetTags");
    sj.ssvhe=jet_iter->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
    sj.csv=jet_iter->bDiscriminator("combinedSecondaryVertexBJetTags");
    sj.csvmva=jet_iter->bDiscriminator("combinedSecondaryVertexMVABJetTags");
    sj.charge=jet_iter->jetCharge();
    sj.ntracks=jet_iter->associatedTracks().size();
    sj.fourMomentum=GENPTOLORP(jet_iter);

    Particle::LorentzVector p4Jet = jet_iter->p4();

    if(runOnMC_){
      double minb2DR=9999.; 
      for(size_t i = 0; i < genParticles->size(); ++ i) {
	const GenParticle & p = (*genParticles)[i];
	int id = p.pdgId();
	if(abs(id)<=6 || id==21 || id==23 || abs(id)==24){
	  double bb2DR=TMath::Sqrt((p.eta()-p4Jet.eta())*(p.eta()-p4Jet.eta())+
				   (p.phi()-p4Jet.phi())*(p.phi()-p4Jet.phi()));
	  if(bb2DR<minb2DR) {minb2DR=bb2DR; sj.b1BestMCid=id; if(p.mother()!=0) sj.b1BestMCmomid=p.mother()->pdgId();}
	}
      }
    }   //isMC
    
    hbbInfo->simpleJets2.push_back(sj);
    
  }


  /*   const GenJet* jet1Mc = bjet1.genJet();
       const GenJet* jet2Mc = bjet2.genJet();
       if(jet1Mc!=0){
       MCbJet1MomId=jet1Mc->mother()->pdgId();
       MCbJet1GMomId=jet1Mc->mother()->mother()->pdgId();
       }

       if(jet2Mc!=0){
       MCbJet2MomId=jet2Mc->mother()->pdgId();
       MCbJet2GMomId=jet2Mc->mother()->mother()->pdgId();
       }
  */
   


  /////// hard jet

  
  double matEta[1000*30],matPhi[1000*30];
  for(int i=0;i<1000;i++){for(int j=0;j<30;j++){matEta[i*j]=-99.;matPhi[i*j]=-99.;}}

  for(edm::View<pat::Jet>::const_iterator jet_iter = jets.begin(); jet_iter!=jets.end(); ++jet_iter){
    
    if(printJet) {std::cout << "Jet Pt: " << jet_iter->pt() << " E,M: " << jet_iter->p4().E() << " " << jet_iter->p4().M() << "\n";} 
    
    reco::Jet::Constituents constituents = jet_iter->getJetConstituents();
    
    //    if(printJet) {std::cout << "NsubJets: " << constituents.size() << "\n";} 
    VHbbEvent::HardJet hj;
    hj.constituents=constituents.size();
    hj.fourMomentum =GENPTOLORP(jet_iter);

    for (unsigned int iJC(0); iJC<constituents.size(); ++iJC ){
      Jet::Constituent icandJet = constituents[iJC];

      if(printJet) {std::cout << "subJet Pt: " << icandJet->pt() << " subJet E,M,eta,phi: " <<  icandJet->p4().E() << "," 
			      << icandJet->p4().M() << "," << icandJet->eta() << "," << icandJet->phi() << "\n"; } 


      hj.subFourMomentum.push_back(GENPTOLORP(icandJet));
      hj.etaSub.push_back(icandJet->eta());
      hj.phiSub.push_back(icandJet->phi());

     
    }
    hbbInfo->hardJets.push_back(hj);
  }
    
  //  HardJetSubEta2.SetMatrixArray(matEta);
  //  HardJetSubPhi2.SetMatrixArray(matPhi);
  //  TMatrixDRow a1(HardJetSubEta2,0);
  //  for(int i=0;i<30;i++){
  //   std::cout << "test: " << a1[i] << "\n";  
  //  }

  // pat subJets with Btag


  for(edm::View<pat::Jet>::const_iterator subjet_iter = subjets.begin(); subjet_iter!=subjets.end(); ++subjet_iter){

    if(printJet) {std::cout << "SubJetTagged Pt: " << subjet_iter->pt() << " E,M,eta,phi,Btag: " << subjet_iter->p4().E() 
			    << "," << subjet_iter->p4().M() << "," << subjet_iter->eta() << "," << subjet_iter->phi()  
			    << "," << subjet_iter->bDiscriminator("combinedSecondaryVertexBJetTags") << "\n";}

    VHbbEvent::SimpleJet sj;

    sj.flavour = subjet_iter->partonFlavour();
    
    sj.tche=subjet_iter->bDiscriminator("trackCountingHighEffBJetTags");
    sj.tchp=subjet_iter->bDiscriminator("trackCountingHighPurBJetTags");
    sj.jp=subjet_iter->bDiscriminator("jetProbabilityBJetTags");
    sj.jpb=subjet_iter->bDiscriminator("jetBProbabilityBJetTags");
    sj.ssvhe=subjet_iter->bDiscriminator("simpleSecondaryVertexHighEffBJetTags");
    sj.csv=subjet_iter->bDiscriminator("combinedSecondaryVertexBJetTags");
    sj.csvmva=subjet_iter->bDiscriminator("combinedSecondaryVertexMVABJetTags");
    sj.charge=subjet_iter->jetCharge();
    sj.ntracks=subjet_iter->associatedTracks().size();
    sj.fourMomentum=GENPTOLORP(subjet_iter);

    hbbInfo->subJets.push_back(sj);

  }


  //
  // met is calomet
  //


  for(edm::View<pat::MET>::const_iterator met = mets.begin(); met!=mets.end(); ++met){
    hbbInfo->calomet.sumEt=met->sumEt();
    hbbInfo->calomet.metSig=met->mEtSig();
    hbbInfo->calomet.eLong=met->e_longitudinal();
    hbbInfo->calomet.fourMomentum=GENPTOLORP(met);
  }

  edm::Handle<edm::View<pat::MET> > metTCHandle;
  iEvent.getByLabel("patMETsTC",metTCHandle);
  edm::View<pat::MET> metsTC = *metTCHandle;
  for(edm::View<pat::MET>::const_iterator metTC = metsTC.begin(); metTC!=metsTC.end(); ++metTC){
    hbbInfo->calomet.sumEt=metTC->sumEt();
    hbbInfo->calomet.metSig=metTC->mEtSig();
    hbbInfo->calomet.eLong=metTC->e_longitudinal();
    hbbInfo->calomet.fourMomentum=GENPTOLORP(metTC);
  }
  edm::Handle<edm::View<pat::MET> > metPFHandle;
  iEvent.getByLabel("patMETsPF",metPFHandle);
  edm::View<pat::MET> metsPF = *metPFHandle;
  for(edm::View<pat::MET>::const_iterator metPF = metsPF.begin(); metPF!=metsPF.end(); ++metPF){
    hbbInfo->calomet.sumEt=metPF->sumEt();
    hbbInfo->calomet.metSig=metPF->mEtSig();
    hbbInfo->calomet.eLong=metPF->e_longitudinal();
    hbbInfo->calomet.fourMomentum=GENPTOLORP(metPF);
  }



  for(edm::View<pat::Muon>::const_iterator mu = muons.begin(); mu!=muons.end(); ++mu){
    VHbbEvent::MuonInfo mf;
    mf.fourMomentum =GENPTOLORP( mu);
    mf.charge=mu->charge();
    mf.tIso=mu->trackIso();
    mf.eIso=mu->ecalIso();
    mf.hIso=mu->hcalIso();
    Geom::Phi<double> deltaphi(mu->phi()-atan2(mf.fourMomentum.Px(), mf.fourMomentum.Py()));
    double acop = deltaphi.value();
    mf.acop=acop;

    mf.ipDb=mu->dB();
    mf.ipErrDb=mu->edB();
    if(mu->isGlobalMuon()) mf.cat=1;
    else if(mu->isTrackerMuon()) mf.cat=2;
    else mf.cat=3;
    TrackRef trkMu1Ref = mu->get<TrackRef>();
    if(trkMu1Ref.isNonnull()){
      const Track* MuTrk1 = mu->get<TrackRef>().get();
      mf.zPVPt=MuTrk1->dz(RecVtxFirst.position());
      mf.zPVProb=MuTrk1->dz(RecVtx.position());
      mf.nHits=MuTrk1->numberOfValidHits();
      mf.chi2=MuTrk1->normalizedChi2();
      TrackRef iTrack1 = mu->innerTrack();
      const reco::HitPattern& p1 = iTrack1->hitPattern();
      mf.nPixelHits=p1.pixelLayersWithMeasurement();
    } 
    if(mu->isGlobalMuon()){
      TrackRef gTrack = mu->globalTrack();
      const reco::HitPattern& q = gTrack->hitPattern();
      mf.globChi2=gTrack.get()->normalizedChi2();
      mf.globNHits=q.numberOfValidMuonHits();
    }else{
      mf.globChi2=-99;
      mf.globNHits=-99;
    }

    //     int muInfo[12];
    //     fillMuBlock(mu,  muInfo);
    if(runOnMC_){
      const GenParticle* muMc = mu->genLepton();
      if(muMc!=0){
	mf.mcId=muMc->pdgId();
	mf.mcFourMomentum=GENPTOLORP(muMc);
	if(muMc->mother()!=0) mf.mcMomId=muMc->mother()->pdgId();
	if(muMc->mother()!=0 && muMc->mother()->mother()!=0) mf.mcgMomId=muMc->mother()->mother()->pdgId();
      } }
    hbbInfo->muInfo.push_back(mf);
  }


  for(edm::View<pat::Electron>::const_iterator elec = electrons.begin(); elec!=electrons.end(); ++elec){
    VHbbEvent::ElectronInfo ef;
    ef.fourMomentum=GENPTOLORP(elec);
    ef.scEta =elec->superCluster()->eta();
    ef.scPhi =elec->superCluster()->phi();
    //    if(ElecEta[eleccont]!=0) ElecEt[eleccont]=elec->superCluster()->energy()/cosh(elec->superCluster()->eta());
    ef.charge=elec->charge();
    ef.tIso=elec->trackIso();
    ef.eIso=elec->ecalIso();
    ef.hIso=elec->hcalIso();
    Geom::Phi<double> deltaphi(elec->superCluster()->phi()-atan2(hbbInfo->calomet.fourMomentum.Py(),hbbInfo->calomet.fourMomentum.Px()));
    ef.acop = deltaphi.value();
    
    if(runOnMC_){
      const GenParticle* elecMc = elec->genLepton();
      if(elecMc!=0){
	ef.mcId=elecMc->pdgId();
	ef.mcFourMomentum=GENPTOLORP(elecMc);
	if(elecMc->mother()!=0) ef.mcMomId=elecMc->mother()->pdgId();
	if(elecMc->mother()!=0 && elecMc->mother()->mother()!=0) ef.mcgMomId=elecMc->mother()->mother()->pdgId();
      }}
    hbbInfo->eleInfo.push_back(ef);
  }

  for(edm::View<pat::Tau>::const_iterator tau = taus.begin(); tau!=taus.end(); ++tau){
    VHbbEvent::TauInfo tf;
    tf.fourMomentum=GENPTOLORP(tau);
    tf.charge=tau->charge();
    tf.tIso=tau->trackIso();
    tf.eIso=tau->ecalIso();
    tf.hIso=tau->hcalIso();
    Geom::Phi<double> deltaphi(tau->phi()-atan2(hbbInfo->calomet.fourMomentum.Py(),hbbInfo->calomet.fourMomentum.Px()));
    double acop = deltaphi.value();
    tf.acop=acop;
    tf.idbyIso=tau->tauID("byIsolation");
    tf.idbyTrackIso=tau->tauID("trackIsolation");
    tf.idbyTaNCfrOnePercent=tau->tauID("byTaNCfrOnePercent");
    tf.idbyTaNCfrHalfPercent=tau->tauID("byTaNCfrHalfPercent");
    tf.idbyTaNCfrQuarterPercent=tau->tauID("byTaNCfrQuarterPercent");
    tf.idbyTaNCfrTenthPercent=tau->tauID("byTaNCfrTenthPercent");  
    tf.idbyTaNC=tau->tauID("byTaNC");
    hbbInfo->tauInfo.push_back(tf);
  }


  // dimuons and dielectrons

  for( size_t i = 0; i < dimuons->size(); i++ ) {
    VHbbEvent::DiMuonInfo df;
    const Candidate & dimuonCand = (*dimuons)[ i ];
    df.fourMomentum= GENPTOLOR(dimuonCand);
    const Candidate * lep0 = dimuonCand.daughter( 0 );
    const Candidate * lep1 = dimuonCand.daughter( 1 );
    // needed to access specific methods of pat::Muon
    const pat::Muon & muonDau0 = dynamic_cast<const pat::Muon &>(*lep0->masterClone());
    const pat::Muon & muonDau1 = dynamic_cast<const pat::Muon &>(*lep1->masterClone());
    
    df.daughter1.fourMomentum=GENPTOLOR(muonDau0);
    df.daughter2.fourMomentum=GENPTOLOR(muonDau1);
    
    df.daughter1.tIso= muonDau0.trackIso();
    df.daughter2.tIso= muonDau1.trackIso();

    df.daughter1.eIso= muonDau0.ecalIso();
    df.daughter2.eIso= muonDau1.ecalIso();

    df.daughter1.hIso= muonDau0.hcalIso();
    df.daughter2.hIso= muonDau1.hcalIso();

    df.daughter1.ipDb=muonDau0.dB();
    df.daughter2.ipDb=muonDau1.dB();

    df.daughter1.ipErrDb=muonDau0.edB();
    df.daughter2.ipErrDb=muonDau1.edB();


    if(muonDau0.isGlobalMuon()) df.daughter1.cat =1;
    else if(muonDau0.isTrackerMuon()) df.daughter1.cat=2;
    else df.daughter1.cat=3;
    if(muonDau1.isGlobalMuon()) df.daughter2.cat =1;
    else if(muonDau1.isTrackerMuon()) df.daughter2.cat=2;
    else df.daughter2.cat=3;

    TrackRef trkMu1Ref = muonDau0.get<TrackRef>();
    TrackRef trkMu2Ref = muonDau1.get<TrackRef>();

    if(trkMu1Ref.isNonnull() && trkMu2Ref.isNonnull()){
      const Track* MuTrk1 = muonDau0.get<TrackRef>().get();
      const Track* MuTrk2 = muonDau1.get<TrackRef>().get();
      df.daughter1.zPVPt=MuTrk1->dz(RecVtxFirst.position());
      df.daughter1.zPVProb=MuTrk1->dz(RecVtx.position());
      df.daughter2.zPVPt=MuTrk2->dz(RecVtxFirst.position());
      df.daughter2.zPVProb=MuTrk2->dz(RecVtx.position());

      df.daughter1.nHits = MuTrk1->numberOfValidHits();
      df.daughter2.nHits = MuTrk2->numberOfValidHits();

      df.daughter1.chi2 = MuTrk1->normalizedChi2();
      df.daughter2.chi2 = MuTrk2->normalizedChi2();

      TrackRef iTrack1 = muonDau0.innerTrack();
      const reco::HitPattern& p1 = iTrack1->hitPattern();
      TrackRef iTrack2 = muonDau1.innerTrack();
      const reco::HitPattern& p2 = iTrack2->hitPattern();

      df.daughter1.nPixelHits = p1.pixelLayersWithMeasurement();
      df.daughter2.nPixelHits = p2.pixelLayersWithMeasurement();

      if(muonDau0.isGlobalMuon()){
	TrackRef gTrack = muonDau0.globalTrack();
	const reco::HitPattern& q = gTrack->hitPattern();
	df.daughter1.globNHits=q.numberOfValidMuonHits();
	df.daughter1.globChi2=gTrack.get()->normalizedChi2();
      }
      if(muonDau1.isGlobalMuon()){
	TrackRef gTrack = muonDau1.globalTrack();
	const reco::HitPattern& q = gTrack->hitPattern();
	df.daughter2.globNHits=q.numberOfValidMuonHits();
	df.daughter2.globChi2=gTrack.get()->normalizedChi2();
      }
  
    }
      
    hbbInfo->diMuonInfo.push_back(df);
  }

  for( size_t i = 0; i < dielectrons->size(); i++ ) {
    VHbbEvent::DiElectronInfo df;
    const Candidate & dielecCand = (*dielectrons)[ i ];

    df.fourMomentum=GENPTOLOR(dielecCand);

    // accessing the daughters of the dimuon candidate
    const Candidate * lep0 = dielecCand.daughter( 0 );
    const Candidate * lep1 = dielecCand.daughter( 1 );
    // needed to access specific methods of pat::Muon
    const pat::Electron & elecDau0 = dynamic_cast<const pat::Electron &>(*lep0->masterClone());
    const pat::Electron & elecDau1 = dynamic_cast<const pat::Electron &>(*lep1->masterClone());

    df.daughter1.fourMomentum = GENPTOLOR(elecDau0);
    df.daughter2.fourMomentum = GENPTOLOR(elecDau1);

    df.daughter1.tIso = elecDau0.trackIso();
    df.daughter2.tIso = elecDau1.trackIso();

    df.daughter1.eIso = elecDau0.ecalIso();
    df.daughter2.eIso = elecDau1.ecalIso();

    df.daughter1.hIso = elecDau0.hcalIso();
    df.daughter2.hIso = elecDau1.hcalIso();
    
    
    hbbInfo->diElectronInfo.push_back(df);
    
  }
  iEvent.put(hbbInfo);

}
  
void
HbbAnalyzerNew::fillMuBlock(edm::View<pat::Muon>::const_iterator mu, int muInfo[15])
{
  if(muon::isGoodMuon(*mu,muon::TMLastStationLoose)) muInfo[0]=1;
  if(muon::isGoodMuon(*mu,muon::TMLastStationTight)) muInfo[1]=1;
  if(muon::isGoodMuon(*mu,muon::TM2DCompatibilityLoose)) muInfo[2]=1;
  if(muon::isGoodMuon(*mu,muon::TM2DCompatibilityTight)) muInfo[3]=1;
  if(muon::isGoodMuon(*mu,muon::TMOneStationLoose)) muInfo[4]=1;
  if(muon::isGoodMuon(*mu,muon::TMOneStationTight)) muInfo[5]=1;
  if(muon::isGoodMuon(*mu,muon::TMLastStationOptimizedLowPtLoose)) muInfo[6]=1;
  if(muon::isGoodMuon(*mu,muon::TMLastStationOptimizedLowPtTight))muInfo[7]=1;
  if(muon::isGoodMuon(*mu,muon::TMOneStationAngLoose)) muInfo[8]=1;
  if(muon::isGoodMuon(*mu,muon::TMOneStationAngTight)) muInfo[9]=1;
  if(muon::isGoodMuon(*mu,muon::TMLastStationAngLoose)) muInfo[10]=1;
  if(muon::isGoodMuon(*mu,muon::TMLastStationAngTight)) muInfo[11]=1;
  if(muon::isGoodMuon(*mu,muon::GMTkChiCompatibility)) muInfo[12]=1;
  if(muon::isGoodMuon(*mu,muon::GMStaChiCompatibility)) muInfo[13]=1;
  if(muon::isGoodMuon(*mu,muon::GMTkKinkTight)) muInfo[14]=1;
}

// ------------ method called once each job just before starting event loop  ------------
void 
HbbAnalyzerNew::beginJob(){
}


// ------------ method called once each job just after ending the event loop  ------------
void 
HbbAnalyzerNew::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HbbAnalyzerNew);
