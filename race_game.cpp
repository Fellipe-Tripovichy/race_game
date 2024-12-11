#include <iostream>
#include <thread>
#include <semaphore.h>
#include <chrono>
#include <random>
#include <mutex>

// Define semáforos
std::binary_semaphore startLine(0);  // Semáforo para iniciar o jogo
std::binary_semaphore finishLine(0); // Semáforo para terminar o jogo
bool gameOver = false;               // Flag para verificar se o jogo acabou
int winnerID = 0;                    // Armazena o ID do jogador vencedor
bool secondPlace = false;
std::mutex logMutex;

// Simula a tarefa do jogador de correr
void player(int id) {
    // Aguarda até que os jogadores estejam prontos para começar
    {
        std::lock_guard<std::mutex> lock(logMutex);
        std::cout << "Player " << id << " esta se preparando...\n";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simula o tempo de preparação
    
    // Aguarda o sinal para iniciar a corrida
    startLine.acquire();
    
    // Simula o tempo de corrida (aleatório para cada jogador)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(3, 6); // Tempo de corrida aleatório entre 3 a 6 segundos

    std::cout << "Player " << id << " comecou a correr...\n";
    std::this_thread::sleep_for(std::chrono::seconds(dis(gen)));

    // Verifica se o jogo acabou (ou seja, se um jogador já terminou)
    if (!gameOver) {
        gameOver = true;  // Marca o fim do jogo
        std::cout << "Player " << id << " chegou a linha de chegada!\n";
        winnerID = id;    // Armazena o ID do jogador vencedor
        finishLine.release();  // Libera o semáforo da linha de chegada para que os outros jogadores possam terminar
    } else {
        // Se o jogo acabou, os jogadores estão aguardando pelo vencedor
        if (!secondPlace) {
            std::cout << "Player " << id << " esta esperando...\n";
            finishLine.release(); // Libera o semáforo para o próximo jogador
        } else {
            std::cout << "Player " << id << " esta esperando...\n";
            finishLine.acquire();  // Espera o semáforo da linha de chegada ser liberado (somente pelo vencedor)
        }
    }
}

// Função principal para iniciar o jogo
int main() {

    std::cout << "Bem-vindo ao jogo de corrida!\n";
    int numPlayers = 0;
    std::cout << "Digite o numero de jogadores (maximo 10): ";
    std::cin >> numPlayers;

    if (numPlayers < 1 || numPlayers > 10) {
        std::cout << "Numero de jogadores invalido. Por favor, insira um número entre 1 e 10." << std::endl;
        return 1;
    }

    // Cria múltiplas threads para os jogadores (ajuste o número de jogadores aqui)
    std::vector<std::thread> players;
    for (int i = 1; i <= numPlayers; ++i) {
        players.push_back(std::thread(player, i));
    }

    // Inicia o jogo quando todos os jogadores estiverem prontos
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Garante que todos os jogadores estejam prontos
    std::cout << "Pronto... Ja... Vai!\n";
    startLine.release(numPlayers); // Libera o semáforo para iniciar o jogo para todos os jogadores
    
    // Junta as threads (aguarda elas terminarem)
    for (auto& t : players) {
        t.join();
    }

    // Anuncia o vencedor (o primeiro jogador a terminar)
    if (gameOver) {
        std::cout << "Fim de Jogo! O jogador " << winnerID << " e o vencedor!\n";
    }

    return 0;
}
