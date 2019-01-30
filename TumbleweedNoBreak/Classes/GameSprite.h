#pragma once
#include "cocos2d.h"
#include "Primitive.h"
namespace Sedna {

	class GameSprite : public cocos2d::Sprite
	{

	public:
		cocos2d::Vec2 getVelocity()const;
		void setVelocity(cocos2d::Vec2 v);
		void updateVelocity(float dt);
		//cocos2d::Vec2 getAccel()const;
		//void setAccel(cocos2d::Vec2);
		//int getMass()const;
		//void setMass(int);

	private:
		cocos2d::Vec2 position;
		cocos2d::Vec2 velocity;
		cocos2d::Vec2 acceleration;
		//int mass;//
	};
	//placeholder class
	class GamePrimitive : public Sedna::SquarePrimitive
	{

	public:
		GamePrimitive(cocos2d::Vec2 START,cocos2d::Vec2 END);
		GamePrimitive(Sedna::SquarePrimitive s);
		cocos2d::Vec2 getVelocity()const;
		void setVelocity(cocos2d::Vec2 v);
		void updateVelocity(float dt);
		//cocos2d::Vec2 getAccel()const;
		//void setAccel(cocos2d::Vec2);
		//int getMass()const;
		//void setMass(int);

	private:
		cocos2d::Vec2 position;
		cocos2d::Vec2 velocity;
		cocos2d::Vec2 acceleration;
		//int mass;//
	};

	class Player : GamePrimitive {

	public:

	private:
	};
}
//	class projectile : public GameSprite
//	{
//	public:
//		enum Team  
//		{
//			enemy,
//			player
//		};
//		Team getTeam()const;
//		void setTeam(const Team);
//	private:
//		Team team;
//		
//	};
//	
//	class Powerup : public GameSprite
//	{
//	public:
//
//		enum Type
//		{
//			Pistol,
//			Shotgun,
//			Minigun,
//			Shield,
//			Speed,
//			Health,
//			Wavey,
//			HighNoon,
//			Slow,
//			SuperDrunk,
//			InvertControls,
//
//		};
//	};
//
//	class Gun : public Powerup
//	{
//	public:
//		void setDamage(const int);
//		int getDamage()const;
//		void setFire(const int);
//		int getFire()const;
//		void setAmmo(const int);
//		int getAmmo()const;
//	private:
//		int damage;
//		int fireRate;
//		int ammo;
//	};
//
//	class Buffs : public Powerup
//	{
//	public:
//
//	private:
//
//	};
//
//	class Player : public GameSprite
//	{
//	public:
//
//
//	private:
//		int health;
//		int points;
//		cocos2d::Vec2 maxVelocity;
//		int maxAlcohol;
//
//
//	};
//
//}