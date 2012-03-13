/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  12 Mar 2012 11:56:22am

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "LoopComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
LoopComponent::LoopComponent ( char* c ){
  setSize(50,50);
  ident = c;
  selected =false;
}
//[/MiscUserDefs]

//==============================================================================
LoopComponent::LoopComponent ()
{

    //[UserPreSize]
    //[/UserPreSize]

    setSize (50, 50);


    //[Constructor] You can add your own custom stuff here..
    ident = "0";
  selected=false;
    //[/Constructor]
}

LoopComponent::~LoopComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void LoopComponent::paint (Graphics& g)
{
  //[UserPrePaint] Add your own custom painting code here..
  float rms = loop.rms*20.f;
  if(rms > 1.f ) rms = 1.f;
  float thick = 2.0f + 5.f*rms*loop.gain;
  
  Colour c,c2,c3;
  if( loop.numSamples != 0 ){
    if( loop.stacking ) c = Colour( 165,81,81).withAlpha(rms);
    else c = Colour( 58,172,62).withAlpha(rms);
    
    if(loop.recording) c2 = Colour( 200,30,30 ).withAlpha(.8f);
    else c2 = Colour( 58,172,62 ).withAlpha(.8f);
    
  }else{
    c = Colour( 80,80,80).withAlpha(.3f);
    c2 = Colour( 30,30,30).withAlpha(.7f);
  }
  
  if(selected) c3 = Colour( 255,0,0 );
  else c3 = Colour( 60, 30, 30 ).withAlpha(.7f);
  
  //[/UserPrePaint]

    g.setColour (c);
    g.fillRoundedRectangle (2.0f, 2.0f, 45.0f, 45.0f, 5.0000f);

    g.setColour (c2);
    g.drawRoundedRectangle (2.0f, 2.0f, 45.0f, 45.0f, 5.0000f, thick);

    g.setColour (c3);
    g.setFont (Font (Font::getDefaultMonospacedFontName(), 15.0000f, Font::bold));
    g.drawText (ident,
                20, 20, 10, 10,
                Justification::centred, true);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void LoopComponent::resized()
{
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void LoopComponent::filesDropped (const StringArray& filenames, int mouseX, int mouseY)
{
    //[UserCode_filesDropped] -- Add your code here...
    //[/UserCode_filesDropped]
}

void LoopComponent::mouseDown (const MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    //((RangLoopComponent*)getParentComponent())->
  setWantsKeyboardFocus(true);
  grabKeyboardFocus();
    //[/UserCode_mouseDown]
}

void LoopComponent::mouseDrag (const MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    //[/UserCode_mouseDrag]
}

void LoopComponent::mouseWheelMove (const MouseEvent& e, float wheelIncrementX, float wheelIncrementY)
{
    //[UserCode_mouseWheelMove] -- Add your code here...
    loop.gain += wheelIncrementY;
    if( loop.gain < 0.f ) loop.gain = 0.f;
    else if( loop.gain > 3.0f) loop.gain = 3.0f;
    //[/UserCode_mouseWheelMove]
}

void LoopComponent::focusGained (FocusChangeType cause)
{
    //[UserCode_focusGained] -- Add your code here...
    //[/UserCode_focusGained]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...


void LoopComponent::audioDeviceIOCallback (const float** inputChannelData,
                            int totalNumInputChannels,
                            float** outputChannelData,
                            int totalNumOutputChannels,
                                           int numSamples){
    loop.audioIO( (float**)inputChannelData, (float**)outputChannelData, numSamples );
}
void LoopComponent::audioDeviceAboutToStart (AudioIODevice* device){}
void LoopComponent::audioDeviceStopped(){}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="LoopComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="50" initialHeight="50">
  <METHODS>
    <METHOD name="filesDropped (const StringArray&amp; filenames, int mouseX, int mouseY)"/>
    <METHOD name="mouseDown (const MouseEvent&amp; e)"/>
    <METHOD name="mouseDrag (const MouseEvent&amp; e)"/>
    <METHOD name="mouseWheelMove (const MouseEvent&amp; e, float wheelIncrementX, float wheelIncrementY)"/>
    <METHOD name="focusGained (FocusChangeType cause)"/>
  </METHODS>
  <BACKGROUND backgroundColour="0">
    <ROUNDRECT pos="2.5 2.5 45 45" cornerSize="5" fill="solid: 61cbc6c7" hasStroke="1"
               stroke="3.0999999, mitered, butt" strokeColour="solid: a03aac3e"/>
    <TEXT pos="20 20 10 10" fill="solid: ff875b5b" hasStroke="0" text="1"
          fontname="Default monospaced font" fontsize="15" bold="1" italic="0"
          justification="36"/>
  </BACKGROUND>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
