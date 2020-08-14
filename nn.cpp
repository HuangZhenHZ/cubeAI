#include <bits/stdc++.h>
using namespace std;

struct NN {
	static const int N=10000;
	
	int n,insz,outsz;
	
	int l[N],r[N];
	//vector<double> w[N];
	double *w[N];
	
	double c[N];
	
	double *ws1[N], *ws2[N];
	double cs1[N], cs2[N];
	
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
			//w[i].resize(r[i]-l[i]);
			if (w[i]) delete[] w[i];
			w[i] = new double [r[i]-l[i]];
			
			if (ws1[i]) delete[] ws1[i];
			ws1[i] = new double [r[i]-l[i]];
			
			if (ws2[i]) delete[] ws2[i];
			ws2[i] = new double [r[i]-l[i]];
			
			for(int j=0; j<r[i]-l[i]; ++j){
				fscanf(f,"%lf",&w[i][j]);
				ws1[i][j] = ws2[i][j] = 0;
			}
		}
		fclose(f);
	}
	
	void push_mat_old(int inl, int inr, int outl, int outr){
		for(int x=inl; x<inr; ++x){
			l[x]=outl;
			r[x]=outr;
			//w[x].resize(outr-outl);
			if (w[x]) delete[] w[x];
			w[x] = new double [outr-outl];
			
			if (ws1[x]) delete[] ws1[x];
			ws1[x] = new double [outr-outl];
			
			if (ws2[x]) delete[] ws2[x];
			ws2[x] = new double [outr-outl];
			
			for(int i=0; i<outr-outl; ++i){
				w[x][i] = ( rand()%10001 - 5000 ) / 1000.0;
				ws1[x][i] = ws2[x][i] = 0;
			}
			
			for(int i=outl; i<outr; ++i){
				c[i] = ( rand()%10001 - 5000 ) / 1000.0;
				cs1[i] = cs2[i] = 0;
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
	
	double loss(double f[]){
		double sum=0;
		for(int i=0; i<outsz; ++i){
			sum += (fout[n-outsz+i] - f[i]) * (fout[n-outsz+i] - f[i]);
		}
		return sum;
	}
	
	int cnt;
	
	void back(double f[]){
		cnt++;
		
		for(int i=0; i<n; ++i) d[i]=0;
		
		for(int i=0; i<outsz; ++i){
			d[n-outsz+i] = fout[n-outsz+i] - f[i];
		}
		
		for(int i=n-1; i>=0; --i){
			for(int j=l[i]; j<r[i]; ++j){
				d[i] += w[i][j-l[i]] * d[j];
				
				double dx = ws1[i][j-l[i]] = ws1[i][j-l[i]] * 0.999 + fout[i] * d[j] * 0.001;
				ws2[i][j-l[i]] = ws2[i][j-l[i]] * 0.999 + dx*dx;
				w[i][j-l[i]] -= dx / sqrt(ws2[i][j-l[i]] + 1);
				/*
				double td = dx * sqrt((ws1[i][j-l[i]] + 1) / (ws2[i][j-l[i]] + 1));
				w[i][j-l[i]] -= td;
				ws1[i][j-l[i]] = ws1[i][j-l[i]] * 0.99 + td*td;
				*/
				//w[i][j-l[i]] -= dx;
				//ws1[i][j-l[i]] += dx;
				//ws2[i][j-l[i]] += dx*dx;
				//w[i][j-l[i]] -= dx;
				//w[i][j-l[i]] -= dx * ( (ws1[i][j-l[i]] += dx) +1 ) / sqrt( (ws2[i][j-l[i]] += dx*dx) + 1); // * rate;
				/*
				ws1[i][j-l[i]] = ws1[i][j-l[i]] * 0.9 + dx;
				ws2[i][j-l[i]] = ws2[i][j-l[i]] * 0.999 + dx*dx;
				double ss = ws1[i][j-l[i]] / (1 - 0.9*0.9);
				double rr = ws2[i][j-l[i]] / (1 - 0.99*0.99);
				w[i][j-l[i]] -= dx * ss / (sqrt(rr)+1e-8) * 2;
				*/
			}
			d[i] *= fout[i] * (1-fout[i]);
			
			double dx = cs1[i] = cs1[i] * 0.999 + d[i] * 0.001;
			cs2[i] = cs2[i] * 0.999 + dx*dx;
			c[i] -= dx / sqrt(cs2[i] + 1);
			/*
			double td = dx * sqrt((cs1[i] + 1) / (cs2[i] + 1));
			c[i] -= td;
			cs1[i] = cs1[i] * 0.99 + td*td;
			*/
			//c[i] -= dx;
			/*
			cs1[i] = cs1[i] * 0.9 + dx;
			cs2[i] = cs2[i] * 0.999 + dx*dx;
			double ss = cs1[i] / (1 - 0.9*0.9);
			double rr = cs2[i] / (1 - 0.99*0.99);
			c[i] -= dx * ss / (sqrt(rr)+1e-8) * 2;
			*/
			//cs[i] += dx*dx;
			//c[i] -= dx;
			//c[i] -= dx * ( (cs1[i] += dx) +1 ) / sqrt( (cs2[i] += dx*dx) + 1); // * rate;
		}
	}
} nn;



int main(){
	/*
	nn.n = 23;
	nn.insz = 2;
	nn.outsz = 1;
	nn.push_mat_old(0,2,2,22);
	nn.push_mat_old(2,22,22,23);
	*/
	
	nn.push_sz(3); // 1
	nn.push_sz(20); // 2
	nn.push_sz(1); // 3
	nn.push_mat(1,2,2);
	nn.push_mat(2,3,3);
	
	double in[8][3] = {{0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};
	double out[8][1] = {{0},{0},{0},{1},{1},{0},{1},{1}};
	
	
	for(int i=0; i<20000; ++i){
		//nn.rate = 0.5; //1.0/pow(i+1,0.1);
		double loss=0;
		for(int j=0; j<8; ++j){
			nn.set_input(in[j]);
			nn.calc();
			loss+=nn.loss(out[j]);
			nn.back(out[j]);
		}
		if (i%200==0) printf("%lf\n",loss);
	}
	putchar('\n');
	
	//nn.write_txt("nn.txt");
	
	
	//nn.read_txt("nn.txt");
	
	//double in[4][2] = {{0,0},{0,1},{1,0},{1,1}};
	//double out[4][1] = {{0},{1},{0},{1}};
	
	for(int i=0; i<8; ++i){
		nn.set_input(in[i]);
		nn.calc();
		double g[1];
		nn.get_output(g);
		printf("%lf\n",g[0]);
	}
	
	return 0;
}






