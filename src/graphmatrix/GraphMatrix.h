/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2021. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "Vector/Vector.h" //��������
#include "Graph/Graph.h" //����ͼADT

template <typename Tv> struct Vertex { //�������Ϊ���������δ�ϸ��װ��
   Tv data; int inDegree, outDegree; VStatus status; //���ݡ����������״̬
   int dTime, fTime; //ʱ���ǩ
   Rank parent; int priority; //�ڱ������еĸ��ڵ㡢���ȼ���
   Vertex ( Tv const& d = ( Tv ) 0 ) : //�����¶���
      data ( d ), inDegree ( 0 ), outDegree ( 0 ), status ( UNDISCOVERED ),
      dTime ( -1 ), fTime ( -1 ), parent ( -1 ), priority ( INT_MAX ) {} //�ݲ�����Ȩ�����
};

template <typename Te> struct Edge { //�߶���Ϊ���������δ�ϸ��װ��
   Te data; int weight; EType type; //���ݡ�Ȩ�ء�����
   Edge ( Te const& d, int w ) : data ( d ), weight ( w ), type ( UNDETERMINED ) {} //����
};

template <typename Tv, typename Te> //�������͡�������
class GraphMatrix : public Graph<Tv, Te> { //�������������ڽӾ�����ʽʵ�ֵ�ͼ
private:
   Vector< Vertex< Tv > > V; //���㼯��������
   Vector< Vector< Edge< Te > * > > E; //�߼����ڽӾ���
public:
   GraphMatrix() { n = e = 0; } //����
   ~GraphMatrix() { //����
      for ( Rank j = 0; j < n; j++ ) //���ж�̬������
         for ( Rank k = 0; k < n; k++ ) //�߼�¼
            delete E[j][k]; //�������
   }
// ����Ļ�����������ѯ��i�����㣨0 <= i < n��
   virtual Tv& vertex ( Rank i ) { return V[i].data; } //����
   virtual int inDegree ( Rank i ) { return V[i].inDegree; } //���
   virtual int outDegree ( Rank i ) { return V[i].outDegree; } //����
   virtual Rank firstNbr ( Rank i ) { return nextNbr ( i, n ); } //�׸��ڽӶ���
   virtual Rank nextNbr ( Rank i, Rank j ) //����ڶ���j����һ�ڽӶ��㣨�����ڽӱ�����Ч�ʣ�
   { while ( ( -1 < j ) && ( !exists ( i, --j ) ) ); return j; } //����������̽
   virtual VStatus& status ( Rank i ) { return V[i].status; } //״̬
   virtual int& dTime ( Rank i ) { return V[i].dTime; } //ʱ���ǩdTime
   virtual int& fTime ( Rank i ) { return V[i].fTime; } //ʱ���ǩfTime
   virtual Rank& parent ( Rank i ) { return V[i].parent; } //�ڱ������еĸ���
   virtual int& priority ( Rank i ) { return V[i].priority; } //�ڱ������е����ȼ���
// ����Ķ�̬����
   virtual Rank insert ( Tv const& vertex ) { //���붥�㣬���ر��
      for ( Rank j = 0; j < n; j++ ) E[j].insert ( NULL ); n++; //������Ԥ��һ��Ǳ�ڵĹ�����
      E.insert ( Vector<Edge<Te>*> ( n, n, ( Edge<Te>* ) NULL ) ); //�����¶����Ӧ�ı�����
      return V.insert ( Vertex<Tv> ( vertex ) ); //������������һ������
   }
   virtual Tv remove ( Rank i ) { //ɾ����i�����㼰������ߣ�0 <= i < n��
      for ( Rank j = 0; j < n; j++ ) //���г���
         if ( exists ( i, j ) ) { delete E[i][j]; V[j].inDegree--; e--; } //����ɾ��
      E.remove ( i ); n--; //ɾ����i��
      Tv vBak = vertex ( i ); V.remove ( i ); //ɾ������i
      for ( Rank j = 0; j < n; j++ ) //�������
         if ( Edge<Te> * x = E[j].remove ( i ) ) { delete x; V[j].outDegree--; e--; } //����ɾ��
      return vBak; //���ر�ɾ���������Ϣ
   }
// �ߵ�ȷ�ϲ���
   virtual bool exists ( Rank i, Rank j ) //��(i, j)�Ƿ����
   { return ( i < n ) && ( j < n ) && E[i][j] != NULL; }
// �ߵĻ�����������ѯ����i��j֮������ߣ�0 <= i, j < n��exists(i, j)��
   virtual EType & type ( Rank i, Rank j ) { return E[i][j]->type; } //��(i, j)������
   virtual Te& edge ( Rank i, Rank j ) { return E[i][j]->data; } //��(i, j)������
   virtual int& weight ( Rank i, Rank j ) { return E[i][j]->weight; } //��(i, j)��Ȩ��
// �ߵĶ�̬����
   virtual void insert ( Te const& edge, int w, Rank i, Rank j ) { //����Ȩ��Ϊw�ı�(i, j)
      if ( exists ( i, j ) ) return; //ȷ���ñ��в�����
      E[i][j] = new Edge<Te> ( edge, w ); //�����±�
      e++; V[i].outDegree++; V[j].inDegree++; //���±߼������������Ķ���
   }
   virtual Te remove ( Rank i, Rank j ) { //ɾ������i��j֮������ߣ�exists(i, j)��
      Te eBak = edge ( i, j ); delete E[i][j]; E[i][j] = NULL; //���ݺ�ɾ���߼�¼
      e--; V[i].outDegree--; V[j].inDegree--; //���±߼������������Ķ���
      return eBak; //���ر�ɾ���ߵ���Ϣ
   }
};