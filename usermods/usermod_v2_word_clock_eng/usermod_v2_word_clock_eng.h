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
    String output = "";

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
        output = "";
        // disable complete matrix at the bigging
        for (int x = 0; x < maskSizeLeds; x++) {
            maskLedsOn[x] = 0;
        }

        // display it is if activated
        if (displayItIs) {
            output += "IT IS";
        }

        if (minutes != 0) {
            uint8_t mintemp = minutes;
            if (minutes >= 30) {
                mintemp = 60 - mintemp;
            }
            switch (mintemp) {
                case 0:
                    output += " HALF";
                    break;
                case 1:
                    output += " ONE";
                    break;
                case 2:
                    output += " TWO";
                    break;
                case 3:
                    output += " THREE";
                    break;
                case 4:
                    output += " FOUR";
                    break;
                case 5:
                    output += " FIVE";
                    break;
                case 6:
                    output += " SIX";
                    break;
                case 7:
                    output += " SEVEN";
                    break;
                case 8:
                    output += " EIGHT";
                    break;
                case 9:
                    output += " NINE";
                    break;
                case 10:
                    output += " TEN";
                    break;
                case 11:
                    output += " ELEVEN";
                    break;
                case 12:
                    output += " TWELVE";
                    break;
                case 13:
                    output += " THIRTEEN";
                    break;
                case 14:
                    output += " FOURTEEN";
                    break;
                case 15:
                    output += " A QUARTER";
                    break;
                case 16:
                    output += " SIXTEEN";
                    break;
                case 17:
                    output += " SEVENTEEN";
                    break;
                case 18:
                    output += " EIGHTEEN";
                    break;
                case 19:
                    output += " NINETEEN";
                    break;
                case 20:
                    output += " TWENTY";
                    break;
                case 21:
                    output += " TWENTY ONE";
                    break;
                case 22:
                    output += " TWENTY TWO";
                    break;
                case 23:
                    output += " TWENTY THREE";
                    break;
                case 24:
                    output += " TWENTY FOUR";
                    break;
                case 25:
                    output += " TWENTY FIVE";
                    break;
                case 26:
                    output += " TWENTY SIX";
                    break;
                case 27:
                    output += " TWENTY SEVEN";
                    break;
                case 28:
                    output += " TWENTY EIGHT";
                    break;
                case 29:
                    output += " TWENTY NINE";
                    break;
                case 30:
                    output += " HALF";
                    break;
            }

            // add past or to
            if (minutes <= 30) {
                output += " PAST";
            } else {
                output += " TO";
                hour++;
            }
        }

        // add hour
        if (hour != 0) {
            switch (hour % 12) {
                case 0:
                    output += " TWELVE";
                    break;
                case 1:
                    output += " ONE";
                    break;
                case 2:
                    output += " TWO";
                    break;
                case 3:
                    output += " THREE";
                    break;
                case 4:
                    output += " FOUR";
                    break;
                case 5:
                    output += " FIVE";
                    break;
                case 6:
                    output += " SIX";
                    break;
                case 7:
                    output += " SEVEN";
                    break;
                case 8:
                    output += " EIGHT";
                    break;
                case 9:
                    output += " NINE";
                    break;
                case 10:
                    output += " TEN";
                    break;
                case 11:
                    output += " ELEVEN";
                    break;
            }
        } else {
            output += " MIDNIGHT";
        }

        if (output.indexOf("MIDNIGHT") == -1) {
            if (hour < 5) {
                output += " AT NIGHT";
            } else if (hour < 12) {
                output += " IN THE MORNING";
            } else if (hour < 17) {
                output += " IN THE AFTERNOON";
            } else if (hour < 21) {
                output += " IN THE EVENING";
            } else {
                output += " AT NIGHT";
            }
        }

        if (!displayItIs) {
            output = output.substring(1);
        }

        Serial.println(output);

        int lastLetterPos = 0;
        String processingString = output;
        int i = 0;
        while (true) {
            int pos = processingString.indexOf(" ");
            if (pos == -1) {
                pos = output.length();
            }
            String word = processingString.substring(0, pos);

            String lettersTmp = letters.substring(lastLetterPos);
            int letterPos = lettersTmp.indexOf(word);
            if (letterPos != -1) {
                for (int i = 0; i < word.length(); i++) {
                    maskLedsOn[i + letterPos + lastLetterPos] = 1;
                }
                lastLetterPos += letterPos;
            }

            if (pos >= output.length() - 2 || i > 10) {
                break;
            }

            processingString = processingString.substring(pos + 1);
            i++;
        }
    }

   public:
    void setup() {}

    void connected() {}

    void loop() {}

    void addToJsonInfo(JsonObject& root) {
        JsonObject user = root["u"];
        if (user.isNull()) user = root.createNestedObject("u");

        JsonArray infoArr = user.createNestedArray(F("WordClockUsermodEng"));

        if (usermodActive) infoArr.add(output);
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
        if (usermodActive == true && toki.getTimeSource() >= TOKI_TS_SEC) {
            if (minute(localTime) != lastMinute) {
                updateDisplay(hour(localTime), minute(localTime));
                lastMinute = minute(localTime);
            }

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