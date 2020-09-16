//Test if a point is inside a triangle.
// By Julian Saknussemm
// JOVANNI TJUANDI (z5213864)

#include <stdio.h>

#define SCANS 8


int test2(double px, double py, double m, double b) {
    if (py < m * px + b) {
        return -1; // point is under line
   } else if (py == m * px + b) {
        return 0;
   } else {
        return 1; // over the line
   } 
}

// test if two points lie on the same side of a line
int test1(double px, double py, double m,double b, double lx,double ly) {
    return (test2(px,py, m,b)==test2(lx,ly,m,b));
}

int tritest(double x0,double y0,double x1,double y1,double x2,double y2,double px, double py){

   int line1, line2, line3; // line eqns
   double m02, m12, b02, b12, m01, b01; // b: y - y1 = m(x - x1), x = 0

   // vertical line checks
   if(x1 == x0) {
      line1 = ((px <= x0) == (x2 <= x0));
   } else {
      m01 = (y1-y0)/(x1-x0);
      b01 = m01 * -x1 + y1;
      line1 = test1(px, py, m01, b01,x2,y2);
   }
    
   if(x1 == x2) {
      line2 = ((px <= x2) == (x0 <= x2));
   } else {
      m12 = (y2-y1)/(x2-x1);
      b12 = m12 * -x2 + y2;
      line2 = test1(px,py, m12, b12,x0,y0);
   }
    
   if(x2 == x0) {
      line3 = ((px <= x0) == (x1 <= x0));
   } else {
      m02 = (y2-y0)/(x2-x0);
      b02 = m02 * -x2 + y2;
      line3 = test1(px, py, m02,b02,x1,y1);
   }
    
   return line1 && line2 && line3;
}

int main (void) {

   double x0,y0,x1,y1,x2,y2,px,py;
   int TotalScanfsReturnValue = 0;

   // get input
   printf("Triangle Vertex A (x,y): ");
      TotalScanfsReturnValue += scanf("%lf,%lf",&x0,&y0);
   printf("Triangle Vertex  B (x,y): ");
      TotalScanfsReturnValue += scanf("%lf,%lf",&x1,&y1);
   printf("Triangle Vertex  C (x,y): ");
      TotalScanfsReturnValue += scanf("%lf,%lf",&x2,&y2);
   printf("Test Point (x,y): ");
      TotalScanfsReturnValue += scanf("%lf,%lf",&px,&py);

   // print error
   if(TotalScanfsReturnValue != SCANS) {
      printf("You're stupid and didn't put in the right inputs!\n");
      return 1;
   }

   // print answer
   printf("Point (%.2lf,%.2lf) is ", px,py);
   if(tritest(x0,y0,x1,y1,x2,y2,px,py)) {
      printf("inside");
   } else {
      printf("outside the Triangle\n");
   } 

   return 0;
}

