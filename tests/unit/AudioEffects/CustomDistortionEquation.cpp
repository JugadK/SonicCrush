#include "../../../src/AudioEffects/CustomDistortionEquation.hpp"
#include <gtest/gtest.h>

TEST(CustomDistortionEquation, EquationExponential) {
  CustomDistortionEquation cde = CustomDistortionEquation();

  cde.setDistortionEquation("x^2");

  EXPECT_TRUE(cde.getDistortionEquation() == "x^2");

  float sample = 0.0f;

  cde.processAudio(sample);

  EXPECT_TRUE(sample == 0.0f);

  sample = 0.4f;

  cde.processAudio(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 0.16f) << sample;
}

TEST(CustomDistortionEquation, EquationEuler) {
  CustomDistortionEquation cde = CustomDistortionEquation();

  cde.setDistortionEquation("2*e*x");

  EXPECT_TRUE(cde.getDistortionEquation() == "2*e*x");

  float sample = 0.0f;

  cde.processAudio(sample);

  EXPECT_EQ(sample, 0.0f);

  sample = 0.4f;

  cde.processAudio(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 2.17f) << sample;
}

TEST(CustomDistortionEquation, GetsEquationPi) {
  CustomDistortionEquation cde = CustomDistortionEquation();

  cde.setDistortionEquation("pi*x");

  EXPECT_TRUE(cde.getDistortionEquation() == "pi*x");

  float sample = 0.0f;

  cde.processAudio(sample);

  EXPECT_EQ(sample, 0.0f);

  sample = 0.4f;

  cde.processAudio(sample);

  EXPECT_EQ(floorf(sample * 100) / 100, 1.25f) << sample;
}