#include "dataconfig.h"

DataConfig::DataConfig(QObject *parent) : QObject(parent)
{
    //1
    int arrary1[4][4] ={{1,1,1,1},
                        {1,1,0,1},
                        {1,0,0,0},
                        {1,1,0,1}};
    QVector<QVector<int>> v;
    for(int i=0;i<4;i++){
        QVector<int> v1;
        for(int j=0;j<4;j++){
            v1.push_back(arrary1[i][j]);
        }
        v.push_back(v1);
    }
    mData.insert(1,v);

    //2
    int arrary2[4][4] ={{1,1,1,1},
                        {1,0,0,1},
                        {1,0,1,0},
                        {1,0,0,1}};
    QVector<QVector<int>> v2;
    for(int i=0;i<4;i++){
        QVector<int> v1;
        for(int j=0;j<4;j++){
            v1.push_back(arrary2[i][j]);
        }
        v2.push_back(v1);
    }
    mData.insert(2,v2);

    //3
        int arrary3[4][4] ={{0,0,0,0},
                            {0,1,1,0},
                            {0,1,1,0},
                            {0,0,0,0}};
        QVector<QVector<int>> v3;
        for(int i=0;i<4;i++){
            QVector<int> v1;
            for(int j=0;j<4;j++){
                v1.push_back(arrary3[i][j]);
            }
            v3.push_back(v1);
        }
        mData.insert(3,v3);

        //4
            int arrary4[4][4] ={{1,1,1,1},
                                {1,1,0,1},
                                {1,0,0,0},
                                {1,1,0,1}};
            QVector<QVector<int>> v4;
            for(int i=0;i<4;i++){
                QVector<int> v1;
                for(int j=0;j<4;j++){
                    v1.push_back(arrary4[i][j]);
                }
                v4.push_back(v1);
            }
            mData.insert(4,v4);
         //5
             int arrary5[4][4] ={{1,1,1,1},
                                 {1,1,0,1},
                                 {1,0,0,0},
                                 {1,1,0,1}};
             QVector<QVector<int>> v5;
             for(int i=0;i<4;i++){
                 QVector<int> v1;
                 for(int j=0;j<4;j++){
                     v1.push_back(arrary5[i][j]);
                 }
                 v5.push_back(v1);
             }
             mData.insert(5,v5);
         //6
             int arrary6[4][4] ={{1,1,1,1},
                                 {1,1,0,1},
                                 {1,0,0,0},
                                 {1,1,0,1}};
             QVector<QVector<int>> v6;
             for(int i=0;i<4;i++){
                 QVector<int> v1;
                 for(int j=0;j<4;j++){
                     v1.push_back(arrary6[i][j]);
                 }
                 v6.push_back(v1);
             }
             mData.insert(6,v6);
             //7
                 int arrary7[4][4] ={{0,1,1,1},
                                     {1,0,1,1},
                                      {1,1,0,1},
                                      {1,1,1,0}};
                  QVector<QVector<int>> v7;
                  for(int i=0;i<4;i++){
                      QVector<int> v1;
                      for(int j=0;j<4;j++){
                          v1.push_back(arrary7[i][j]);
                      }
                      v7.push_back(v1);
                  }
                  mData.insert(7,v7);
                  //8
                      int arrary8[4][4] ={{1,1,1,1},
                                          {1,1,0,1},
                                          {1,0,0,0},
                                          {1,1,0,1}};
                      QVector<QVector<int>> v8;
                      for(int i=0;i<4;i++){
                          QVector<int> v1;
                          for(int j=0;j<4;j++){
                              v1.push_back(arrary8[i][j]);
                          }
                          v8.push_back(v1);
                      }
                      mData.insert(8,v8);
                   //9
                   int arrary9[4][4] ={{1,1,1,1},
                                       {1,1,0,1},
                                       {1,0,0,0},
                                       {1,1,0,1}};
                   QVector<QVector<int>> v9;
                   for(int i=0;i<4;i++){
                       QVector<int> v1;
                       for(int j=0;j<4;j++){
                           v1.push_back(arrary9[i][j]);
                       }
                       v9.push_back(v1);
                   }
                   mData.insert(9,v9);
                   //10
                       int arrary10[4][4] ={{1,1,1,1},
                                           {1,1,0,1},
                                           {1,0,0,0},
                                           {1,1,0,1}};
                       QVector<QVector<int>> v10;
                       for(int i=0;i<4;i++){
                           QVector<int> v1;
                           for(int j=0;j<4;j++){
                               v1.push_back(arrary10[i][j]);
                           }
                           v10.push_back(v1);
                       }
                       mData.insert(10,v10);
                    //11
                        int arrary11[4][4] ={{1,1,1,1},
                                            {1,1,0,1},
                                            {1,0,0,0},
                                            {1,1,0,1}};
                        QVector<QVector<int>> v11;
                        for(int i=0;i<4;i++){
                            QVector<int> v1;
                            for(int j=0;j<4;j++){
                                v1.push_back(arrary11[i][j]);
                            }
                            v11.push_back(v1);
                        }
                        mData.insert(11,v11);
                        //12
                            int arrary12[4][4] ={{1,1,1,1},
                                                {1,1,0,1},
                                                {1,0,0,0},
                                                {1,1,0,1}};
                            QVector<QVector<int>> v12;
                            for(int i=0;i<4;i++){
                                QVector<int> v1;
                                for(int j=0;j<4;j++){
                                    v1.push_back(arrary12[i][j]);
                                }
                                v12.push_back(v1);
                            }
                            mData.insert(12,v12);
                      //13
                          int arrary13[4][4] ={{1,1,1,1},
                                              {1,1,0,1},
                                              {1,0,0,0},
                                              {1,1,0,1}};
                          QVector<QVector<int>> v13;
                          for(int i=0;i<4;i++){
                              QVector<int> v1;
                              for(int j=0;j<4;j++){
                                  v1.push_back(arrary13[i][j]);
                              }
                              v13.push_back(v1);
                          }
                          mData.insert(13,v13);
                          //14
                              int arrary14[4][4] ={{1,0,1,1},
                                                  {0,1,0,1},
                                                  {1,0,1,0},
                                                  {1,1,0,1}};
                              QVector<QVector<int>> v14;
                              for(int i=0;i<4;i++){
                                  QVector<int> v1;
                                  for(int j=0;j<4;j++){
                                      v1.push_back(arrary14[i][j]);
                                  }
                                  v14.push_back(v1);
                              }
                              mData.insert(14,v14);
                  //15
                      int arrary15[4][4] ={{0,1,0,1},
                                          {1,0,0,1},
                                          {1,0,0,0},
                                          {0,1,0,1}};
                      QVector<QVector<int>> v15;
                      for(int i=0;i<4;i++){
                          QVector<int> v1;
                          for(int j=0;j<4;j++){
                              v1.push_back(arrary15[i][j]);
                          }
                          v15.push_back(v1);
                      }
                      mData.insert(15,v15);
                      //16
                          int arrary16[4][4] ={{1,1,1,1},
                                              {1,1,0,1},
                                              {1,0,0,0},
                                              {1,1,0,1}};
                          QVector<QVector<int>> v16;
                          for(int i=0;i<4;i++){
                              QVector<int> v1;
                              for(int j=0;j<4;j++){
                                  v1.push_back(arrary16[i][j]);
                              }
                              v16.push_back(v1);
                          }
                           mData.insert(16,v16);
                           //17
                               int arrary17[4][4] ={{1,1,1,1},
                                                   {1,1,0,1},
                                                   {1,0,0,0},
                                                   {1,1,0,1}};
                               QVector<QVector<int>> v17;
                               for(int i=0;i<4;i++){
                                   QVector<int> v1;
                                   for(int j=0;j<4;j++){
                                       v1.push_back(arrary17[i][j]);
                                   }
                                   v17.push_back(v1);
                               }
                               mData.insert(17,v17);
                               //18
                                   int arrary18[4][4] ={{1,1,1,1},
                                                       {1,1,0,1},
                                                       {1,0,0,0},
                                                       {1,1,0,1}};
                                   QVector<QVector<int>> v18;
                                   for(int i=0;i<4;i++){
                                       QVector<int> v1;
                                       for(int j=0;j<4;j++){
                                           v1.push_back(arrary18[i][j]);
                                       }
                                       v18.push_back(v1);
                                   }
                                   mData.insert(18,v18);
                                   //19
                                       int arrary19[4][4] ={{1,1,1,1},
                                                           {1,1,0,1},
                                                           {1,0,0,0},
                                                           {1,1,0,1}};
                                       QVector<QVector<int>> v19;
                                       for(int i=0;i<4;i++){
                                           QVector<int> v1;
                                           for(int j=0;j<4;j++){
                                               v1.push_back(arrary19[i][j]);
                                           }
                                           v19.push_back(v1);
                                       }
                                       mData.insert(19,v19);
                                       //20
                                           int arrary20[4][4] ={{0,0,0,0},
                                                               {0,0,0,0},
                                                               {0,0,0,0},
                                                               {0,0,0,0}};
                                           QVector<QVector<int>> v20;
                                           for(int i=0;i<4;i++){
                                               QVector<int> v1;
                                               for(int j=0;j<4;j++){
                                                   v1.push_back(arrary20[i][j]);
                                               }
                                               v20.push_back(v1);
                                           }
                                           mData.insert(20,v20);
}
