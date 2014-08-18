/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "FM.h"
#include "MainComponent.h"
#include "../menc/menc.h"



String arrayToString(Array<double> array)
{
		String outputString;
		for (int i=0; i<array.size(); i++) {
				outputString += String(array[i]) += ", ";
		}
		return outputString;
}

String arrayToNoteNameString(Array<double> array)
{
		StringArray outputString;
		menc::Note myNote;
		for (int i=0; i<array.size();i++){
				myNote.fromFrequency((float)array[i]);
				outputString.addIfNotAlreadyThere(myNote.toPrettyString());
		}
		return outputString.joinIntoString(",  ");
}



//==============================================================================
MainContentComponent::MainContentComponent() : carrierSlider(Slider::LinearHorizontal, Slider::TextBoxRight), cmRatioSlider(Slider::LinearHorizontal, Slider::TextBoxRight), indexSlider(Slider::LinearHorizontal, Slider::TextBoxRight), playButton("Send MIDI")
{
		addAndMakeVisible(&carrierLabel);
		
		carrierSlider.setRange(0.0, 500.0);
		carrierSlider.setValue(100.0, sendNotification);
		carrierSlider.setTextBoxIsEditable(true);
		carrierSlider.addListener(this);
		addAndMakeVisible(&carrierSlider);
		
		addAndMakeVisible(&cmRatioLabel);
		
		cmRatioSlider.setRange(0.0, 10.0);
		cmRatioSlider.setValue(1.0, sendNotification);
		cmRatioSlider.setTextBoxIsEditable(true);
		cmRatioSlider.addListener(this);
		addAndMakeVisible(&cmRatioSlider);
		
		addAndMakeVisible(&indexLabel);
		
		indexSlider.setRange(0.0, 30.0);
		indexSlider.setValue(1.0, sendNotification);
		indexSlider.setTextBoxIsEditable(true);
		indexSlider.addListener(this);
		addAndMakeVisible(&indexSlider);
		
		addAndMakeVisible(&outcomeLabel);
		addAndMakeVisible(&outcome);
		
		addAndMakeVisible(&noteNameLabel);
		addAndMakeVisible(&noteNameOutcome);
		
		addAndMakeVisible(&playButton);
		
    setSize (500, 400);
}

MainContentComponent::~MainContentComponent()
{
}

void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xffeeddff));

    g.setFont (Font (16.0f));
    g.setColour (Colours::black);
}

void MainContentComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
		carrierLabel.setBoundsRelative(0.05, 0.0, 0.90, 0.10);
		carrierLabel.setText("Carrier Frequency", sendNotification);
		carrierSlider.setBoundsRelative(0.05, 0.05, 0.90, 0.10);
		
		cmRatioLabel.setBoundsRelative(0.05, 0.10, 0.90, 0.10);
		cmRatioLabel.setText("C-M Ratio", sendNotification);
		cmRatioSlider.setBoundsRelative(0.05, 0.15, 0.90, 0.10);
		
		indexLabel.setBoundsRelative(0.05, 0.20, 0.90, 0.10);
		indexLabel.setText("Index", sendNotification);
		indexSlider.setBoundsRelative(0.05, 0.25, 0.90, 0.10);
		
		outcomeLabel.setBoundsRelative(0.05, 0.30, 0.90, 0.10);
		outcomeLabel.setText("FM Spectrum", sendNotification);
		outcome.setBoundsRelative(0.05, 0.35, 0.90, 0.25);
		
		noteNameLabel.setBoundsRelative(0.05, 0.60, 0.90, 0.10);
		noteNameLabel.setText("Note Names", sendNotification);
		noteNameOutcome.setBoundsRelative(0.05, 0.65, 0.90, 0.25);
		
		playButton.setBoundsRelative(0.8, 0.90, 0.15, 0.08);
}


void MainContentComponent::sliderValueChanged(Slider* slider)
{
		if (&carrierSlider == slider || &cmRatioSlider == slider || &indexSlider == slider) {
				String outputString, outputNoteNameString;
				FM myFM (carrierSlider.getValue(), cmRatioSlider.getValue(), indexSlider.getValue());
				//myFM.runFM();
				outputString = arrayToString(myFM.getSpectrum());
				outcome.setText(outputString, sendNotification);
				
				outputNoteNameString = arrayToNoteNameString(myFM.getSpectrum());
				noteNameOutcome.setText(outputNoteNameString, sendNotification);
		}

}