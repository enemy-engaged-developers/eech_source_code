#include "ogre_int.hpp"

void OGREEE_CALL ogre_node_get_position(struct OgreNode* node, struct VEC3D* position)
{
	Ogre::SceneNode* sn = reinterpret_cast<Ogre::SceneNode*>(node);
	const Ogre::Vector3& v = sn->getPosition();
	position->x = v.x;
	position->y = v.y;
	position->z = v.z;
	position->z = -position->z;
}

void OGREEE_CALL ogre_node_set_position(struct OgreNode* node, struct VEC3D* position)
{
	Ogre::SceneNode* sn = reinterpret_cast<Ogre::SceneNode*>(node);
	Ogre::Vector3 v(position->x, position->y, position->z);
	v.z = -v.z;
	sn->setPosition(v);
}

void OGREEE_CALL ogre_node_get_orientation(struct OgreNode* node, matrix3x3 orientation)
{
	Ogre::SceneNode* sn = reinterpret_cast<Ogre::SceneNode*>(node);
	//FIXME
	Ogre::Matrix3 m;
	sn->getOrientation().ToRotationMatrix(m);
	memcpy(orientation, m[0], sizeof(matrix3x3));
}

void OGREEE_CALL ogre_node_set_orientation(struct OgreNode* node, matrix3x3 orientation)
{
	Ogre::SceneNode* sn = reinterpret_cast<Ogre::SceneNode*>(node);
	//FIXME
	sn->setOrientation(Ogre::Matrix3(orientation));
}

void OGREEE_CALL ogre_node_set_visible(struct OgreNode* node, int visible)
{
	Ogre::SceneNode* sn = reinterpret_cast<Ogre::SceneNode*>(node);
	sn->setVisible(visible != 0, true);
}
