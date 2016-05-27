#include "TMath.h"

double Eff_gh_hg(double e){
   double eff;
   eff = (902.5-609.7*log(e)+131.8*pow(log(e),2)-8.906*pow(log(e),3))/e;
   return eff;
}

double Eff_gh_lg(double e){
   double eff;
   eff = (-294.3+93.28*log(e)-5.459*pow(log(e),2))/e;
   return eff;
}

double Eff_gg_hg(double e){
   double eff;
   eff = (223.3-167.5*log(e)+40.46*pow(log(e),2)-2.999*pow(log(e),3))/e;
   return eff;
}

double Eff_gg_lg(double e){
   double eff;
   eff = (-278.6+141.6*log(e)-22.03*pow(log(e),2)+1.155*pow(log(e),3))/e;
   return eff;
}
