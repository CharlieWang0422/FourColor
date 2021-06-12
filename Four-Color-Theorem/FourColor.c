#include<bits/stdc++.h>
#include<unordered_set>

using namespace std;


int i,j;
int color_save;
int color_variety = 1;
int table[30][30];
vector<vector<int>> country_relationship(100,vector<int>(100,0)) , country_relationship2, S;
vector<int>country_color(100,96),country_sequence;



 // DFS function
void DFS(unsigned int pos){
	//end condition 
		if(pos == country_sequence.size()){
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
		else if(pos!=country_sequence.size()+1){
			for(i=1;i<=color_variety;i++){ 
				color_save = 96+i;
				country_color[country_sequence[pos]] = color_save;
				// make sure this way has not tried before
				for(unsigned int k = 0;k<S.size();k++){
					if(S[k] == country_color){
						country_color[country_sequence[pos]] = 96;
						// go to place
						goto place;
					}
				}
				// Confirm that the neighbors are the same
				for(unsigned int j = 1;j < country_sequence.size();j++){
					if(country_relationship2[pos][country_sequence[j]] == 1){
						if(country_color[country_sequence[j]] == color_save && country_sequence[j] != country_sequence[pos]){
							country_color[country_sequence[pos]] = 96;
							// go to place
							goto place;
							}
						}
				}
				// record this way
				S.push_back(country_color);
				// go to next country
                // cout << pos;
				DFS(pos+1);
				return;
				// if the color can not accord,come to this place
				place:
				// Check if the colors are all used up
				if(i == color_variety){
					country_color[country_sequence[pos-1]] = 96;
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
    		scanf("%2d", &table[i][j]);

    		} 
    }
    country_sequence.push_back(0);
    // check neigbor relationship
    for(i=0;i<30;i++){
    	for(j=0;j<30;j++){
    		// record appear country sequence
    		if(table[i][j] !=0){
    			for(unsigned int x = 0; x < country_sequence.size();x++){
    				if(country_sequence[x] == table[i][j]){
    					goto place1;
    				}
    			}
    			country_sequence.push_back(table[i][j]);
    		}
    		place1:
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
    // rearrange the sequence in the order of appearance of the country
    country_relationship2.push_back(country_relationship[0]);
    for(unsigned int k = 1 ; k < country_sequence.size() ; k++){
        country_relationship2.push_back(country_relationship[country_sequence[k]]);
    }
    
    DFS(1);
    // write the color to the table
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