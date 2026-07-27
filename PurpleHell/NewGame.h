#ifndef NEWGAME_H
#define NEWGAME_H

// Reseta os arquivos de save (res/Player/*.txt) para o estado inicial de um
// jogo novo: 1 personagem aleatorio, 0 de gold e 1 item aleatorio (stats
// gerados como na loja). Chamado ao iniciar um "New Game".
namespace NewGame {
	void resetSaveFiles();
}

#endif // !NEWGAME_H
