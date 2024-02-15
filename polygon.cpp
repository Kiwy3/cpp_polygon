#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>

using namespace std;

double Polygon::norme(double x1, double y1, double x2, double y2){ //renvoit la norme d'un vecteur selon les coordonnees de 2 points
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

double Polygon::angle(double x1, double y1, double x2, double y2, double x3, double y3){ //renvoit l'angle entre deux vecteurs
	double num=(x2-x1)*(x3-x2)+(y2-y1)*(y3-y2);
	double den=(norme(x1, y1, x2, y2)*norme(x2, y2, x3, y3));
	double ans=acos(num/den);
	return ans;
}
bool Polygon::align(double x1,double y1, double x2, double y2, double x3, double y3 ){
	double coef = (y3-y1)/(x3-x1);
	double ord_ori = y3 - coef*x3;
	bool ans = false;
	
	if (y2 == coef * x2 + ord_ori) ans = true;
	
	return ans;
}

void Polygon::clean(){
	while(align(X[-2],Y[-2],X[0],Y[0],X[1],Y[1])) {
		//erase the first point and replace the copy of the first point at the end
		X.erase(X.begin());
		Y.erase(Y.begin());
		X[-1]=X[0];
		Y[-1]=Y[0];
		n--;
		
	}
	for (int i = 1;i<n;i++){
		if (align(X[i-1],Y[i-1],X[i],Y[i],X[i+1],Y[i+1])){
			X.erase(X.begin()+i);
			Y.erase(Y.begin()+i);
			
			n=n-1;
			i--;
			
		}		
	}	
}

bool Polygon::cut(double x1,double y1, double x2, double y2, double x3, double y3,double x4, double y4){
	//Coeff directeur et ordonnée a l'origine des 2 droites
	double a = (y2-y1)/(x2-x1);
	double b = y2 - a*x2;
	double c = (y4-y3)/(x4-x3);
	double d = y4 - c*x4;
	bool ans = false;
	if (c!=a) {
		double xT = (b-d)/(c-a);
		if (min(x1,x2)<= xT && max(x1,x2)>=xT && max(x3,x4)>=xT && min(x3,x4)<= xT) ans = true;
	}
	return ans;
}
double Polygon::T_area(double x1,double y1, double x2, double y2, double x3, double y3){	
	double x_max = max(max(x3,x1),x2);
	double x_min = min(min(x3,x1),x2);
	double base = x_max - x_min;
	double y_max = max(max(y3,y1),y2);
	double y_min = min(min(y3,y1),y2);
	double hauteur = y_max-y_min;		
	return base*hauteur/2;	
}

void Polygon::create(){
	n=0;
	X.clear();
	Y.clear();
}

void Polygon::load(){
    string file;
    bool premiereLigne=true;
    std::string ligne;
    int i=0;
    //cout << "Saisir le nom du fichier : " << endl;
    //cin >> file;
    //file=file+".txt";
    
    file ="carre.txt"; //pour le debug uniquement : ecrire direct la dedans le nom du fichier
    
    ifstream fichier(file.c_str()); //On ouvre le fichier

    if(fichier)  //On teste si tout est OK
    {
    	cout<<"Fichier "<<file<< " ouvert avec succes !"<< endl;
   	 
    	while(getline(fichier, ligne)){
   		 
   		 if (premiereLigne==true){ //on recupere n et on dimensionne les vecteurs X et Y
   			 premiereLigne=false;
   			 std::istringstream strm(ligne);
   			 strm>>n;
   			 X.resize(n+1);
   			 Y.resize(n+1);
   		 }
   		 else{
   			 std::istringstream strm(ligne);
   			 strm>>X[i]>>Y[i];
   			 i++;
   		 }
   		 
   	 }
    }
    else
    {
    	cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
    X[n]=X[0]; //on ajoute le 1er compossant a la fin
    Y[n]=Y[0];
    clean();
}	


bool Polygon::regular(){
	bool regulier = true;
	double tailleCote = norme(X[0], Y[0], X[1], Y[1]);
	double tailleAngle= angle(X[0], Y[0], X[1], Y[1], X[2], Y[2]);
	for(int i=1; i<n;i++){ //On verifie que tout les cotes ont la meme norme
  	  if (norme(X[i], Y[i], X[i+1], Y[i+1])>=tailleCote+0.01 or norme(X[i], Y[i], X[i+1], Y[i+1])<=tailleCote-0.01){
  		  regulier =  false;
  	  }
	}
	for(int i=1; i<n;i++){ //On verifie que tout les angles soient les memes
	
  	  if(i==n-1){
  		  if (angle(X[i], Y[i], X[i+1], Y[i+1], X[1], Y[1])>=tailleAngle+0.01 or angle(X[i], Y[i], X[i+1], Y[i+1], X[1], Y[1])<=tailleAngle-0.01){
			regulier =  false;
  		  }
  	  }
  	  else {
		if (angle(X[i], Y[i], X[i+1], Y[i+1], X[i+2], Y[i+2])>=tailleAngle+0.01 or angle(X[i], Y[i], X[i+1], Y[i+1], X[i+2], Y[i+2])<=tailleAngle-0.01){
  		  regulier =  false;
  	  }
  }
	}
	return regulier;
}


void Polygon::afficher(){
    cout<<"Polygone de "<<n<<" sommets"<<endl;
    cout<<" X ; Y "<<endl;
    for(int i=0; i<=n; i++){
   	 cout<<X[i]<<" ; "<<Y[i]<<endl;
    }
    cout<<endl;
    cout<<"Convexe ? "<<(convex()?"oui":"non")<<endl;
    cout<<"Simple ? "<<(simple()?"oui":"non")<<endl;
    cout<<"Regulier ? "<<(regular()?"oui":"non")<<endl;
    cout<<"Perimetre : "<<perimeter()<<endl;
    cout<<"Aire : "<<area()<<endl;
	

    cout<<endl;
}


double Polygon::perimeter(){
	double len=0;
	for (int i = 1;i<=n;i++) {
	len += norme(X[i-1],Y[i-1],X[i],Y[i]);
	}
	
	return len;
}


bool Polygon::simple (){
	bool ans = true;	
	
	for (int i = 0;i<n;i++){
		for (int k = i;k<n;k++){
			int diff = abs(i-k);
			if ((diff>1 & diff<n-1)&cut(X[i],Y[i],X[i+1],Y[i+1],X[k],Y[k],X[k+1],Y[k+1])){
				ans = false;
			}
		}
	}
	
	return ans;
}

bool Polygon::inside(double x,double y){
	int numCrossings = 0;

    for (int i = 0; i < n; i++) {
        double x1 = X[i];
        double y1 = Y[i];
        double x2 = X[(i + 1) % n];
        double y2 = Y[(i + 1) % n];
		bool YA = (y1 >= y) != (y2 > y);
        // Verifier si la ligne horizontale passant par le point coupe le segment
        if ((y1 >= y) != (y2 > y) &&
            x >= (x2 - x1) * (y - y1) / (y2 - y1) + x1) {
            numCrossings++;
        }
    }
    // Le point est à l'intérieur du polygone si le nombre de croisements est impair
    return (numCrossings % 2 == 1);
}
	

double Polygon::area(){
	double res = 0;
	
	for (int i = 0; i <= n-1; i++) {
		res += X[i]*Y[i+1]-X[i+1]*Y[i];				
	}
	
	res = abs(res/2);
	return res;
}

bool Polygon::convex(){
	if (n==3){
  	  return true;
	}
	double coef, b; //identification d'une droite d'equation y=coef*x + b
	bool supInitial, sup;
	for(int i=0; i<n;i++){
  	  coef=((Y[i+1]-Y[i])/(X[i+1]-X[i]));
  	  b=-coef*X[i]+Y[i];
  	  if (i!=n-1){
  		  if(coef*X[i+2]+b>=Y[i+2]){ //on teste si un point est au dessus ou en dessous de la droite determinee
  			  supInitial=false;
  		  }
  		  else{
  			  supInitial=true;
  		  }
  	  }
  	  else{
  		  if(coef*X[1]+b>=Y[1]){ //on teste si un point est au dessus ou en dessous de la droite determinee
  			  supInitial=false;
  		  }
  		  else{
  			  supInitial=true;
  			  }
  	  }
  	  for(int j=0; j<n;j++){ //on teste la position relative de tout les points du polygone pour la droite determinee
  	      if((j==0 and i==n) or (j==0 and i+1==n)){
  	     	 continue;
   		 }
  		 if(j!=i and j!=i+1){
  			  if(coef*X[j]+b>=Y[j]){
  				  sup=false;
  			  }
  			  else{
  				  sup=true;
  			  }
  			  if (sup!=supInitial){ //on compare la position du point j avec celle du point initial
  				  return false;
  			  }
  		  }
  	  }
	}
	return true;
}
