#include <TH2.h>
#include <TFile.h>
#include <cmath>
#include <iostream>
#include <string>

TH2 * FR_2lss_mu = 0;
TH2 * FR_2lss_el = 0;

bool loadFRHisto(const std::string &histoName, const char *file, const char *name) {
    TH2 **histo = 0;
    if (histoName == "FR_ttlMC_mu") histo = & FR_ttlMC_mu;
    if (histoName == "FR_ttlMC_el") histo = & FR_ttlMC_el;
    if (histo == 0)  {
        std::cerr << "ERROR: histogram " << histoName << " is not defined in fakeRate.cc." << std::endl;
        return 0;
    }

    if (*histo != 0) delete *histo;
    TFile *f = TFile::Open(file);
    if (f->Get(name) == 0) {
        std::cerr << "ERROR: could not find " << name << " in " << file << std::endl;
        *histo = 0;
    } else {
        *histo = (TH2*) f->Get(name)->Clone(name);
        (*histo)->SetDirectory(0);
    }
    f->Close();
    return histo != 0;
}

float fakeRateWeight_2lss(float l1pt, float l1eta, int l1pdgId, float l1mva,
                         float l2pt, float l2eta, int l2pdgId, float l2mva) 
{
    int nfail = (l1mva < -0.2)+(l2mva < -0.2);
    switch (nfail) {
        case 1: {
            double fpt,feta; int fid;
            if (l1mva < l2mva) { fpt = l1pt; feta = std::abs(l1eta); fid = abs(l1pdgId); }
            else               { fpt = l2pt; feta = std::abs(l2eta); fid = abs(l2pdgId); }
            TH2 *hist = (fid == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt)));
            int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta)));
            double fr = hist->GetBinContent(ptbin,etabin);
            return fr/(1-fr);
        }
        case 2: {
            TH2 *hist1 = (abs(l1pdgId) == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(l1pt)));
            int etabin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(std::abs(l1eta))));
            double fr1 = hist1->GetBinContent(ptbin1,etabin1);
            TH2 *hist2 = (abs(l2pdgId) == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin2  = std::max(1, std::min(hist2->GetNbinsX(), hist2->GetXaxis()->FindBin(l2pt)));
            int etabin2 = std::max(1, std::min(hist2->GetNbinsY(), hist2->GetYaxis()->FindBin(std::abs(l2eta))));
            double fr2 = hist2->GetBinContent(ptbin2,etabin2);
            return fr1*fr2/((1-fr1)*(1-fr2));
        }
        default: return 0;
    }
}


float fakeRateWeight_3l(float l1pt, float l1eta, int l1pdgId, float l1mva,
			float l2pt, float l2eta, int l2pdgId, float l2mva,
			float l3pt, float l3eta, int l3pdgId, float l3mva) 
{
  int nfail = (l1mva < -0.2)+(l2mva < -0.2)+(l3mva < -0.2);
  double mvas[]={l1mva, l2mva, l3mva};
  double pts[]={l1pt, l2pt, l3pt};
  double etas[]={l1eta, l2eta, l3eta};
  int pdgids[]={l1pdgId, l2pdgId, l3pdgId};
  multimap<double,double> ptBymva;
  multimap<double,double> etaBymva;
  multimap<int,double> pdgidBymva;
  for (unsigned int i = 0; i < 3 ; ++i){
    ptBymva.insert(pair<double,double>(pts[i],mvas[i]));
    etaBymva.insert(pair<double,double>(etas[i],mvas[i]));
    pdgidBymva.insert(pair<double,double>(pdgids[i],mvas[i]));
  }
  multimap<float,int>::iterator ptmavait = ptBymva.begin();
  multimap<float,int>::iterator etamvait = etaBymva.begin();
  multimap<float,int>::iterator pdgidmvait = pdgidBymva.begin();
  

    switch (nfail) {
        case 1: {
            double fpt,feta; int fid;
	    fpt = ptmvait->first; feta = std::abs(etamvait->first); fid = abs(ptmvait->first);
	    TH2 *hist = (fid == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt)));
            int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta)));
            double fr = hist->GetBinContent(ptbin,etabin);
            return fr/(1-fr);
        }
        case 2: {
	    double fpt1,feta1; int fid1;
	    double fpt2,feta2; int fid2;
	    fpt1 = ptmvait->first; feta1 = std::abs(etamvait->first); fid1 = abs(ptmvait->first); 
	    fpt2 = (ptmvait+1)->first; feta2 = std::abs((etamvait+1)->first); fid2 = abs((ptmvait+1)->first); 
	    TH2 *hist1 = (fid1 == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin1  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt1)));
            int etabin1 = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta1)));
            double fr1 = hist1->GetBinContent(ptbin1,etabin1);
	    TH2 *hist2 = (fid2 == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin2  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt2)));
            int etabin2 = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta2)));
            double fr2 = hist2->GetBinContent(ptbin2,etabin2);
	    return fr1*fr2/((1-fr1)*(1-fr2));
        }
        case 3: {
	    TH2 *hist1 = (abs(l1pdgId) == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(l1pt)));
            int etabin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(std::abs(l1eta))));
            double fr1 = hist1->GetBinContent(ptbin1,etabin1);
            TH2 *hist2 = (abs(l2pdgId) == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin2  = std::max(1, std::min(hist2->GetNbinsX(), hist2->GetXaxis()->FindBin(l2pt)));
            int etabin2 = std::max(1, std::min(hist2->GetNbinsY(), hist2->GetYaxis()->FindBin(std::abs(l2eta))));
            double fr2 = hist2->GetBinContent(ptbin2,etabin2);
	    TH2 *hist3 = (abs(l3pdgId) == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin3  = std::max(1, std::min(hist3->GetNbinsX(), hist3->GetXaxis()->FindBin(l3pt)));
            int etabin3 = std::max(1, std::min(hist3->GetNbinsY(), hist3->GetYaxis()->FindBin(std::abs(l3eta))));
            double fr3 = hist3->GetBinContent(ptbin3,etabin3);
            return fr1*fr2*fr3/((1-fr1)*(1-fr2)*(1-fr3));

	}

        default: return 0;
    }
}


float fakeRateWeight_4l(float l1pt, float l1eta, int l1pdgId, float l1mva,
			float l2pt, float l2eta, int l2pdgId, float l2mva,
			float l3pt, float l3eta, int l3pdgId, float l3mva,
			float l4pt, float l4eta, int l4pdgId, float l4mva) 
{
  int nfail = (l1mva < -0.2)+(l2mva < -0.2)+(l3mva < -0.2)+(l4mva < -0.2);
  double mvas[]={l1mva, l2mva, l3mva, l4mva};
  double pts[]={l1pt, l2pt, l3pt, l4pt};
  double etas[]={l1eta, l2eta, l3eta, l4eta};
  int pdgids[]={l1pdgId, l2pdgId, l3pdgId, l4pdgId};
  multimap<double,double> ptBymva;
  multimap<double,double> etaBymva;
  multimap<int,double> pdgidBymva;
  for (unsigned int i = 0; i < 4 ; ++i){
    ptBymva.insert(pair<double,double>(pts[i],mvas[i]));
    etaBymva.insert(pair<double,double>(etas[i],mvas[i]));
    pdgidBymva.insert(pair<double,double>(pdgids[i],mvas[i]));
  }
  multimap<float,int>::iterator ptmavait = ptBymva.begin();
  multimap<float,int>::iterator etamvait = etaBymva.begin();
  multimap<float,int>::iterator pdgidmvait = pdgidBymva.begin();
  
    switch (nfail) {
        case 1: {
            double fpt,feta; int fid;
            fpt = ptmvait->first; feta = std::abs(etamvait->first); fid = abs(ptmvait->first);
            TH2 *hist = (fid == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt)));
            int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta)));
            double fr = hist->GetBinContent(ptbin,etabin);
            return fr/(1-fr);
        }
        case 2: {
	    double fpt1,feta1; int fid1;
	    double fpt2,feta2; int fid2;
	    fpt1 = ptmvait->first; feta1 = std::abs(etamvait->first); fid1 = abs(ptmvait->first); 
	    fpt2 = (ptmvait+1)->first; feta2 = std::abs((etamvait+1)->first); fid2 = abs((ptmvait+1)->first);
	    TH2 *hist1 = (fid1 == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin1  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt1)));
            int etabin1 = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta1)));
            double fr1 = hist1->GetBinContent(ptbin1,etabin1);
	    TH2 *hist2 = (fid2 == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin2  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt2)));
            int etabin2 = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta2)));
            double fr2 = hist2->GetBinContent(ptbin2,etabin2);
	    return fr1*fr2/((1-fr1)*(1-fr2));
        }
        case 3: {
            double fpt1,feta1; int fid1;
	    double fpt2,feta2; int fid2;
	    double fpt3,feta3; int fid3;
	    fpt1 = ptmvait->first; feta1 = std::abs(etamvait->first); fid1 = abs(ptmvait->first); 
	    fpt2 = (ptmvait+1)->first; feta2 = std::abs((etamvait+1)->first); fid2 = abs((ptmvait+1)->first);
	    fpt3 = (ptmvait+2)->first; feta3 = std::abs((etamvait+2)->first); fid3 = abs((ptmvait+2)->first);
	    TH2 *hist1 = (fid1 == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin1  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt1)));
            int etabin1 = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta1)));
            double fr1 = hist1->GetBinContent(ptbin1,etabin1);
	    TH2 *hist2 = (fid2 == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin2  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt2)));
            int etabin2 = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta2)));
            double fr2 = hist2->GetBinContent(ptbin2,etabin2);
	    TH2 *hist3 = (fid3 == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin3  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(fpt3)));
            int etabin3 = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(feta3)));
            double fr3 = hist3->GetBinContent(ptbin3,etabin3);
            return fr1*fr2*fr3/((1-fr1)*(1-fr2)*(1-fr3));
	}
        
        case 4: {
            TH2 *hist1 = (abs(l1pdgId) == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin1  = std::max(1, std::min(hist1->GetNbinsX(), hist1->GetXaxis()->FindBin(l1pt)));
            int etabin1 = std::max(1, std::min(hist1->GetNbinsY(), hist1->GetYaxis()->FindBin(std::abs(l1eta))));
            double fr1 = hist1->GetBinContent(ptbin1,etabin1);
            TH2 *hist2 = (abs(l2pdgId) == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin2  = std::max(1, std::min(hist2->GetNbinsX(), hist2->GetXaxis()->FindBin(l2pt)));
            int etabin2 = std::max(1, std::min(hist2->GetNbinsY(), hist2->GetYaxis()->FindBin(std::abs(l2eta))));
            double fr2 = hist2->GetBinContent(ptbin2,etabin2);
	    TH2 *hist3 = (abs(l3pdgId) == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin3  = std::max(1, std::min(hist3->GetNbinsX(), hist3->GetXaxis()->FindBin(l3pt)));
            int etabin3 = std::max(1, std::min(hist3->GetNbinsY(), hist3->GetYaxis()->FindBin(std::abs(l3eta))));
            double fr3 = hist3->GetBinContent(ptbin3,etabin3);
	    TH2 *hist4 = (abs(l4pdgId) == 11 ? FR_ttlMC_el : FR_ttlMC_mu);
            int ptbin4  = std::max(1, std::min(hist4->GetNbinsX(), hist4->GetXaxis()->FindBin(l4pt)));
            int etabin4 = std::max(1, std::min(hist4->GetNbinsY(), hist4->GetYaxis()->FindBin(std::abs(l4eta))));
            double fr4 = hist4->GetBinContent(ptbin4,etabin4);
	    
            return fr1*fr2*fr3*fr4/((1-fr1)*(1-fr2)*(1-fr3)*(1-fr4));
	}  

        default: return 0;
    }
}









void fakeRate() {}
