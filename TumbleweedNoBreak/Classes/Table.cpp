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

	void Table::collideTable(std::vector<Table*>& tableList)
	{
		for (int i = 0; i < tableList.size(); i++) {
			cocos2d::Vec2 distanceVector((tableList[i]->getBox()->getLocation().x - this->getBox()->getLocation().x),
				(tableList[i]->getBox()->getLocation().y - this->getBox()->getLocation().y));
			tableList[i]->spriteSwitch();
			//times 2 to give a better feel to kicking the table
			tableList[i]->getBox()->addForce(distanceVector.x * 2, distanceVector.y * 2);

			if (tableList[i]->getBox()->getVelocity() != cocos2d::Vec2(0, 0)) {

				tableList[i]->getBox()->addForce(
					tableList[i]->getBox()->getVelocity().x * -1,
					tableList[i]->getBox()->getVelocity().y * -1);
			}
		}

	}
}
