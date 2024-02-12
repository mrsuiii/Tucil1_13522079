#include<bits/stdc++.h>

#include<fstream>
#include<ctime>
#include<chrono>
#include<sstream>
#include<string>
using namespace std;
using namespace std :: chrono;
vector<vector<string>> matrix;
vector<pair<vector<string>,int>> seq;
int token_size,seq_length;
vector<string> tokens;
vector<vector<int>> checked;
int buffer,m ,n,n_seq;
int optimum_reward=0,rew;
vector<string> buff1;
vector<pair<int,int>>path1;
vector<string> optimal_buff;
vector<pair<int,int>> optimal_path;
void solve(vector<string> buff,vector<pair<int,int>> path,int x,int y,int dir){
    if((int)buff.size()>buffer){
        return ;
    }
        int current_reward=0;
        for(int i=0;i<n_seq;i++){
            for(int  j=0;j<(int)buff.size()-(int)seq[i].first.size()+1;j++){
                vector<string> t = {buff.begin()+j,buff.begin()+j+(int)seq[i].first.size()};
                if(t==seq[i].first){
                    current_reward+= seq[i].second;
                }
            }
        }
        if(current_reward>rew){
             rew= current_reward;
            buff1 = buff;
            path1 = path;
        }
    string token = matrix[y][x];
    if(dir==0){
        for(int i=0;i<n;i++){
            buff.push_back(token);
        path.push_back({x,y});
        checked[y][x]= 1;
            if(checked[i][x]==0){
            solve(buff,path,x,i,1);
            }
            checked[y][x]=0;
            buff.pop_back();
    path.pop_back();
            }
    }else{
        for(int i =0;i<m;i++){
            buff.push_back(token);
        path.push_back({x,y});
        checked[y][x]= 1;
            if(checked[y][i]==0){
                solve(buff,path,i,y,0);
            }
            checked[y][x]= 0;
            buff.pop_back();
    path.pop_back();
        }
    }
}
int main(){
    string choice;
    cout << "Masukan tipe input(cli/txt): "<<"\n";
    cin >> choice;
    if(choice=="cli"){
        cin >> token_size;
        srand(time(0));
        tokens.resize(token_size);
        for(int i=0;i<token_size;i++){
            cin >> tokens[i];
        }
        cin >> buffer;
        cin >> m >> n;
        checked.resize(n);
        matrix.resize(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int random = rand()%token_size;
                matrix[i].push_back(tokens[random]);
                checked[i].push_back(0);
            }
        }
        
        cin >> n_seq;
        seq.resize(n_seq);
        cin >> seq_length;
        for(int i=0;i<n_seq;i++){
            int range= seq_length-1;
            int r = rand()% range + 2;
            
            while(r--){
                int random = rand()%token_size;
                seq[i].first.push_back(tokens[random]);
            }
            
            int reward = rand()%100+1;
            seq[i].second = reward;
        }
        auto start = high_resolution_clock::now();
        for(int i=0;i<m;i++){
            rew = 0;
            solve(buff1,path1,i,0,0);
            if(rew>optimum_reward){
                optimum_reward = rew;
                optimal_buff = buff1;
                optimal_path = path1;
            }

        }
        
        cout << "matriks permainan:\n";
        for(int i=0;i<n;i++){
            for(int j=0;j<m ;j++){
                cout << matrix[i][j]<< " ";
            }
            cout << "\n";
        }
        cout << "sequence:\n";
        for(int i=0;i<n_seq;i++){
            for(auto s: seq[i].first){
                cout << s<< " ";

            }
            cout << "\n"<<seq[i].second;
            cout <<"\n";
        }cout<<"\n";
        cout << optimum_reward<<"\n";
        if(optimal_buff.size()!=0){
            
        for(auto s: optimal_buff){
            cout << s<< " ";
        }cout << "\n";
        for(auto s : optimal_path){
            cout <<s.first+1<<", "<<s.second+1;
            cout << "\n";
        }
        }
        cout <<"\n\n";
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end-start);
        cout << duration.count()<< " ms"<<"\n";
        cout<< "\n\n";
        cout << "apakah ingin menyimpan solusi? (y/n)";
        char c;
        cin >>c;
        if(c=='y'){
            string filepath;
            cout << "Masukan nama file output:(.txt) ";
            cin >> filepath;
            ofstream outputFile(filepath);
            outputFile << "matriks permainan:\n";
        for(int i=0;i<n;i++){
            for(int j=0;j<m ;j++){
                outputFile << matrix[i][j]<< " ";
            }
            outputFile << "\n";
        }
        outputFile << "sequence:\n";
        for(int i=0;i<n_seq;i++){
            for(auto s: seq[i].first){
                outputFile << s<< " ";

            }
            outputFile << "\n"<<seq[i].second;
            outputFile <<"\n";
        }outputFile<<"\n";
        outputFile << optimum_reward<<"\n";
        if(optimal_buff.size()!=0){
        for(auto s: optimal_buff){
            outputFile << s<< " ";
        }outputFile << "\n";
        for(auto s : optimal_path){
            outputFile <<s.first+1<<", "<<s.second+1;
            outputFile << "\n";
        }
        outputFile<<"\n\n"<< duration.count()<<" ms"<<"\n";
        }
        }
        }else if(choice=="txt"){
            string inputPath ;
            cout << "Masukan alamat file: "<<"\n";
            cin >> inputPath;
            ifstream inp(inputPath);
            if(!inp){
                cerr << "Gagal membuka file" << endl;
                return 1;
            }
            string line;
            getline(inp,line);
            buffer = stoi(line);
            getline(inp,line);
            istringstream iss(line);
            iss >> m >> n;
            matrix.resize(n);
            checked.resize(n);
            for(int i=0;i<n;i++){
                getline(inp,line);
                istringstream iss(line);
                
                for(int j=0;j<m;j++){
                    string token;
                    iss >> token;
                    if(token.size()!=2){
                        cerr << "panjang token harus 2"<<endl;
                        return 1;
                    }
                    matrix[i].push_back(token);
                    checked[i].push_back(0);
                    }
            }
            getline(inp,line);
            n_seq = stoi(line);
            seq.resize(n_seq);
            for(int i=0;i<n_seq;i++){
                getline(inp,line);
                string token ; 
                stringstream ss(line);
                while(ss >> token){
                    seq[i].first.push_back(token);
                    
                }
                getline(inp,line);
                int reward;
                reward = stoi(line);
                seq[i].second = reward;
            }
            inp.close();
            auto start = high_resolution_clock::now();
            for(int i=0;i<m;i++){
            rew = 0;
            solve(buff1,path1,i,0,0);
            if(rew>optimum_reward){
                optimum_reward = rew;
                optimal_buff = buff1;
                optimal_path = path1;
            }

        }
        
        cout << optimum_reward<<"\n";
        cout << "hello"<<"\n";
        if(optimal_buff.size()!=0){
            
        for(auto s: optimal_buff){
            cout << s<< " ";
        }cout << "\n";
        for(auto s : optimal_path){
            cout <<s.first+1<<", "<<s.second+1;
            cout << "\n";
        }
        }
        cout <<"\n\n";
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end-start);
        cout << duration.count()<< " ms"<<"\n";
        cout<< "\n\n";
        cout << "apakah ingin menyimpan solusi? (y/n)";
        char c;
        cin >>c;
        if(c=='y'){
            string filepath;
            cout << "Masukan nama file output:(.txt) ";
            cin >> filepath;
            ofstream outputFile(filepath);
        outputFile << optimum_reward<<"\n";
        if(optimal_buff.size()!=0){
            
        for(auto s: optimal_buff){
            outputFile << s<< " ";
        }outputFile << "\n";
        for(auto s : optimal_path){
            outputFile <<s.first+1<<", "<<s.second+1;
            outputFile << "\n";
        }
        outputFile<<"\n\n"<< duration.count()<<" ms"<<"\n";
        outputFile.close();
        }
        }
            
            
        }


}