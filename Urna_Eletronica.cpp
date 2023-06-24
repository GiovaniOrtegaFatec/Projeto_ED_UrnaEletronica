#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Candidato { //cria a struct Candidato contendo nome e n�mero deles
    string nome;
    int numero;
};

struct Eleitor { //cria a struct eleitor contendo nome e n�mero de t�tulo
    string nome;
    int numeroTitulo;
};

struct Voto { //cria a struct voto contendo n�mero de t�tulo e o n�mero do candidato 
    int numeroTitulo;
    int numeroCandidato;
};

struct RegistroVotacao { //cria a struct registrovotacao utilizadno o ponteiro Voto* que aponta para um array dinamicamente alocado de elementos do tipo Voto
    Voto* votos; //cont�m a capacidade m�xima e o tamanho do registro de voto
    int capacidade;
    int tamanho;
};


void insereCandidato(Candidato* listaCandidato, int& tamanhoLista) { //fun��o feita para inserir um novo candidato com nome e n�mero com o ponteiro listaCandidato e tamanhoLista feito para armazenar o tamanho atual da lista
    Candidato novoCandidato;
    cout << "Digite o nome do candidato: ";
    cin.ignore(); //usada para descartar caracteres indesejados
    getline(cin, novoCandidato.nome);
    cout << "Digite o numero do candidato: ";
    cin >> novoCandidato.numero;
    listaCandidato[tamanhoLista++] = novoCandidato; //vetor da lista
}

void imprimeListaCandidato(const Candidato* listaCandidato, int tamanhoLista) { //fun��o feita para mostrar a lista dos candidatos j� criados
    cout << "Lista de candidatos:" << endl;
    for (int i = 0; i < tamanhoLista; i++) {
        cout << "Nome: " << listaCandidato[i].nome << ", Numero: " << listaCandidato[i].numero << endl; //[i] feito para mostrar mostrar todos os candidatos
    }
}

void removeCandidato(Candidato* listaCandidato, int& tamanhoLista) { //fun��o feita para remover os candidatos j� criados
    int numeroCandidato;
    cout << "Digite o n�mero do candidato que ir� remover: ";
    cin >> numeroCandidato;
    for (int i = 0; i < tamanhoLista; i++) {
        if (listaCandidato[i].numero == numeroCandidato) { // se o n�mero for igual de algum candidato j� criado ele remove aquele candidato 
            for (int j = i; j < tamanhoLista - 1; j++) {
                listaCandidato[j] = listaCandidato[j + 1];
            }
            tamanhoLista--;
            cout << "Candidato removido!" << endl;
            return;
        }
    }
    cout << "Candidato n�o encontrado!" << endl; //se n�o houver nenhum candidato com aquele n�mero, aparece essa mensagem
}

void salvaCandidato(const Candidato* listaCandidato, int tamanhoLista) {
    ofstream arquivo("lista_candidatos.txt"); //arquivo de sa�da
    if (arquivo.is_open()) { //se o arquivo estiver aberto ir� reallizar o if que ir� salvar os candidatos criados
        for (int i = 0; i < tamanhoLista; i++) {
            arquivo << "Nome: " << listaCandidato[i].nome << ", N�mero: " << listaCandidato[i].numero << endl;
        }
        arquivo.close();
        cout << "Candidatos salvos!" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo." << endl;
    }
}

void carregaCandidato(Candidato* listaCandidato, int& tamanhoLista) {
    ifstream arquivo("lista_candidatos.txt"); //arquivo de entrada 
    if (arquivo.is_open()) { //se o arquivo estiver aberto ir� realizar o if que ir� carregar os candidatos do arquivo de texto
        tamanhoLista = 0;
        string nome;
        int numero;
        while (arquivo >> nome >> numero) { //o loop 'while' continuar� enquanto houver dados para serem lidos do arquivo.
            Candidato candidato;
            candidato.nome = nome;
            candidato.numero = numero;
            listaCandidato[tamanhoLista++] = candidato;
        }
        arquivo.close();
        cout << "Candidatos carregados!" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo." << endl;
    }
}


void insereEleitor(Eleitor* listaEleitores, int& tamanhoLista) { //fun��o feita para inserir um novo eleitor com o ponteiro listaEleitores e tamanhoLista para armazenar o tamanho atual da lista
    Eleitor novoEleitor;
    cout << "Digite o nome do eleitor: ";
    cin.ignore();
    getline(cin, novoEleitor.nome);
    cout << "Digite o numero do titulo do eleitor: ";
    cin >> novoEleitor.numeroTitulo;
    listaEleitores[tamanhoLista++] = novoEleitor;
}

void salvaEleitores(const Eleitor* listaEleitores, int tamanhoLista) { //fun��o feita para salvar eleitores que foram cadastrados 
    ofstream arquivo("lista_eleitores.txt"); //arquivo de sa�da 
    if (arquivo.is_open()) { //se o arquivo estiver aberto ir� realizar o if que salva os novos eleitores criados
        for (int i = 0; i < tamanhoLista; i++) {
            arquivo << listaEleitores[i].nome << " " << listaEleitores[i].numeroTitulo << endl;
        }
        arquivo.close();
        cout << "Eleitores salvos!" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo." << endl;
    }
}

void carregaEleitores(Eleitor* listaEleitores, int& tamanhoLista) { //fun��o feita para carregar os eleitores salvos do arquivo de texto 
    ifstream arquivo("lista_eleitores.txt"); //arquivo de entrada 
    if (arquivo.is_open()) { //se o arquivo estiver aberto ir� realizar o if que tem a fun��o de ler os eleitores do arquivo txt
        tamanhoLista = 0;
        string nome;
        int numeroTitulo;
        while (arquivo >> nome >> numeroTitulo) { //o loop 'while' continuar� enquanto houver dados para serem lidos do arquivo.
            Eleitor eleitor;
            eleitor.nome = nome;
            eleitor.numeroTitulo = numeroTitulo;
            listaEleitores[tamanhoLista++] = eleitor;
        }
        arquivo.close();
        cout << "Eleitores carregados!" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo." << endl;
    }
}

bool verificarEleitorApto(const Eleitor* listaEleitores, int tamanhoLista, int numeroTitulo) { //fun��o feita para verificar se o eleitor est� apto, feita em bool para retornar verdadeiro ou falso
    for (int i = 0; i < tamanhoLista; i++) {
        if (listaEleitores[i].numeroTitulo == numeroTitulo) { //se o n�mero de t�tulo estiver dentro da lista, o eleitor estar� apto
            return true;
        }
    }
    return false;
}

void inicializarRegistroVotacao(RegistroVotacao& registro, int capacidadeInicial) { //fun��o feita para iniciar o registro do voto, com um objeto chamado registro e a capacidade inicial
    registro.votos = new Voto[capacidadeInicial]; //array din�mico do tipo Voto, tamanho definido pela capacidade inicial
    registro.capacidade = capacidadeInicial; //capacidade m�xima de votos 
    registro.tamanho = 0; //inicialmente n�o h� votos armazenados 
}

void salvaVotos(const Voto* listaVotos, int tamanhoLista) { //fun��o feita para salvar os votos realizados 
    ofstream arquivo("registro_votos.txt"); //arquivo de sa�da
    if (arquivo.is_open()) { //se o arquivo estiver aberto, ser� cadastrado um novo voto
        for (int i = 0; i < tamanhoLista; i++) {
            arquivo << listaVotos[i].numeroTitulo << " " << listaVotos[i].numeroCandidato << endl;
        }
        arquivo.close();
        cout << "Votos salvos!" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo." << endl;
    }
}

void carregaVotos(Voto* listaVotos, int& tamanhoLista) { //fun��o feita para carregar os votos do arquivo de texto 
    ifstream arquivo("registro_votos.txt"); //arquivo de entrada 
    if (arquivo.is_open()) { // se o arquivo estiver aberto os dados ser�o carregados
        tamanhoLista = 0;
        int numeroTitulo;
        int numeroCandidato;
        while (arquivo >> numeroTitulo >> numeroCandidato) { //o loop 'while' continuar� enquanto houver dados para serem lidos do arquivo.
            Voto voto;
            voto.numeroTitulo = numeroTitulo;
            voto.numeroCandidato = numeroCandidato;
            listaVotos[tamanhoLista++] = voto;
        }
        arquivo.close();
        cout << "Votos carregados!" << endl;
    } else {
        cout << "N�o foi poss�vel abrir o arquivo." << endl;
    }
}

void gerarRelatorioVotos(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato) {
    cout << "Relat�rio de votos por candidato:" << endl;
    for (int i = 0; i < tamanhoListaCandidato; i++) {
        int contadorVotos = 0;
        for (int j = 0; j < tamanhoListaVotos; j++) {
            if (listaVotos[j].numeroCandidato == listaCandidato[i].numero) {
                contadorVotos++;
            }
        }
        cout << "Candidato: " << listaCandidato[i].nome << ", N�mero: " << listaCandidato[i].numero << ", Votos: " << contadorVotos << endl;
    }
}

void gerarResultadoVotacao(int tamanhoListaVotos){
	cout << "Relat�rio total de votos: " << tamanhoListaVotos << endl;
}

void gerarELeitoresFaltantes(const Eleitor* listaEleitores, int tamanhoListaEleitores, const Voto* listaVotos, int tamanhoListaVotos){
	cout << "Relat�rio de eleitores faltantes: " << endl;
	for(int i = 0; i < tamanhoListaEleitores; i++){
		bool eleitorVotou = false;
		for(int j = 0; j < tamanhoListaVotos; j++){
			if(listaEleitores[i].numeroTitulo == listaVotos[j].numeroTitulo){
				eleitorVotou = true;
				break;
			}
		}
		if(!eleitorVotou){
			cout << "Eleitor: " << listaEleitores[i].nome << ", N�mero: " << listaEleitores[i].numeroTitulo << endl;
		}
	}
}

bool verificarEleitorVotou(const Voto* listaVotos, int tamanhoListaVotos, int numeroTitulo) { //fun��o criada para verficar se o eleitor j� votou e n�o ter votos duplicados
    for (int i = 0; i < tamanhoListaVotos; i++) {
        if (listaVotos[i].numeroTitulo == numeroTitulo) {
            return true;
        }
    }
    return false;
}

void salvarResultado(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato, const Eleitor* listaEleitores, int tamanhoListaEleitores){
	ofstream arquivo("resultado_votacao.txt"); //arquivo de sa�da 
	if(arquivo.is_open()){ //se o arquivo estiver aberto, o if ir� ser realizado para salvar os resultados da vota��o
		arquivo << "Relat�rio de votos por candidato: " << endl;
		for(int i= 0; i < tamanhoListaCandidato; i++){
			int contadorVotos = 0;
			for(int j = 0; j < tamanhoListaVotos; j++){
				if(listaVotos[j].numeroCandidato == listaCandidato[i].numero){
					contadorVotos++;
				}
			}
			arquivo << "Candidato: " << listaCandidato[i].nome << ", N�mero: " << listaCandidato[i].numero << ", Votos: " << contadorVotos << endl;
		}
		arquivo << endl;
		arquivo << "Relat�rio do total de votos: " << tamanhoListaVotos << endl;
		arquivo << "Relat�rio de eleitores faltantes:" << endl;
		for(int i = 0; i < tamanhoListaEleitores; i++){
			bool eleitorVotou = false;
			for(int j = 0; j < tamanhoListaVotos; j++){
				if(listaEleitores[i].numeroTitulo == listaVotos[j].numeroCandidato){
					eleitorVotou = true;
					break;
				}
			}
			if(!eleitorVotou){
				arquivo << "Eleitor: " << listaEleitores[i].nome << ", N�mero: " << listaEleitores[i].numeroTitulo << endl;
			}
		}
		arquivo.close();
		cout << "Relat�rios salvos!" << endl;
	}else{
		cout << "N�o foi poss�vel abrir o arquivo." << endl;
	}
}

int encontrarVencedor(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato){ //fun��o criada para encontrar o vencedor da elei��o
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


void mostrarQuantidadeVotosPorCandidato(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato) { //fun��o criada para mostrar quantos votos foram captados para cada candidato
    cout << "Quantidade de votos por candidato:" << endl;
    for (int i = 0; i < tamanhoListaCandidato; i++) {
        int contadorVotos = 0;
        for (int j = 0; j < tamanhoListaVotos; j++) {
            if (listaVotos[j].numeroCandidato == listaCandidato[i].numero) {
                contadorVotos++;
            }
        }
        cout << "Candidato: " << listaCandidato[i].nome << ", N�mero: " << listaCandidato[i].numero << ", Votos: " << contadorVotos << endl;
    }
}

void realizaVotacao(const Candidato* listaCandidato, int tamanhoCandidato, const Eleitor* listaEleitores, int tamanhoEleitores, RegistroVotacao& registro) { //fun��o criada para realizar a vota��o 
    int numeroTitulo;
    cout << "Digite o n�mero do t�tulo do eleitor: ";
    cin >> numeroTitulo;
    if (!verificarEleitorApto(listaEleitores, tamanhoEleitores, numeroTitulo)) {
        cout << "Eleitor n�o autorizado!" << endl;
        return;
    }
    
    cout << "Eleitor apto para votar. Candidatos dispon�veis:" << endl;
    imprimeListaCandidato(listaCandidato, tamanhoCandidato);
    
    int numeroCandidato;
    cout << "Digite o n�mero do candidato: ";
    cin >> numeroCandidato;
    bool candidatoEncontrado = false;
    for (int i = 0; i < tamanhoCandidato; i++) {
        if (listaCandidato[i].numero == numeroCandidato) {
            candidatoEncontrado = true;
            break;
        }
    }
    if (!candidatoEncontrado) {
        cout << "Candidato n�o encontrado!" << endl;
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



int main() {
	setlocale(LC_ALL, "Portuguese");
    const int MAX_CANDIDATOS = 100;
    Candidato listaCandidato[MAX_CANDIDATOS]; //tamanho m�ximo da lista de candidatos 
    int tamanhoListaCandidato = 0; 

    const int MAX_ELEITORES = 100;
    Eleitor listaEleitores[MAX_ELEITORES]; //tamanho m�ximo da lista de eleitores 
    int tamanhoListaEleitores = 0;
    
    const int MAX_VOTOS = 100;
	Voto listaVotos[MAX_VOTOS]; //tamanho m�ximo da lista de votos (1 por eleitor)
	int tamanhoListaVotos = 0;

    carregaCandidato(listaCandidato, tamanhoListaCandidato); //carrega os candidatos 
    carregaEleitores(listaEleitores, tamanhoListaEleitores); //carrega os eleitores 
    
    RegistroVotacao registro;
    inicializarRegistroVotacao(registro, 100);

    int escolha; //fun��o para fazer um 'menu' de op��es
    do {
        cout << "---------------- Vota��o ----------------" << endl;
        cout << "01 - Inserir candidato" << endl;
        cout << "02 - Remover candidato" << endl;
        cout << "03 - Listar candidatos" << endl;
        cout << "04 - Inserir eleitor" << endl;
        cout << "05 - Verificar se eleitor est� apto" << endl;
        cout << "06 - Votar" << endl;
        cout << "07 - Visualizar quantidade de votos por candidato" << endl;
        cout << "08 - Visualizar vencedor da vota��o" << endl;
        cout << "09 - Sair" << endl;
        cout << "Digite a fun��o desejada: ";
        cin >> escolha;

        switch (escolha) {
            case 1: //ir� inserir o candidato e salv�-lo no arquivo de texto
                insereCandidato(listaCandidato, tamanhoListaCandidato);
                salvaCandidato(listaCandidato, tamanhoListaCandidato);
                break;
            case 2: //ir� remover o candidato e salv�-lo no arquivo de texto 
                removeCandidato(listaCandidato, tamanhoListaCandidato);
                salvaCandidato(listaCandidato, tamanhoListaCandidato);
                break;
            case 3: //ir� mostrar a lista de candidatos que j� foram cadastrados
                imprimeListaCandidato(listaCandidato, tamanhoListaCandidato);
                break;
            case 4: //ir� inserir o eleitor e salv�-lo no arquivo de texto 
                insereEleitor(listaEleitores, tamanhoListaEleitores);
                salvaEleitores(listaEleitores, tamanhoListaEleitores);
                break;
            case 5: //ir� verificar se o eleitor est� apto pelo n�mero de t�tulo 
                int numeroTitulo;
                cout << "Digite o numero de titulo do eleitor: ";
                cin >> numeroTitulo;
                if (verificarEleitorApto(listaEleitores, tamanhoListaEleitores, numeroTitulo)) {
                    cout << "O eleitor est� apto!" << endl;
                } else {
                    cout << "N�o foi poss�vel encontrar o eleitor ou ele n�o est� apto!" << endl;
                }
                break;
            case 6: //ir� cadastrar um novo voto
    			realizaVotacao(listaCandidato, tamanhoListaCandidato, listaEleitores, tamanhoListaEleitores, registro);
    			salvaVotos(listaVotos, tamanhoListaVotos);
    			break;
    		case 7: //ir� mostrar quantos votos cada candidato teve 
    			mostrarQuantidadeVotosPorCandidato(registro.votos, registro.tamanho, listaCandidato, tamanhoListaCandidato);
            case 8: //ir� mostrar o candidato que venceu a elei��o 
            	salvarResultado(listaVotos, tamanhoListaVotos, listaCandidato, tamanhoListaCandidato, listaEleitores, tamanhoListaEleitores);
            	int indiceVencedor = encontrarVencedor(listaVotos, tamanhoListaVotos, listaCandidato, tamanhoListaCandidato);
            	cout << "Candidato vencedor: " << listaCandidato[indiceVencedor].nome << ", Numero: " << listaCandidato[indiceVencedor].numero << endl;
        }
    } while (escolha != 9); //quando a escolha for 9, o programa ir� fechar
    
    return 0;
}


