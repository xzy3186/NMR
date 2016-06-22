//define lineshapes of the NMR spectrum with different modulations (ramp, and sine).
#include <math.h>
const double PI = 3.141592653589793;

Double_t LineShapeMarieke(Double_t *x, Double_t *p){
   //the function is taken from the Ph.D thesis of M.De Rydt, Eq. 5.16.
   //The integration can be calculated analytically and the result can be found
   //in the masterplan of E650.
   return p[0]+p[1]-p[1]*pow(0.5/p[3],2)*pow(sqrt(pow(p[2]-x[0]+p[3],2)+pow(p[4],2))-sqrt(pow(p[2]-x[0]-p[3],2)+pow(p[4],2)),2);
}

Double_t LineShapeRamp(Double_t *x, Double_t *p){
   //the function is taken from the Ph.D thesis of D.Yordanov, Eq. 2.68.
   double LS = atan(2*(x[0]-p[2]+p[3])/p[4]) - atan(2*(x[0]-p[2]-p[3])/p[4]);
   double Norm = 2*atan(2*p[3]/p[4]);
   double NormLS = LS/Norm;
   return p[0] + p[1] * NormLS;
}

double GaussChebyshevInt(int NNodes, double x, double cent, double mod, double width){
   //the function is taken from the Ph.D thesis of D.Yordanov. The form of
   //Gauss-Chebyshev integration is taken from Wikipedia.
   double sum = 0;
   for(int i=0; i<NNodes; i++){
      double xi = cos(PI*(2*i-1)/NNodes);
      double wi = PI/NNodes;
      sum = sum + 1/(1+pow((2*(mod*xi+x-cent)/width),2))*wi;
   }
   return sum;
}

Double_t LineShapeSine(Double_t *x, Double_t *p){
   //the function is taken from the Ph.D thesis of D.Yordanov, Eq. 2.69.
   //the numerical integration is carried out by the Gauss-Chebyshev
   //integration.
   double basel = p[0]; //baseline
   double amp = p[1]; //amplitude
   double cent = p[2]; //centroid
   double mod = p[3]; //modulation
   double width = p[4]; //width
   double NormLS = GaussChebyshevInt(50,x[0],cent,mod,width)/GaussChebyshevInt(50,cent,cent,mod,width);
   return basel + amp * NormLS;
}
