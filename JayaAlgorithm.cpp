#include<bits/stdc++.h>
using namespace std;
int Xmax=100,Xmin=-100;//Xi values ranges given

float evaluate(vector<float> xval){
	float ans=0;
	for(int i=1;i<xval.size()-1;i++){
		ans += xval[i]*xval[i];
	}
	return ans;
}
int bestfx(vector<float>fxval){
	return min_element(fxval.begin(),fxval.end())-fxval.begin();
}
int worstfx(vector<float>fxval){
	return max_element(fxval.begin(),fxval.end())-fxval.begin();
}
int main(){
	srand(time(NULL));
	int pop_count,var_count,maxitr;
	float Bestvalue;
	cout<<"Enter the size of the population"<<endl;
	cin>>pop_count;
	cout<<"Enter the count of features"<<endl;
	cin>>var_count;
	cout<<"enter no of iteration you want to execute:"<<endl;
	cin>>maxitr;
	//declare 2d array for storing the values
	vector<vector<float> >population(pop_count+1,vector<float>(var_count+2));
	for(int i=1;i<=pop_count;i++){
		for(int j=1;j<=var_count;j++){
			population[i][j]=rand()%(Xmax-Xmin+1)+Xmin;
		}
	}
	vector<float>fxvalues(pop_count+1); //stores fx values means value of last colum  of the 2d array
	//now calculate function values
	for(int i=1;i<=pop_count;i++){
		fxvalues[i]=population[i][var_count+1]=evaluate(population[i]);
	}
	int itr=0;
	while(++itr<=maxitr){
		//Now find best and worst values Index
	int bestIndex=bestfx(fxvalues);
	int worstIndex=worstfx(fxvalues);
	//now calculate Newxval
	vector<vector<float> >Newpopulation(pop_count+1,vector<float>(var_count+2));
	float r1=(float)rand()/RAND_MAX,r2=(float)rand()/RAND_MAX;	
//	cout<<r1 <<" "<< r2 <<endl;
	for(int i=1;i<=pop_count;i++){
		for(int j=1;j<=var_count;j++){
			Newpopulation[i][j]=population[i][j]+r1 *(population[bestIndex][j] - abs(population[i][j]))
			 -r2*(population[worstIndex][j] - abs(population[i][j]));
		}
	}
	vector<float>Newfxvalues(pop_count+1); //stores fx values means value of last colum  of the 2d array
	//now calculate function values
	for(int i=1;i<=pop_count;i++){
		fxvalues[i]=population[i][var_count+1]=evaluate(population[i]);
		Newfxvalues[i]=Newpopulation[i][var_count+1]=evaluate(Newpopulation[i]);
	}
	vector<float> Allfxvalues(fxvalues.begin(),fxvalues.end());
//	Allfxvalues.insert(Allfxvalues.end(),Newfxvalues.begin(),Newfxvalues.end());
	for(auto val:Newfxvalues){
		Allfxvalues.push_back(val);
	}
	sort(Allfxvalues.begin(),Allfxvalues.end());
	Allfxvalues=vector<float>(Allfxvalues.begin()+2,Allfxvalues.begin()+2+pop_count);
	int k=1;//used as counter
	vector<vector<float> >Finalpopulation(pop_count+1,vector<float>(var_count+2));
	for(int i=1;i<=pop_count;i++){
		if(find(Allfxvalues.begin(),Allfxvalues.end(),population[i][var_count+1])!=Allfxvalues.end()){
			Finalpopulation[k++]=population[i];
		}
	}
		for(int i=1;i<=pop_count;i++){
					if(k>pop_count)break;
		if(find(Allfxvalues.begin(),Allfxvalues.end(),Newpopulation[i][var_count+1])!=Allfxvalues.end()){
			Finalpopulation[k++]=Newpopulation[i];
		}
	}
	cout<<"********************************"<<endl;
	cout<<"Iteration number :"<<itr<<endl;
	for (int i=1;i<=pop_count;i++){
		for(int j=1;j<=var_count+1;j++){
			cout<<population[i][j]<<" ";
//			population[i][j]=Finalpopulation[i][j];
		}
		cout<<endl;
	}
		cout<<" New population value : "<<endl;
		for (int i=1;i<=pop_count;i++){
		for(int j=1;j<=var_count+1;j++){
			cout<<Newpopulation[i][j]<<" ";
//			population[i][j]=Finalpopulation[i][j];
		}
		cout<<endl;
	}
	cout<<endl;
		for (int i=1;i<=pop_count;i++){
		for(int j=1;j<=var_count+1;j++){
			cout<<Finalpopulation[i][j]<<" ";
			population[i][j]=Finalpopulation[i][j];
		}
		cout<<endl;
	}
	 Bestvalue=*(min_element(Allfxvalues.begin(),Allfxvalues.end()));
		cout<<" final fx values"<<endl;
	for(auto fx:Allfxvalues){
		cout<<fx<<" ";
	}
	cout<<endl;
//	fxvalues=Allfxvalues;
//	memcpy(population,Finalpopulation,(pop_count+1)*(var_count+2)*sizeof(float));
	}
	cout<<endl;
	cout<<" ############################"<<endl;
	for(int i=1;i<=pop_count;i++){
		if(population[i][var_count+1]==Bestvalue){
			cout<<" optimized value of function is ="<< Bestvalue<<endl;
			cout<<"And corresponding features are : "<< endl;
			for(int j=1;j<var_count+1;j+=1){
				cout<<"Value of X"<<j<<" is = "<<population[i][j]<<endl;
			}
			break;
		}
	}
	return 0;
}



