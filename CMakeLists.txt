cmake_minimum_required(VERSION 3.15)


project(SonicCrush VERSION 0.0.1)


add_subdirectory(modules/JUCE)
add_subdirectory(modules/muparser)


juce_add_plugin(SonicCrush
    VERSION 0.0.1
    COMPANY_NAME BasedInc.
    PLUGIN_MANUFACTURER_CODE BASE
    PLUGIN_CODE basd
    ProductName "SonicCrush"
    # VERSION ...                               # Set this if the plugin version is different to the project version
    # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
    # ICON_SMALL ...
    # COMPANY_NAME ...                          # Specify the name of the plugin's author
    # IS_SYNTH TRUE/FALSE                       # Is this a synth or an effect?
   #  NEEDS_MIDI_INPUT TRUE              # Does the plugin need midi input?
   #  NEEDS_MIDI_OUTPUT TRUE             # Does the plugin need midi output?
   # IS_MIDI_EFFECT TRUE  
   # VST_NUM_MIDI_INS 1 
   # VST_NUM_MIDI_OUTS 1             # Is this plugin a MIDI effect?
    # EDITOR_WANTS_KEYBOARD_FOCUS TRUE/FALSE    # Does the editor need keyboard focus?
    COPY_PLUGIN_AFTER_BUILD TRUE       # Should the plugin be installed to a default location after building?
    MICROPHONE_PERMISSION_ENABLED TRUE  
    LV2_URI https://github.com/JugadK                    # A unique four-character plugin id with exactly one upper-case character
    FORMATS VST3 Standalone LV2                # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "SonicCrush")  # The name of the final executable, which can differ from the target name


target_sources(SonicCrush
    PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp)

target_compile_definitions(SonicCrush
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(SonicCrush
    PRIVATE
        muparser
        juce::juce_audio_utils
        juce::juce_opengl
        juce::juce_graphics
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)