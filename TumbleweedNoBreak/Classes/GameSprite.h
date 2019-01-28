#pragma once
#include "cocos2d.h"
namespace SednaSprites {

	class GameSprite : public cocos2d::Sprite
	{

	public:
		cocos2d::Vec2 getVelocity()const;
		void setVelocity(cocos2d::Vec2);
		cocos2d::Vec2 getAccel()const;
		void setAccel(cocos2d::Vec2);
		int getMass()const;
		void setMass(int);

	private:
		cocos2d::Vec2 velocity;
		cocos2d::Vec2 acceleration;
		int mass;
	};

	class projectile : public GameSprite
	{
	public:
		enum Team
		{
			enemy,
			player
		};
		Team getTeam()const;
		void setTeam(const Team);
	private:
		Team team;
		
	};
	
	class Powerup : public GameSprite
	{
	public:

	private:
		enum Type
		{
			Pistol,
			Shotgun,
			Minigun,
			Shield,
			Speed,
			Health,
			Wavey,
			HighNoon,
			Slow,
			SuperDrunk,
			InvertControls,

		};
	};

	class Gun : public Powerup
	{
	public:
		void setDamage(const int);
		int getDamage()const;
		void setFire(const int);
		int getFire()const;
		void setAmmo(const int);
		int getAmmo()const;
	private:
		int damage;
		int fireRate;
		int ammo;
	};

	class Buffs : public Powerup
	{
	public:

	private:

	};

	class Player : public GameSprite
	{
	public:


	private:
		int health;
		int points;
		cocos2d::Vec2 maxVelocity;
		int maxAlcohol;


	};

}