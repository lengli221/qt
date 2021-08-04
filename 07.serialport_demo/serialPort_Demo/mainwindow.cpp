#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSerialPort>
#include <QSerialPortInfo>

QSerialPort serial;
QByteArray rec;
QByteArray send;

/*
** ModBus CRC16
**	@param:
**		const void*s:数据项
**		int:数据项长度
**	@return:
**		uint16:CRC16码
*/
uint16_t modBusCRC16(const void* s,int n){
    uint16_t c = 0xFFFF, b = 0;
    int i = 0, k =0;

    for(k = 0;k < n; k++){
        b = (((uint8_t*)s)[k]);
        for(i = 0;i < 8; i++){
            c = ((b^c)&1)?(c>>1)^0xA001 : (c>>1);
            b >>= 1;
        }
    }
    return (c << 8) | (c >> 8);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*扫描串口*/
    ui->cbb->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        list << info.portName() << info.serialNumber();
        ui->cbb->addItem(list.first());
    }
    /*初始化参数*/
    ui->edit_BmsId->setText("BT106002004NYYZTTHD200224002");
    ui->dsb_Vol->setValue(66.54);
    ui->dsb_Cur->setValue(18.68);
    ui->sp_Soc->setValue(90);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serialPort_readyRead(){
    /*读取数据*/
    QByteArray buffer = serial.readAll();
    /*copy data*/
    rec.append(buffer);
    for(;rec.size()>=8;){
        if(rec[0] == (char)0x01){
            uint16_t crc16 = modBusCRC16(rec,6);
            uint16_t get_crc16 = (uint8_t)rec[6] << 8 | (uint8_t)rec[7];
            if(crc16 == get_crc16){
                uint16_t addr = (uint8_t)rec[2] << 8 | (uint8_t)rec[3];
                uint16_t vol = 0;
                uint16_t cur = 0;
                uint16_t crc16 = 0;
                send.clear();
                send.append((char)0x01);
                send.append((char)rec[1]);
                switch (rec[1]) {/*功能吗*/
                    case 0x01:
                        send.append((char)0x07);
                        /*故障位*/
                        send.append((char)0x00);
                        send.append((char)0x00);
                        send.append((char)0x00);
                        send.append((char)0x00);
                        send.append((char)0x00);
                        send.append((char)0x00);
                        send.append((char)0x00);
                        break;
                    case 0x03:
                        switch(addr){
                            case 0:
                                send.append((char)0x68);
                                /*电压*/
                                vol = ui->dsb_Vol->value()*100;
                                send.append((char)(vol>>8));
                                send.append((char)(vol&0xFF));
                                /*电芯数量*/
                                send.append((char)0x00);
                                send.append((char)20);
                                /*SOC*/
                                send.append((char)0);
                                send.append(ui->sp_Soc->value());
                                /*剩余容量*/
                                send.append((char)0x00);
                                send.append((char)0x00);
                                /*SOH*/
                                send.append((char)0x00);
                                send.append((char)0x00);
                                /*充电电流*/
                                cur = ui->dsb_Cur->value()*100;
                                send.append((char)(cur>>8));
                                send.append((char)(cur&0xFF));
                                /*环境温度*/
                                send.append((char)0x00);
                                send.append((char)0x00);
                                /*电芯温度*/
                                send.append((char)0x00);
                                send.append((char)0x00);
                                /*板卡温度(MOS管温度)*/
                                send.append((char)0x00);
                                send.append((char)0x00);
                                /*电芯电压1-40*/
                                for(int i=0;i<40;i++){
                                    send.append((char)0x0C);
                                    send.append((char)0xFD);
                                }
                                /*请求充电电流*/
                                send.append((char)0x00);
                                send.append((char)0x00);
                                /*最高充电电压*/
                                send.append((char)0x00);
                                send.append((char)0x00);
                                /*充电允许和禁止*/
                                send.append((char)0x00);
                                send.append((char)0x00);
                                break;
                            case 0x03E8:
                                send.append((char)ui->edit_BmsId->text().size());
                                send.append(ui->edit_BmsId->text().toLatin1());
                                break;
                            default:

                            break;
                        }
                        break;
                }
                crc16 = modBusCRC16(send,send.size());
                send.append((char)(crc16 >> 8));
                send.append((char)(crc16&0xFF));
                serial.write(send);
                send.clear();
                rec.remove(0,8);
            }else{
                rec.remove(0,1);
            }
        }else{
           rec.remove(0,1);
        }
    }
}

void MainWindow::on_btn_serialPort_clicked()
{
    if(serial.isOpen()){
        serial.close();
        ui->btn_serialPort->setText("打开串口");
    }else{
        /**/
        serial.setPortName(ui->cbb->currentText());
        serial.setBaudRate(115200);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);
        /*打开串口*/
        if(serial.open(QIODevice::ReadWrite)){
            ui->btn_serialPort->setText("关闭串口");
            /*串口接收信号槽*/
            connect(&serial,&QSerialPort::readyRead,this,&MainWindow::serialPort_readyRead);
        }
    }
}
