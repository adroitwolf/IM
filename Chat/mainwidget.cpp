#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "itemwidget.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QVariantList>
#include <QVariantMap>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFileDialog>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{

    ui->setupUi(this);
    setWindowTitle("欢迎来到 OO");
    //设置背景
    QFile qssfile(":/resource/mainWidget.css");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();

    this->setStyleSheet(qss);
    //设置背景
    QPalette pal = this->palette();
    QPixmap pixmap= QPixmap(":/resource/main-bg.jpg").scaled(this->size());
    pal.setBrush(QPalette::Background,QBrush(pixmap));
    setPalette(pal);
    //初始化info
    QString IpString;
    file.setFileName(":/resource/Ip.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }
    while(!file.atEnd()) {
        QByteArray line = file.readLine();
        IpString = QString(line);
    }
    info.setIp(IpString);
    info.setPort("9999");

    //不可点击按钮
    ui->ButtonAgree->setEnabled(false);
    ui->ButtonFileSend->setEnabled(false);


    //信号接收
    connect(ui->listWidgetRequest,&QListWidget::itemDoubleClicked,this,&MainWidget::setButton);
    connect(&addWidget,&AddFriendWidget::addBack,
            [=]()
            {
                ui->ButtonAddFriend->setEnabled(true);
            });
    connect(ui->listWidgetFrds,&QListWidget::itemDoubleClicked,
            [=]()
            {
                this->dealListFrdChoose();
                ui->ButtonFileSend->setEnabled(true);
            });

    connect(&fileWidget,&FileSend::fileSizeOverLoad,[=]{
                //文件过大
                QMessageBox::information(this,"OverLoad","选择文件过大,需小于10M");
                ui->ButtonFileSend->setEnabled(true);
            });
    connect(&fileWidget,&FileSend::sendOver,[=]{
                //文件传输完毕
                ui->ButtonFileSend->setEnabled(true);
            });


}

MainWidget::~MainWidget()
{
    delete ui;
}

/**
 * @brief MainWidget::nowAdd
 * @param user
 */
void MainWidget::nowAdd(User user)//WAIT
{
    //图标变化
    QFile qssfile(":/resource/mainWidgetAdd.css");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();

    this->setStyleSheet(qss);

    //加入新请求
    QList<User> addNow = userInfo.getAddRequest();
    addNow.append(user);
    userInfo.setAddRequest(addNow);
}

/**
 * @brief MainWidget::dealFriends
 */
void MainWidget::dealFriends()//设置好友列表
{
    qDebug()<<"enter deal list";
    for(int i = 0;i<userInfo.getFriends().size();i++)
    {
        ItemWidget *itemWidget = new ItemWidget();
        itemWidget->setItemWidget(userInfo.getFriends()[i]);
        QListWidgetItem *item=new QListWidgetItem;
        item->setSizeHint(QSize(250,70));
        ui->listWidgetFrds->addItem(item);
        ui->listWidgetFrds->setItemWidget(item,itemWidget);
    }
}

/**
 * @brief MainWidget::on_ButtonAddFriend_clicked
 */

void MainWidget::on_ButtonAddFriend_clicked()
{
    addWidget.setUserInfo(this->userInfo);
    QFile qssfile(":/resource/addNew.css");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();

    addWidget.setStyleSheet(qss);
    //设置背景
    QPalette pal = addWidget.palette();
    QPixmap pixmap= QPixmap(":/resource/add-bg.jpg").scaled(addWidget.size());
    pal.setBrush(QPalette::Background,QBrush(pixmap));
    addWidget.setPalette(pal);

    addWidget.show();
    addWidget.getUserInfo(userInfo.getUser());
}

/**
 * @brief MainWidget::on_ButtonMy_clicked
 */
void MainWidget::on_ButtonMy_clicked()
{

    QPalette pal = infoWidget.palette();
    QPixmap pixmap= QPixmap(":/resource/self-info.jpg").scaled(infoWidget.size());
    pal.setBrush(QPalette::Background,QBrush(pixmap));
    infoWidget.setPalette(pal);
    infoWidget.show();
}

void MainWidget::setUserInfo(UserInfo userInfo)
{
    this->userInfo = userInfo;
    //初始化个人信息界面
    infoWidget.setUser(userInfo.getUser());
    //检测是否有新加好友请求
    if(userInfo.getAddRequest().size() > 0)
    {
        QFile qssfile(":/resource/mainWidgetAdd.css");
        qssfile.open(QFile::ReadOnly);
        QString qss;
        qss = qssfile.readAll();

        this->setStyleSheet(qss);

    }
}

UserInfo MainWidget::getUserInfo()
{
    return this->userInfo;
}


void MainWidget::on_ButtonNewAdd_clicked()
{
    ui->ButtonAgree->setEnabled(false);
    ui->ButtonRefuse->setEnabled(false);
    if(userInfo.getAddRequest().size() != 0)
    {
        QFile qssfile(":/resource/mainWidget.css");
        qssfile.open(QFile::ReadOnly);
        QString qss;
        qss = qssfile.readAll();

        this->setStyleSheet(qss);
        ui->page_3->show();
        ui->page->hide();
        ui->page_2->hide();
        ui->page_4->hide();
        for(int i = 0;i<userInfo.getAddRequest().size();i++)
        {
            ItemWidget *itemWidget = new ItemWidget();
            itemWidget->setItemWidget(userInfo.getAddRequest()[i]);
            QListWidgetItem *item=new QListWidgetItem;
            item->setSizeHint(QSize(250,70));
            ui->listWidgetRequest->addItem(item);
            ui->listWidgetRequest->setItemWidget(item,itemWidget);
        }
    }
    else
    {
        ui->page_4->show();
        ui->page->hide();
        ui->page_2->hide();
        ui->page_3->hide();
//        qDebug()<<userInfo.getAddRequest().size();
//        for(int i = 0;i<userInfo.getAddRequest().size();i++)
//        {
//            ItemWidget *itemWidget = new ItemWidget();
//            itemWidget->setItemWidget(userInfo.getAddRequest()[i]);
//            QListWidgetItem *item=new QListWidgetItem;
//            item->setSizeHint(QSize(250,70));
//            ui->listWidgetRequest->addItem(item);
//            ui->listWidgetRequest->setItemWidget(item,itemWidget);
//        }
    }
}

void MainWidget::on_ButtonMsg_clicked()
{
    ui->page->show();
    ui->page_2->hide();
    ui->page_3->hide();
    ui->page_4->hide();
}

void MainWidget::on_ButtonAgree_clicked()
{

    QList<User> temp = userInfo.getFriends();
    int a = ui->listWidgetRequest->currentRow();
    temp.insert(temp.size(),userInfo.getAddRequest()[a]);
    userInfo.setFriends(temp);

    ItemWidget *itemWidget = new ItemWidget();
    itemWidget->setItemWidget(userInfo.getAddRequest()[a]);
    qDebug()<<userInfo.getAddRequest()[a].getStatus();
    QListWidgetItem *item=new QListWidgetItem;
    item->setSizeHint(QSize(250,70));
    ui->listWidgetFrds->addItem(item);
    ui->listWidgetFrds->setItemWidget(item,itemWidget);

    //发送选中行的信息给服务器，表示同意添加
    mainOp.dealAgreeAdd(userInfo.getUser(),userInfo.getAddRequest()[a],info);
    //删除请求列表中的条目
    userInfo.getAddRequest().removeAt(a);
    ui->listWidgetRequest->takeItem(a);
    ui->ButtonAgree->setEnabled(false);//按钮不可点击
    ui->ButtonRefuse->setEnabled(false);
}

void MainWidget::setButton()
{
    ui->ButtonAgree->setEnabled(true);
    ui->ButtonRefuse->setEnabled(true);
}

void MainWidget::dealListFrdChoose()
{
    ui->listWidgetFrds->item(ui->listWidgetFrds->currentRow())->setBackgroundColor(QColor(0,0,0,0));
    ui->labelChating->setText("("+userInfo.getFriends()[ui->listWidgetFrds->currentRow()].getAccount()
            +")"+userInfo.getFriends()[ui->listWidgetFrds->currentRow()].getNickName());
    ui->page->show();
    ui->page_2->hide();
    ui->page_3->hide();
    ui->page_4->hide();
    ui->textBrowserMsg->clear();

    setSelectFlag(true);//设置点击flag
    setCurrentRow(ui->listWidgetFrds->currentRow());//获取点击的行序号

    for(int i = 0;i<this->userInfo.getFriends()[ui->listWidgetFrds->currentRow()].getMessage().size();i++)
    {
        if(this->userInfo.getFriends()[ui->listWidgetFrds->currentRow()].getMessage()[i].getSenderQQ() == this->userInfo.getUser().getAccount())
        {
            ui->textBrowserMsg->append("[我:"+this->userInfo.getFriends()[ui->listWidgetFrds->currentRow()].getMessage()[i].getCDate()+
                    "]:"+this->userInfo.getFriends()[ui->listWidgetFrds->currentRow()].getMessage()[i].getContext());
        }
        else
        {
            QString nickName;
            for(int j = 0;j < this->userInfo.getFriends().size();j++)
            {
                if(this->userInfo.getFriends()[j].getAccount() ==
                        this->userInfo.getFriends()[ui->listWidgetFrds->currentRow()].getMessage()[i].getSenderQQ())
                {
                    nickName = this->userInfo.getFriends()[j].getNickName();
                }
            }
            ui->textBrowserMsg->append(
                        "["+nickName+":"+this->userInfo.getFriends()[ui->listWidgetFrds->currentRow()].getMessage()[i].getCDate()+"]:"+
                        this->userInfo.getFriends()[ui->listWidgetFrds->currentRow()].getMessage()[i].getContext());
        }
    }
}



void MainWidget::addNewList(User user)//
{
    qDebug()<<"enter addnewlist";
    ItemWidget *itemWidget = new ItemWidget();

    itemWidget->setItemWidget(user);
    QListWidgetItem *item=new QListWidgetItem;
    item->setSizeHint(QSize(250,70));
    ui->listWidgetFrds->addItem(item);
    ui->listWidgetFrds->setItemWidget(item,itemWidget);

    QList<User> temp = userInfo.getFriends();
    temp.insert(temp.size(),user);
    userInfo.setFriends(temp);
}

void MainWidget::on_ButtonSet_clicked()
{

    QFile qssfile(":/resource/addNew.css");
    qssfile.open(QFile::ReadOnly);
    QString qss;
    qss = qssfile.readAll();

    setWidget.setStyleSheet(qss);
    //设置背景
    QPalette pal = setWidget.palette();
    QPixmap pixmap= QPixmap(":/resource/add-bg.jpg").scaled(setWidget.size());
    pal.setBrush(QPalette::Background,QBrush(pixmap));
    setWidget.setPalette(pal);
    setWidget.show();
}

void MainWidget::on_ButtonSend_clicked()
{
    //发送消息
    //空消息
    if(ui->textEdit->toPlainText().isEmpty() == 1)
    {
        return;
    }
    if(getSlectFlag() == false)
    {
        ui->listWidgetFrds->setCurrentRow(this->currentRow);
    }
    else
    {
        //获取当前的好友
        int a = ui->listWidgetFrds->currentRow();
        //获取时间
        currentTime = QDateTime::currentDateTime();
        QString time = currentTime.toString("yyyy.MM.dd hh:mm:ss");
        Message msg;
        msg.setCDate(time);
        msg.setContext(ui->textEdit->toPlainText());
        msg.setSenderQQ(userInfo.getUser().getAccount());
        msg.setReceviceQQ(userInfo.getFriends()[a].getAccount());
        mainOp.dealSend(msg,info);

        //
        qDebug()<<"enter add my message";
        //更新friends` message
        int i = ui->listWidgetFrds->currentRow();
        QList<Message> tempMessage;
        tempMessage = this->userInfo.getFriends()[i].getMessage();
        tempMessage.insert(this->userInfo.getFriends()[i].getMessage().size(),msg);
        User friendL = this->userInfo.getFriends()[i];
        friendL.setMessage(tempMessage);
        QList<User> temp = this->userInfo.getFriends();
        temp.replace(i,friendL);
        this->userInfo.setFriends(temp);

        ui->textBrowserMsg->append("[我："+time+"]:"+ui->textEdit->toPlainText());
        ui->textEdit->clear();
    }
}

void MainWidget::changeStatus(QString qq, QString status)
{

    //修改好友状态
    int size = -1;
    foreach (User friendL, this->userInfo.getFriends())
    {
        size++;
        if(friendL.getAccount() == qq)
        {
            //更新friends状态
            friendL.setStatus(status);
            QList<User> temp = this->userInfo.getFriends();
            temp.replace(size,friendL);
            this->userInfo.setFriends(temp);
            ui->listWidgetFrds->clearSelection();
        }
    }

    //更新好友列表
    int n = ui->listWidgetFrds->count();
    for(int i = 0;i<n;i++)
    {
        QListWidgetItem *item = ui->listWidgetFrds->takeItem(0);
        delete  item;
    }
    this->dealFriends();
    setSelectFlag(false);//未选择item
}

void MainWidget::dealMessage(Message msg)
{
    for(int i = 0;i<userInfo.getFriends().size();i++)
    {
        if(userInfo.getFriends()[i].getAccount() == msg.getSenderQQ())
        {
            //更新friends的 message
            QList<Message> tempMessage;
            tempMessage = this->userInfo.getFriends()[i].getMessage();
            tempMessage.insert(this->userInfo.getFriends()[i].getMessage().size(),msg);
            User friendL = userInfo.getFriends()[i];
            friendL.setMessage(tempMessage);
            QList<User> temp = this->userInfo.getFriends();
            temp.replace(i,friendL);
            this->userInfo.setFriends(temp);

            if(ui->listWidgetFrds->currentRow() == i)
            {
                QString nickName;
                nickName = userInfo.getFriends()[i].getNickName();
                ui->textBrowserMsg->append("["+nickName+" "+msg.getCDate()+"]:"+msg.getContext());
            }
            else
            {
                ui->listWidgetFrds->item(i)->setBackgroundColor(QColor(220,20,60,80));
            }
        }
    }
}

void MainWidget::dealOulineMessage(QList<Message> outlineMessage)
{

    QList<User> tempUser = userInfo.getFriends();


    for(int i = 0;i<outlineMessage.size();i++)
    {
        for(int j = 0;j<userInfo.getFriends().size();j++)
        {

            if(outlineMessage[i].getSenderQQ() == userInfo.getFriends()[j].getAccount())
            {
                QList<Message> tempMessageList;
                tempMessageList = userInfo.getFriends()[j].getMessage();
                tempMessageList.append(outlineMessage[i]);
                User tempU = userInfo.getFriends()[j];
                tempU.setMessage(tempMessageList);
                tempUser.replace(j,tempU);
                userInfo.setFriends(tempUser);
                ui->listWidgetFrds->item(j)->setBackgroundColor(QColor(220,20,60,80));
                break;
            }
        }
    }
}

void MainWidget::on_ButtonRefuse_clicked()
{
    ui->listWidgetRequest->takeItem(ui->listWidgetRequest->currentRow());
    ui->ButtonRefuse->setEnabled(false);
    ui->ButtonAgree->setEnabled(false);
}


void MainWidget::on_ButtonFileSend_clicked()//发文件
{
    //获取文件路径
        QString filepath = QFileDialog::getOpenFileName(this,"open","../");//路径名
        if(filepath.isEmpty()==false)
        {

            this->fileWidget.show();
            ui->ButtonFileSend->setEnabled(false);
            //传入数据
            this->fileWidget.setUserInfo(this->userInfo.getFriends()[ui->listWidgetFrds->currentRow()]);
            this->fileWidget.setHostInfo(this->info);
            this->fileWidget.setSelfInfo(this->userInfo.getUser());
            this->fileWidget.setFilePath(filepath);
            this->fileWidget.requestSend();

        }
        else
        {
            QMessageBox::information(this,"选择文件路径错误","选择文件路径错误!");
        }

}

void MainWidget::dealFileSend(QString code)
{
    fileWidget.dealSend(code);
}

void MainWidget::dealFileSendFailed()
{
    QMessageBox::information(this,"发送请求失败","发送失败");
    fileWidget.hide();
}

void MainWidget::dealOutlineRequestFileReceive(QList<FileDate> fileList)
{
    for(int i = 0;i<fileList.size();i++)
    {
        QString msg = QString("是否接收("+fileList[i].getSenderQQ()+")的文件:"+fileList[i].getFileName());
        QMessageBox::StandardButton rb = QMessageBox::question(
                    this, "文件待接收", msg
                    , QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (rb == QMessageBox::Yes)
        {
            this->fileWidget.agreeReceiveRequest(fileList[i]);
        }
        else if(rb == QMessageBox::No)
        {
            this->fileWidget.refuseReceiveRequest(fileList[i]);
        }
    }
}

void MainWidget::dealOnlineFileReceive(FileDate fileData)
{
    QString msg = QString("是否接收("+fileData.getSenderQQ()+")的文件:"+fileData.getFileName());
    QMessageBox::StandardButton rb = QMessageBox::question(
                this, "文件待接收", msg
                , QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (rb == QMessageBox::Yes)
    {
        this->fileWidget.agreeReceiveRequest(fileData);
        qDebug()<<"front filesize:"<<fileData.getFileSize();
    }
    else if(rb == QMessageBox::No)
    {
        this->fileWidget.refuseReceiveRequest(fileData);
    }
}

