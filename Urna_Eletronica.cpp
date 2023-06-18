#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Candidato {
    string nome;
    int numero;
};

struct Eleitor {
    string nome;
    int numeroTitulo;
};

struct Voto {
    int numeroTitulo;
    int numeroCandidato;
};

struct RegistroVotacao {
    Voto* votos;
    int capacidade;
    int tamanho;
};


void insereCandidato(Candidato* listaCandidato, int& tamanhoLista) {
    Candidato novoCandidato;
    cout << "Digite o nome do candidato: ";
    cin.ignore();
    getline(cin, novoCandidato.nome);
    cout << "Digite o numero do candidato: ";
    cin >> novoCandidato.numero;
    listaCandidato[tamanhoLista++] = novoCandidato;
}

void imprimeListaCandidato(const Candidato* listaCandidato, int tamanhoLista) {
    cout << "Lista de candidatos:" << endl;
    for (int i = 0; i < tamanhoLista; i++) {
        cout << "Nome: " << listaCandidato[i].nome << ", Numero: " << listaCandidato[i].numero << endl;
    }
}

void removeCandidato(Candidato* listaCandidato, int& tamanhoLista) {
    int numeroCandidato;
    cout << "Digite o número do candidato que irá remover: ";
    cin >> numeroCandidato;
    for (int i = 0; i < tamanhoLista; i++) {
        if (listaCandidato[i].numero == numeroCandidato) {
            for (int j = i; j < tamanhoLista - 1; j++) {
                listaCandidato[j] = listaCandidato[j + 1];
            }
            tamanhoLista--;
            cout << "Candidato removido!" << endl;
            return;
        }
    }
    cout << "Candidato não encontrado!" << endl;
}

void salvaCandidato(const Candidato* listaCandidato, int tamanhoLista) {
    ofstream arquivo("lista_candidatos.txt");
    if (arquivo.is_open()) {
        for (int i = 0; i < tamanhoLista; i++) {
            arquivo << "Nome: " << listaCandidato[i].nome << ", Número: " << listaCandidato[i].numero << endl;
        }
        arquivo.close();
        cout << "Candidatos salvos!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

void carregaCandidato(Candidato* listaCandidato, int& tamanhoLista) {
    ifstream arquivo("lista_candidatos.txt");
    if (arquivo.is_open()) {
        tamanhoLista = 0;
        string nome;
        int numero;
        while (arquivo >> nome >> numero) {
            Candidato candidato;
            candidato.nome = nome;
            candidato.numero = numero;
            listaCandidato[tamanhoLista++] = candidato;
        }
        arquivo.close();
        cout << "Candidatos carregados!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}


void insereEleitor(Eleitor* listaEleitores, int& tamanhoLista) {
    Eleitor novoEleitor;
    cout << "Digite o nome do eleitor: ";
    cin.ignore();
    getline(cin, novoEleitor.nome);
    cout << "Digite o numero do titulo do eleitor: ";
    cin >> novoEleitor.numeroTitulo;
    listaEleitores[tamanhoLista++] = novoEleitor;
}

void salvaEleitores(const Eleitor* listaEleitores, int tamanhoLista) {
    ofstream arquivo("lista_eleitores.txt");
    if (arquivo.is_open()) {
        for (int i = 0; i < tamanhoLista; i++) {
            arquivo << listaEleitores[i].nome << " " << listaEleitores[i].numeroTitulo << endl;
        }
        arquivo.close();
        cout << "Eleitores salvos!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

void carregaEleitores(Eleitor* listaEleitores, int& tamanhoLista) {
    ifstream arquivo("lista_eleitores.txt");
    if (arquivo.is_open()) {
        tamanhoLista = 0;
        string nome;
        int numeroTitulo;
        while (arquivo >> nome >> numeroTitulo) {
            Eleitor eleitor;
            eleitor.nome = nome;
            eleitor.numeroTitulo = numeroTitulo;
            listaEleitores[tamanhoLista++] = eleitor;
        }
        arquivo.close();
        cout << "Eleitores carregados!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

bool verificarEleitorApto(const Eleitor* listaEleitores, int tamanhoLista, int numeroTitulo) {
    for (int i = 0; i < tamanhoLista; i++) {
        if (listaEleitores[i].numeroTitulo == numeroTitulo) {
            return true;
        }
    }
    return false;
}

void inicializarRegistroVotacao(RegistroVotacao& registro, int capacidadeInicial) {
    registro.votos = new Voto[capacidadeInicial];
    registro.capacidade = capacidadeInicial;
    registro.tamanho = 0;
}

void salvaVotos(const Voto* listaVotos, int tamanhoLista) {
    ofstream arquivo("registro_votos.txt");
    if (arquivo.is_open()) {
        for (int i = 0; i < tamanhoLista; i++) {
            arquivo << listaVotos[i].numeroTitulo << " " << listaVotos[i].numeroCandidato << endl;
        }
        arquivo.close();
        cout << "Votos salvos!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

void carregaVotos(Voto* listaVotos, int& tamanhoLista) {
    ifstream arquivo("registro_votos.txt");
    if (arquivo.is_open()) {
        tamanhoLista = 0;
        int numeroTitulo;
        int numeroCandidato;
        while (arquivo >> numeroTitulo >> numeroCandidato) {
            Voto voto;
            voto.numeroTitulo = numeroTitulo;
            voto.numeroCandidato = numeroCandidato;
            listaVotos[tamanhoLista++] = voto;
        }
        arquivo.close();
        cout << "Votos carregados!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

void liberarRegistroVotacao(RegistroVotacao& registro) {
    delete[] registro.votos;
}

void gerarRelatorioVotos(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato) {
    cout << "Relatório de votos por candidato:" << endl;
    for (int i = 0; i < tamanhoListaCandidato; i++) {
        int contadorVotos = 0;
        for (int j = 0; j < tamanhoListaVotos; j++) {
            if (listaVotos[j].numeroCandidato == listaCandidato[i].numero) {
                contadorVotos++;
            }
        }
        cout << "Candidato: " << listaCandidato[i].nome << ", Número: " << listaCandidato[i].numero << ", Votos: " << contadorVotos << endl;
    }
}

void gerarResultadoVotacao(int tamanhoListaVotos){
	cout << "Relatório total de votos: " << tamanhoListaVotos << endl;
}

void gerarELeitoresFaltantes(const Eleitor* listaEleitores, int tamanhoListaEleitores, const Voto* listaVotos, int tamanhoListaVotos){
	cout << "Relatório de eleitores faltantes: " << endl;
	for(int i = 0; i < tamanhoListaEleitores; i++){
		bool eleitorVotou = false;
		for(int j = 0; j < tamanhoListaVotos; j++){
			if(listaEleitores[i].numeroTitulo == listaVotos[j].numeroTitulo){
				eleitorVotou = true;
				break;
			}
		}
		if(!eleitorVotou){
			cout << "Eleitor: " << listaEleitores[i].nome << ", Número: " << listaEleitores[i].numeroTitulo << endl;
		}
	}
}

void salvarResultado(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato, const Eleitor* listaEleitores, int tamanhoListaEleitores){
	ofstream arquivo("resultado_votacao.txt");
	if(arquivo.is_open()){
		arquivo << "Relatório de votos por candidato: " << endl;
		for(int i= 0; i < tamanhoListaCandidato; i++){
			int contadorVotos = 0;
			for(int j = 0; j < tamanhoListaVotos; j++){
				if(listaVotos[j].numeroCandidato == listaCandidato[i].numero){
					contadorVotos++;
				}
			}
			arquivo << "Candidato: " << listaCandidato[i].nome << ", Número: " << listaCandidato[i].numero << ", Votos: " << contadorVotos << endl;
		}
		arquivo << endl;
		arquivo << "Relatório do total de votos: " << tamanhoListaVotos << endl;
		arquivo << "Relatório de eleitores faltantes:" << endl;
		for(int i = 0; i < tamanhoListaEleitores; i++){
			bool eleitorVotou = false;
			for(int j = 0; j < tamanhoListaVotos; j++){
				if(listaEleitores[i].numeroTitulo == listaVotos[j].numeroCandidato){
					eleitorVotou = true;
					break;
				}
			}
			if(!eleitorVotou){
				arquivo << "Eleitor: " << listaEleitores[i].nome << ", Número: " << listaEleitores[i].numeroTitulo << endl;
			}
		}
		arquivo.close();
		cout << "Relatórios salvos!" << endl;
	}else{
		cout << "Não foi possível abrir o arquivo." << endl;
	}
}

int encontrarVencedor(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato){
	int* contadorVotos = new int[tamanhoListaCandidato](); //Inicia todos os elementos com zero
	for(int i = 0; i < tamanhoListaVotos; i++){
		int numeroCandidato = listaVotos->numeroCandidato;
		for(int j = 0; j < tamanhoListaCandidato; j++){
			if(listaCandidato[j].numero == numeroCandidato){
				contadorVotos[j]++;
				break;
			}
		}
	}
	int indiceVencedor = 0;
	int maisVotado = contadorVotos[0];
	for(int i = 1; i < tamanhoListaCandidato; i++){
		if(contadorVotos[i] > maisVotado){
			indiceVencedor = i;
			maisVotado = contadorVotos[i];
		}
	}
	delete[] contadorVotos;
	return indiceVencedor;
}

bool verificarEleitorVotou(const Voto* listaVotos, int tamanhoListaVotos, int numeroTitulo) {
    for (int i = 0; i < tamanhoListaVotos; i++) {
        if (listaVotos[i].numeroTitulo == numeroTitulo) {
            return true;
        }
    }
    return false;
}

void realizaVotacao(const Candidato* listaCandidato, int tamanhoCandidato, const Eleitor* listaEleitores, int tamanhoEleitores, RegistroVotacao& registro) {
    int numeroTitulo;
    cout << "Digite o número do título do eleitor: ";
    cin >> numeroTitulo;
    if (!verificarEleitorApto(listaEleitores, tamanhoEleitores, numeroTitulo)) {
        cout << "Eleitor não autorizado!" << endl;
        return;
    }
    
    cout << "Eleitor apto para votar. Candidatos disponíveis:" << endl;
    imprimeListaCandidato(listaCandidato, tamanhoCandidato);
    
    int numeroCandidato;
    cout << "Digite o número do candidato: ";
    cin >> numeroCandidato;
    bool candidatoEncontrado = false;
    for (int i = 0; i < tamanhoCandidato; i++) {
        if (listaCandidato[i].numero == numeroCandidato) {
            candidatoEncontrado = true;
            break;
        }
    }
    if (!candidatoEncontrado) {
        cout << "Candidato não encontrado!" << endl;
        return;
    }
    
    if (registro.tamanho == registro.capacidade) {
        int novaCapacidade = registro.capacidade * 2;
        Voto* novoArray = new Voto[novaCapacidade];
        for (int i = 0; i < registro.tamanho; i++) {
            novoArray[i] = registro.votos[i];
        }
        delete[] registro.votos;
        registro.votos = novoArray;
        registro.capacidade = novaCapacidade;
    }
    
    Voto novoVoto;
    novoVoto.numeroTitulo = numeroTitulo;
    novoVoto.numeroCandidato = numeroCandidato;
    registro.votos[registro.tamanho++] = novoVoto;
    
    cout << "Voto registrado!" << endl;
}

void mostrarQuantidadeVotosPorCandidato(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato) {
    cout << "Quantidade de votos por candidato:" << endl;
    for (int i = 0; i < tamanhoListaCandidato; i++) {
        int contadorVotos = 0;
        for (int j = 0; j < tamanhoListaVotos; j++) {
            if (listaVotos[j].numeroCandidato == listaCandidato[i].numero) {
                contadorVotos++;
            }
        }
        cout << "Candidato: " << listaCandidato[i].nome << ", Número: " << listaCandidato[i].numero << ", Votos: " << contadorVotos << endl;
    }
}


int main() {
	setlocale(LC_ALL, "Portuguese");
    const int MAX_CANDIDATOS = 100;
    Candidato listaCandidato[MAX_CANDIDATOS];
    int tamanhoListaCandidato = 0;

    const int MAX_ELEITORES = 100;
    Eleitor listaEleitores[MAX_ELEITORES];
    int tamanhoListaEleitores = 0;
    
    const int MAX_VOTOS = 1000;
	Voto listaVotos[MAX_VOTOS];
	int tamanhoListaVotos = 0;

    carregaCandidato(listaCandidato, tamanhoListaCandidato);
    carregaEleitores(listaEleitores, tamanhoListaEleitores);
    
    RegistroVotacao registro;
    inicializarRegistroVotacao(registro, 100);

    int escolha;
    do {
        cout << "---------------- Votação ----------------" << endl;
        cout << "01 - Inserir candidato" << endl;
        cout << "02 - Remover candidato" << endl;
        cout << "03 - Listar candidatos" << endl;
        cout << "04 - Inserir eleitor" << endl;
        cout << "05 - Verificar se eleitor está apto" << endl;
        cout << "06 - Votar" << endl;
        cout << "07 - Visualizar quantidade de votos por candidato" << endl;
        cout << "08 - Visualizar vencedor da votação" << endl;
        cout << "09 - Sair" << endl;
        cout << "Digite a função desejada: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                insereCandidato(listaCandidato, tamanhoListaCandidato);
                salvaCandidato(listaCandidato, tamanhoListaCandidato);
                break;
            case 2:
                removeCandidato(listaCandidato, tamanhoListaCandidato);
                salvaCandidato(listaCandidato, tamanhoListaCandidato);
                break;
            case 3:
                imprimeListaCandidato(listaCandidato, tamanhoListaCandidato);
                break;
            case 4:
                insereEleitor(listaEleitores, tamanhoListaEleitores);
                salvaEleitores(listaEleitores, tamanhoListaEleitores);
                break;
            case 5:
                int numeroTitulo;
                cout << "Digite o numero de titulo do eleitor: ";
                cin >> numeroTitulo;
                if (verificarEleitorApto(listaEleitores, tamanhoListaEleitores, numeroTitulo)) {
                    cout << "O eleitor está apto!" << endl;
                } else {
                    cout << "Não foi possível encontrar o eleitor ou ele não está apto!" << endl;
                }
                break;
            case 6:
    			realizaVotacao(listaCandidato, tamanhoListaCandidato, listaEleitores, tamanhoListaEleitores, registro);
    			break;
    		case 7:
    			mostrarQuantidadeVotosPorCandidato(registro.votos, registro.tamanho, listaCandidato, tamanhoListaCandidato);
            case 8:
            	salvarResultado(listaVotos, tamanhoListaVotos, listaCandidato, tamanhoListaCandidato, listaEleitores, tamanhoListaEleitores);
            	int indiceVencedor = encontrarVencedor(listaVotos, tamanhoListaVotos, listaCandidato, tamanhoListaCandidato);
            	cout << "Candidato vencedor: " << listaCandidato[indiceVencedor].nome << ", Numero: " << listaCandidato[indiceVencedor].numero << endl;
        }
    } while (escolha != 9);
    
    liberarRegistroVotacao(registro);
    salvaVotos(listaVotos, tamanhoListaVotos);
    

    return 0;
}


