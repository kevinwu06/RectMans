#include "client.h"

Client::Client()
{
};

//连接
bool Client::Connect(QString ip,QString port)
{
    socket.connectToHost(ip,port.toInt());
    if(!socket.waitForConnected(2000)){
        qDebug("连接失败");
        return 0;
    }
    qDebug("成功连接");
    connect(&socket,SIGNAL(readyRead()),this,SLOT(receiveData()));
    return 1;
}

//接受数据
void Client::receiveData()
{
    // QByteArray 转 int[]
    QByteArray array=socket.readAll();
    int data[3];
     for (int i=0; i<3; i++)
     {
         int unTemp;
         memcpy(&unTemp, array.data() + sizeof(int) * i, sizeof(int));
         data[i] = unTemp;
     }
    x=data[0];
    y=data[1];
    dir=data[2];
}

//发送数据
void Client::sendData(int x_self,int y_self,int dir_self)
{
    //int[] 转 QByteArray
    int  self[3] = {x_self,y_self,dir_self};
    QByteArray array;
    array.append((char*)self, sizeof(int) * 3);
    socket.write(array);
}
//获取对方数据
int Client::getX()
{
    return x;
}
int Client::getY()
{
    return y;
}
int Client::getDir()
{
    return dir;
}
