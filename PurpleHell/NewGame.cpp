#include "NewGame.h"
#include <fstream>
#include "BinaryIO.h"
#include "Shop.h"
#include "Hero.h"
#include "Item.h"

// Slots vazios seguem a convencao do jogo: um registro com name == "slot".
static void writeHeroRecord(std::ostream& os, const std::string& name, const std::string& job, int hp, int power, int special) {
	bin::writeStr(os, name);
	bin::writeStr(os, job);
	bin::writeInt(os, hp);
	bin::writeInt(os, power);
	bin::writeInt(os, special);
}

static void writeItemRecord(std::ostream& os, const std::string& name, int hp, int power, int type) {
	bin::writeStr(os, name);
	bin::writeInt(os, hp);
	bin::writeInt(os, power);
	bin::writeInt(os, type);
}

void NewGame::resetSaveFiles() {
	// A loja ja gera heros/itens aleatorios no seu construtor (Refresh()),
	// entao reaproveitamos essa mesma logica "como a loja".
	Shop shop;
	Hero* hero = shop.getHero(0);
	Item* item = shop.getItem(0);

	// Info: gold=0, run=1, level=1
	{
		std::ofstream ofs("res/Player/Info.txt", std::ios::binary | std::ios::trunc);
		bin::writeHeader(ofs);
		bin::writeInt(ofs, 0);
		bin::writeInt(ofs, 1);
		bin::writeInt(ofs, 1);
	}

	// Team (3 slots): 1 heroi aleatorio + 2 vazios
	{
		std::ofstream ofs("res/Player/Team.txt", std::ios::binary | std::ios::trunc);
		bin::writeHeader(ofs);
		bin::writeInt(ofs, 3);
		writeHeroRecord(ofs, hero->getName(), hero->GetJob(), hero->getHp(), hero->getPower(), hero->getSpecial());
		writeHeroRecord(ofs, "slot", "slot", 0, 0, 0);
		writeHeroRecord(ofs, "slot", "slot", 0, 0, 0);
	}

	// Units (10 slots): roster vazio
	{
		std::ofstream ofs("res/Player/Units.txt", std::ios::binary | std::ios::trunc);
		bin::writeHeader(ofs);
		bin::writeInt(ofs, 10);
		for (int i = 0; i < 10; i++) writeHeroRecord(ofs, "slot", "slot", 0, 0, 0);
	}

	// Inventory (20 slots): 1 item aleatorio + 19 vazios
	{
		std::ofstream ofs("res/Player/Inventory.txt", std::ios::binary | std::ios::trunc);
		bin::writeHeader(ofs);
		bin::writeInt(ofs, 20);
		writeItemRecord(ofs, item->getName(), item->getHp(), item->getPower(), item->getSpecial());
		for (int i = 0; i < 19; i++) writeItemRecord(ofs, "slot", 0, 0, 0);
	}

	// equiped (6 slots): nada equipado
	{
		std::ofstream ofs("res/Player/equiped.txt", std::ios::binary | std::ios::trunc);
		bin::writeHeader(ofs);
		bin::writeInt(ofs, 6);
		for (int i = 0; i < 6; i++) writeItemRecord(ofs, "slot", 0, 0, 0);
	}
}
