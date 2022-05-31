cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(SonicCrush VERSION 0.0.1)

find_package(CURL)
add_subdirectory(modules/JUCE)
add_subdirectory(modules/muparser)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



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
    MICROPHONE_PERMISSION_ENABLED TRUE                      # A unique four-character plugin id with exactly one upper-case character
    FORMATS VST3 Standalone                 # The formats to build. Other valid formats are: AAX Unity VST AU AUv3
    PRODUCT_NAME "SonicCrush")  # The name of the final executable, which can differ from the target name



target_compile_definitions(SonicCrush
    PUBLIC
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
        JUCE_VST3_CAN_REPLACE_VST2=0)

target_sources(SonicCrush
        PUBLIC
            src/AudioEffects/AudioEffect.hpp
            src/AudioEffects/CustomDistortionEquation.cpp
            src/AudioEffects/CustomDistortionEquation.hpp
            src/AudioEffects/TripleSmoothingDistortion.cpp
            src/AudioEffects/TripleSmoothingDistortion.hpp
            src/AudioEffects/SquareClipping.cpp
            src/AudioEffects/SawToothClipping.cpp
            src/EffectChain.cpp
            src/AudioEffectParameter.cpp
            src/PluginEditor.cpp
            src/PluginProcessor.cpp
            )

target_link_libraries(SonicCrush
        PRIVATE
            gtest_main
            muparser
            juce::juce_audio_utils
            juce::juce_opengl
            juce::juce_core
            juce::juce_graphics
        PUBLIC
            juce::juce_recommended_config_flags
            juce::juce_recommended_lto_flags
            juce::juce_recommended_warning_flags
            )

enable_testing()

add_executable(
          SonicCrush_Testing
          tests/unit/AudioEffects/TripleSmoothingDistortion.cpp
          tests/unit/AudioEffects/CustomDistortionEquation.cpp
          tests/unit/AudioEffects/SquareClipping.cpp
          tests/unit/AudioEffects/SawToothClipping.cpp
          tests/unit/AudioEffectParameter.cpp
          tests/integration/EffectChain.cpp
          tests/mocks/MockAudioProcessor.hpp
          src/AudioEffects/CustomDistortionEquation.cpp
          src/AudioEffects/TripleSmoothingDistortion.cpp
          src/AudioEffects/SquareClipping.cpp
          src/AudioEffects/SawToothClipping.cpp
          src/EffectChain.cpp
          src/PluginProcessor.cpp
          src/AudioEffectParameter.cpp
          src/PluginEditor.cpp
          modules/
        )


target_compile_definitions(SonicCrush_Testing
PUBLIC
    # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
    JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_plugin` call
    JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_plugin` call
    JUCE_VST3_CAN_REPLACE_VST2=0)


target_include_directories(SonicCrush_Testing PRIVATE ${GTK_INCLUDE_DIR})        
    
target_link_libraries(
          SonicCrush_Testing
          curl
          gtest_main
          gmock
          muparser
          juce::juce_opengl
          juce::juce_core
          juce::juce_audio_utils
        )

include(GoogleTest)
gtest_discover_tests(SonicCrush_Testing)
