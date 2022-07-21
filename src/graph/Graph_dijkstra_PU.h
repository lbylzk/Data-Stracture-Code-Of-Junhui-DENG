/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2021. All rights reserved.
 ******************************************************************************************/

#pragma once

template <typename Tv, typename Te> struct DijkPU { //���Dijkstra�㷨�Ķ������ȼ�������
   virtual void operator() ( Graph<Tv, Te>* g, Rank s, Rank w ) {
      if ( UNDISCOVERED == g->status ( w ) ) //����sÿһ��δ�����ֵ��ڽӶ���w����Dijkstra����
         if ( g->priority ( w ) > g->priority ( s ) + g->weight ( s, w ) ) { //���ɳ�
            g->priority ( w ) = g->priority ( s ) + g->weight ( s, w ); //�������ȼ�������
            g->parent ( w ) = s; //��ͬʱ���¸��ڵ�
         }
   }
};