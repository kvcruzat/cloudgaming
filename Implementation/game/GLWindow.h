// Khen Cruzat - sc13kvc - 200760716

#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QWidget>

class QSlider;
class QLabel;
class QCheckBox;		// forward declaration
class GLPolygonWidget;
class QSpinBox;

/**
 * Class definition for Qt window config
 */
class GLWindow : public QWidget {

	public:
		GLWindow();

	private:
		QSlider* sliderTransCreate();	// helper functions to create sliders
		QSlider* sliderRotCreate();
		QSlider* sliderScaleCreate();

		GLPolygonWidget* glPolyWidget;
		QSlider* sliderX;
		QSlider* sliderY;
		QSlider* sliderZ;
		QSlider* sliderXrot;
		QSlider* sliderYrot;
		QSlider* sliderZrot;
		QSlider* sliderScale;
		QCheckBox* lightButton;
		QCheckBox* shadingButton;
		QCheckBox* leavesButton;
		QSpinBox* seasonsSelector;
		QLabel* labelTrans;
		QLabel* labelX;
		QLabel* labelY;
		QLabel* labelZ;
		QLabel* labelRot;
		QLabel* labelScale;
		QLabel* labelLight;
		QLabel* labelShading;
		QLabel* labelLeaves;
		QLabel* labelSeasons;
};

#endif