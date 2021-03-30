#include <Transcritor.hpp>

Transcritor::Transcritor()
{
    this->tamColunas = 0;
}

Transcritor::~Transcritor()
{
    delete[] colunas;
    delete[] chaves;
    delete[] posicoes;
}

void Transcritor::transcrever()
{
    string nomeArquivo;
    Coluna modelo;
    int dados[6];

    do
    {
        cout << "Qual o nome do arquivo a ser lido?" << endl;
        cin >> nomeArquivo;
        bancoDados.open(nomeArquivo);
        if (bancoDados.is_open())
        {
            break;
        }
        else
        {
            cout << "### Erro ao abrir o arquivo, confira o nome correto. ###" << endl;
        }
    } while (true);

    checarNumeroColunas();

    colunas = new Coluna[tamColunas];
    chaves = new string[tamColunas];
    posicoes = new int[tamColunas];

    bancoDados.ignore(256, '\n');

    for (int i = 0; i < tamColunas; i++)
    {
        getline(bancoDados, modelo.codigo, ';');
        getline(bancoDados, modelo.regiao, ';');
        getline(bancoDados, modelo.UF, ';');
        getline(bancoDados, modelo.data, ';');

        lerDados(dados);
        modelo.setDados(dados);

        chaves[i] = modelo.codigo;
        posicoes[i] = i;
        colunas[i] = modelo;
    }

    bancoDados.close();

    //TODO Sort
}

void Transcritor::lerDados(int dados[])
{
    string aux;

    for (int i = 0; i < 5; i++)
    {
        getline(bancoDados, aux, ';');
        dados[i] = stoi(aux);
    }

    getline(bancoDados, aux);
    dados[5] = stoi(aux);
}

void Transcritor::checarNumeroColunas()
{
    bancoDados.ignore(256, '\n');

    while (bancoDados.good())
    {
        bancoDados.ignore(256, '\n');
        tamColunas++;
    }

    bancoDados.clear();
    bancoDados.seekg(0);
}