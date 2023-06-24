#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Candidato { //cria a struct Candidato contendo nome e número deles
    string nome;
    int numero;
};

struct Eleitor { //cria a struct eleitor contendo nome e número de título
    string nome;
    int numeroTitulo;
};

struct Voto { //cria a struct voto contendo número de título e o número do candidato 
    int numeroTitulo;
    int numeroCandidato;
};

struct RegistroVotacao { //cria a struct registrovotacao utilizadno o ponteiro Voto* que aponta para um array dinamicamente alocado de elementos do tipo Voto
    Voto* votos; //contém a capacidade máxima e o tamanho do registro de voto
    int capacidade;
    int tamanho;
};


void insereCandidato(Candidato* listaCandidato, int& tamanhoLista) { //função feita para inserir um novo candidato com nome e número com o ponteiro listaCandidato e tamanhoLista feito para armazenar o tamanho atual da lista
    Candidato novoCandidato;
    cout << "Digite o nome do candidato: ";
    cin.ignore(); //usada para descartar caracteres indesejados
    getline(cin, novoCandidato.nome);
    cout << "Digite o numero do candidato: ";
    cin >> novoCandidato.numero;
    listaCandidato[tamanhoLista++] = novoCandidato; //vetor da lista
}

void imprimeListaCandidato(const Candidato* listaCandidato, int tamanhoLista) { //função feita para mostrar a lista dos candidatos já criados
    cout << "Lista de candidatos:" << endl;
    for (int i = 0; i < tamanhoLista; i++) {
        cout << "Nome: " << listaCandidato[i].nome << ", Numero: " << listaCandidato[i].numero << endl; //[i] feito para mostrar mostrar todos os candidatos
    }
}

void removeCandidato(Candidato* listaCandidato, int& tamanhoLista) { //função feita para remover os candidatos já criados
    int numeroCandidato;
    cout << "Digite o número do candidato que irá remover: ";
    cin >> numeroCandidato;
    for (int i = 0; i < tamanhoLista; i++) {
        if (listaCandidato[i].numero == numeroCandidato) { // se o número for igual de algum candidato já criado ele remove aquele candidato 
            for (int j = i; j < tamanhoLista - 1; j++) {
                listaCandidato[j] = listaCandidato[j + 1];
            }
            tamanhoLista--;
            cout << "Candidato removido!" << endl;
            return;
        }
    }
    cout << "Candidato não encontrado!" << endl; //se não houver nenhum candidato com aquele número, aparece essa mensagem
}

void salvaCandidato(const Candidato* listaCandidato, int tamanhoLista) {
    ofstream arquivo("lista_candidatos.txt"); //arquivo de saída
    if (arquivo.is_open()) { //se o arquivo estiver aberto irá reallizar o if que irá salvar os candidatos criados
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
    ifstream arquivo("lista_candidatos.txt"); //arquivo de entrada 
    if (arquivo.is_open()) { //se o arquivo estiver aberto irá realizar o if que irá carregar os candidatos do arquivo de texto
        tamanhoLista = 0;
        string nome;
        int numero;
        while (arquivo >> nome >> numero) { //o loop 'while' continuará enquanto houver dados para serem lidos do arquivo.
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


void insereEleitor(Eleitor* listaEleitores, int& tamanhoLista) { //função feita para inserir um novo eleitor com o ponteiro listaEleitores e tamanhoLista para armazenar o tamanho atual da lista
    Eleitor novoEleitor;
    cout << "Digite o nome do eleitor: ";
    cin.ignore();
    getline(cin, novoEleitor.nome);
    cout << "Digite o numero do titulo do eleitor: ";
    cin >> novoEleitor.numeroTitulo;
    listaEleitores[tamanhoLista++] = novoEleitor;
}

void salvaEleitores(const Eleitor* listaEleitores, int tamanhoLista) { //função feita para salvar eleitores que foram cadastrados 
    ofstream arquivo("lista_eleitores.txt"); //arquivo de saída 
    if (arquivo.is_open()) { //se o arquivo estiver aberto irá realizar o if que salva os novos eleitores criados
        for (int i = 0; i < tamanhoLista; i++) {
            arquivo << listaEleitores[i].nome << " " << listaEleitores[i].numeroTitulo << endl;
        }
        arquivo.close();
        cout << "Eleitores salvos!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

void carregaEleitores(Eleitor* listaEleitores, int& tamanhoLista) { //função feita para carregar os eleitores salvos do arquivo de texto 
    ifstream arquivo("lista_eleitores.txt"); //arquivo de entrada 
    if (arquivo.is_open()) { //se o arquivo estiver aberto irá realizar o if que tem a função de ler os eleitores do arquivo txt
        tamanhoLista = 0;
        string nome;
        int numeroTitulo;
        while (arquivo >> nome >> numeroTitulo) { //o loop 'while' continuará enquanto houver dados para serem lidos do arquivo.
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

bool verificarEleitorApto(const Eleitor* listaEleitores, int tamanhoLista, int numeroTitulo) { //função feita para verificar se o eleitor está apto, feita em bool para retornar verdadeiro ou falso
    for (int i = 0; i < tamanhoLista; i++) {
        if (listaEleitores[i].numeroTitulo == numeroTitulo) { //se o número de título estiver dentro da lista, o eleitor estará apto
            return true;
        }
    }
    return false;
}

void inicializarRegistroVotacao(RegistroVotacao& registro, int capacidadeInicial) { //função feita para iniciar o registro do voto, com um objeto chamado registro e a capacidade inicial
    registro.votos = new Voto[capacidadeInicial]; //array dinâmico do tipo Voto, tamanho definido pela capacidade inicial
    registro.capacidade = capacidadeInicial; //capacidade máxima de votos 
    registro.tamanho = 0; //inicialmente não há votos armazenados 
}

void salvaVotos(const Voto* listaVotos, int tamanhoLista) { //função feita para salvar os votos realizados 
    ofstream arquivo("registro_votos.txt"); //arquivo de saída
    if (arquivo.is_open()) { //se o arquivo estiver aberto, será cadastrado um novo voto
        for (int i = 0; i < tamanhoLista; i++) {
            arquivo << listaVotos[i].numeroTitulo << " " << listaVotos[i].numeroCandidato << endl;
        }
        arquivo.close();
        cout << "Votos salvos!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
}

void carregaVotos(Voto* listaVotos, int& tamanhoLista) { //função feita para carregar os votos do arquivo de texto 
    ifstream arquivo("registro_votos.txt"); //arquivo de entrada 
    if (arquivo.is_open()) { // se o arquivo estiver aberto os dados serão carregados
        tamanhoLista = 0;
        int numeroTitulo;
        int numeroCandidato;
        while (arquivo >> numeroTitulo >> numeroCandidato) { //o loop 'while' continuará enquanto houver dados para serem lidos do arquivo.
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

bool verificarEleitorVotou(const Voto* listaVotos, int tamanhoListaVotos, int numeroTitulo) { //função criada para verficar se o eleitor já votou e não ter votos duplicados
    for (int i = 0; i < tamanhoListaVotos; i++) {
        if (listaVotos[i].numeroTitulo == numeroTitulo) {
            return true;
        }
    }
    return false;
}

void salvarResultado(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato, const Eleitor* listaEleitores, int tamanhoListaEleitores){
	ofstream arquivo("resultado_votacao.txt"); //arquivo de saída 
	if(arquivo.is_open()){ //se o arquivo estiver aberto, o if irá ser realizado para salvar os resultados da votação
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

int encontrarVencedor(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato){ //função criada para encontrar o vencedor da eleição
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


void mostrarQuantidadeVotosPorCandidato(const Voto* listaVotos, int tamanhoListaVotos, const Candidato* listaCandidato, int tamanhoListaCandidato) { //função criada para mostrar quantos votos foram captados para cada candidato
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

void realizaVotacao(const Candidato* listaCandidato, int tamanhoCandidato, const Eleitor* listaEleitores, int tamanhoEleitores, RegistroVotacao& registro) { //função criada para realizar a votação 
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



int main() {
	setlocale(LC_ALL, "Portuguese");
    const int MAX_CANDIDATOS = 100;
    Candidato listaCandidato[MAX_CANDIDATOS]; //tamanho máximo da lista de candidatos 
    int tamanhoListaCandidato = 0; 

    const int MAX_ELEITORES = 100;
    Eleitor listaEleitores[MAX_ELEITORES]; //tamanho máximo da lista de eleitores 
    int tamanhoListaEleitores = 0;
    
    const int MAX_VOTOS = 100;
	Voto listaVotos[MAX_VOTOS]; //tamanho máximo da lista de votos (1 por eleitor)
	int tamanhoListaVotos = 0;

    carregaCandidato(listaCandidato, tamanhoListaCandidato); //carrega os candidatos 
    carregaEleitores(listaEleitores, tamanhoListaEleitores); //carrega os eleitores 
    
    RegistroVotacao registro;
    inicializarRegistroVotacao(registro, 100);

    int escolha; //função para fazer um 'menu' de opções
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
            case 1: //irá inserir o candidato e salvá-lo no arquivo de texto
                insereCandidato(listaCandidato, tamanhoListaCandidato);
                salvaCandidato(listaCandidato, tamanhoListaCandidato);
                break;
            case 2: //irá remover o candidato e salvá-lo no arquivo de texto 
                removeCandidato(listaCandidato, tamanhoListaCandidato);
                salvaCandidato(listaCandidato, tamanhoListaCandidato);
                break;
            case 3: //irá mostrar a lista de candidatos que já foram cadastrados
                imprimeListaCandidato(listaCandidato, tamanhoListaCandidato);
                break;
            case 4: //irá inserir o eleitor e salvá-lo no arquivo de texto 
                insereEleitor(listaEleitores, tamanhoListaEleitores);
                salvaEleitores(listaEleitores, tamanhoListaEleitores);
                break;
            case 5: //irá verificar se o eleitor está apto pelo número de título 
                int numeroTitulo;
                cout << "Digite o numero de titulo do eleitor: ";
                cin >> numeroTitulo;
                if (verificarEleitorApto(listaEleitores, tamanhoListaEleitores, numeroTitulo)) {
                    cout << "O eleitor está apto!" << endl;
                } else {
                    cout << "Não foi possível encontrar o eleitor ou ele não está apto!" << endl;
                }
                break;
            case 6: //irá cadastrar um novo voto
    			realizaVotacao(listaCandidato, tamanhoListaCandidato, listaEleitores, tamanhoListaEleitores, registro);
    			salvaVotos(listaVotos, tamanhoListaVotos);
    			break;
    		case 7: //irá mostrar quantos votos cada candidato teve 
    			mostrarQuantidadeVotosPorCandidato(registro.votos, registro.tamanho, listaCandidato, tamanhoListaCandidato);
            case 8: //irá mostrar o candidato que venceu a eleição 
            	salvarResultado(listaVotos, tamanhoListaVotos, listaCandidato, tamanhoListaCandidato, listaEleitores, tamanhoListaEleitores);
            	int indiceVencedor = encontrarVencedor(listaVotos, tamanhoListaVotos, listaCandidato, tamanhoListaCandidato);
            	cout << "Candidato vencedor: " << listaCandidato[indiceVencedor].nome << ", Numero: " << listaCandidato[indiceVencedor].numero << endl;
        }
    } while (escolha != 9); //quando a escolha for 9, o programa irá fechar
    
    return 0;
}


