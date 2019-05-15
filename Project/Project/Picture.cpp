#include "Picture.h"

using namespace sf;
using namespace std;

Picture::Picture()
{
}

Picture::Picture(const sf::Texture & _picture)
{
	picture.setTexture(_picture);

}

Picture::Picture(const sf::Texture & _picture, const Vector2f _position, const int & _monsterPictureX, const int & _monsterPictureY, const int & _monsterSize) : Picture(_picture)
{
	picture.setTextureRect(IntRect(_monsterPictureX, _monsterPictureY, _monsterSize, _monsterSize));
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	picture.setPosition(_position);
}

Picture::Picture(const Texture & _picture, const Vector2f _position, const Vector2f _scale) : Picture(_picture)
{
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 2);
	picture.setPosition(_position);
	picture.setScale(_scale);
}

Picture::Picture(const Texture & _picture, const Vector2f _position, const int & _rotation)
{
	picture.setTexture(_picture);
	picture.setOrigin(picture.getGlobalBounds().width / 2, picture.getGlobalBounds().height / 3);
	picture.setPosition(_position);
	picture.setRotation(_rotation);
}

Picture::~Picture()
{
}
