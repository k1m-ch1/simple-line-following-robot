So we want our angle at which the ir sensor still detect the line to be around 45 to 60 degrees.

So if the distance from the furthest sensor to the middle is $x$, and the distance between the "axel line" and the sensor itself is $r$, then:

$$
\tan \theta = \frac{x}{r}
$$


So, if we actual heading in PID (not very accurate, but I think it's a good mapping):

$$
\theta = \arctan {\frac{x}{r}}
$$

In our case:

- $x \approx 27.5mm$

For $\theta = 60$:

$$
r = \frac{x}{\tan\theta} = \frac{27.5}{\tan 60} = 15.9mm
$$

For $\theta = 30$ meanwhile:

$$
r = 47.63mm
$$

