#ifndef __ALADDIN_CORE_QUAD_TREE_H__
#define __ALADDIN_CORE_QUAD_TREE_H__

#include "QuadNode.h"
#include "Logger.h"

NAMESPACE_ALA
{
  ALA_CLASS_HEADER_0(QuadTree)
private:

  // for space partitioning and calculating
  float _spaceMinX;
  float _spaceMinY;
  float _unitWidth;
  float _unitHeight;
  int _level;

  // main tree
  std::map<std::string, QuadNode*> _tree;

  // for index mapping and fast calculating tree index from position (mat index)
  int _matSize;
  std::string** _indexMat;
  std::vector<QuadNode*> _visibleNodes;

  // for debug logging
  Logger _logger;
  std::set<std::string> _oldVisibleIndices;

public:
  QuadTree(const float spaceMinX, const float spaceMinY,
    const float spaceWidth, const float spaceHeight,
    const int level = 3);

  virtual ~QuadTree();

  int getLevel() const;

  void updateVisibility(const float minVisibleX, const float minVisibleY,
    const float maxVisibleX, const float maxVisibleY);

  const std::vector<QuadNode*>& getVisibleNodes() const;

  QuadNode* getNode(const std::string& index) const;

  float getSpaceMinX() const;

  float getSpaceMinY() const;

  float getUnitWidth() const;

  float getUnitHeight() const;

private:
  char toQuadIndex(const int x, const int y) const;
};
}

#endif //!__ALADDIN_CORE_QUAD_TREE_H__
