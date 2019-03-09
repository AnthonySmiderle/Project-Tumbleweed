#include "Table.h"
#include "Potion.h"
namespace Sedna {

	Sedna::Table::Table(float x, float y) {
		std::string tableImage;
		int tempInt = rand() % 10;
		if (tempInt == 1)
		{
			beer = new Potion(health);
			tableImage = "Table_HealthPot.png";
		}
		else if (tempInt == 2)
		{
			beer = new Potion(rapid);
			tableImage = "Table_RFPot.png";
		}
		else if (tempInt == 0)
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
		sprite->setScale(0.9f);
		this->hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 31, 5, 50);
		hitBox->getDrawNode()->setVisible(false);
		this->objectHp = 5;
	}
	void Sedna::Table::spriteSwitch()
	{
		sprite->setTexture("TableKnocked.png");
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
