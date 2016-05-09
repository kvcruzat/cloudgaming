// Khen Cruzat - sc13kvc - 200760716

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>

#include <QtWidgets>
#include <QtNetwork>

#include "GLPolygonWidget.h"
#include "GLWindow.h"

/**
 * Class implementation of Qt window config
 */
GLWindow::GLWindow(QWidget *parent) :QWidget(parent), tcpServer(0), networkSession(0)
{
	setWindowTitle("GLWidget");
 	setMinimumSize(800,600);

	glPolyWidget = new GLPolygonWidget;	// Creates instance of OpenGL widget

	sliderX = sliderTransCreate();
	sliderY = sliderTransCreate();	// Creates translation sliders
	sliderZ = sliderTransCreate();

	labelTrans = new QLabel();
	labelTrans->setText("Translation");
	labelTrans->setAlignment(Qt::AlignHCenter);

	sliderXrot = sliderRotCreate();
	sliderYrot = sliderRotCreate();		// Creates rotation sliders
	sliderZrot = sliderRotCreate();

	labelX = new QLabel();
	labelX->setText("X");
	labelX->setAlignment(Qt::AlignHCenter);
	labelY = new QLabel();
	labelY->setText("Y");
	labelY->setAlignment(Qt::AlignHCenter);
	labelZ = new QLabel();
	labelZ->setText("Z");
	labelZ->setAlignment(Qt::AlignHCenter);

	labelRot = new QLabel();
	labelRot->setText("Rotation");
	labelRot->setAlignment(Qt::AlignHCenter);

	moveTreeButton = new QPushButton("Move Tree");
	moveTreeButton->setMaximumWidth(150);

	sliderScale = sliderScaleCreate();
	labelScale = new QLabel();			// Creates scale sliders
	labelScale->setText("Scale");
	labelScale->setAlignment(Qt::AlignHCenter);

	seasonsSelector = new QSpinBox();
	seasonsSelector->setMaximumWidth(150);
	seasonsSelector->setRange(1, 15);
    seasonsSelector->setSingleStep(1);
    seasonsSelector->setValue(1);
	labelSeasons = new QLabel();
	labelSeasons->setText("Seasons");
	labelSeasons->setBuddy(seasonsSelector);
	labelSeasons->setAlignment(Qt::AlignLeft);

	lightButton = new QCheckBox();
	lightButton->setChecked(true);		// Creates light checkbox
	labelLight = new QLabel();
	labelLight->setText("Lighting");
	labelLight->setBuddy(lightButton);
	labelLight->setAlignment(Qt::AlignLeft);

	shadingButton = new QCheckBox();
	shadingButton->setChecked(true);		// Creates shading checkbox
	labelShading = new QLabel();
	labelShading->setText("Smooth Shading");
	labelShading->setBuddy(shadingButton);
	labelShading->setAlignment(Qt::AlignLeft);

	leavesButton = new QCheckBox();
	leavesButton->setChecked(false);		// Creates leaves checkbox
	labelLeaves = new QLabel();
	labelLeaves->setText("Leaves");
	labelLeaves->setBuddy(leavesButton);
	labelLeaves->setAlignment(Qt::AlignLeft);

	// Connects widgets to custom slots
	connect(sliderX, SIGNAL(valueChanged(int)), glPolyWidget, SLOT(translateX(int)));
	connect(sliderY, SIGNAL(valueChanged(int)), glPolyWidget, SLOT(translateY(int)));
	connect(sliderZ, SIGNAL(valueChanged(int)), glPolyWidget, SLOT(translateZ(int)));
	connect(sliderXrot, SIGNAL(valueChanged(int)), glPolyWidget, SLOT(rotateX(int)));
	connect(sliderYrot, SIGNAL(valueChanged(int)), glPolyWidget, SLOT(rotateY(int)));
	connect(sliderZrot, SIGNAL(valueChanged(int)), glPolyWidget, SLOT(rotateZ(int)));
	connect(sliderScale, SIGNAL(valueChanged(int)), glPolyWidget, SLOT(setScale(int)));
	connect(lightButton, SIGNAL(clicked(bool)), glPolyWidget, SLOT(setLight(bool)));
	connect(shadingButton, SIGNAL(clicked(bool)), glPolyWidget, SLOT(setShading(bool)));
	connect(leavesButton, SIGNAL(clicked(bool)), glPolyWidget, SLOT(setLeaves(bool)));
	connect(seasonsSelector, SIGNAL(valueChanged(int)), glPolyWidget, SLOT(setSeasons(int)));
	connect(moveTreeButton, SIGNAL(released()), glPolyWidget, SLOT(moveTree()));

	QHBoxLayout* translateLayout = new QHBoxLayout;
	translateLayout->addWidget(sliderX);
	translateLayout->addWidget(sliderY);
	translateLayout->addWidget(sliderZ);

	QHBoxLayout* labelAxisLayout = new QHBoxLayout;
	labelAxisLayout->addWidget(labelX);
	labelAxisLayout->addWidget(labelY);
	labelAxisLayout->addWidget(labelZ);
	
	QHBoxLayout* rotationLayout = new QHBoxLayout;
	rotationLayout->addWidget(sliderXrot);
	rotationLayout->addWidget(sliderYrot);			// Handles widget layout
	rotationLayout->addWidget(sliderZrot);

	QFormLayout* formLayout = new QFormLayout;
	formLayout->addRow(lightButton, labelLight);
	formLayout->addRow(shadingButton, labelShading);
	formLayout->addRow(leavesButton, labelLeaves);

	QVBoxLayout* controlLayout = new QVBoxLayout;
	controlLayout->addWidget(labelTrans);
	controlLayout->addLayout(translateLayout);
	controlLayout->addLayout(labelAxisLayout);
	controlLayout->addWidget(labelRot);
	controlLayout->addLayout(rotationLayout);
	controlLayout->addWidget(moveTreeButton);
	controlLayout->addWidget(labelScale);
	controlLayout->addWidget(sliderScale);
	controlLayout->addWidget(labelSeasons);
	controlLayout->addWidget(seasonsSelector);
	controlLayout->addLayout(formLayout);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(glPolyWidget);
	mainLayout->addLayout(controlLayout);
	setLayout(mainLayout);

	QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        networkSession->open();
    } else {
        sessionOpened();
    }

	connect(tcpServer, SIGNAL(newConnection()), this, SLOT( sendData()) );

}

// method to help create translation sliders
QSlider* GLWindow::sliderTransCreate() {
	QSlider* slider = new QSlider(Qt::Vertical);
	slider->setRange(-200, 200);
	slider->setTickInterval(1);
	slider->setValue(0);

	return slider;
}

// method to help create rotation sliders
QSlider* GLWindow::sliderRotCreate() {
	QSlider* slider = new QSlider(Qt::Vertical);
	slider->setRange(-360, 360);
	slider->setTickInterval(1);
	slider->setValue(0);

	return slider;
}

// method to help create scale sliders
QSlider* GLWindow::sliderScaleCreate() {
	QSlider* slider = new QSlider(Qt::Horizontal);
	slider->setRange(-100, 100);
	slider->setTickInterval(1);
	slider->setValue(0);
	slider->setMaximumWidth(150);

	return slider;
}

// Send connection confirmation message to client
void GLWindow::sendData()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << QString::fromStdString("Connected to Server");
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(disconnected()),
            clientConnection, SLOT(deleteLater()));

    clientConnection->write(block);

    blockSize = 0;
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readData()));
 
}

// Listen to messages sent from client
void GLWindow::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        QMessageBox::critical(this, tr("Game Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    qDebug() << ipAddress << tcpServer->serverPort();

}

// read in commands sent from client
void GLWindow::readData()
{	
	// QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    QDataStream in(clientConnection);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0) {
        if (clientConnection->bytesAvailable() < (int)sizeof(quint16)){
            return;
        }  
        in >> blockSize;
    }

    if (clientConnection->bytesAvailable() < blockSize){
        return;
    }

    QString message;
    in >> message;

    qDebug() << message;
    blockSize = 0;

    glPolyWidget->simulateKey(message.toStdString());
} 