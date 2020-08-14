#include <bits/stdc++.h>
using namespace std;
typedef long long LL;


struct cube {
	/*
	0 front
	1 right
	2 back
	3 left
	4 top
	5 bottom
	*/
	
	inline static void rtt0(int &a, int &b, int &c, int &d){
		int t=a;
		a=b; b=c; c=d; d=t;
	}
	
	inline static void rtt1(int &a, int &b, int &c, int &d){
		int t=d;
		d=c; c=b; b=a; a=t;
	}
	
	int s[6][8];
	
	void init(){
		for(int i=0; i<6; ++i){
			for(int j=0; j<8; ++j){
				s[i][j] = i;
			}
		}
	}
	
	/*
	0 counter-clockwise
	1 clockwise
	*/
	
	inline void front0(){
		rtt0(s[0][0],s[0][2],s[0][4],s[0][6]);
		rtt0(s[0][1],s[0][5],s[0][7],s[0][3]);
		
		rtt0(s[4][6],s[1][0],s[5][2],s[3][4]);
		rtt0(s[4][7],s[1][3],s[5][1],s[3][5]);
		rtt0(s[4][4],s[1][6],s[5][0],s[3][2]);
	}
	
	inline void front1(){
		rtt1(s[0][0],s[0][2],s[0][4],s[0][6]);
		rtt1(s[0][1],s[0][5],s[0][7],s[0][3]);
		
		rtt1(s[4][6],s[1][0],s[5][2],s[3][4]);
		rtt1(s[4][7],s[1][3],s[5][1],s[3][5]);
		rtt1(s[4][4],s[1][6],s[5][0],s[3][2]);
	}
	
	inline void right0(){
		rtt0(s[1][0],s[1][2],s[1][4],s[1][6]);
		rtt0(s[1][1],s[1][5],s[1][7],s[1][3]);
		
		rtt0(s[4][4],s[2][0],s[5][4],s[0][4]);
		rtt0(s[4][5],s[2][3],s[5][5],s[0][5]);
		rtt0(s[4][2],s[2][6],s[5][2],s[0][2]);
	}
	
	inline void right1(){
		rtt1(s[1][0],s[1][2],s[1][4],s[1][6]);
		rtt1(s[1][1],s[1][5],s[1][7],s[1][3]);
		
		rtt1(s[4][4],s[2][0],s[5][4],s[0][4]);
		rtt1(s[4][5],s[2][3],s[5][5],s[0][5]);
		rtt1(s[4][2],s[2][6],s[5][2],s[0][2]);
	}
	
	inline void back0(){
		rtt0(s[2][0],s[2][2],s[2][4],s[2][6]);
		rtt0(s[2][1],s[2][5],s[2][7],s[2][3]);
		
		rtt0(s[4][2],s[3][0],s[5][6],s[1][4]);
		rtt0(s[4][1],s[3][3],s[5][7],s[1][5]);
		rtt0(s[4][0],s[3][6],s[5][4],s[1][2]);
	}
	
	inline void back1(){
		rtt1(s[2][0],s[2][2],s[2][4],s[2][6]);
		rtt1(s[2][1],s[2][5],s[2][7],s[2][3]);
		
		rtt1(s[4][2],s[3][0],s[5][6],s[1][4]);
		rtt1(s[4][1],s[3][3],s[5][7],s[1][5]);
		rtt1(s[4][0],s[3][6],s[5][4],s[1][2]);
	}
	
	inline void left0(){
		rtt0(s[3][0],s[3][2],s[3][4],s[3][6]);
		rtt0(s[3][1],s[3][5],s[3][7],s[3][3]);
		
		rtt0(s[4][0],s[0][0],s[5][0],s[2][4]);
		rtt0(s[4][3],s[0][3],s[5][3],s[2][5]);
		rtt0(s[4][6],s[0][6],s[5][6],s[2][2]);
	}
	
	inline void left1(){
		rtt1(s[3][0],s[3][2],s[3][4],s[3][6]);
		rtt1(s[3][1],s[3][5],s[3][7],s[3][3]);
		
		rtt1(s[4][0],s[0][0],s[5][0],s[2][4]);
		rtt1(s[4][3],s[0][3],s[5][3],s[2][5]);
		rtt1(s[4][6],s[0][6],s[5][6],s[2][2]);
	}
	
	inline void top0(){
		rtt0(s[4][0],s[4][2],s[4][4],s[4][6]);
		rtt0(s[4][1],s[4][5],s[4][7],s[4][3]);
		
		rtt0(s[0][0],s[3][0],s[2][0],s[1][0]);
		rtt0(s[0][1],s[3][1],s[2][1],s[1][1]);
		rtt0(s[0][2],s[3][2],s[2][2],s[1][2]);
	}
	
	inline void top1(){
		rtt1(s[4][0],s[4][2],s[4][4],s[4][6]);
		rtt1(s[4][1],s[4][5],s[4][7],s[4][3]);
		
		rtt1(s[0][0],s[3][0],s[2][0],s[1][0]);
		rtt1(s[0][1],s[3][1],s[2][1],s[1][1]);
		rtt1(s[0][2],s[3][2],s[2][2],s[1][2]);
	}
	
	inline void bottom0(){
		rtt0(s[5][0],s[5][2],s[5][4],s[5][6]);
		rtt0(s[5][1],s[5][5],s[5][7],s[5][3]);
		
		rtt0(s[0][6],s[1][6],s[2][6],s[3][6]);
		rtt0(s[0][7],s[1][7],s[2][7],s[3][7]);
		rtt0(s[0][4],s[1][4],s[2][4],s[3][4]);
	}
	
	inline void bottom1(){
		rtt1(s[5][0],s[5][2],s[5][4],s[5][6]);
		rtt1(s[5][1],s[5][5],s[5][7],s[5][3]);
		
		rtt1(s[0][6],s[1][6],s[2][6],s[3][6]);
		rtt1(s[0][7],s[1][7],s[2][7],s[3][7]);
		rtt1(s[0][4],s[1][4],s[2][4],s[3][4]);
	}
	
	void rtt(int x){
		if (x<6){
			if (x<3){
				if (x==0) front0(); // 0
				else if (x==1) front1(); // 1
				else right0(); // 2
			} else {
				if (x==3) right1(); // 3
				else if (x==4) back0(); // 4
				else back1(); // 5
			}
		} else {
			if (x<9){
				if (x==6) left0(); // 6
				else if (x==7) left1(); // 7
				else top0(); // 8
			} else {
				if (x==9) top1(); // 9
				else if (x==10) bottom0(); // 10
				else bottom1(); // 11
			}
		}
	}
};



int main(){
	return 0;
}

	
	
	
	
	
	
	
	


