#include "filesearch.h"

using namespace std;

int main(){
	cout<<"Digite o nome da pasta onde deseja procurar: ";
	string folder;
	getline(cin, folder);
	FileSearch n = FileSearch(folder);
	while(true){
		string q;
		cout<<"Digite sua pesquisa: "; 
		getline(cin, q);
		n.find(q);
		q.clear();
	}
	return 0;
}
