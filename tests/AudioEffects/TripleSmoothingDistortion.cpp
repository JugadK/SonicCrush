#include "../../src/AudioEffects/TripleSmoothingDistortion.cpp"
#include <gtest/gtest.h>

TEST(TripleSmoothingDistortion, ProcessAudio) {
    TripleSmoothingDistortion tsd = TripleSmoothingDistortion();

    float sample = 0.0f;

    tsd.processAudio(sample);

    EXPECT_EQ(0.0f, sample);

    sample = 0.6f;

    tsd.processAudio(sample);

    std::cout << sample;

    std::cout << "fpsjakdfsd";

    EXPECT_EQ(floorf(sample * 100) / 100, 0.21f);
}