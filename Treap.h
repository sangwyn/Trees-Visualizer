#ifndef TREESSFML__TREAP_H_
#define TREESSFML__TREAP_H_

#include "TreapNode.h"
#include <SFML/Graphics.hpp>
#include <utility>

class Treap {
 public:
  TreapNode *start;
  int GetMaxDepth(TreapNode *&p);
  std::pair<TreapNode *, TreapNode *> Split(TreapNode *&t,
                                            int lambda);
  TreapNode *Merge(TreapNode *&t1, TreapNode *&t2);
  bool Find(TreapNode *&t, int key);
  void InsertNode(TreapNode *&t, int key);
  void RemoveNode(TreapNode *&t, int key);
  void Draw(sf::RenderWindow &window,
            sf::Font &font,
            sf::Vector2f mouse_pos,
            TreapNode *p,
            TreapNode *parent,
            int depth,
            int max_depth,
            std::vector<sf::Text> &all_text,
            std::vector<sf::CircleShape> &all_sprites);
  Treap();
};

#endif
