#include <DirectIO.h>

int mic12DiffCounter = 0;
int mic34DiffCounter = 0;

Input<2> mic1;
Input<3> mic2;
Input<4> mic3;
Input<5> mic4;

void setup()
{
    Serial.begin(115200);
    Serial.println("start.");
}

void loop()
{
    boolean micFlag1 = false;
    boolean micFlag2 = false;
    boolean micFlag3 = false;
    boolean micFlag4 = false;

    while (!micFlag1 || !micFlag2 || !micFlag3 || !micFlag4)
    {
        // update micFlag values.
        // only update the ones which aren't high yet for faster computation speed.
        if (!micFlag1)
            micFlag1 = mic1;
        if (!micFlag2)
            micFlag2 = mic2;
        if (!micFlag3)
            micFlag3 = mic3;
        if (!micFlag4)
            micFlag4 = mic4;

        // track diff between mic 1 and 2
        if (micFlag1 && !micFlag2)
        {
            mic12DiffCounter--;
        }
        if (micFlag2 && !micFlag1)
        {
            mic12DiffCounter++;
        }

        // track diff between mic 2 and 3
        if (micFlag3 && !micFlag4)
        {
            mic34DiffCounter--;
        }
        if (micFlag4 && !micFlag3)
        {
            mic34DiffCounter++;
        }
    }

    Serial.print("mic12 diff: ");
    Serial.println(mic12DiffCounter);
    Serial.print("mic34 diff: ");
    Serial.println(mic34DiffCounter);

    // wait until all mics are low again.
    while (micFlag1 || micFlag2 || micFlag3 || micFlag4)
    {
        micFlag1 = mic1;
        micFlag2 = mic2;
        micFlag3 = mic3;
        micFlag4 = mic4;
    }

    mic12DiffCounter = 0;
    mic34DiffCounter = 0;
}
