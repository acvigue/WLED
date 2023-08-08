#pragma once

#include "wled.h"

/*
 * Usermods allow you to add own functionality to WLED more easily
 * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
 *
 * This usermod can be used to drive a wordclock with a 11x10 pixel matrix with WLED. There are also 4 additional dots for the minutes.
 * The visualisation is desribed in 4 mask with LED numbers (single dots for minutes, minutes, hours and "clock/Uhr").
 * There are 2 parameters to chnage the behaviour:
 *
 * active: enable/disable usermod
 * diplayItIs: enable/disable display of "It Is" on the clock.
 */

class WordClockUsermodEng : public Usermod {
   private:
    uint8_t lastMinute = 99;

    bool usermodActive = false;
    bool displayItIs = false;

// defines for mask sizes
#define maskSizeLeds 256

    String letters =
        "ITLISOTWENTYRONETWOETENMTHIRTEENFIVEMELEVENIFOURTHREEPNINETEENSUFOURTEENMIDNIGHTSIXTEENDEIGHTEENSEVENTEENOTWELVEHALFELQUARTEROTOPASTRONESATW"
        "OSIXTWELVETFOURAFIVESEVENMEIGHTENINETENTTHREECELEVENINOTHENAFTERNOONMORNINGSATENIGHTEVENINGCANDTCOLDCOOLETWARMURAHOT";

    // overall mask to define which LEDs are on
    int maskLedsOn[maskSizeLeds] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // update the display
    void updateDisplay(uint8_t hour, uint8_t minutes) {
        std::vector<std::string> output;
        // disable complete matrix at the bigging
        for (int x = 0; x < maskSizeLeds; x++) {
            maskLedsOn[x] = 0;
        }

        // display it is if activated
        if (displayItIs) {
            output.push_back("IT");
            output.push_back("IS");
        }

        if (minutes != 0) {
            uint8_t mintemp = minutes;
            if (minutes >= 30) {
                mintemp = 60 - mintemp;
            }
            switch (mintemp) {
                case 0:
                    output.push_back("HALF");
                    break;
                case 1:
                    output.push_back("ONE");
                    break;
                case 2:
                    output.push_back("TWO");
                    break;
                case 3:
                    output.push_back("THREE");
                    break;
                case 4:
                    output.push_back("FOUR");
                    break;
                case 5:
                    output.push_back("FIVE");
                    break;
                case 6:
                    output.push_back("SIX");
                    break;
                case 7:
                    output.push_back("SEVEN");
                    break;
                case 8:
                    output.push_back("EIGHT");
                    break;
                case 9:
                    output.push_back("NINE");
                    break;
                case 10:
                    output.push_back("TEN");
                    break;
                case 11:
                    output.push_back("ELEVEN");
                    break;
                case 12:
                    output.push_back("TWELVE");
                    break;
                case 13:
                    output.push_back("THIRTEEN");
                    break;
                case 14:
                    output.push_back("FOURTEEN");
                    break;
                case 15:
                    output.push_back("A");
                    output.push_back("QUARTER");
                    break;
                case 16:
                    output.push_back("SIXTEEN");
                    break;
                case 17:
                    output.push_back("SEVENTEEN");
                    break;
                case 18:
                    output.push_back("EIGHTEEN");
                    break;
                case 19:
                    output.push_back("NINETEEN");
                    break;
                case 20:
                    output.push_back("TWENTY");
                    break;
                case 21:
                    output.push_back("TWENTY");
                    output.push_back("ONE");
                    break;
                case 22:
                    output.push_back("TWENTY");
                    output.push_back("TWO");
                    break;
                case 23:
                    output.push_back("TWENTY");
                    output.push_back("THREE");
                    break;
                case 24:
                    output.push_back("TWENTY");
                    output.push_back("FOUR");
                    break;
                case 25:
                    output.push_back("TWENTY");
                    output.push_back("FIVE");
                    break;
                case 26:
                    output.push_back("TWENTY");
                    output.push_back("SIX");
                    break;
                case 27:
                    output.push_back("TWENTY");
                    output.push_back("SEVEN");
                    break;
                case 28:
                    output.push_back("TWENTY");
                    output.push_back("EIGHT");
                    break;
                case 29:
                    output.push_back("TWENTY");
                    output.push_back("NINE");
                    break;
                case 30:
                    output.push_back("HALF");
                    break;
            }

            // add past or to
            if (minutes <= 30) {
                output.push_back("PAST");
            } else {
                output.push_back("TO");
                hour++;
            }
        }

        // add hour
        if (hour != 0) {
            switch (hour % 12) {
                case 0:
                    output.push_back("TWELVE");
                    break;
                case 1:
                    output.push_back("ONE");
                    break;
                case 2:
                    output.push_back("TWO");
                    break;
                case 3:
                    output.push_back("THREE");
                    break;
                case 4:
                    output.push_back("FOUR");
                    break;
                case 5:
                    output.push_back("FIVE");
                    break;
                case 6:
                    output.push_back("SIX");
                    break;
                case 7:
                    output.push_back("SEVEN");
                    break;
                case 8:
                    output.push_back("EIGHT");
                    break;
                case 9:
                    output.push_back("NINE");
                    break;
                case 10:
                    output.push_back("TEN");
                    break;
                case 11:
                    output.push_back("ELEVEN");
                    break;
            }
        } else {
            output.push_back("MIDNIGHT");
        }

        if (hour != 0 || minute != 0) {
            if (hour < 5 || hour >= 21) {
                output.push_back("AT");
                output.push_back("NIGHT");
            } else if (hour < 12) {
                output.push_back("IN");
                output.push_back("THE");
                output.push_back("MORNING");
            } else if (hour < 17) {
                output.push_back("IN");
                output.push_back("THE");
                output.push_back("AFTERNOON");
            } else if (hour < 21) {
                output.push_back("IN");
                output.push_back("THE");
                output.push_back("EVENING");
            }
        }

        int lastLetterPos = 0;
        for (int i = 0; i < output.size(); i++) {
            std::string word = output[i];
            String lettersTmp = letters.substring(lastLetterPos);

            int wordStartPos = lettersTmp.indexOf(word.c_str());
            if (wordStartPos != -1) {
                for (int i = 0; i < word.length(); i++) {
                    maskLedsOn[i + wordStartPos + lastLetterPos] = 1;
                }
                lastLetterPos += wordStartPos;
            }
        }
    }

   public:
    void setup() {}

    void connected() {}

    void loop() {
        if (usermodActive == true && toki.getTimeSource() >= TOKI_TS_SEC) {
            if (minute(localTime) != lastMinute) {
                updateDisplay(hour(localTime), minute(localTime));
                lastMinute = minute(localTime);
            }
        }
    }

    void addToJsonState(JsonObject& root) {}

    void readFromJsonState(JsonObject& root) {}

    void addToConfig(JsonObject& root) {
        JsonObject top = root.createNestedObject(F("WordClockUsermodEng"));
        top[F("active")] = usermodActive;
        top[F("displayItIs")] = displayItIs;
    }

    bool readFromConfig(JsonObject& root) {
        JsonObject top = root[F("WordClockUsermodEng")];

        bool configComplete = !top.isNull();

        configComplete &= getJsonValue(top[F("active")], usermodActive);
        configComplete &= getJsonValue(top[F("displayItIs")], displayItIs);

        return configComplete;
    }

    /*
     * handleOverlayDraw() is called just before every show() (LED strip update frame) after effects have set the colors.
     * Use this to blank out some LEDs or set them to a different color regardless of the set effect mode.
     * Commonly used for custom clocks (Cronixie, 7 segment)
     */
    void handleOverlayDraw() {
        if (usermodActive && toki.getTimeSource() >= TOKI_TS_SEC) {
            for (int y = 0; y < 16; y++) {
                for (int x = 0; x < 16; x++) {
                    if (maskLedsOn[(y * 16) + x] == 0) {
                        strip.setPixelColorXY(x, y, RGBW32(0, 0, 0, 0));
                    }
                }
            }
        }
    }

    uint16_t getId() { return USERMOD_ID_WORDCLOCK_ENG; }
};