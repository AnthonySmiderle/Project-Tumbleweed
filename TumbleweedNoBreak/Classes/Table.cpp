#include "Table.h"
#include "Potion.h"
namespace Sedna {

	Sedna::Table::Table(float x, float y) {
		std::string tableImage;
		if (rand() % 8 == 0)
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
		
		this->sprite = cocos2d::Sprite::create(tableImage);
		sprite->setScale(spriteScale);
		this->hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 28, 5, 50);
		hitBox->getDrawNode()->setVisible(false);
		this->objectHp = 5;
	}

	Table::Table(float x, float y, potionType p)
	{
		std::string tableImage;
		if (p=health)
		{
			beer = new Potion(health);
			tableImage = "Table_HealthPot.png";
		}
		else if (p=revive)
		{
			beer = new Potion(revive);
			tableImage = "Table_RFPot.png";
		}
		else if (p=invinc)
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
		sprite->setTexture("TableKnocked.png");
		knocked = true;
	}

	void Table::collideTable(Table* table)
	{

			if (this->getBox()->checkCollision(*table->getBox())) {

			cocos2d::Vec2 distanceVector((table->getBox()->getLocation().x - this->getBox()->getLocation().x),
				(table->getBox()->getLocation().y - this->getBox()->getLocation().y));
			table->spriteSwitch();
			//times 2 to give a better feel to kicking the table
			table->getBox()->addForce(distanceVector.x * 2, distanceVector.y * 2);
			}

			if (table->getBox()->getVelocity() != cocos2d::Vec2(0, 0)) {

					table->getBox()->addForce(
					table->getBox()->getVelocity().x * -1,
					table->getBox()->getVelocity().y * -1);
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
