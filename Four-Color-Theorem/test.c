#include<bits/stdc++.h>


using namespace std;

int i,j,x;
int color_save;
int color_variety = 1;
int table[30][30];
int colors[100] = {0};
int country_relationship[100][100]={0};
vector<vector<int>> S;
vector<int>country_color(100,96);


 // DFS function
void DFS(int pos){
	//end condition 
		if(pos == 100){
		  	return;
		}
		// If the colors are not enough
		else if(pos == 0){
			color_variety++;
			pos = 1;
			S.clear();
			DFS(pos);
		}
		// try to fill the color
		else if(pos!=100){
			for(i=1;i<=color_variety;i++){ 
				color_save = 96+i;
				country_color[pos] = color_save;
				// make sure this way has not tried before
				for(unsigned int k = 0;k<S.size();k++){
					if(S[k] == country_color){
						country_color[pos] = 96;
						// go to place
						goto place;
					}
				}
				// Confirm that the neighbors are the same
				for(j = 1;j <= 100;j++){
					if(country_relationship[pos][j] == 1){
						if(country_color[j] == color_save && j != pos){
							country_color[pos] = 96;
							// go to place
							goto place;
							}
						}

				}
				// record this way
				S.push_back(country_color);
				// go to next country
				DFS(pos+1);
				return;
				// if the color can not accord,come to this place
				place:
				// Check if the colors are all used up
				if(i == color_variety){
					country_color[pos-1] = 96;
					DFS(pos-1);
					return; 
					}	
				}
			}
	// DFS finish
}	
	// main function
int main(){
	// scan the file
    freopen("color900_1.txt","r",stdin);
    freopen("color900_1_out.txt","w",stdout);
    for(i=0; i<30; i++) {
    	for(j=0; j<30; j++) {
    		scanf("%d", &table[i][j]);

    		} 
    }
    // check neigbor relationship
    for(i=0;i<30;i++){
    	for(j=0;j<30;j++){	
    		if(i!=29){
    			country_relationship[table[i][j]][table[i+1][j]] = 1;
    		}
    		if(i!= 0){
    			country_relationship[table[i][j]][table[i-1][j]] = 1;
    		}
    		if(j!=29){
    			country_relationship[table[i][j]][table[i][j+1]] = 1;
    		}
    		if(j!=0){
    			country_relationship[table[i][j]][table[i][j-1]] = 1;
    		}
    	}
    }
    DFS(1);
    // fill color
	 for(i=0;i<30;i++){
    	for(j=0;j<30;j++){	
    		table[i][j] = country_color[table[i][j]];
    	}
    }
    // print out the result
    for(i = 0; i < 30; i++) {
    	for(j = 0; j < 30; j++) {
    		if (j == 29) {
    			cout << char(table[i][j]) << "\n";
    		} 
    		else {
    			cout << char(table[i][j]) << " ";
    		}
		}
	}
	printf("The minimum number of color(s) needed is %d",color_variety );
}