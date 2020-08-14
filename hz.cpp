#include <bits/stdc++.h>
using namespace std;


struct NN {
	static const int N=10000;
	
	int n,insz,outsz;
	
	int l[N],r[N];
	vector<double> w[N];
	
	double c[N];
	
	void write_txt(const char name[]){
		FILE *f = fopen(name,"w");
		fprintf(f,"%d %d %d\n",n,insz,outsz);
		for(int i=0; i<n; ++i){
			fprintf(f,"%d %d %lf",l[i],r[i],c[i]);
			for(int j=0; j<r[i]-l[i]; ++j){
				fprintf(f," %lf",w[i][j]);
			}
			fprintf(f,"\n");
		}
		fclose(f);
	}
	
	void read_txt(const char name[]){
		FILE *f = fopen(name,"r");
		fscanf(f,"%d%d%d",&n,&insz,&outsz);
		for(int i=0; i<n; ++i){
			fscanf(f,"%d%d%lf",&l[i],&r[i],&c[i]);
			w[i].resize(r[i]-l[i]);
			for(int j=0; j<r[i]-l[i]; ++j){
				fscanf(f,"%lf",&w[i][j]);
			}
		}
		fclose(f);
	}
	
	void push_mat_old(int inl, int inr, int outl, int outr){
		for(int x=inl; x<inr; ++x){
			l[x]=outl;
			r[x]=outr;
			w[x].resize(outr-outl);
			
			for(int i=0; i<outr-outl; ++i){
				w[x][i] = ( rand()%10001 - 5000 ) / 5000.0;
			}
			
			for(int i=outl; i<outr; ++i){
				c[i] = ( rand()%10001 - 5000 ) / 5000.0;
			}
		}
	}
	
	int sz[N],sz_top;
	
	void push_sz(int s){
		n = sz[sz_top+1] = sz[sz_top] + s;
		sz_top++;
		insz = sz[1];
		outsz = s;
	}
	
	void push_mat(int in_id, int out1, int out2){
		push_mat_old(sz[in_id-1],sz[in_id],sz[out1-1],sz[out2]);
	}
	
	double fin[N],fout[N],d[N];
	
	void set_input(double f[]){
		for(int i=0; i<insz; ++i){
			fin[i] = f[i];
		}
	}
	
	void get_output(double f[]){
		for(int i=0; i<outsz; ++i){
			f[i] = fout[n-outsz+i];
		}
	}
	
	double my_exp(double x){
		x = 1.0 + x/256.0;
		x*=x; x*=x; x*=x; x*=x;
		x*=x; x*=x; x*=x; x*=x;
		return x;
	}
	
	void calc(){
		for(int i=insz; i<n; ++i) fin[i]=0;
		
		for(int i=0; i<n; ++i){
			fout[i] = 1.0 / ( 1.0 + my_exp(-fin[i]-c[i]) );
			
			for(int j=l[i]; j<r[i]; ++j){
				fin[j] += fout[i] * w[i][j-l[i]];
			}
		}
	}
	
	void back(double f[]){
		for(int i=0; i<n; ++i) d[i]=0;
		
		for(int i=0; i<outsz; ++i){
			d[n-outsz+i] = fout[n-outsz+i] - f[i];
		}
		
		for(int i=n-1; i>=0; --i){
			for(int j=l[i]; j<r[i]; ++j){
				d[i] += w[i][j-l[i]] * d[j];
				w[i][j-l[i]] -= fout[i] * d[j] * 0.5;
			}
			d[i] *= fout[i] * (1-fout[i]);
			c[i] -= d[i] * 0.5;
		}
	}
} nn;


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
	
	void to_input(double f[]){
		for(int i=0; i<6*8*6; i++) f[i]=0;
		int t=0;
		for(int i=0; i<6; i++){
			for(int j=0; j<8; j++){
				f[t+s[i][j]]=1;
				t+=6;
			}
		}
	}
	
	void encode(int a[]){
		for(int i=0; i<6; ++i){
			a[i]=0;
			for(int j=0; j<8; ++j){
				a[i] = a[i]<<3 | s[i][j];
			}
		}
	}
	
	void decode(const int a[]){
		for(int i=0; i<6; ++i){
			int t=a[i];
			for(int j=7; j>=0; j--){
				s[i][j] = t & 7;
				t >>= 3;
			}
		}
	}
	
	unsigned long long hash() const {
		unsigned long long x=0;
		for(int i=0; i<6; i++){
			for(int j=0; j<8; j++){
				x = x*1331 + s[i][j] + 1;
			}
		}
		return x;
	}	
	
	bool check() const {
		for(int i=0; i<6; i++){
			for(int j=0; j<8; j++){
				if (s[i][j]!=i) return false;
			}
		}
		return true;
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
		
		rtt0(s[0][2],s[3][2],s[2][2],s[1][2]);
		rtt0(s[0][1],s[3][1],s[2][1],s[1][1]);
		rtt0(s[0][0],s[3][0],s[2][0],s[1][0]);
	}
	
	inline void top1(){
		rtt1(s[4][0],s[4][2],s[4][4],s[4][6]);
		rtt1(s[4][1],s[4][5],s[4][7],s[4][3]);
		
		rtt1(s[0][2],s[3][2],s[2][2],s[1][2]);
		rtt1(s[0][1],s[3][1],s[2][1],s[1][1]);
		rtt1(s[0][0],s[3][0],s[2][0],s[1][0]);
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




void init_nn(){
	nn.push_sz(48*6); // 1 input
	nn.push_sz(512); // 2
	nn.push_sz(256); // 3
	nn.push_sz(128); // 4
	nn.push_sz(128); // 5
	nn.push_sz(12); // 6
	nn.push_sz(1); // 7
	nn.push_mat(1,2,2);
	nn.push_mat(2,3,3);
	nn.push_mat(3,4,5);
	nn.push_mat(4,6,6);
	nn.push_mat(5,7,7);
	nn.outsz = 13;
}

/*
cube c;
set<unsigned long long> hs;
int cnt;

double fin[48*6];
double fout[13];

void dfs(int dep, int frtt){
	unsigned long long h = c.hash();
	if (hs.count(h)) return;
	hs.insert(h);
	cnt++;
	printf("cnt=%d\n",cnt);
	
	c.to_input(fin);
	for(int i=0; i<13; ++i) fout[i]=0;
	fout[frtt^1]=1;
	fout[12]=1.0/sqrt(dep);
	
	nn.set_input(fin);
	nn.calc();
	nn.back(fout);
	
	if (dep>3) return;
	for(int i=0; i<12; i++){
		c.rtt(i);
		dfs(dep+1,i);
		c.rtt(i^1);
	}
}
*/

double fin[48*6];
double fout[13];

const int N=1000000;
int q[N][6],l,r;
int dep[N],frtt[N];
cube c;
unordered_set<unsigned long long> hs;

void bfs(){
	c.init();
	c.encode(q[l=r=0]);
	dep[0]=1;
	hs.clear();
	hs.insert(c.hash());
	
	while (l<=r){
		//if (l%100==0) printf("l=%d\n",l);
		
		c.decode(q[l++]);
		
		
		c.to_input(fin);
		for(int i=0; i<13; ++i) fout[i]=0;
		//printf("%d\n",frtt[l-1]^1);
		fout[frtt[l-1]^1]=1;
		fout[12]=1.0/sqrt(dep[l-1]);
		
		nn.set_input(fin);
		nn.calc();
		nn.back(fout);
		
		
		if (dep[l-1]>1) continue;
		for(int i=0; i<12; i++){
			c.rtt(i);
			unsigned long long h=c.hash();
			if (!hs.count(h)){
				hs.insert(h);
				c.encode(q[++r]);
				dep[r]=dep[l-1]+1;
				frtt[r]=i;
			}
			c.rtt(i^1);
		}
	}
}


int try_solve(cube c){
	int step=0;
	while (!c.check() && step<20){
		c.to_input(fin);
		nn.set_input(fin);
		nn.calc();
		nn.get_output(fout);
		int mi=0;
		for(int i=1; i<12; ++i){
			if (fout[i]>fout[mi]) mi=i;
		}
		c.rtt(mi);
		step++;
	}
	return step;
}



int main(){
	/*
	init_nn();
	bfs();
	printf("%d\n",r);
	*/
	
	/*
	for(int i=0; i<12; ++i){
		c.init();
		c.rtt(i);
		c.encode(q[0]);
		c.decode(q[0]);
		c.rtt(i^1);
		c.encode(q[0]);
		c.decode(q[0]);
		printf("%d\n",int(c.check()));
	}
	*/
	
	
	init_nn();
	
	for(int t=1; t<=1000; ++t){
		printf("%d\n",t);
		for(int i=0; i<12; ++i){
			c.init();
			c.rtt(i);
			c.to_input(fin);
			for(int j=0; j<13; ++j) fout[j]=0;
			fout[i^1]=1;
			
			nn.set_input(fin);
			nn.calc();
			nn.back(fout);
		}
	}
	
	//nn.write_txt("c.txt");
	
	
	
	//nn.read_txt("c.txt");
	
	//init_nn();
	
	
	for(int i=0; i<12; ++i){
		c.init();
		c.rtt(i);
		c.to_input(fin);
			
		nn.set_input(fin);
		nn.calc();
		nn.get_output(fout);
		
		for(int j=0; j<12; ++j) printf("%lf ",fout[j]);
		printf("\n");
	}
	
	
	/*
	bfs();
	printf("%d\n",r);
	*/
	
	
	//init_nn();
	//bfs();
	
	/*
	nn.read_txt("c.txt");
	
	for(int i=0; i<5; ++i){
		bfs();
		printf("%d\n",i+1);
	}
	
	nn.write_txt("c.txt");
	*/
	
	
	//nn.read_txt("c.txt");
	
	/*
	for(int i=0; i<12; ++i){
		for(int j=0; j<12; ++j){
			for(int k=0; k<12; ++k){
				for(int w=0; w<12; ++w){
					c.init();
					c.rtt(i);
					c.rtt(j);
					c.rtt(k);
					c.rtt(w);
					printf("%d\n",try_solve(c));
				}
			}
		}
	}
	*/
	
	/*
	for(int i=0; i<100; ++i){
		c.init();
		for(int j=0; j<5; ++j) c.rtt(rand()%12);
		printf("%d\n",try_solve(c));
	}
	*/
	
	return 0;
}



