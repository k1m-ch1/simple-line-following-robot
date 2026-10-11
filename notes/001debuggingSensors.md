So there's something weird with the 5th sensor:

```
2981, 3004, 2826, 3102, 1152, 3047, 2954, 3085
```

I suspect that it might have something to do with wires so i'm just going to see whether the issue still persists when I reverse the wires.

If I were to reverse the wires, we essentially reverse the list, and should expect:

```
3085, 2954, 3047, 1152, 3102, 2826, 3004, 2981
```

If the 5th wire is causing it, then the same pattern should persist.

Result:

```
3108, 2980, 3086, 3063, 1168, 2910, 3089, 3270
```

So it has to be something with the wiring or something.

To combat this, I guess I could just calibrate it by specifying the minimum value and maximum value of the ADC output and the point interpolation factor $\alpha$ in which we transition from 0 to 1 for black line detection.
