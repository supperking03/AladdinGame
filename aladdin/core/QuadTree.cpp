#include "QuadTree.h"

NAMESPACE_ALA
{
  ALA_CLASS_SOURCE_0(ala::QuadTree)

  QuadTree::QuadTree(const float spaceMinX, const float spaceMinY,
    const float spaceWidth, const float spaceHeight,
    const int level)
  : _spaceMinX(spaceMinX), _spaceMinY(spaceMinY),
  _level(level), _logger("QuadTree") {
  ALA_ASSERT(level >= 1 && level <= 5);
  _matSize = static_cast<int>(powf(2, static_cast<float>(level)));
  _unitWidth = spaceWidth / _matSize;
  _unitHeight = spaceHeight / _matSize;

  // build tree
  std::queue<std::string> treeQueue;
  treeQueue.push("0");
  treeQueue.push("1");
  treeQueue.push("2");
  treeQueue.push("3");
  while (!treeQueue.empty()) {
    const auto index = treeQueue.front();
    treeQueue.pop();

    _tree.emplace(index, new QuadNode());

    const auto nodeLevel = static_cast<int>(index.length());
    if (nodeLevel < level) {
      treeQueue.push(index + "0");
      treeQueue.push(index + "1");
      treeQueue.push(index + "2");
      treeQueue.push(index + "3");
    }
  }

  // build index mat
  _indexMat = new std::string*[_matSize];
  for (auto r = 0; r < _matSize; ++r) {
    _indexMat[r] = new std::string[_matSize];
  }

  const auto levelSizeT = static_cast<size_t>(_level);
  for (auto r = 0; r < _matSize; ++r) {
    for (auto c = 0; c < _matSize; ++c) {
      auto unitSize = _matSize / 2;
      auto x = c;
      auto y = r;

      std::string index;
      while (index.length() < levelSizeT) {
        index.push_back(toQuadIndex(x / unitSize, y / unitSize));
        x %= unitSize;
        y %= unitSize;
        unitSize /= 2;
      }

      _indexMat[r][c] = index;
    }
  }
}

QuadTree::~QuadTree() {
  for (const auto it : _tree) {
    delete it.second;
  }

  for (int r = 0; r < _matSize; ++r)
    delete[] _indexMat[r];
  delete[] _indexMat;
}

int QuadTree::getLevel() const {
  return _level;
}

void QuadTree::updateVisibility(const float minVisibleX, const float minVisibleY,
  const float maxVisibleX, const float maxVisibleY) {
  _visibleNodes.clear();

  const auto tminVisibleX = minVisibleX - _spaceMinX;
  const auto tmaxVisibleX = maxVisibleX - _spaceMinX;
  const auto tminVisibleY = minVisibleY - _spaceMinY;
  const auto tmaxVisibleY = maxVisibleY - _spaceMinY;

  const auto left = MAX(0, MIN(_matSize - 1, static_cast<int>(truncf(tminVisibleX / _unitWidth))));
  const auto right = MAX(0, MIN(_matSize - 1, static_cast<int>(truncf(tmaxVisibleX / _unitWidth))));
  const auto bottom = MAX(0, MIN(_matSize - 1, static_cast<int>(truncf(tminVisibleY / _unitHeight))));
  const auto top = MAX(0, MIN(_matSize - 1, static_cast<int>(truncf(tmaxVisibleY / _unitHeight))));

  std::set<std::string> visibleIndices;

  // find visible nodes
  const auto levelSizeT = static_cast<size_t>(_level);

  for (auto r = bottom; r <= top; ++r) {
    for (auto c = left; c <= right; ++c) {
      const auto& index = _indexMat[r][c];
      for (size_t s = 1; s <= levelSizeT; ++s) {
        visibleIndices.emplace(index.substr(0, s));
      }
    }
  }

  /* debug
  if ( visibleIndices == _oldVisibleIndices ) {}
  else {
  std::stringstream stringBuilder;
  for ( const auto& index : visibleIndices ) stringBuilder << index << ' ';
  _logger.debug( "Visibility changed: %s", stringBuilder.str().c_str() );
  _oldVisibleIndices = visibleIndices;
  }
  */

  for (const auto& id : visibleIndices) _visibleNodes.push_back(_tree[id]);
}

const std::vector<QuadNode*>& QuadTree::getVisibleNodes() const {
  return _visibleNodes;
}

QuadNode* QuadTree::getNode(const std::string& index) const {
  return _tree.at(index);
}

float QuadTree::getSpaceMinX() const {
  return _spaceMinX;
}

float QuadTree::getSpaceMinY() const {
  return _spaceMinY;
}

float QuadTree::getUnitWidth() const {
  return _unitWidth;
}

float QuadTree::getUnitHeight() const {
  return _unitHeight;
}

char QuadTree::toQuadIndex(const int x, const int y) const {
  if (x == 0) {
    if (y == 0) return '0';
    return '2';
  }
  if (y == 0) return '1';
  return '3';
}
}
