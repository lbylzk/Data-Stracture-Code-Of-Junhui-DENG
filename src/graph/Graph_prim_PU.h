/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2021. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename Tv, typename Te>
struct PrimPU
{ //针对Prim算法的顶点优先级更新器
   virtual void operator()(Graph<Tv, Te> *g, Rank s, Rank w)
   {
      if (UNDISCOVERED == g->status(w)) //对于s每一尚未被发现的邻接顶点w
         if (g->priority(w) > g->weight(s, w))
         {                                    //按Prim策略做松弛
            g->priority(w) = g->weight(s, w); //更新优先级（数）
            g->parent(w) = s;                 //更新父节点
         }
   }
};