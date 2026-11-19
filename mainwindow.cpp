#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_iniciar,&QPushButton::clicked,this,&MainWindow::iniciar_servidor);
    connect(&servidor,&QTcpServer::newConnection,this,&MainWindow::nueva_conexion);
}

void MainWindow::iniciar_servidor()
{
    if(!servidor.isListening())
    {
        bool ok;
        uint16_t port=ui->lineEdit_port->text().toUShort(&ok);
        if(!ok || port==0)
        {
            qDebug()<<"error, ingrese un puerto valido";
            return;
        }
        if(servidor.listen(QHostAddress::Any,port))
        {
            qDebug()<<"servidor iniciado";
        }
    }
}

void MainWindow::nueva_conexion()
{
    socket= servidor.nextPendingConnection();

    connect(socket,&QTcpSocket::readyRead,this,&MainWindow::leer_datos);
    qDebug()<<"cliente conectado";
}

void MainWindow::leer_datos()
{
    QByteArray datos=socket->readAll();
    QString comando=QString::fromUtf8(datos).trimmed();
    QDateTime fecha=QDateTime::currentDateTime();
    QString respuesta;

    if(comando=="year")
    {
        respuesta=QString::number(fecha.date().year());
    }
    else if(comando=="month")
    {
        respuesta=QString::number(fecha.date().month());
    }
    else if(comando=="day")
    {
        respuesta=QString::number(fecha.date().day());
    }
    else if(comando=="date")
    {
        respuesta=fecha.date().toString("dd/MM/yyyy");
    }
    else if(comando=="hour")
    {
        respuesta=QString::number(fecha.time().hour());
    }
    else if(comando=="min")
    {
        respuesta=QString::number(fecha.time().minute());
    }
    else if(comando=="sec")
    {
        QString::number(fecha.time().second());
    }
    else if(comando=="time")
    {
        respuesta=fecha.time().toString("HH:mm:ss");
    }
    else if(comando=="datetime")
    {
        respuesta=fecha.toString("dd/MM/yyyy  HH:mm:ss");
    }
    else
    {
        return;
    }

    socket->write(respuesta.toUtf8());
}


MainWindow::~MainWindow()
{
    delete ui;
}
