#include "Table.h"
namespace Sedna {

	Sedna::Table::Table(float x, float y) {
		this->sprite = cocos2d::Sprite::create("Table.png");
		sprite->setScale(0.9f);
		this->hitBox = new CirclePrimitive(cocos2d::Vec2(x, y), 28, 5, 50);
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
}
