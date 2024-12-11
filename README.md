<h1>SSC0140 – SISTEMAS OPERACIONAIS I</h1>

<h2>Alunos</h2>
Fellipe Tripovichy - 9850332 <br>
Luan Benson Ribeiro - 13672085 <br>
Gustavo de Araújo Poffo - 13672849 <br>

<br>
<h2>Descrição do Jogo</h2>

É um jogo de simulação de corrida onde múltiplos jogadores competem para ser o primeiro a chegar à linha de chegada. Os jogadores são representados por threads, e a sincronização do jogo é gerida utilizando semáforos. O primeiro jogador a alcançar a linha de chegada é declarado o vencedor, e os outros jogadores aguardam sua vez para completar a corrida.
<h3>Como o jogo funciona:</h3>
1. Preparação dos Jogadores: O jogo começa com a preparação de todos os jogadores, que aguardam o sinal para iniciar a corrida. Cada jogador tem seu tempo de corrida aleatório, representando um comportamento dinâmico durante a simulação.

2. Início da Corrida: Após todos os jogadores estarem prontos, o semáforo startLine é liberado para todos ao mesmo tempo, sinalizando o início da corrida.

3. Execução da Corrida: Cada jogador começa sua corrida, simulada por um tempo aleatório. Assim que o primeiro jogador chega à linha de chegada, ele marca o fim do jogo, e o jogador é declarado o vencedor.

4. Espera dos Jogadores Restantes: Os jogadores restantes, após o fim do jogo, ficam aguardando a liberação da linha de chegada, o que ocorre apenas quando o vencedor já tiver completado a corrida.

5. Finalização: Após todos os jogadores terem concluído a corrida, o vencedor é anunciado, e o jogo termina.

<h3>Como rodar o jogo:</h3>
1. Compilação: O código está escrito em C++. Para compilar e executar, você pode usar um compilador C++ como o g++:

`g++ -std=c++20 -o race_game race_game.cpp -pthread`

2. Execução: Após a compilação, basta executar o programa com o seguinte comando:

`./corrida`

<h3>Uso de Semáforos no Jogo:</h3>
Os semáforos são usados para controlar a sincronização entre as threads (jogadores) e coordenar as ações do jogo.

1. Semáforo startLine:
    - Objetivo: Controla o início da corrida.
    - Como funciona: Todos os jogadores aguardam até que o semáforo startLine seja liberado. Quando ele é liberado, todos os jogadores começam a correr ao mesmo tempo.
    - Razão: Sem o semáforo, os jogadores poderiam começar a corrida em momentos diferentes, o que comprometeria a equidade do jogo.

2. Semáforo finishLine:
    - Objetivo: Controla a chegada à linha de chegada.
    - Como funciona: Quando o primeiro jogador chega à linha de chegada, ele libera o semáforo finishLine, permitindo que os outros jogadores possam finalizar a corrida. Os jogadores restantes aguardam sua vez de liberar o semáforo ou, dependendo do estado do jogo, esperam até que o vencedor tenha terminado sua corrida.
    - Razão: O semáforo finishLine garante que o jogo siga a lógica de "um vencedor por vez". Isso impede que múltiplos jogadores sejam declarados vencedores, mesmo que já tenha havido um vencedor.
  
<h3>Uso de Threads no Jogo:</h3>
As threads são usadas para representar os jogadores do jogo, onde cada jogador é executado como uma thread separada.

1. Representação dos Jogadores:
   - Cada jogador é representado por uma thread. O número de threads é definido de acordo com o número de jogadores que o usuário escolher ao iniciar o jogo (máximo de 10).
   - A função player é executada em uma thread para cada jogador, permitindo que todos joguem simultaneamente, mas com a lógica de sincronização dos semáforos controlando a execução de suas ações.

2. Simulação da Corrida:
   - Cada thread (jogador) simula seu tempo de corrida de forma independente, mas de acordo com a sincronização dos semáforos.
   - O uso de threads permite que o jogo seja executado de forma mais realista e interativa, com múltiplos jogadores competindo em paralelo, sem que uma ação dependa da outra diretamente.


<br>
<h2>Conclusão</h2>
Esse código é um exemplo de como as threads e semáforos podem ser usados para implementar um jogo simples de corrida, permitindo a simulação de múltiplos jogadores competindo simultaneamente, mas de maneira controlada e sincronizada. O uso dos semáforos garante que a execução seja coordenada entre os jogadores e evita que o jogo tenha múltiplos vencedores.
