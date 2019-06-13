#include "filesearch.h"

FileSearch::FileSearch(string directory){
	read_files(directory);
	set_idf();
	set_w_file_word();
}

void FileSearch::find(string &query){
	vector<string> words = return_query(query);
	map<double, string> ranking;
	list<double> order;
	set_w_query(words);
	for(string name_file : files_names){
		order.push_back(cosine_distance(w_query, w_file_word[name_file]));
		ranking[cosine_distance(w_query, w_file_word[name_file])] = name_file;
	}
	order.sort();
	order.reverse();
	if(order.front() == 0){
		cout<<"Sua pesquisa - "<<query<<" - nao encontrou nenhum documento correspondente."<<endl;
	}
	else{
		cout<<"----------- RANKING -----------"<<endl;
		for(double x : order){
			if(x != 0){
				cout<<"|           "<<ranking[x]<<endl;
			}
		}
		cout<<"-------------------------------"<<endl;
	}

	w_query.clear();
	words.clear();
	ranking.clear();
	order.clear();
}

void FileSearch::list_file(string directory){
			string fix = "../" + directory + "/";
			const char *dir = fix.c_str();
      DIR *pDIR;
      struct dirent *rfile;
      if(pDIR=opendir(dir)){
              while(rfile = readdir(pDIR)){
                      if( strcmp(rfile->d_name, ".") != 0 and strcmp(rfile->d_name, "..") != 0 ){
                      	files_names.push_back(rfile->d_name);
                      }
              }
              closedir(pDIR);
      }
}

void FileSearch::set_idf(){
		double size_files = term_frequency.size();
		map<string, set<string> >::iterator map_it;

		for(map_it = coordinate.begin(); map_it != coordinate.end(); ++map_it){
						 inverse_document_frequency[map_it->first] = log(size_files / coordinate[map_it->first].size());
			}
}

void FileSearch::read_files(string directory){
	string line;
	string word;
	ifstream file;

	list_file(directory);

	for(string file_name : files_names){
		file.open("../" + directory + "/" + file_name);
		while(getline(file, line)){
			istringstream line_to_cut(line);
			while(getline(line_to_cut, word, ' ')){
				//Rodamos essa parte do codigo mais vezes para retirar pontuações seguidas.
				for(int i = 0; i < 3; i++){
					if(word.back() == '.' or word.back() == ',' or word.back() == '?' or word.back() == '!' or
				        word.back() == ';' or word.back() == '~' or word.back() == '.' or word.back() == '(' or
						 word.back() == ')' or word.back() == '"' or word.back() == ':' or word.back() == '[' or
						 word.back() == ']' or word.back() == '*' or word.back() == '/' or word.back() == '<' or
				 		 word.back() == '>' or word.back() == 39 )
						 {word.erase(word.end()-1);}
					if(int(word.find('-')) > 0){word.erase(word.find('-'), 1);}

					if(word.front() == '.' or word.front() == ',' or word.front() == '?' or word.front() == '!' or
						 word.front() == ';' or word.front() == '~' or word.front() == '.' or word.front() == '(' or
						 word.front() == ')' or word.front() == '"' or word.front() == ':' or word.front() == '[' or
						 word.front() == ']' or word.front() == '*' or word.front() == '/' or word.front() == '<' or 
						 word.front() == '>' or word.front() == 39)
						 {word.erase(word.begin());}
					if(int(word.find('-')) > 0){word.erase(word.find('-'), 1);}
				}
				transform(word.begin(), word.end(), word.begin(), ::tolower);

				if(word[0] != 0){
					coordinate[word].insert(file_name);
					term_frequency[file_name][word] += 1;
				}
      }
		}
		file.close();
	}
}

void FileSearch::set_w_file_word(){

	map<string, set<string> >::iterator map_it;
	for(string name_file : files_names){
			for(map_it = coordinate.begin(); map_it != coordinate.end(); ++map_it){
					w_file_word[name_file].push_back(
						term_frequency[name_file][map_it->first] * inverse_document_frequency[map_it->first]);
			}
	 }
}

void FileSearch::set_w_query(vector<string> &words){
	map<string, set<string> >::iterator map_it;
	for(map_it = coordinate.begin(); map_it != coordinate.end(); ++map_it){
			w_query.push_back(
			count(words.begin(), words.end(), map_it->first) * inverse_document_frequency[map_it->first]);
	}
}

vector<string> FileSearch::return_query(string &query){
	string word;
	vector<string> words;

	istringstream line_query(query);
	while(getline(line_query, word, ' ')){
		for(int i = 0; i < 3; i++){
			if(word.back() == '.' or word.back() == ',' or word.back() == '?' or word.back() == '!' or
				 word.back() == ';' or word.back() == '~' or word.back() == '.' or word.back() == '(' or
				 word.back() == ')' or word.back() == '"' or word.back() == ':' or word.back() == '[' or
				 word.back() == ']' or word.back() == '*' or word.back() == '/' or word.back() == '<' or
				 word.back() == '>' or word.back() == 39 )
				 {word.erase(word.end()-1);}

			if(word.front() == '.' or word.front() == ',' or word.front() == '?' or word.front() == '!' or
				 word.front() == ';' or word.front() == '~' or word.front() == '.' or word.front() == '(' or
				 word.front() == ')' or word.front() == '"' or word.front() == ':' or word.front() == '[' or
				 word.front() == ']' or word.front() == '*' or word.front() == '/' or word.front() == '<' or 
				 word.front() == '>' or word.front() == 39)
				 {word.erase(word.begin());}
			}
		if(int(word.find('-')) > 0){word.erase(word.find('-'), 1);}

		transform(word.begin(), word.end(), word.begin(), ::tolower);

		if(word[0] != 0){
				words.push_back(word);
			}
	}
	return words;
}

double FileSearch::cosine_distance(vector<double>& a, vector<double>& b){
  double num = 0.0, den1 = 0.0, den2 = 0.0 ;
    for(int i = 0; i < a.size(); ++i) {
     num+=a[i]*b[i] ;
     den1+=a[i]*a[i] ;
     den2+=b[i]*b[i] ;
     }
	if(isnan(num/(sqrt(den1)*sqrt(den2)))){return 0.0;} 
	else{return num/(sqrt(den1)*sqrt(den2));}
}
