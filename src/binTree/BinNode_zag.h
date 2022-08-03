/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2021. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename T>
BinNodePosi<T> BinNode<T>::zag()
{ //逆时针旋转
   BinNodePosi<T> rChild = rc;
   rChild->parent = this->parent;
   if (rChild->parent)
      ((this == rChild->parent->lc) ? rChild->parent->lc : rChild->parent->rc) = rChild;
   rc = rChild->lc;
   if (rc)
      rc->parent = this;
   rChild->lc = this;
   this->parent = rChild;
   // update heights
   height = 1 + max(stature(lc), stature(rc));
   rChild->height = 1 + max(stature(rChild->lc), stature(rChild->rc));
   for (BinNodePosi<T> x = rChild->parent; x; x = x->parent)
      if (HeightUpdated(*x))
         break;
      else
         x->height = 1 + max(stature(x->lc), stature(x->rc));
   return rChild;
}
