#ifndef GENERICHISTOGRAMS_H_
#define GENERICHISTOGRAMS_H_

#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "CMGTools/Common/interface/HistogramCreator.h"

#include <string>
#include <map>
#include <memory>
#include <vector>

namespace cmg{
  
  template<class T>
  class GenericHistograms : public cmg::HistogramCreator<T>{
    protected:
        
        typedef StringObjectFunction<T> function;
        struct HistogramAxis{
            public:
                function fn_;
                std::string obs_;
                float low_;
                float high_;
                int nbins_;
                HistogramAxis(const std::string& obs,const float low,const float high,const int nbins):
                    fn_(obs),
                    obs_(obs),low_(low),high_(high),nbins_(nbins){
                    }
        };
        typedef std::map<std::string, std::vector<HistogramAxis> > Histograms;

    public:
 
        GenericHistograms(const edm::ParameterSet& ps):
            cmg::HistogramCreator<T>::HistogramCreator(ps),
            histos_(new Histograms){
                initHistograms(ps.getParameter<edm::ParameterSet>("histograms"));
        }
        
        virtual void fill(const T& cand);
        virtual void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup){
            cmg::HistogramCreator<T>::fill(iEvent,iSetup);
        }

     protected:

        virtual void defineHistograms();
        void initHistograms(const edm::ParameterSet& ps);
        const std::auto_ptr<Histograms> histos_;
        
        
};

}

template<class T>
void cmg::GenericHistograms<T>::initHistograms(const edm::ParameterSet& ps){
    
    std::vector<std::string> parameterNames = ps.getParameterNames();
    for(std::vector<std::string>::const_iterator n = parameterNames.begin(); n != parameterNames.end(); n++){
        std::string name = *n;
        std::vector<edm::ParameterSet> axes = ps.getParameter<std::vector<edm::ParameterSet> >(name);
        std::vector<HistogramAxis> ax;
        for(std::vector<edm::ParameterSet>::const_iterator a = axes.begin(); a != axes.end(); a++){
            //parameters for the histogram
            const std::string var = a->getParameter<std::string>("var");
            const double low = a->getParameter<double>("low");
            const double high = a->getParameter<double>("high");
            const int nbins = a->getParameter<int>("nbins");
            ax.push_back(HistogramAxis(var,low,high,nbins));
            std::cout << name << " Axis: " << var << "\t" << low << "\t" << high << "\t" << nbins << std::endl;
        }
        (*histos_)[name] = ax;
    }    
}

template<class T>
void cmg::GenericHistograms<T>::defineHistograms(){
    
    for(typename Histograms::const_iterator it = histos_->begin(); it != histos_->end(); it++){
           const unsigned int size = it->second.size();
           switch(size){
                case 1:
                    {   
                        HistogramAxis axis = it->second.at(0);
                        add1DHistogram(it->first,it->first,
                        axis.nbins_,axis.low_,axis.high_,
                        cmg::HistogramCreator<T>::fs_.operator->());
                        break;
                    }
                case 2:
                    {
                        HistogramAxis axisX = it->second.at(0);
                        HistogramAxis axisY = it->second.at(1);   
                        add2DHistogram(it->first,it->first,
                        axisX.nbins_,axisX.low_,axisX.high_,
                        axisY.nbins_,axisY.low_,axisY.high_,
                        cmg::HistogramCreator<T>::fs_.operator->());
                        break;
                    }                   
                case 3:
                    {
                        HistogramAxis axisX = it->second.at(0);
                        HistogramAxis axisY = it->second.at(1);
                        HistogramAxis axisZ = it->second.at(2);   
                        
                        add3DHistogram(it->first,it->first,
                        axisX.nbins_,axisX.low_,axisX.high_,
                        axisY.nbins_,axisY.low_,axisY.high_,
                        axisZ.nbins_,axisZ.low_,axisZ.high_,
                        cmg::HistogramCreator<T>::fs_.operator->());
                        break;
                    }
                default:
                        std::cerr << "Unsupported number of variables for histogram " << it->first << std::endl;
           }         
    }
}

template<class T>
void cmg::GenericHistograms<T>::fill(const T& cand){
    
    for(typename Histograms::const_iterator it = histos_->begin(); it != histos_->end(); it++){
        const unsigned int size = it->second.size();
        switch(size){
            case 1:
                    {   
                        HistogramAxis axis = it->second.at(0);
                        fill1DHistogram(it->first,axis.fn_(cand));
                        break;
                    }
           case 2:
                    {
                        HistogramAxis axisX = it->second.at(0);
                        HistogramAxis axisY = it->second.at(1);   
                        fill2DHistogram(it->first,axisX.fn_(cand),axisY.fn_(cand));
                        break;
                    }                   
           case 3:
                    {
                        HistogramAxis axisX = it->second.at(0);
                        HistogramAxis axisY = it->second.at(1);
                        HistogramAxis axisZ = it->second.at(2);   
                        fill3DHistogram(it->first,axisX.fn_(cand),axisY.fn_(cand),axisZ.fn_(cand));
                        break;
                    }
           default:
                        std::cerr << "Unsupported number of variables for histogram " << it->first << std::endl;
           }         
    }
}


#endif /*GENERICHISTOGRAMS_H_*/
