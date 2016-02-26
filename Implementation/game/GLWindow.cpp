// Khen Cruzat - sc13kvc - 200760716

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>

#include "GLPolygonWidget.h"
#include "GLWindow.h"

/**
 * Class implementation of Qt window config
 */
GLWindow::GLWindow()
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

	sliderScale = sliderScaleCreate();
	labelScale = new QLabel();			// Creates scale sliders
	labelScale->setText("Scale");
	labelScale->setAlignment(Qt::AlignHCenter);

	seasonsSelector = new QSpinBox();
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
	controlLayout->addWidget(labelScale);
	controlLayout->addWidget(sliderScale);
	controlLayout->addWidget(labelSeasons);
	controlLayout->addWidget(seasonsSelector);
	controlLayout->addLayout(formLayout);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addWidget(glPolyWidget);
	mainLayout->addLayout(controlLayout);
	setLayout(mainLayout);

}

// method to help create translation sliders
QSlider* GLWindow::sliderTransCreate() {
	QSlider* slider = new QSlider(Qt::Vertical);
	slider->setRange(-100, 100);
	slider->setTickInterval(1);
	slider->setValue(0);

	return slider;
}

// method to help create rotation sliders
QSlider* GLWindow::sliderRotCreate() {
	QSlider* slider = new QSlider(Qt::Vertical);
	slider->setRange(-180, 180);
	slider->setTickInterval(1);
	slider->setValue(0);

	return slider;
}

// method to help create scale sliders
QSlider* GLWindow::sliderScaleCreate() {
	QSlider* slider = new QSlider(Qt::Horizontal);
	slider->setRange(-50, 50);
	slider->setTickInterval(1);
	slider->setValue(0);
	slider->setMaximumWidth(150);

	return slider;
}