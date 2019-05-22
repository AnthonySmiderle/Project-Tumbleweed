#include "Table.h"
#include "Potion.h"
namespace Sedna {

	Sedna::Table::Table(float x, float y) {
		std::string tableImage;//creating a randomized table
		if (rand() % 8 == 0)//chance of different types of beers
		{
			beer = new Potion(health);
			tableImage = "Table_HealthPot.png";
		}
		else if (rand() % 20 == 0)
		{
			beer = new Potion(revive);
			tableImage = "Table_RFPot.png";
		}
		else if (rand() % 20 == 0)
		{
			beer = new Potion(invinc);
			tableImage = "Table_invPot.png";
		}
		else
		{
			beer = new Potion(blank);
			tableImage = "Table.png";
		}
		
		this->sprite = cocos2d::Sprite::create(tableImage);//creating the image
		sprite->setScale(spriteScale);//scaling
		this->hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 28, 5, 50);//creating a hitbox
		hitBox->getDrawNode()->setVisible(false);//hide the hitbox
		this->objectHp = 5;//give the object health
	}

	Table::Table(float x, float y, int p)//constructor for a table with a specified beer type otherwise the same as the previous constructor
	{
		std::string tableImage;
		if (p==health)
		{
			beer = new Potion(health);
			tableImage = "Table_HealthPot.png";
		}
		else if (p==revive)
		{
			beer = new Potion(revive);
			tableImage = "Table_RFPot.png";
		}
		else if (p==invinc)
		{
			beer = new Potion(invinc);
			tableImage = "Table_invPot.png";
		}
		else
		{
			beer = new Potion(blank);
			tableImage = "Table.png";
		}
		this->sprite = cocos2d::Sprite::create(tableImage);
		sprite->setScale(spriteScale);
		this->hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 28, 5, 50);
		hitBox->getDrawNode()->setVisible(false);
		this->objectHp = 5;
	}
	
	void Sedna::Table::spriteSwitch()
	{
		sprite->setTexture("TableKnocked.png");//this shows that the table has been kicked over
		knocked = true;
	}

	void Table::collideTable(Table* table)//this allows for tables to act like a Newtons cradle
	{

			if (this->getBox()->checkCollision(*table->getBox())) {//if they are colliding

				cocos2d::Vec2 distanceVector((table->getBox()->getLocation().x - this->getBox()->getLocation().x),
					(table->getBox()->getLocation().y - this->getBox()->getLocation().y));
				table->spriteSwitch();
			//times 2 to give a better feel to kicking the table
				table->getBox()->addForce(distanceVector.x * 2, distanceVector.y * 2,dt);
			}

			if (table->getBox()->getVelocity() != cocos2d::Vec2(0, 0)) {

					table->getBox()->addForce(
					table->getBox()->getVelocity().x * -1,
					table->getBox()->getVelocity().y * -1,dt);
			}

	}
	potionType Table::getBeer()
	{
		return beer->getType();
	}
	void Table::setBeer(potionType a)
	{
		beer->setType(a);
	}
}
