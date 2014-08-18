/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent   : public Component, public Slider::Listener
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

		void sliderValueChanged(Slider*);
		void labelTextChanged(Label*);
    void paint (Graphics&);
    void resized();

private:
    //==============================================================================
		Label carrierLabel;
		Slider carrierSlider;

		Label cmRatioLabel;
		Slider cmRatioSlider;
		
		Label indexLabel;
		Slider indexSlider;

		Label outcomeLabel;
		Label outcome;
		
		Label noteNameLabel;
		Label noteNameOutcome;
		
		TextButton playButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
