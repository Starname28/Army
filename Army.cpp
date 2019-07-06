// Army.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

class IWarior
{
public:
	virtual void info() = 0;
	virtual ~IWarior(){}
};

class IBowman
{
public:
	virtual void info() = 0;
	virtual ~IBowman() {}
};

class IHeal
{
public:
	virtual void info() = 0;
	virtual ~IHeal() {}
};

class ICavaler
{
public:
	virtual void info() = 0;
	virtual ~ICavaler() {}
};

class Sword
{
public:
	void Cut()
	{
		std::cout << "----Cut----" << std::endl;
	}
};

class Bow
{
public:
	void Shut()
	{
		std::cout << "----Shut----" << std::endl;
	}
};

class Aye
{
public:
	void Hack()
	{
		std::cout << "----Hack----" << std::endl;
	}
};

class Horse
{
public:
	void Go()
	{
		std::cout << "----GO----" << std::endl;
	}
};

class Vitamine
{
public:
	void Treat()
	{
		std::cout << "----Treat----" << std::endl;
	}
};

class Spear
{
public:
	void Beat()
	{
		std::cout << "----Beat----" << std::endl;
	}
};

class Warior : public IWarior
{
	Sword sword;
public:
	virtual void info() override
	{
		sword.Cut();
	}
	virtual ~Warior() {}
};

class Bowman : public IBowman
{
	Bow bow;
public:
	virtual void info() override
	{
		bow.Shut();
	}
	virtual ~Bowman() {}
};

class Heal : public IHeal
{
	Aye aye;
	Vitamine vitamine;
public:
	virtual void info() override
	{
		aye.Hack();
		vitamine.Treat();
	}
	virtual ~Heal() {}
};

class Cavaler : public ICavaler
{
	Horse horse;
	Spear spear;
public:
	virtual void info() override
	{
		horse.Go();
		spear.Beat();
	}
	virtual ~Cavaler() {}
};

class Legolas : virtual public Heal, virtual public Bowman
{
public:
	virtual void info() override
	{
		Heal::info();
		Bowman::info();
	}
	virtual ~Legolas(){}
};

class Aragorn : virtual public Warior, virtual public Bowman, virtual public Cavaler
{
public:
	virtual void info() override
	{
		Warior::info();
		Bowman::info();
		Cavaler::info();
	}
	virtual ~Aragorn(){}
};

class Gendolf : virtual public Heal, virtual public Cavaler
{
public:
	virtual void info() override
	{
		Heal::info();
		Cavaler::info();
	}
	virtual ~Gendolf(){}
};

class enemyLegolas : virtual public Heal, virtual public Bowman
{
public:
	virtual void info() override
	{
		Heal::info();
		Bowman::info();
	}
	virtual ~enemyLegolas() {}
};

class enemyAragorn : virtual public Warior, virtual public Bowman, virtual public Cavaler
{
public:
	virtual void info() override
	{
		Warior::info();
		Bowman::info();
		Cavaler::info();
	}
	virtual ~enemyAragorn() {}
};

class enemyGendolf : virtual public Heal, virtual public Cavaler
{
public:
	virtual void info() override
	{
		Heal::info();
		Cavaler::info();
	}
	virtual ~enemyGendolf() {}
};

class ArmyFactory
{
public:
	virtual Warior* createWarior() = 0;
	virtual Bowman* createBowman() = 0;
	virtual Cavaler* createCavaler() = 0;
	virtual Heal* createHeal() = 0;
	virtual ~ArmyFactory() {}
};

class ALightArmyFactory : public ArmyFactory
{
public:
	Warior* createWarior() override
	{
		return new Aragorn;
	}

	Bowman* createBowman() override
	{
		return new Legolas;
	}

	Cavaler* createCavaler() override
	{
		return new Gendolf;
	}

	Heal* createHeal() override
	{
		return new Gendolf;
	}
};

class ADarknesstArmyFactory : public ArmyFactory
{
public:
	Warior* createWarior() override
	{
		return new enemyAragorn;
	}

	Bowman* createBowman() override
	{
		return new enemyLegolas;
	}

	Cavaler* createCavaler() override
	{
		return new enemyGendolf;
	}

	Heal* createHeal() override
	{
		return new enemyGendolf;
	}
};

class Army
{
public:
	~Army()
	{
		int i;
		for (i = 0; i<m_w.size(); ++i)  delete m_w[i];
		for (i = 0; i<m_b.size(); ++i)  delete m_b[i];
		for (i = 0; i<m_h.size(); ++i)  delete m_h[i];
		for (i = 0; i<m_c.size(); ++i)  delete m_c[i];
	}

	void info() 
	{
		int i;
		for (i = 0; i<m_w.size(); ++i)  m_w[i]->info();
		for (i = 0; i<m_b.size(); ++i)  m_b[i]->info();
		for (i = 0; i<m_h.size(); ++i)  m_h[i]->info();
		for (i = 0; i<m_c.size(); ++i)  m_c[i]->info();
	}

	std::vector<Warior*> m_w;
	std::vector<Bowman*> m_b;
	std::vector<Heal*> m_h;
	std::vector<Cavaler*> m_c;
};

class Game
{
public:
	Army* createArmy(ArmyFactory& factory)
	{
		Army *army = new Army;
		army->m_w.push_back(factory.createWarior());
		army->m_b.push_back(factory.createBowman());
		army->m_c.push_back(factory.createCavaler());
		army->m_h.push_back(factory.createHeal());
		return army;
	}
};

int main()
{
	Game game;
	ALightArmyFactory al_factory;
	ADarknesstArmyFactory ad_factory;

	Army* al = game.createArmy(al_factory);
	Army* ad = game.createArmy(ad_factory);
	std::cout << "Army Light: " << std::endl;
	al->info();
	std::cout << "\nArmy Darkness: " << std::endl;
	ad->info();
	system("pause");
    return 0;
}

