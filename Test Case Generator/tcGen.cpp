#include<bits/stdc++.h>
using namespace std;

struct varProperty{
	long int minimum;
	long int maximum;
	long int minPlus;
	long int maxMinus;
	long int minMinus;
	long int maxPlus;
	long int nominal;
	
};
int t=1;

void printFirstRow(long int n){
	cout << "\"Test Case Id\",";
	for(long int i=0; i<n; i++){
		cout << "\"variable-" << i+1 << "\"";
		if(i!=(n-1)) cout << ",";
	}
	cout << "\n";
}

void printNominals(varProperty* varList, long int n){
	cout << "1,";
	for(long int i=0; i<n; i++){
		if(i!=(n-1)) cout << varList[i].nominal << ",";
		else cout << varList[i].nominal << "\n";
	}
}

void printVariations(long int *values, long int n, long int tc){
	cout << tc <<",";
	for(long int i=0; i<n; i++){
		if(i!=(n-1)) cout << values[i]<< ",";
		else cout << values[i] << "\n";
	}
}

void printCasesForBVC(varProperty* varList,long int *values, long int n, long int &tc){
	for(long int i=0; i<n; i++){
		
		for(int k = 0; k<4; k++ ){
			tc++;
			
			if(k==0) values[i] = varList[i].minimum;
			else if(k==1) values[i] = varList[i].minPlus;
			else if(k==2) values[i] = varList[i].maximum;
			else values[i] = varList[i].maxMinus;
			
			printVariations(values,n,tc);
			
		}
		values[i]  =  varList[i].nominal;
	}
}

void printCasesForRobust(varProperty* varList,long int *values, long int n, long int &tc){
	for(long int i=0; i<n; i++){
		
		for(int k = 0; k<2; k++ ){
			tc++;
			
			if(k==0) values[i] = varList[i].minMinus;
			else values[i] = varList[i].maxPlus;
			
			printVariations(values,n,tc);
			
		}
		values[i]  =  varList[i].nominal;
	}
}

void initializeNominalValues(long int *values,varProperty* varList, long int n){
	for(long int i=0; i<n; i++){
		values[i] = varList[i].nominal;
	}
}

void BVC(varProperty* varList, long int n){
		
	printFirstRow(n);
	
	long int values[n];
	long int tc = 1;
	
	initializeNominalValues(values,varList,n);
	printVariations(values,n,tc);
	printCasesForBVC(varList,values,n,tc);
	
}

void RobustTesting(varProperty* varList, long int n){
	printFirstRow(n);
	
	long int values[n];
	long int tc = 1;
	
	initializeNominalValues(values,varList,n);
	printVariations(values,n,tc);
	printCasesForBVC(varList,values,n,tc);
	printCasesForRobust(varList,values,n,tc);
}

void setValuesFromCombination(long int *values,
  varProperty *varList,
  int *data,
  long int n){
  	
  	for(long int i=0; i<n; i++){
  		 			
		if(data[i]==1) values[i] = varList[i].nominal;
		else if(data[i]==2) values[i] = varList[i].minimum;
		else if(data[i]==3) values[i] = varList[i].maximum;
		else if(data[i]==4) values[i] = varList[i].minPlus;
		else values[i] = varList[i].maxMinus;
		
  	}
	
}

void combine(int *variation,
  int *data, 
  long int index,
  long int *values,
  varProperty *varList,
  long int n,
  long int &tc){
	
	for(long int i=0; i<5; i++){
		data[index] = variation[i];
		
		if(index==(n-1)) {
			setValuesFromCombination(values,varList,data,n);
			printVariations(values,n,tc);
			tc++;
		}
		else{
			combine(variation,data,index+1,values,varList,n,tc);
		}
	}

}

void WorstCaseTesting(varProperty* varList, long int n){
	
	printFirstRow(n);
	
	int variation[5] = {1,2,3,4,5};
	int data[n];
	long int values[n];
	long int tc = 1;
	
	initializeNominalValues(values,varList,n);
	combine(variation,data,0,values,varList,n,tc);
	
}

int main(){
//	freopen("inp.txt", "r", stdin);
//	freopen("bvc.csv", "w", stdout);
	
	
	long int n;
	cin >> n;
	
	varProperty varList[n];
	
	for(long int i=0; i<n; i++){
		cin >> varList[i].minimum;
		cin >> varList[i].maximum;
		
		varList[i].maxMinus = varList[i].maximum - 1;
		varList[i].maxPlus = varList[i].maximum + 1;
		varList[i].minMinus = varList[i].minimum - 1;
		varList[i].minPlus = varList[i].minimum + 1;
		varList[i].nominal = (varList[i].maximum + varList[i].minimum)/2;
	}
	
	//bvc
	freopen("bvc.csv", "w", stdout);
	BVC(varList,n);
	
	//robust
	freopen("robust.csv", "w", stdout);
	RobustTesting(varList,n);
	
	//worstCase
	freopen("worstCase.csv", "w", stdout);
	WorstCaseTesting(varList,n);
	
	return 0;
}



