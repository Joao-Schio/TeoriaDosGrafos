/**
 * Aluno João Pedro Schio Ortega
 * comando de compilacao usado - g++ src/<regex para todos>.cpp -o pccm -Wall -Werror -std=c++20
 * por algum motivo o Werror nao compilar com asteristico dentro de comentario
 * estou reentregando o trabalho após a data de entrega
 * por que depois de testar com os grafos maiores percebi que o algoritmo estava MUITO lento
 * 
 * 
 * consideracoes : 
 *     Não use o a implementação do foreach do c++ por que ele é MUITO lento
 * 
 * 
 * 
 * Consideracoes apos a recorrecao (desculpe a falta de acentos, estou em um SO novo e ainda nao o configurei direito)
 * 
 * O problema nao era o mergesort sempre em todos os meus testes ele rodava bem rapido
 * Eu achava que o problema era a std::tuple mas tambem nao era
 * 
 * o problema era que eu fazia um vetor de verticies, e entao sempre que eu acessava um verticie 
 * ele tinha que passar por um construtor e quando ele saia do escopo um destrutor
 * entao (nao me pergunte quanto tempo eu demorei pra descobrir isso)
 * 
 * mudando as classes para um vetor de ponteiros para verticie cada verticie so passa por um construtor e um destrutor
 * o que aumenta significativamente a velocidade do programa
 * 
 * mas quando eu descobri ja tinha me livrado da tupla entao fica sem msm
 * 
*/



#include <iostream>
#include "Grafo.hpp"

void leGrafo(std::string nomeArquivo, Grafo *g){
    FILE *arquivo = fopen(nomeArquivo.c_str(), "r");
    if(arquivo == NULL){
        std::cout << "E" << std::endl;
        exit(1);
    }
    char inicio = 'i';
    while(fscanf(arquivo, "%c", &inicio) != EOF){
        if(inicio == 'I'){
            int arestas,arcos;
            fscanf(arquivo, "%d %d", &arestas, &arcos);
            g -> setNumVertices(arestas);
            g -> setNumArestas(arcos);
        }

        else if(inicio == 'N'){
            int id, gEntrada, gSaida;
            fscanf(arquivo, "%d %d %d", &id, &gEntrada, &gSaida);
            g -> addVerticie(id,gEntrada, gSaida);
        }

        else if(inicio == 'E'){
            int id, vizinho, custo;
            fscanf(arquivo, "%d %d %d", &id, &vizinho, &custo);
            g -> addArco(id,vizinho,custo);
        }
        else if(inicio == 'T'){
            break;
        }
    }
    fclose(arquivo);
}



void merge(std::vector<Verticie*> &v, int inicio,int meio, int fim){
    int tamanho1 = meio - inicio + 1;
    int tamanho2 = fim - meio;
    Verticie **aux1;
    Verticie **aux2;
    aux1 = new Verticie*[tamanho1];
    aux2 = new Verticie*[tamanho2];

    for(int i = 0; i < tamanho1; i++){
        aux1[i] = v.at(i + inicio);
    }
    for(int i = 0; i < tamanho2; i++){
        aux2[i] = v.at(1 + meio + i);
    }

    int i = 0, j = 0, k = inicio;

    while(i < tamanho1 && j < tamanho2){
        if(aux1[i] -> getId() > aux2[j] -> getId()){
            v.at(k) = aux2[j];
            j++;
        }
        else{
            v.at(k) = aux1[i];
            i++;
        }
        k++;
    }   
    while(j < tamanho2){
        v.at(k) = aux2[j];
        j++;
        k++;
    }
    while(i < tamanho1){
        v.at(k) = aux1[i];
        i++;
        k++;
    }
    delete [] aux1;
    delete [] aux2;
}

void imprimeVisitacao(std::vector<Verticie*> &O,int iteracao){
    printf("O %d ",iteracao);
    for(unsigned i = 0; i < O.size(); i++){
        printf("%d ",O.at(i) -> getId());
    }
    printf("\n");
}

void mergesort(std::vector<Verticie*> &v, int inicio, int fim){
    if(fim > inicio){
        int meio = (fim + inicio) / 2;
        mergesort(v,inicio,meio);
        mergesort(v, meio + 1, fim);
        merge(v,inicio,meio,fim);
    }
}


void desmarcar(std::vector<bool> &v){
    for(unsigned i = 0; i < v.size(); i++){
        v.at(i) = false;
    }
}


void printCaminho(std::vector<Verticie*> *anterior, std::vector<int> *custo, Verticie *v, Grafo *g){
    std::vector<Verticie*> todos = g -> getVerticesVetor();
    mergesort(todos,0,todos.size() - 1);
    /**
     * grafo.txt não necessariamente tem os vertices em ordem crescente
     * entao na hora da impressão é preciso ordenar
    */

   /**
    * Exemplo
    * se o grafo g-5-6.txt fosse
    *       I 5 6
            N 0 1 2
            N 2 1 1
            N 3 2 1
            N 1 1 1
            N 4 1 1
            E 0 1 5
            E 0 4 3
            E 1 2 1
            E 2 3 3
            E 3 0 1
            E 4 3 1
            T
        Com o N 1 1 1 apos os vertices 0 2 3 os prints nao estariam certos
    */


    for(unsigned x = 0; x < todos.size(); x++){
        Verticie *i = todos.at(x);
        if(i -> igual(*v)){
            printf("P %d 0 1 %d\n",i -> getId(),i -> getId());
        }
        else if(anterior -> at(i -> getId()) -> igual(Verticie())){
            printf("U %d\n",i -> getId());
        }
        else if (!i -> igual(*v)){
            std::vector<int> idCaminho;
            Verticie *aux = anterior -> at(i -> getId());
            while(!aux -> igual(*v) && !aux -> igual(Verticie())){
                idCaminho.insert(idCaminho.begin(),aux -> getId());
                aux = anterior -> at(aux -> getId());
            }
            printf("P %d %d %ld %d ",i -> getId(),custo -> at(i -> getId()),idCaminho.size() + 2,v -> getId());
            for(int j : idCaminho){
                printf("%d ",j);
            }
            printf("%d\n",i -> getId());
        }
    }
}

bool cicloNeg(Grafo *g, Verticie *v, std::vector<int> *custo){
    for(unsigned x = 0; x < g -> getNumVertices(); x++){
        Verticie *u = g -> getVerticie(x);
        std::vector<Arco> arcos = u -> getArcos();
        for(unsigned y = 0; y < arcos.size(); y++){
            Arco arco = arcos.at(y);
            Verticie vArco = *(arco.getDestino());
            int custoArco = arco.getCusto();
            if(custo -> at(vArco.getId()) > custo -> at(u -> getId()) + custoArco){
                return true;
            }
        }
    }
    return false;
}

void podeParar(std::vector<Verticie*> &O, int iteracoes, int tamGrafo){
    for(int i = iteracoes + 1; i < tamGrafo; i++){
        imprimeVisitacao(O,i);
    }
}

void passaPraFrente(std::vector<Verticie*> &O, int pos){
    Verticie *aux = O.at(pos);
    for(unsigned i = pos; i > 0; i--){
        O.at(i) = O.at(i - 1);
    }
    O.at(0) = aux;
}

void bellmanford(Grafo *g, Verticie *v,std::vector<Verticie*> *anterior, std::vector<int> *custo){
    // Entradas grafo G, verticie de origem V, vetor de verticies que armazena o anterior de um id
    // vetor de custo que armazena o custo da origem ate o verticie com o id 
    for(unsigned i = 0; i < g -> getNumVertices();i++){
       anterior -> at(i) = new Verticie();
        custo -> at(i) = 200000000; // numero muito maior que o custo maximo
    }
    custo -> at(v -> getId()) = 0;
    // definindo a ordem
    std::vector<Verticie*> O = g -> getVerticesVetor();
    
    // achando a posicao do verticie V em O
    // definindo a ordem comecando em V e seguindo em ordem crescente de ID

    int idV = -1;
    for(unsigned i = 0; i < O.size() && idV == -1; i++){
        if(O.at(i) -> igual(*v)){
            idV = i;
        }
    }
    Verticie *aux = O.at(0);
    O.at(0) = O.at(idV);
    O.at(idV) = aux;
    mergesort(O,1,O.size() - 1);

    std::vector<bool> processados(g -> getNumVertices());
    std::vector<bool> reduzidos(g -> getNumVertices());
    std::vector<bool> reduzidoApos(g -> getNumVertices());
    std::vector<bool> inserido(g -> getNumVertices());

    mergesort(O,1,O.size() - 1);
    long iteracoes = 0;
    while(iteracoes < g -> getNumVertices()){
        imprimeVisitacao(O,iteracoes);
        desmarcar(processados);
        desmarcar(reduzidos);
        desmarcar(reduzidoApos);
        desmarcar(inserido);

        bool entrouNoRedApos = false; // ja que agora estou usando os vetores reduzidos com o tamanho total
        bool entrouNoRed = false; // preciso de uma flag para saber quando eles nao foram definidos para poder parar
        for(unsigned i = 0; i < O.size(); i++){
            Verticie *u = O.at(i);
            processados.at(u -> getId()) = true;
            std::vector<Arco> arcos = u -> getArcos();
            for(unsigned j = 0; j < arcos.size(); j++){
                Arco arco = arcos.at(j);
                int idDestino = arco.getIdDestino();
                int custoArco = arco.getCusto();
                if(custo -> at(idDestino) > custo -> at(u -> getId()) + custoArco){
                    custo -> at(idDestino) = custo -> at(u -> getId()) + custoArco;
                    anterior -> at(idDestino) = u;
                    if(processados.at(idDestino)){
                        reduzidoApos.at(idDestino) = true;
                        entrouNoRedApos = true;
                    }
                    else if(!processados.at(idDestino)){ 
                        reduzidos.at(idDestino) = true;
                        entrouNoRed = true;
                    }
                }
            }
        }
        if(!entrouNoRedApos && !entrouNoRed){
            podeParar(O,iteracoes,g -> getNumVertices());
            break;
        }
        int pos = 0;
        std::vector<Verticie*> OLinha(g -> getNumVertices());

        for(unsigned x = 0; x < O.size(); x++){
            Verticie *i = O.at(x);
            if(reduzidoApos.at(i -> getId())){
                OLinha.at(pos) = i;
                inserido.at(i -> getId()) = true;
                pos++;
            }
        }
        for(unsigned x = 0; x < O.size(); x++){
            Verticie *i = O.at(x);
            if(reduzidos.at(i -> getId()) && !inserido.at(i -> getId())){
                OLinha.at(pos) = i;
                inserido.at(i -> getId()) = true;
                pos++;
            }
        }
        for(unsigned x = 0; x < O.size(); x++){
            Verticie *i = O.at(x);
            if(!inserido.at(i -> getId())){
                OLinha.at(pos) = i;
                inserido.at(i -> getId()) = true;
                pos++;
            }
        }
        iteracoes++;
        O = OLinha;
        OLinha.clear();
    }
    if(!cicloNeg(g,v,custo))
        printCaminho(anterior,custo,v,g);
    else if(cicloNeg(g,v,custo)){
        std::cout << "C" << std::endl;
    }
}


int main(int argc, char **argv){

    int idVerticie;

    if(argc != 3){
        std::cout << "E" << std::endl;
        exit(1);
    }
    std::string nomeArquivo = argv[1];
    std::string vId = argv[2];
    idVerticie = std::stoi(vId);
    Grafo *g = new Grafo();
    leGrafo(nomeArquivo, g);


    // como esse vetor nao eh um vetor* ele nao precisa de delete explicito
    std::vector<Verticie*> anteriores(g -> getNumVertices()); 
    // e os objetos que estao nele vao ser deletados quando o g++ chamar a funcao de destrutor do grafo

    std::vector<int> distancias(g -> getNumVertices());

    Verticie *v = g -> getVerticie(idVerticie);

    bellmanford(g,v,&anteriores,&distancias);
    
    delete g;
    return 0;
}
