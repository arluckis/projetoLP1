#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Astronauta {
public:
    string cpf;
    int idade;
    string nome;
    bool disponivel;
    bool morto;

    Astronauta(string cpfUnico, int idadeUnico, string nomeUnico) : cpf(cpfUnico), idade(idadeUnico), nome(nomeUnico), disponivel(true), morto(false) {}

    void imprimir() const {
        cout << "CPF: " << cpf << ", Nome: " << nome << ", Idade: " << idade << endl;
    }

    static vector<Astronauta> astronautas;

    static void CadastrarAstronauta(const string& cpf, int idade, string nome) {
        astronautas.push_back(Astronauta(cpf, idade, nome));
        cout << "Astronauta cadastrado com sucesso! Segue os dados cadastrados: " << endl;
        cout << "CPF: " << cpf << ", Nome: " << nome << ", Idade: " << idade << endl;
    }

    static void imprimirAstronautasMortos() {
        cout << "Lista de Astronautas Mortos:" << endl;
        for (const auto& astronauta : astronautas) {
            if (astronauta.morto) {
                astronauta.imprimir();
            }
        }
    }

    static Astronauta* buscarAstronautaPorCPF(const string& cpf) {
        for (auto& astronauta : astronautas) {
            if (astronauta.cpf == cpf) {
                return &astronauta;
            }
        }
        return nullptr;
    }
};

vector<Astronauta> Astronauta::astronautas;

class Voo {
public:
    int codigoVoo;
    string statusVoo;
    vector<Astronauta*> passageiros;

    Voo(int codigo) : codigoVoo(codigo), statusVoo("Planejado") {}

    static vector<Voo> voos;

    static void CadastrarVoo() {
        static int codigo = 1;
        voos.push_back(Voo(codigo));
        cout << "Voo criado, codigo do voo: " << codigo << endl;
        codigo++;
    }

    void adicionarAstronauta(Astronauta* astronauta) {
        if (statusVoo == "Planejado" && astronauta->disponivel) {
            passageiros.push_back(astronauta);
            astronauta->disponivel = false;
            cout << "Astronauta adicionado no voo com sucesso!" << endl;
        } else {
            cout << "Nao e possível adicionar o astronauta ao voo. O voo nao esta em planejamento ou o astronauta nao esta disponível." << endl;
        }
    }

    void removerAstronauta(const string& cpf) {
        if (statusVoo == "Planejado") {
            for (auto it = passageiros.begin(); it != passageiros.end(); ++it) {
                if ((*it)->cpf == cpf) {
                    (*it)->disponivel = true;
                    passageiros.erase(it);
                    return;
                }
            }
            cout << "Voo planejado." << endl;
        } else {
            cout << "Nao e possivel remover o astronauta do voo. O voo nao esta em planejamento." << endl;
        }
    }

    void lancar() {
        if (statusVoo == "Planejado" && !passageiros.empty()) {
            statusVoo = "Em curso";
            for (auto& astronauta : passageiros) {
                astronauta->disponivel = false;
            }
            cout << "Voo lançado!" << endl;
        } else {
            cout << "Nao foi possivel lancar o voo. Verifique se ele foi criado e se ha astronautas nele." << endl;
        }
    }

    void explodir() {
        if (statusVoo == "Em curso") {
            statusVoo = "Explodido";
            for (auto& astronauta : passageiros) {
                astronauta->morto = true;
            }
        } else {
            cout << "Para explodir o voo e necessario que ele esteja em curso." << endl;
        }
    }

    void finalizar() {
        if (statusVoo == "Em curso") {
            statusVoo = "Finalizado";
            for (auto& astronauta : passageiros) {
                astronauta->disponivel = true;
            }
            cout << "Voo finalizado com sucesso." << endl;
        } else {
            cout << "Para finalizar o voo e necessario que ele esteja em curso." << endl;
        }
    }

    void imprimir() const {
        cout << "Codigo do Voo: " << codigoVoo << ", Status: " << statusVoo << endl;
        cout << "Passageiros:" << endl;
        for (const auto& astronauta : passageiros) {
            astronauta->imprimir();
        }
    }

    static void listarVoos() {
        cout << "Lista de Voos:" << endl;
        for (const auto& voo : voos) {
            voo.imprimir();
        }
    }
};

vector<Voo> Voo::voos;

bool executarOpcao(int opcao) {
    if (opcao == 1) {
        string cpf;
        int idade;
        string nome;
        cout << "Digite o CPF do Astronauta:" << endl;
        cin >> cpf;
        if (cpf.length() == 11){
            cout << "Digite a idade do Astronauta:" << endl;
            cin >> idade;
            cin.ignore();
            cout << "Digite o nome do Astronauta:" << endl;
            getline(cin, nome);
            Astronauta::CadastrarAstronauta(cpf, idade, nome);
        }
        else {
            cout << "CPF informado nao e valido pois nao possui 11 digitos." << endl;
            
        }
    }
    if (opcao == 2) {
        Voo::CadastrarVoo();
    }
    if (opcao == 3) {
        int codigo;
        string cpf;
        cout << "Digite o codigo do voo:" << endl;
        cin >> codigo;
        cout << "Digite o CPF do Astronauta:" << endl;
        cin >> cpf;
        Astronauta* astronauta = Astronauta::buscarAstronautaPorCPF(cpf);
        if (astronauta) {
            for (auto& voo : Voo::voos) {
                if (voo.codigoVoo == codigo) {
                    voo.adicionarAstronauta(astronauta);
                }
            }
        } else {
            cout << "Astronauta nao encontrado." << endl;
        }
    }
    if (opcao == 4) {
        int codigo;
        string cpf;
        cout << "Digite o codigo do voo:" << endl;
        cin >> codigo;
        cout << "Digite o CPF do Astronauta:" << endl;
        cin >> cpf;
        for (auto& voo : Voo::voos) {
            if (voo.codigoVoo == codigo) {
                voo.removerAstronauta(cpf);
            }
        }
    }
    if (opcao == 5) {
        int codigo;
        cout << "Digite o codigo do voo para lancar:" << endl;
        cin >> codigo;
        for (auto& voo : Voo::voos) {
            if (voo.codigoVoo == codigo) {
                voo.lancar();
            }
        }
    }
    if (opcao == 6) {
        int codigo;
        cout << "Digite o codigo do voo para explodir:" << endl;
        cin >> codigo;
        for (auto& voo : Voo::voos) {
            if (voo.codigoVoo == codigo) {
                voo.explodir();
                cout << "Voo explodido!" << endl;
            }
        }
    }
    if (opcao == 7) {
        int codigo;
        cout << "Digite o codigo do voo para finalizar:" << endl;
        cin >> codigo;
        for (auto& voo : Voo::voos) {
            if (voo.codigoVoo == codigo) {
                voo.finalizar();
            }
        }
    }
    if (opcao == 8) {
        Voo::listarVoos();
    }
    if (opcao == 9) {
        Astronauta::imprimirAstronautasMortos();
    }
    if (opcao == 10) {
        cout << "Obrigado por utilizar nosso painel. Ate a proxima!" << endl;
        exit(0);
    }

        cout << "Deseja fazer mais alguma operacao?" << endl;
        cout << "Opcoes:" << endl;
        cout << "1 - Sim. Voltar ao Menu Principal." << endl;
        cout << "2 - Sair." << endl;
        cout << "Digite apenas o numero da opcao." << endl;
        int opcaoPainel;
        cin >> opcaoPainel;
        if (opcaoPainel == 1){
            return true;
        }
        else {
            executarOpcao(10);
        }
}

    
void menu() {
    bool loopMenu = true;
    while (loopMenu) {
        cout << "Painel Voos e Astronautas, Opcoes:" << endl;
        cout << "1 - Cadastrar Astronauta." << endl;
        cout << "2 - Cadastrar Voo" << endl;
        cout << "3 - Adicionar Astronauta em Voo" << endl;
        cout << "4 - Remover Astronauta de um Voo" << endl;
        cout << "5 - Lancar Voo" << endl;
        cout << "6 - Explodir Voo" << endl;
        cout << "7 - Finalizar Voo" << endl;
        cout << "8 - Listar todos os Voos" << endl;
        cout << "9 - Listar todos os astronautas mortos" << endl;
        cout << "10 - Sair" << endl;
        cout << "Digite apenas o numero da opcao." << endl;

        int opcao;
        cin >> opcao;
        loopMenu = executarOpcao(opcao);
    }
}

int main() {
    menu();
    return 0;
}
